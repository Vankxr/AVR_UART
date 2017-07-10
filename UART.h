/*
 * UART.h
 *
 * Created: 25/05/2017 16:45:37
 * Author : joaob
 */ 


#ifndef UART_H_
#define UART_H_

#define UART_FIFO_SIZE 64

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern volatile uint8_t UART0_RX_FIFO[UART_FIFO_SIZE];
extern volatile uint16_t UART0_RX_FIFO_HEAD;
extern volatile uint16_t UART0_RX_FIFO_TAIL;

extern void UART0_Init(uint32_t baud, uint8_t double_speed);
extern uint8_t UART0_Read_Byte();
extern inline uint16_t UART0_Available() {
	return (UART_FIFO_SIZE + UART0_RX_FIFO_HEAD - UART0_RX_FIFO_TAIL) % UART_FIFO_SIZE;
}
extern void UART0_Flush();
extern void UART0_Read(uint8_t* dst, uint8_t count);
extern void UART0_Write_Byte(uint8_t byte);
extern void UART0_Write(uint8_t* src, uint8_t count);


extern volatile uint8_t UART1_RX_FIFO[UART_FIFO_SIZE];
extern volatile uint16_t UART1_RX_FIFO_HEAD;
extern volatile uint16_t UART1_RX_FIFO_TAIL;

extern void UART1_Init(uint32_t baud, uint8_t double_speed);
extern uint8_t UART1_Read_Byte();
extern inline uint16_t UART1_Available() {
	return (UART_FIFO_SIZE + UART1_RX_FIFO_HEAD - UART1_RX_FIFO_TAIL) % UART_FIFO_SIZE;
}
extern void UART1_Flush();
extern void UART1_Read(uint8_t* dst, uint8_t count);
extern void UART1_Write_Byte(uint8_t byte);
extern void UART1_Write(uint8_t* src, uint8_t count);

#endif /* UART_H_ */