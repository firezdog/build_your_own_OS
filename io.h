#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 * Sends the given data to the given I/O port. Defined in io.s
 * 
 * @param port the I/O port to send the data to
 * @param data the data to send to that port
 */

void outb(unsigned short port, unsigned char data);

#endif