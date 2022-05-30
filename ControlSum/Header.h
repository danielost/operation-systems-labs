#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>

uint64_t crc32(char* buf, uint64_t len) {
    uint64_t crcTable[256];
    uint64_t crc;

    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        }

        crcTable[i] = crc;
    };

    crc = 0xFFFFFFFFUL;

    while (len--) {
        crc = crcTable[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    }

    return crc ^ 0xFFFFFFFFUL;
};

void writeSum(char* path) {
    std::fstream file;
    file.open(path, std::ios::out | std::ios::in | std::ios::ate | std::ios::binary);
    if (!file)
        std::cout << "Error!";
    else {
        std::streamoff size = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[size];
        memset(buffer, 0, sizeof(buffer) + 1);

        file.read(buffer, size);

        uint64_t crc = crc32(buffer, size);

        file.seekg(0, std::ios::end);
        file.write((char*)&crc, sizeof(crc));
        file.close();
    }
}

uint64_t checkSum(std::ifstream& file) {
    if (!file) {
        std::cout << "Error!";
    }
    else {
        file.seekg(-(int)sizeof(uint64_t), std::ios::end);
        std::streamoff size = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[size];
        uint64_t len = size;
        memset(buffer, 0, sizeof(buffer) + 1);
        file.read(buffer, size);

        return crc32(buffer, len);
    }
    file.close();
}

uint64_t readSum(std::ifstream& file) {
    if (!file) {
        std::cout << "Error!";
        return 0;
    }
    else {
        std::streamoff size = file.tellg();
        file.seekg(-(int)sizeof(uint64_t), file.end);
        uint64_t checkSum;
        file.read((char*)&checkSum, sizeof(checkSum));
        return checkSum;
    }
}
//Made by D(e/a)n