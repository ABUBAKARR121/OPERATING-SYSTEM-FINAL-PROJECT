#include "console.h"
#include "../../core/system.h"
static uint8_t cf=VGA_WHITE,cb=VGA_BLACK;
void console_init(void){vga_init();cf=VGA_WHITE;cb=VGA_BLACK;console_clear();}
void console_clear(void){vga_clear(cf,cb);}
void console_write(const char* s){vga_write(s,cf,cb);}
void console_write_int(int n){char b[32];int i=0,neg=0;if(n==0){console_write("0");return;}if(n<0){neg=1;n=-n;}while(n){b[i++]='0'+n%10;n/=10;}if(neg)b[i++]='-';for(int j=i-1;j>=0;j--)vga_putchar(b[j],cf,cb);}
void console_write_colored(const char* s,uint8_t c){vga_write_color(s,c);}
void console_newline(void){vga_putchar('\n',cf,cb);}
