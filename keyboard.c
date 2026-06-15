#include "keyboard.h"
#include "../display/vga.h"
#include "../../core/system.h"
static int shift=0,caps=0;
static const char ascii[128]={0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' '};
static const char shift_ascii[128]={0,0,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,'A','S','D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' '};
void keyboard_init(void){shift=0;caps=0;}
static char get_ascii(uint8_t sc){if(sc&0x80){uint8_t r=sc&0x7F;if(r==0x2A||r==0x36)shift=0;return 0;}if(sc==0x2A||sc==0x36){shift=1;return 0;}if(sc==0x3A){caps=!caps;return 0;}return(shift^caps)?shift_ascii[sc]:ascii[sc];}
char keyboard_getchar(void){while(1){if(inb(0x64)&0x01){char c=get_ascii(inb(0x60));if(c)return c;}}}
void keyboard_read_line(char* buf,int max){int i=0;while(i<max-1){char c=keyboard_getchar();if(c=='\n'){vga_putchar('\n',VGA_WHITE,VGA_BLACK);break;}if(c=='\b'){if(i>0){i--;vga_putchar('\b',VGA_WHITE,VGA_BLACK);}continue;}buf[i++]=c;vga_putchar(c,VGA_WHITE,VGA_BLACK);}buf[i]='\0';}
