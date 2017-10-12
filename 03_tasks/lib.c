#include <stdarg.h>
#include "uart.h"


/* La fonction memcpy permet de copier n octets de src vers dest.
 * Les adresses sont lineaires.
 */
void *memcpy (char *dst, char *src, int n)
{
    char *p = dst;
    while (n--)
        *dst++ = *src++;
    return p;
}

int strcpy (char *dst, char *src)
{
    int i = 0;
    while ((dst[i] = src[i]))
        i++;

    return i;
}

int strcmp (char *dst, char *src)
{
    int i = 0;

    while ((dst[i] == src[i])) {
        if (src[i++] == 0)
            return 0;
    }

    return 1;
}

int strlen (char *s)
{
    int i = 0;
    while (*s++)
        i++;
    return i;
}

void itoa (char *buf, unsigned long int n, unsigned int base)
{
    unsigned long int tmp;
    int i, j;

    tmp = n;
    i = 0;

    do {
        tmp = n % base;
        buf[i++] = (char) ((tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10));
    } while (n /= base);
    buf[i--] = 0;

    for (j = 0; j < i; j++, i--) {
        tmp = buf[j];
        buf[j] = buf[i];
        buf[i] = (char) tmp;
    }
}

void printk (char *s, ...)
{
    va_list ap;

    char buf[16];
    int i, j, size, buflen, neg;

    unsigned char c;
    int ival;
    unsigned int uival;

    va_start (ap, s);

    while ((c = *s++)) {
        size = 0;
        neg = 0;

        if (c == 0)
            break;
        else if (c == '%') {
            c = *s++;
            if (c >= '0' && c <= '9') {
                size = c - '0';
                c = *s++;
            }

            if (c == 'd') {
                ival = va_arg (ap, int);
                if (ival < 0) {
                    uival = 0 - ival;
                    neg++;
                } else
                    uival = ival;
                itoa (buf, uival, 10);

                buflen = strlen (buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0; i--, j--)
                        buf[i] = (j >= 0) ? buf[j] : '0';

                if (neg)
                    printk ("-%s", buf);
                else
                    printk (buf);
            } else if (c == 'u') {
                uival = va_arg (ap, int);
                itoa (buf, uival, 10);

                buflen = strlen (buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0; i--, j--)
                        buf[i] = (j >= 0) ? buf[j] : '0';

                printk (buf);
            } else if (c == 'x' || c == 'X') {
                uival = va_arg (ap, int);
                itoa (buf, uival, 16);

                buflen = strlen (buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0; i--, j--)
                        buf[i] = (j >= 0) ? buf[j] : '0';

                printk ("0x%s", buf);
            } else if (c == 'p') {
                uival = va_arg (ap, int);
                itoa (buf, uival, 16);
                size = 8;

                buflen = strlen (buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0; i--, j--)
                        buf[i] = (j >= 0) ? buf[j] : '0';

                printk ("0x%s", buf);
            } else if (c == 's') {
                printk ((char *) va_arg (ap, int));
            }
        } else
            serial_out (c);
    }

    return;
}
