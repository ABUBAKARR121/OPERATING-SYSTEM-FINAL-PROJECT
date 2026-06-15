#include "kernel.h"
#include "../drivers/display/vga.h"
#include "../drivers/input/keyboard.h"
#include "../proc/scheduler.h"
#include "../mem/memory.h"
#include "../fs/vfs.h"
#include "../shell/shell.h"
#include "login.h"
#include "../../libc/stdio.h"

void show_logo(void) {
    /* Outer shadow (dark grey) */
    vga_write_color("\n  \xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\n", VGA_DARK_GREY);
    /* Main double-line border (green top/bottom, white sides) */
    vga_write_color("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n", VGA_GREEN);
    vga_write_color("  \xBA                                          \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA    \xDC\xDC\xDC  SIERRA LEONE OS (SLeOS)  \xDC\xDC\xDC    \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA    \xDC\xDC\xDC  Limkokwing University    \xDC\xDC\xDC    \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA    \xDC\xDC\xDC        2026               \xDC\xDC\xDC    \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA                                          \xBA\n", VGA_WHITE);
    /* Sierra Leone flag colour bar (green-white-blue) */
    vga_write_color("  \xBA   ", VGA_WHITE);
    vga_write_color("\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", VGA_GREEN);
    vga_write_color("\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0", VGA_WHITE);
    vga_write_color("\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0\xB0   \xBA\n", VGA_LIGHT_BLUE);
    vga_write_color("  \xBA                                          \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA   Empowering Local Innovation            \xBA\n", VGA_LIGHT_BLUE);
    vga_write_color("  \xBA   SDG 4 : Quality Education               \xBA\n", VGA_YELLOW);
    vga_write_color("  \xBA   SDG 9 : Industry, Innovation & Infra    \xBA\n", VGA_YELLOW);
    vga_write_color("  \xBA   SDG 10: Reduced Inequalities            \xBA\n", VGA_YELLOW);
    vga_write_color("  \xBA                                          \xBA\n", VGA_WHITE);
    vga_write_color("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n", VGA_GREEN);
    /* Bottom shadow */
    vga_write_color("  \xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\n\n", VGA_DARK_GREY);
}

void kernel_init(void) {
    vga_init();
    keyboard_init();
    show_logo();

    if (!login_prompt()) {
        vga_write_color("  Login failed. Halting.\n", VGA_RED);
        while (1) __asm__ volatile ("hlt");
    }

    memory_init();
    scheduler_init();
    vfs_init();
    shell_init();

    vga_write_color("  [OK] All systems ready.\n\n", VGA_GREEN);
    vga_write_color("  Type 'help' for available commands.\n", 0x07);
}

void kernel_main(void) {
    kernel_init();
    shell_run();
    while (1) { hlt(); }
}
