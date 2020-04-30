avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o boutton.o boutton.c
avr-gcc -mmcu=atmega328p boutton.o -o boutton
avr-objcopy -O ihex -R .eeprom boutton boutton.hex
avrdude -F -V -c arduino -p ATMEGA328P -P COM10 -b 115200 -U flash:w:boutton.hex
pause