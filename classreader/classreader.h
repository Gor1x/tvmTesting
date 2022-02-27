#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "clazz/clazz.h"

class ClassReader {
private:
    std::string _fileName;
    int _fd;
    int _isFailed;

    uint8_t swapBytes(uint8_t value) {
        return value;
    }

    uint16_t swapBytes(uint16_t value) {
        return (value >> 8) | (value << 8); 
    }

    uint32_t swapBytes(uint32_t value) {
        return (value >> 24) & 0xFF |
               ((value >> 8) & 0xFF00) |
               ((value << 8) & 0xFF0000) |
               ((value << 24) & 0xFF000000); 
    }

    template<typename T>
    T read() {
        T v;
        int remained = sizeof(T);
        std::byte* base = reinterpret_cast<std::byte*>(&v);
        while (remained > 0) {
            int n = ::read(_fd, base + (sizeof(T) - remained), remained);
            if (n < 0) {
                std::cout << "Failed to read. errno " << errno << " " << strerror(errno) << std::endl;
                _isFailed = true;
            }

            remained -= n;
        }

        return swapBytes(v);
    }

    void fill(std::shared_ptr<u1> data, uint16_t size) {
        int remained = size;
        while (remained > 0) {
            int n = ::read(_fd, data.get() + (size - remained), remained);
            if (n < 0) {
                std::cout << "Failed to read. errno " << errno << " " << strerror(errno) << std::endl;
                _isFailed = true;
            }

            remained -= n;
        }

    }

    std::shared_ptr<CPool::Entity> readCPool();

public:

    ClassReader(std::string fileName) : _fileName{fileName}, _isFailed{false} {
    }

    std::shared_ptr<Clazz> readClass();

    ~ClassReader() {
        if (_fd >= 0) {
            close(_fd); 
        }
    }
};

