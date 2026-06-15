#include "vga.h"
#include "../../core/system.h"
static uint16_t* const vga_buffer = (uint16_t*)VGA_ADDRESS;
static uint8_t vga_x = 0, vga_y = 0, vga_fg = VGA_WHITE, vga_bg = VGA_BLACK;
uint16_t vga_entry(unsigned char c, uint8_t fg, uint8_t bg) { return (uint16_t)c | (uint16_t)((bg << 4) | (fg & 0x0F)) << 8; }
void vga_init(void) { vga_x=0; vga_y=0; vga_fg=VGA_LIGHT_GREY; vga_bg=VGA_BLACK; vga_clear(vga_fg, vga_bg); }
void vga_clear(uint8_t fg, uint8_t bg) { uint16_t b=vga_entry(' ',fg,bg); for(int i=0;i<VGA_WIDTH*VGA_HEIGHT;i++) vga_buffer[i]=b; vga_x=0; vga_y=0; vga_set_cursor(0,0); }
void vga_scroll(void) { for(int i=0;i<VGA_WIDTH*(VGA_HEIGHT-1);i++) vga_buffer[i]=vga_buffer[i+VGA_WIDTH]; uint16_t b=vga_entry(' ',vga_fg,vga_bg); for(int i=VGA_WIDTH*(VGA_HEIGHT-1);i<VGA_WIDTH*VGA_HEIGHT;i++) vga_buffer[i]=b; if(vga_y>0) vga_y--; }
void vga_putchar(char c, uint8_t fg, uint8_t bg) { if(c=='\n'){vga_x=0;vga_y++;}else if(c=='\r'){vga_x=0;}else if(c=='\b'){if(vga_x>0){vga_x--;vga_buffer[vga_y*VGA_WIDTH+vga_x]=vga_entry(' ',fg,bg);}}else{vga_buffer[vga_y*VGA_WIDTH+vga_x]=vga_entry(c,fg,bg);vga_x++;} if(vga_x>=VGA_WIDTH){vga_x=0;vga_y++;} if(vga_y>=VGA_HEIGHT)vga_scroll(); vga_set_cursor(vga_x,vga_y); }
void vga_write(const char* str, uint8_t fg, uint8_t bg) { while(*str) vga_putchar(*str++,fg,bg); }
void vga_write_color(const char* str, uint8_t color) { while(*str) vga_putchar(*str++,color&0x0F,(color>>4)&0x0F); }
void vga_set_cursor(uint8_t x, uint8_t y) { uint16_t p=y*VGA_WIDTH+x; outb(0x3D4,0x0F);outb(0x3D5,(uint8_t)(p&0xFF));outb(0x3D4,0x0E);outb(0x3D5,(uint8_t)((p>>8)&0xFF));vga_x=x;vga_y=y; }
void vga_get_cursor(uint8_t* x, uint8_t* y) { *x=vga_x;*y=vga_y; }
