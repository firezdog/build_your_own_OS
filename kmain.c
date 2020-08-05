#include "io.h"

/* the I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
/* the I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15
void fbuf_move_cursor(unsigned short pos);

#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_RED 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15
char* fbuf = (char*) 0x000B8000;
void fbuf_write_cell(unsigned int row, unsigned int column, char c, unsigned char fg_color, unsigned char bg_color);

int kmain() {
    fbuf_write_cell(5, 0, 'H', FB_WHITE, FB_BLACK);
    fbuf_move_cursor(1032);
    return 3405691582;  // cafebabe in hexadecimal
}

/*
fb_write_cell:
    Writes a character with given foreground and background colors to the given cell of the frame buffer.

    @param row      row 0 to 24 in the frame buffer
    @oaram column   column 0 to 80 in the frame buffer
    @param c        the character to write
    @param fg_color the foreground color
    @param bg_color the background color
*/
void fbuf_write_cell(unsigned int row, unsigned int column, char c, unsigned char fg_color, unsigned char bg_color) {
    /* logic:
    We multiply row 80 and add column to get the cell number (no validation now), 
        then multiply that by 2 because each cell takes up two indices.
    A cell is 16 bytes or 2 char entries or 4 words -- represented by 4 hexadecimals.  
        The first entry gets the character itself.  
        The second entry is divided into two parts:
            (1) the foreground color and (2) the background color.  
        Each is 4 bits (some hex) followed by hex 0.
        The first entry gets shifted to the left to make room for the second entry.
        Example: fg = 0x02, bg = 0x08.
            Shift fg to the left to get 0x20 and then add the background (using  bitwise or) to get 0x28.
    */
    int i = 2 * (80 * row + column);
    fbuf[i] = c;
    fbuf[i + 1] = ((fg_color & 0x0F) << 4) | (bg_color & 0x0F);
}

void fbuf_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0x00FF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}