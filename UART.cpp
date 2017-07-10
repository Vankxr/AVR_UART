/*
 * UART.cpp
 *
 * Created: 25/05/2017 16:45:37
 * Author: joaob
 */ 

#include "UART.h"

volatile uint8_t UART0_RX_FIFO[UART_FIFO_SIZE];
volatile uint16_t UART0_RX_FIFO_HEAD = 0;
volatile uint16_t UART0_RX_FIFO_TAIL = 0;

ISR(USART0_RX_vect) {
	UART0_RX_FIFO[UART0_RX_FIFO_HEAD] = UDR0;
	
	UART0_RX_FIFO_HEAD++;
	if(UART0_RX_FIFO_HEAD > UART_FIFO_SIZE - 1) UART0_RX_FIFO_HEAD = 0;
}

void UART0_Init(uint32_t baud, uint8_t double_speed) {
	UBRR0 = (uint16_t)(F_CPU / ((double_speed ? 8 : 16) * baud) - 1);
	
	if(double_speed) {
		UCSR0A = (1 << U2X0);
	}
	
	UCSR0B = (1 << RXCIE0) | (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
uint8_t UART0_Read_Byte() {
	uint8_t b = UART0_RX_FIFO[UART0_RX_FIFO_TAIL];
	
	UART0_RX_FIFO_TAIL++;
	if(UART0_RX_FIFO_TAIL > UART_FIFO_SIZE - 1) UART0_RX_FIFO_TAIL = 0;
	
	return b;
}
void UART0_Flush() {
	UART0_RX_FIFO_TAIL = UART0_RX_FIFO_HEAD;
}
void UART0_Read(uint8_t* dst, uint8_t count) {
	for(uint8_t i = 0; i < count; i++) {
		*(dst + i) = UART0_Read_Byte();
	}
}
void UART0_Write_Byte(uint8_t byte) {
	while(!(UCSR0A & (1 << UDRE0)));
	
	UDR0 = byte;
}
void UART0_Write(uint8_t* src, uint8_t count) {
	for(uint8_t i = 0; i < count; i++) {
		UART0_Write_Byte(*(src + i));
	}
}


volatile uint8_t UART1_RX_FIFO[UART_FIFO_SIZE];
volatile uint16_t UART1_RX_FIFO_HEAD = 0;
volatile uint16_t UART1_RX_FIFO_TAIL = 0;

ISR(USART1_RX_vect) {
	UART1_RX_FIFO[UART1_RX_FIFO_HEAD] = UDR1;
	
	UART1_RX_FIFO_HEAD++;
	if(UART1_RX_FIFO_HEAD > UART_FIFO_SIZE - 1) UART1_RX_FIFO_HEAD = 0;
}

void UART1_Init(uint32_t baud, uint8_t double_speed) {
	UBRR1 = (uint16_t)(F_CPU / ((double_speed ? 8 : 16) * baud) - 1);
	
	if(double_speed) {
		UCSR1A = (1 << U2X1);
	}
	
	UCSR1B = (1 << RXCIE1) | (1 << TXEN1) | (1 << RXEN1);
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}
uint8_t UART1_Read_Byte() {
	uint8_t b = UART1_RX_FIFO[UART1_RX_FIFO_TAIL];
	
	UART1_RX_FIFO_TAIL++;
	if(UART1_RX_FIFO_TAIL > UART_FIFO_SIZE - 1) UART1_RX_FIFO_TAIL = 0;
	
	return b;
}
void UART1_Flush() {
	UART1_RX_FIFO_TAIL = UART1_RX_FIFO_HEAD;
}
void UART1_Read(uint8_t* dst, uint8_t count) {
	for(uint8_t i = 0; i < count; i++) {
		*(dst + i) = UART1_Read_Byte();
	}
}
void UART1_Write_Byte(uint8_t byte) {
	while(!(UCSR1A & (1 << UDRE1)));
	
	UDR1 = byte;
}
void UART1_Write(uint8_t* src, uint8_t count) {
	for(uint8_t i = 0; i < count; i++) {
		UART1_Write_Byte(*(src + i));
	}
}