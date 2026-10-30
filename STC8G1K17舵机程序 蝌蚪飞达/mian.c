/***************   STC8G1K17A 50Hz SG90舵机控制  ******************/
#include <STC8G.H>
#include <intrins.h>
#include <string.h>

/*==================== IO 定义 ====================*/
sbit K1        = P3 ^ 2;   // 按键输入
sbit PWM_OUT   = P3 ^ 3;   // 舵机 PWM 输出
sbit SERVO_LED = P5 ^ 4;   // 舵机动作指示灯
// UART1 固定引脚: RXD=P3.0, TXD=P3.1

/*==================== 全局变量 ====================*/
unsigned int  count = 0;          // 50us 中断计数
unsigned char servo_cnt = 10;     // 舵机高电平计数(10=0°,30=90°,50=180°)
bit           servo_running = 0;  // 舵机动作标志

/*==================== UART 接收缓冲 ====================*/
#define UART_BUF_SIZE 16
char          uart_buf[UART_BUF_SIZE];
unsigned char uart_idx = 0;
bit           uart_cmd_ready = 0;

/*==================== 延时函数 @11.0592MHz ====================*/
void Delay200ms(void)
{
	unsigned char data i, j, k;
	i = 12; j = 57; k = 122;
	do { do { while (--k); } while (--j); } while (--i);
}

void delay_20ms(void)
{
	unsigned char i, j;
	i = 216; j = 37;
	do { while (--j); } while (--i);
}

void delay_500ms(void)
{
	unsigned char data i, j, k;
	i = 29; j = 14; k = 54;
	do { do { while (--k); } while (--j); } while (--i);
}

/*==================== 舵机角度设置 ====================
 * 舵机 PWM 参数: Timer0 每 50us 中断一次
 * 周期 400 * 50us = 20ms (50Hz)
 * 0°  = 0.5ms = 10 次中断
 * 90° = 1.5ms = 30 次中断
 * 180°= 2.5ms = 50 次中断
 * servo_cnt 范围 10~50
 */
void Servo_SetAngle(unsigned char angle)
{
	if (angle > 180) angle = 180;
	servo_cnt = 10 + (unsigned int)angle * 40 / 180;
}

/*==================== 推料动作(180°→0°) ====================*/
void Servo_Push(void)
{
	servo_running = 1;
	SERVO_LED = 1;              // 动作开始, LED 常亮
	Delay200ms();
	Servo_SetAngle(180);        // 转到 180° 推料
	delay_500ms();
	Servo_SetAngle(0);          // 回到 0° 复位
	delay_20ms();
	Delay200ms();
	servo_running = 0;
	SERVO_LED = 0;              // 动作结束, LED 熄灭
}

/*==================== Timer0 初始化(50us 中断) ====================*/
void Timer0_Init(void)
{
	AUXR |= 0x80;        // T0 1T 模式
	TMOD = (TMOD & 0xF0) | 0x01;  // T0 模式 1(16 位), 与 0xFDD7 重装值匹配
	TL0  = 0xD7;
	TH0  = 0xFD;         // 重装值: 65536 - 553 = 0xFDD7 (11.0592MHz, 50us)
	TF0  = 0;
	TR0  = 1;
	ET0  = 1;
}

/*==================== Timer0 中断: 生成舵机 PWM ====================*/
void Timer0_ISR(void) interrupt 1
{
	TL0 = 0xD7;
	TH0 = 0xFD;          // 重装 50us 初值
	count++;
	PWM_OUT = (count <= servo_cnt) ? 1 : 0;
	if (count >= 400) count = 0;   // 20ms 周期清零
}

/*==================== UART1 初始化 9600bps @11.0592MHz ====================*/
void UART1_Init(void)
{
	SCON  = 0x50;         // 8 位 UART, 可变波特率, 允许接收
	AUXR |= 0x40;         // Timer1 1T 模式
	AUXR &= ~0x01;        // UART1 选择 Timer1 为波特率发生器
	TMOD &= 0x0F;         // 清除 Timer1 模式位
	TMOD |= 0x20;         // Timer1 模式 2(8 位自动重装)
	TH1 = TL1 = 0xDC;     // 9600bps: 256 - 11059200/(32*9600) = 220 = 0xDC
	TR1 = 1;              // 启动 Timer1
	ES  = 1;              // 允许串口中断
}

