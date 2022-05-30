#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>

uint64_t crc32(char* buf, uint64_t len) {
    uint64_t crc_table[256];
    uint64_t crc;

    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        }

        crc_table[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    while (len--) {
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    }

    return crc ^ 0xFFFFFFFFUL;
};

uint64_t checkSum(std::ifstream& file) {
    if (!file) {
        std::cout << "Error!";
    } else {
        file.seekg(-(int)sizeof(uint64_t), std::ios::end);
        std::streamoff size = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buf = new char[size];
        uint64_t len = size;
        memset(buf, 0, sizeof(buf) + 1);
        file.read(buf, size);

        return crc32(buf, len);
    }
    file.close();
}

uint64_t readSum(std::ifstream& file) {
    if (!file) {
        std::cout << "Error!";
        return 0;
    } else {
        std::streamoff size = file.tellg();
        file.seekg(-(int)sizeof(uint64_t), file.end);
        uint64_t x;
        file.read((char*)&x, sizeof(x));
        return x;
    }
}