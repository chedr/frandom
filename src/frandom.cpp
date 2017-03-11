/**
 * Generate random files quickly.
 * @file   frandom.cpp
 * @author Charles Roydhouse
 */

#include "Random.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

/** RNG buffer size */
static constexpr int64_t BUFFER_SIZE = 4 * 1024 * 1024;

/**
 * Write random bytes to destination file.
 * @param destination
 * @param bytes
 * @return 0 on success, 2 on failure.
 */
int frandom_write(std::string destination, int64_t bytes)
{
    frandom::Random random;
    auto buffer = frandom::make_shared_array<char>(BUFFER_SIZE);
    std::ofstream output(destination);
    int64_t to_write = 0, remaining = bytes;
    bool good = output.good();
    while (good && remaining) {
        if (!random.bytes(buffer.get(), BUFFER_SIZE)) {
            std::cerr << "RNG error" << std::endl;
            return 2;
        }
        to_write = std::min(BUFFER_SIZE, remaining);
        output.write(buffer.get(), to_write);
        good = output.good();
        remaining -= to_write;
    }
    if (!good) {
        std::cerr << std::strerror(errno) << std::endl;
        return 3;
    }
    output.flush();
    return 0;
}


/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: frandom file bytes" << std::endl;
        return 1;
    }

    std::string destination(argv[1]);
    int64_t bytes = std::atoll(argv[2]);
    return frandom_write(destination, bytes);
}
