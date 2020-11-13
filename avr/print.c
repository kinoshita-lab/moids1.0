#include <stdarg.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

void xmit(u8);


/*void _udeci(u16 u){
	u16 div=10000;
	u8  flg=0;
	for(;;){
		if(u/div){
			xmit('0'+(u/div));
			flg=1;
			u-=(u/div)*div;
		}
		else if(flg || (div==1)){
			xmit('0');
		}
		div=div/10;
		if(div==0) break;
	}
}
*/

const static s8 hexchar[16]={
'0','1','2','3','4','5','6','7',
'8','9','A','B','C','D','E','F'
};

void _hex(u16 u){
	u8 i;
	i=u>>8;
	xmit(hexchar[(i>>4)&15]);
	xmit(hexchar[i&15]);
	i=u;
	xmit(hexchar[(i>>4)&15]);
	xmit(hexchar[i&15]);
}

//	%d:•„†‚ ‚è‚P‚Oi”
//	%u:•„†‚È‚µ‚P‚Oi”
//	%x:‚P‚Ui”
//	%s:•¶š—ñ
//	%c:•¶š
//	\n:‰üs

void print(char *fmt, ... ){
	va_list args;
	u8  i;
	s16 d;
	u16 u;
	u8  *ss;

	va_start(args,fmt);
	for(;;){
		if(*fmt=='%'){
			switch(fmt[1]){

/*			case 'd':		//	%d:•„†‚ ‚è‚P‚Oi”
				fmt+=2;
				d=va_arg(args,int);
				if(d<0){
					xmit('-');
					u=-d;
				}
				else{
					u=d;
				}
				_udeci(u);
				break;
			case 'u':		//	%u:•„†‚È‚µ‚P‚Oi”
				fmt+=2;
				u=va_arg(args,int);
				_udeci(u);
				break;
*/
			case 'x':		//	%x:‚P‚Ui”
				fmt+=2;
				u=va_arg(args,int);
				_hex(u);
				break;
			case 's':		//	%s:•¶š—ñ
				fmt+=2;
				ss=va_arg(args,s8 *);
				for(i=0;;i++){
					if(ss[i]==0) break;
					xmit(ss[i]);
				}
				break;
			case 'c':		//	%c:•¶š
				fmt+=2;
				d=va_arg(args,int);
				xmit(d);
				break;
			default:
				xmit(*fmt);
				fmt++;
				break;
			}
		}
		else{
			if(*fmt==0) break;
			xmit(*fmt);
			fmt++;
		}
	}
	va_end(args);
}
