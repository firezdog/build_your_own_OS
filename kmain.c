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
void fbuf_write_cell(unsigned int cell, char c, unsigned char fg_color, unsigned char bg_color);

int kmain() {
    fbuf_write_cell(10, 'H', FB_LIGHT_RED, FB_WHITE);
    fbuf_write_cell(11, 'E', FB_LIGHT_RED, FB_WHITE);
    fbuf_write_cell(12, 'L', FB_LIGHT_RED, FB_WHITE);
    fbuf_write_cell(13, 'L', FB_LIGHT_RED, FB_WHITE);
    fbuf_write_cell(14, 'O', FB_LIGHT_RED, FB_WHITE);
    return 3405691582;  // cafebabe in hexadecimal
}

/*
fb_write_cell:
    Writes a character with given foreground and background colors to the given cell of the frame buffer.

    @param cell     the location in the frame buffer
    @param c        the character to write
    @param fg_color the foreground color
    @param bg_color the background color
*/
void fbuf_write_cell(unsigned int cell, char c, unsigned char fg_color, unsigned char bg_color) {
    /* logic: a cell is 16 bytes or 2 char entries or 4 words -- represented by 4 hexadecimals.  
    The first entry gets the character itself.  
    The second entry is divided into two parts:
        (1) the foreground color and (2) the background color.  
    Each is 4 bits (some hex) followed by hex 0.
    The first entry gets shifted to the left to make room for the second entry.
    Example: fg = 0x02, bg = 0x08.
    Shift fg to the left to get 0x20 and then add the background (using  bitwise or) to get 0x28.
    Remember that a word is 4 bytes (16 bits), represented by 2 hexadecimals.
    */
    int i = 2 * cell;
    fbuf[i] = c;
    fbuf[i + 1] = ((fg_color & 0x0F) << 4) | (bg_color & 0x0F);
}