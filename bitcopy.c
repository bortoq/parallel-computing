/*
 * TODO: find author on stackoverflow and ask for license
 *
 * update 20241021:
 *  fixed warning: comparison of integer expressions of different signedness: ‘unsigned int’ and ‘int’
 */
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>

/*
 * copy bits from one array to another (n, src, s, dst, d)
 *
 * n - number of bits to copy
 * src - source array
 * s - source bit index
 * dst - destination array
 * d - destination bit index
 */
void bitcpy(size_t src_len, const void *src_org, size_t src_offset, void *dst_org, size_t dst_offset)
{
#define PREPARE_FIRST_COPY()                                  \
    do {                                                      \
      if ((signed)src_len >= (CHAR_BIT - dst_offset_modulo)) {\
        *dst &= reverse_mask[dst_offset_modulo];              \
        src_len -= CHAR_BIT - dst_offset_modulo;              \
      }                                                       \
      else {                                                  \
        *dst &= reverse_mask[dst_offset_modulo]               \
          | reverse_mask_xor[dst_offset_modulo + src_len];    \
        c &= reverse_mask[dst_offset_modulo + src_len];       \
        src_len = 0;                                          \
      }                                                       \
    } while(0)

  static const unsigned char reverse_mask[] = {
    0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff};
  static const unsigned char reverse_mask_xor[] = {
    0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00};

  if(src_len)
  {
    const unsigned char *src;
    unsigned char *dst;
    int src_offset_modulo;
    int dst_offset_modulo;

    src = (const unsigned char*)src_org + (src_offset / CHAR_BIT);
    dst = (unsigned char*)dst_org + (dst_offset / CHAR_BIT);

    src_offset_modulo = src_offset % CHAR_BIT;
    dst_offset_modulo = dst_offset % CHAR_BIT;

    if(src_offset_modulo == dst_offset_modulo)
    {
      int byte_len;
      int src_len_modulo;
      if(src_offset_modulo)
      {
        unsigned char c;

        c = reverse_mask_xor[dst_offset_modulo] & *src++;
        PREPARE_FIRST_COPY();
        *dst++ |= c;
      }

      byte_len = src_len / CHAR_BIT;
      src_len_modulo = src_len % CHAR_BIT;

      if(byte_len)
      {
        memcpy(dst, src, byte_len);
        src += byte_len;
        dst += byte_len;
      }
      if(src_len_modulo)
      {
        *dst &= reverse_mask_xor[src_len_modulo];
        *dst |= reverse_mask[src_len_modulo] & *src;
      }
    }
    else
    {
      int bit_diff_ls;
      int bit_diff_rs;
      int byte_len;
      int src_len_modulo;
      unsigned char c;

      /* Begin: Line things up on destination */
      if(src_offset_modulo > dst_offset_modulo)
      {
        bit_diff_ls = src_offset_modulo - dst_offset_modulo;
        bit_diff_rs = CHAR_BIT - bit_diff_ls;

        c = *src++ << bit_diff_ls;
        c |= *src >> bit_diff_rs;
        c &= reverse_mask_xor[dst_offset_modulo];
      }
      else
      {
        bit_diff_rs = dst_offset_modulo - src_offset_modulo;
        bit_diff_ls = CHAR_BIT - bit_diff_rs;

        c = *src >> bit_diff_rs & reverse_mask_xor[dst_offset_modulo];
      }

      PREPARE_FIRST_COPY();
      *dst++ |= c;

      /* Middle: copy with only shifting the source */
      byte_len = src_len / CHAR_BIT;

      while(--byte_len >= 0)
      {
        c = *src++ << bit_diff_ls;
        c |= *src >> bit_diff_rs;
        *dst++ = c;
      }

      /* End: copy the remaining bits */
      src_len_modulo = src_len % CHAR_BIT;
      if(src_len_modulo)
      {
        c = *src++ << bit_diff_ls;
        c |= *src >> bit_diff_rs;
        c &= reverse_mask[src_len_modulo];

        *dst &= reverse_mask_xor[src_len_modulo];
        *dst |= c;
      }
    }
  }
}

