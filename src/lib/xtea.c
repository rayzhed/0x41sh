#include "libc.h"

typedef unsigned int u32;

void xtea(void *data, size_t size, const char *password, int decrypt)
{
    u32 key[4] = {0, 0, 0, 0};
    u32 *block = (u32 *)data;
    u32 left;
    u32 right;
    u32 sum;
    u32 delta = 0x9E3779B9;
    size_t i = 0;
    size_t p = 0;
    int round;

    while (password[p]) {
        key[p % 4] = key[p % 4] * 33 ^ (unsigned char)password[p];
        p++;
    }
    while (i + 1 < size / 4) {
        left = block[i];
        right = block[i + 1];
        sum = decrypt ? 0xC6EF3720 : 0;
        round = 0;
        while (round < 32) {
            if (decrypt) {
                right -= (((left << 4) ^ (left >> 5)) + left)
                    ^ (sum + key[(sum >> 11) & 3]);
                sum -= delta;
                left -= (((right << 4) ^ (right >> 5)) + right)
                    ^ (sum + key[sum & 3]);
            } else {
                left += (((right << 4) ^ (right >> 5)) + right)
                    ^ (sum + key[sum & 3]);
                sum += delta;
                right += (((left << 4) ^ (left >> 5)) + left)
                    ^ (sum + key[(sum >> 11) & 3]);
            }
            round++;
        }
        block[i] = left;
        block[i + 1] = right;
        i += 2;
    }
}
