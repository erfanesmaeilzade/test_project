/*
 * rgb.c
 *
 * Created: 29/03/2020 07:53:34 �.�
 * Author: MKH
 */

#include <io.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void main(void)
{
DDRD.2=1;
DDRD.3=1;
DDRD.4=1;
PORTD.2=0;
PORTD.3=1;
PORTD.4=1;
while (1)
    {
        PORTD.2=1;
        PORTD.3=1;
        PORTD.4=0;    
    }
}
