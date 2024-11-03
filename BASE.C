#include <htc.h>
#include "base.h"
#include "Delay.h"

/*
 *      Ovladani pohonu vrat garaze (uspora enerigie pripojenim k siti v okamziku pohybu)  - PIC16F628A
 * 		Casovac (zapnuti zdroje pohonu) je mozne aktivovat tlacitkem SEMAFOR na uzlrazvukovem semaforu
 */

__CONFIG(WDTDIS &INTIO &PWRTDIS &BORDIS &LVPDIS &MCLRDIS &INTIO);

typedef unsigned char uchar;

//-------------------------------------------------------------------------

void Init(void) {
	PORTA = 0b00000000; // Inicializace PORTA
	CMCON = 0x07; // Vypnuti comparatoru

	TRISA = 0b00000000;
	asm("NOP");
	PORTA = 0b11111101;
	PORTB = 0b00000000;
	TRISB = 0b00011110;

	OPTION = 0b10010110; // set Timer0 for 1:256, internal clock
	TMR0 = 0x00; // set Timer0 for initial state
	T0IF = 0; // reset Timer0 overflow flag
	T0IE = 0; // disable Timer0 Overflow interrupt

	PCON = 0b00001000; //Int Osc 4MHz
	VRCON = 0x00;
	T1CON = 0x00;

	INTCON = 0b10100000;
}

//-------------------------------------------------------------------------

void scan_START(void) /* Osetreni zakmitu tlacitka MS*/
{
	char x;
	char t;
	t = 250;
	flag1.start = 1;
	do {
		x = START;
		if (x == 0) {
			t--;
		} else {
			flag1.start = 0;
			break;
		}
	} while (t > 0);
}

void scan_SEMAFOR(void) /* Osetreni zakmitu tlacitka SEMAFOR*/
{
	char x;
	char t;
	t = 250;
	flag1.semafor = 1;
	do {
		x = SEMAFOR;
		if (x == 0) {
			t--;
		} else {
			flag1.semafor = 0;
			break;
		}
	} while (t > 0);
}

void NastavTimerVypnuti(void) {
	RELE_SIT = 1;
	time_ = TIME;
	flag1.odpocet_rele = 1;
	time_odpocet_rele = TIME_ODPOCET_RELE;
	flag1.ukonci = 0;
}

void NastavFlagy(void) {
	flag1.odpocet_rele = 0;
	flag1.ukonci = 0;
	flag1.odpocitavani = 1;
}

void main(void) {
	flag1.sleep = 1;
	flag1.start = 0;
	flag1.semafor = 0;
	flag1.odpocitavani = 0;
	flag1.odpocet_rele = 0;

	Init();

	Delay_100mS(5);

	for (;;) {
		//Semafor
		if (!SEMAFOR) {
			flag1.semafor = 1;
			scan_SEMAFOR();
			if (flag1.semafor) {
				NastavTimerVypnuti();
				NastavFlagy();
			}
			while (!SEMAFOR)
				;
		}

		if (!START) {
			flag1.start = 1;
			scan_START();
			if (flag1.start) {
				flag1.sleep = 0;
				if (!flag1.odpocitavani) {
					NastavTimerVypnuti();

					do {
						RELE_POHYB = 0;
						Delay_100mS(2);
						RELE_POHYB = 1;
						Delay_100mS(2);
					} while (SGN_SMER_OPEN && SGN_SMER_CLOSE && !flag1.ukonci);
				} else {
					RELE_POHYB = 0;
					Delay_100mS(5);
					RELE_POHYB = 1;
				}
				NastavFlagy();

				while (!START)
					;
			}
		}

		SGN_SMER_OUT = !SGN_SMER_OPEN;
	}
}

//-------------------------------------------------------------------------


interrupt timer(void) {
	GIE = 0;
	if (T0IE && T0IF) {
		if (flag1.odpocitavani) {
			time_--;
			if (time_ == 0) {
				RELE_SIT = 0;
				RELE_POHYB = 1;
				flag1.sleep = 1;
				flag1.odpocitavani = 0;
				time_ = TIME;
			}
		}

		if (flag1.odpocet_rele) {
			time_odpocet_rele--;
			if (time_odpocet_rele == 0) {
				flag1.odpocet_rele = 0;
				flag1.ukonci = 1;
			}
		}
		T0IF = 0;
	}
	GIE = 1;
}