/*==================== UART1 发送一个字节 ====================*/
void UART1_SendByte(unsigned char dat)
{
	SBUF = dat;
	while (!TI);
	TI = 0;
}

/*==================== UART1 发送字符串 ====================*/
void UART1_SendString(char *s)
{
	while (*s) UART1_SendByte(*s++);
}

/*==================== UART1 中断接收(行缓冲) ====================*/
void UART1_ISR(void) interrupt 4
{
	unsigned char dat;
	if (RI) {
		RI = 0;
		dat = SBUF;
		if (dat == '\n' || dat == '\r') {
			if (uart_idx > 0) {
				uart_buf[uart_idx] = '\0';
				uart_cmd_ready = 1;
			}
			uart_idx = 0;
		} else if (uart_idx < UART_BUF_SIZE - 1) {
			uart_buf[uart_idx++] = dat;
		}
	}
}

/*==================== 串口命令解析 ====================
 * 支持命令(以 \n 或 \r 结尾):
 *   P / PUSH  -> 执行推料动作(180°→0°)
 *   0         -> 转到 0°
 *   90        -> 转到 90°
 *   180       -> 转到 180°
 *   0~180 数字 -> 转到指定角度
 *   GET       -> 查询当前角度
 */
void UART_ProcessCommand(void)
{
	unsigned int  val;
	unsigned char i;
	bit           valid;

	if (!uart_cmd_ready) return;
	uart_cmd_ready = 0;

	if (strcmp(uart_buf, "P") == 0 || strcmp(uart_buf, "PUSH") == 0) {
		Servo_Push();
		UART1_SendString("OK:PUSH\r\n");
	} else if (strcmp(uart_buf, "GET") == 0) {
		unsigned char angle = (unsigned char)((unsigned int)(servo_cnt - 10) * 180 / 40);
		UART1_SendString("ANGLE:");
		UART1_SendByte('0' + angle / 100);
		UART1_SendByte('0' + (angle / 10) % 10);
		UART1_SendByte('0' + angle % 10);
		UART1_SendString("\r\n");
	} else {
		/* 尝试解析为数字角度 */
		val = 0; i = 0; valid = 1;
		while (uart_buf[i] != '\0') {
			if (uart_buf[i] >= '0' && uart_buf[i] <= '9') {
				val = val * 10 + (uart_buf[i] - '0');
			} else {
				valid = 0;
				break;
			}
			i++;
		}
		if (valid && i > 0 && val <= 180) {
			Servo_SetAngle((unsigned char)val);
			UART1_SendString("OK\r\n");
		} else {
			UART1_SendString("ERR\r\n");
		}
	}
}

/*==================== 按键扫描 ====================*/
void Key_Scan(void)
{
	if (K1 == 0) {
		delay_20ms();            // 消抖
		if (K1 == 0) {
			while (K1 == 0);     // 等待松开
			Servo_Push();        // 执行推料
		}
	}
}

/*==================== 主函数 ====================*/
void main(void)
{
	/* P3.0 RXD(准双向), P3.1 TXD(推挽), P3.2 按键(准双向), P3.3 PWM(推挽) */
	P3M0 = (P3M0 & ~0x0D) | 0x0A;
	P3M1 &= ~0x0F;
	/* P5.4 LED 推挽输出: M0=1, M1=0 */
	P5M0 |= 0x10;
	P5M1 &= ~0x10;

	SERVO_LED = 0;        // 上电 LED 熄灭
	servo_cnt = 10;       // 上电舵机 0°

	Timer0_Init();
	UART1_Init();
	EA = 1;               // 开启总中断

	UART1_SendString("STC8G1K17 Servo Feeder Ready\r\n");

	while (1) {
		Key_Scan();
		UART_ProcessCommand();
	}
}
