#include "commands.h"
#include "../proc/scheduler.h"
#include "../mem/memory.h"
#include "../fs/vfs.h"
#include "../../libc/stdio.h"
#include "../../libc/string.h"
#include "../drivers/display/vga.h"
#include "../core/system.h"

void cmd_help(int argc, char* argv[]) {
    kprint_color("\n  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n", VGA_CYAN);
    kprint_color("  \xBA     SLeOS COMMAND REFERENCE      \xBA\n", VGA_CYAN);
    kprint_color("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n", VGA_CYAN);
    kprint_color("  help        ", VGA_YELLOW); kprint("- This menu\n");
    kprint_color("  clear       ", VGA_YELLOW); kprint("- Clear screen\n");
    kprint_color("  ps          ", VGA_YELLOW); kprint("- Process list\n");
    kprint_color("  mem         ", VGA_YELLOW); kprint("- Memory info\n");
    kprint_color("  ls          ", VGA_YELLOW); kprint("- List files\n");
    kprint_color("  create      ", VGA_YELLOW); kprint("- Create file (create <name>)\n");
    kprint_color("  cat/read    ", VGA_YELLOW); kprint("- Read file (cat <file>)\n");
    kprint_color("  write       ", VGA_YELLOW); kprint("- Write to file (write <file> <text>)\n");
    kprint_color("  delete/del  ", VGA_YELLOW); kprint("- Delete file\n");
    kprint_color("  logo        ", VGA_YELLOW); kprint("- Show welcome banner\n");
    kprint_color("  reboot      ", VGA_YELLOW); kprint("- Restart the system\n");
    kprint_color("  about       ", VGA_YELLOW); kprint("- About SLeOS\n");
    kprint_color("  sysinfo     ", VGA_YELLOW); kprint("- System details\n");
    kprint("\n");
}

void cmd_clear(int argc, char* argv[]) { vga_clear(VGA_WHITE, VGA_BLACK); }
void cmd_ps(int argc, char* argv[]) { scheduler_display(); }
void cmd_mem(int argc, char* argv[]) { memory_display(); }
void cmd_ls(int argc, char* argv[]) { vfs_cmd_ls(); }

void cmd_create(int argc, char* argv[]) {
    if (argc < 2) {
        kprint_color("  Usage: create <name>\n", VGA_RED);
        return;
    }
    vfs_cmd_create(argv[1]);
}

void cmd_read(int argc, char* argv[]) {
    if (argc < 2) {
        kprint_color("  Usage: cat <name>\n", VGA_RED);
        return;
    }
    vfs_cmd_read(argv[1]);
}

/* FIXED: join all arguments after the filename with spaces */
void cmd_write(int argc, char* argv[]) {
    if (argc < 3) {
        kprint_color("  Usage: write <filename> <text>\n", VGA_RED);
        return;
    }

    char buffer[MAX_FILE_SIZE];  /* max file size from file.h */
    int pos = 0;

    for (int i = 2; i < argc && pos < MAX_FILE_SIZE - 1; i++) {
        char* word = argv[i];
        while (*word && pos < MAX_FILE_SIZE - 1) {
            buffer[pos++] = *word++;
        }
        /* add a space between words (but not after the last one) */
        if (i < argc - 1 && pos < MAX_FILE_SIZE - 1) {
            buffer[pos++] = ' ';
        }
    }
    buffer[pos] = '\0';

    vfs_cmd_write(argv[1], buffer);
}

void cmd_delete(int argc, char* argv[]) {
    if (argc < 2) {
        kprint_color("  Usage: delete <name>\n", VGA_RED);
        return;
    }
    vfs_cmd_delete(argv[1]);
}

void cmd_about(int argc, char* argv[]) {
    kprint_color("\n  SLeOS v1.0  |  Limkokwing Univ 2026\n  SDG 4, 9, 10\n\n", VGA_GREEN);
}

void cmd_sysinfo(int argc, char* argv[]) {
    kprint("\n  OS: SLeOS 1.0 | Arch: x86 QEMU | Files: 256 max, 4KB each\n\n");
}

void cmd_reboot(int argc, char* argv[]) {
    kprint_color("\n  Rebooting...\n", VGA_YELLOW);
    while (inb(0x64) & 0x02);
    outb(0x64, 0xFE);
    __asm__ volatile ("int $0");
}

void cmd_logo(int argc, char* argv[]) {
    vga_write_color("\n  \xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\xDC\n", VGA_DARK_GREY);
    vga_write_color("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n", VGA_GREEN);
    vga_write_color("  \xBA                                          \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA    \xDC\xDC\xDC  SIERRA LEONE OS (SLeOS)  \xDC\xDC\xDC    \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA    \xDC\xDC\xDC  Limkokwing University    \xDC\xDC\xDC    \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA    \xDC\xDC\xDC        2026               \xDC\xDC\xDC    \xBA\n", VGA_WHITE);
    vga_write_color("  \xBA                                          \xBA\n", VGA_WHITE);
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
    vga_write_color("  \xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\n\n", VGA_DARK_GREY);
}
