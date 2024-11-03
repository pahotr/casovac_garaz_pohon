#ifndef _BASE
#define _BASE

#define LOCAL static

struct event_bits1 	     // bit structure for housekeeping flags
{
	unsigned start : 1;	
	unsigned odpocitavani : 1;
	unsigned sleep:1;
	unsigned odpocet_rele:1;
	unsigned ukonci:1;
	unsigned semafor:1;
} flag1; 		

int time_=0;
int time_odpocet_rele = 0;


#define PortBit(port,bit) ((unsigned)&(port)*8+(bit))
LOCAL bit RELE_SIT @ PortBit(PORTA, 1); 
LOCAL bit SGN_SMER_OPEN @ PortBit(PORTB, 3); 
LOCAL bit SGN_SMER_CLOSE @ PortBit(PORTB, 2); 
LOCAL bit SGN_SMER_OUT @ PortBit(PORTB, 0); 
LOCAL bit RELE_POHYB @ PortBit(PORTA, 3); 
LOCAL bit START @ PortBit(PORTB, 1); 
LOCAL bit SEMAFOR @ PortBit(PORTB, 4);

#define TIME 3500
#define TIME_ODPOCET_RELE 500

#endif
