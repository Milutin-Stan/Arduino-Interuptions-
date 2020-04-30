#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#define BLINK_DELAY_MS 500

void USART_Transmit(unsigned char data);
void USART_Init(unsigned int ubrr);

static void led_on(void)
{
    PORTB |= (1<<PORTB5);
}

static void led_off(void)
{
    PORTB &= ~(1<<PORTB5);
}

ISR(PCINT0_vect) /* pin change interrupt service routine */
{
    if((PCIFR&(1<<PCIF0)==1)&(PCMSK0 |= (1<<PCINT0)))
    {
        for (int i=1; i<10;i++)
            {
                led_on();
                _delay_ms(BLINK_DELAY_MS);
                led_off();
                _delay_ms(BLINK_DELAY_MS);
                USART_Transmit('z');
            }
    }
    cli();
}


int main (void)
{

    USART_Init(MYUBRR);
 /* set pin 5 of PORTB for output*/
 DDRB |= (1<<5) ;
 DDRB &= ~(1<<0); // Configuring PB0 as Input
 
 PORTB |= (1<<PORTB0); // enable pull-up 
 PCICR |= (1<<PCIE0); // enable Pin Change 0 interrupt 
 PCMSK0 |= (1<<PCINT0); // PORTB4 is also PCINT4 */
 sei(); /* enable interrupts globally */

 while(1) { 
  

  }
}

void USART_Init(unsigned int ubrr)
{
/*Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
//Enable receiver and transmitter 
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
/* Wait for empty transmit buffer */
while (!(UCSR0A & (1<<UDRE0)))
;
/* Put data into buffer, sends the data */
UDR0 = data;
}