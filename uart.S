/*
;-----------------------------------------------------------------------------;
; Software implemented UART
;
; Send/Receive r24 to host via an ISP cable.
;
; NOTE: MOSI and MISO are not inverted signals.
;       MISO pin must be configured as output before transmiting.
;       Don't enable any interrupt during these routines are being executed.
;
;            3.58M  4MHz  4.19M  6MHz  6.144  8MHz  10MHz  12MHz  12.288
; 115.2kbps     -     -      -     -     16    21     27     33     34
;  57.6kbps    19    21     22    33     34    44     56     67     69
;  38.4kbps    29    33     34    50     52    67(68) 85    102    105
;  19.2kbps    60    67     71   102    105   138    173    208    211
;   9.6kbps   122   138    144   208    211     -      -      -      -
*/

#define	BPS	44	//See above.
/* FOR MEGA169 */
/*
#define	MOSI	2	//Bit position of MOSI and MISO on the I/O register
#define	MISO	3	//
#define PORTB	0x0005
#define PINB	0x0003
*/
	

/* FOR MEGA8 */
#define MOSI 3
#define MISO 4
#define PORTB 0x0018
#define PINB 0x0016	
	
    .global xmit,receive

    .func xmit
xmit:				//Transmit r24. r17 and r18 will be broken. (14 words)
	push	r17
	push	r18
	com	r24		//
	sec			//Start bit
	ldi	r18,10		//bit count
l3:
	ldi	r17,BPS-1	//Wait for full bit time
l0:
	dec	r17		//
	brne	l0		//
	brcs	l1		//MISO = bit for send
	sbi	PORTB,MISO	//
l1:
	brcc	l2		//
	cbi	PORTB,MISO	//
l2:
	lsr	r24		//next bit
	dec	r18		//All sent ?
	brne	l3		//no, coutinue

l5:
	dec	r18		//wait
	brne	l5		//

	pop	r18
	pop	r17
	ret
.endfunc


    .func receive
receive: 			//Receive into r24. r17 will be broken. (16 words)
	push	r17
	ldi	r24,0x80	//Shift register for receive
l10:
	sbis	PINB,MOSI	//Wait for fall edge of MOSI
	rjmp	l10		//
l11:
	sbic	PINB,MOSI	//
	rjmp	l11		//
	ldi	r17,BPS/2	//Wait for half bit time
l12:
	dec	r17		//
	brne	l12		//
l14:
	ldi	r17,BPS		//Wait for full bit time
l13:
	dec	r17		//
	brne	l13		//
	lsr	r24		//Next bit
	sbic	PINB,MOSI	//Read MOSI into r24.7
	ori	r24,0x80	//
	brcc	l14		//All bits received?  no, continue
	pop	r17
	ret			//                   yes, exit
.endfunc


