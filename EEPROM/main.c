#include <io.h>

// I2C Bus functions
#include <i2c.h>

// Alphanumeric LCD functions
#include <alcd.h>

#include <delay.h>

// Declare your global variables here

#define DEVICE_ADDR            0xA0 

void EEPROM_writeByte(unsigned char devAddr, unsigned char memAddr, unsigned char data);
unsigned char EEPROM_readByte(unsigned char devAddr, unsigned char memAddr); 

void EEPROM_writePage(unsigned char devAddr, unsigned char memAddr, unsigned char* data, unsigned char len);
void EEPROM_readPage(unsigned char devAddr, unsigned char memAddr, unsigned char* data, unsigned char len);

#include <stdio.h>


void main(void)
{
// Declare your local variables here
unsigned char data;
char tempStr[6] = "Hello"; 
char str[16];

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Bit-Banged I2C Bus initialization
// I2C Port: PORTD
// I2C SDA bit: 1
// I2C SCL bit: 0
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

/*data = EEPROM_readByte(DEVICE_ADDR, 20);
sprintf(str, "%u", data);
EEPROM_writeByte(DEVICE_ADDR, 20, ++data);*/

EEPROM_writePage(DEVICE_ADDR, 25, tempStr, sizeof(tempStr));
EEPROM_readPage(DEVICE_ADDR, 25, str, sizeof(tempStr));

lcd_clear();
lcd_puts(str);


while (1)
      {
      // Place your code here

      }
}

void EEPROM_writeByte(unsigned char devAddr, unsigned char memAddr, unsigned char data){
    i2c_start();
    i2c_write(devAddr);
    i2c_write(memAddr);
    i2c_write(data);
    i2c_stop(); 
    delay_ms(5);
}
unsigned char EEPROM_readByte(unsigned char devAddr, unsigned char memAddr){
    unsigned char temp;
    i2c_start();
    i2c_write(devAddr);
    i2c_write(memAddr);
    i2c_start();
    i2c_write(devAddr | 1);
    temp = i2c_read(0);
    i2c_stop();
    return temp;
}

void EEPROM_writePage(unsigned char devAddr, unsigned char memAddr, unsigned char* data, unsigned char len){
    i2c_start();
    i2c_write(devAddr);
    i2c_write(memAddr);
    while (len--) {
        i2c_write(*data++);
    }
    i2c_stop();  
    delay_ms(5);
}
void EEPROM_readPage(unsigned char devAddr, unsigned char memAddr, unsigned char* data, unsigned char len){
    i2c_start();
    i2c_write(devAddr);
    i2c_write(memAddr);
    i2c_start();    
    i2c_write(devAddr | 1);
    while (--len) {
        *data++ = i2c_read(1);
    }   
    *data = i2c_read(0);
    i2c_stop();
}
