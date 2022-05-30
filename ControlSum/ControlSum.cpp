#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>

uint64_t crc32(char* buf, uint64_t len)
{
    uint64_t crc_table[256];
    uint64_t crc;

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

        crc_table[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFUL;
};

int main()
{
    std::cout << "Hello World!\n";
}