/**
 * Random number generator class definitions.
 * @file   Random.h
 * @author Charles Roydhouse
 */

#include "Random.h"
#include <cstdint>
#include <immintrin.h>
#include <cstring>
#include <chrono>

using namespace frandom;

/** Software RNG seed */
static thread_local std::uint32_t soft_seed = static_cast<std::uint32_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()
);

/**
 * CPUID inline ASM.
 * @param regs
 * @param h
 */
static void cpu_id(int *regs, int h)
{
    __asm__ __volatile__(
#if defined __x86_64__
    "pushq %%rbx;\n"
#else
    "pushl %%ebx;\n"
#endif
    "cpuid;\n"
#if defined __x86_64__
    "popq %%rbx;\n"
#else
    "popl %%ebx;\n"
#endif
    : "=a"(regs[0]), [ebx] "=r"(regs[1]), "=c"(regs[2]), "=d"(regs[3])
    : "a"(h));
}


/**
 * Detect RDRAND via CPUID.
 * @return
 */
static int has_rdrand()
{
    int regs[4];
    cpu_id(regs, 1);
    return (regs[2] & (1 << 30)) != 0;
}


/**
 * Software RNG function (Intel fast RNG algorithm).
 * @return
 */
static std::uint32_t softrand()
{
    soft_seed = (214013 * soft_seed + 2531011);
    return (soft_seed >> 16) & 0x7FFF;
}


Random::Random(bool force_software) : m_rng(nullptr)
{
    if (!force_software && has_rdrand()) {
        this->m_rng = &Random::rdrand;
    }
    else {
        this->m_rng = &Random::softrand;
    }
}


Random::~Random()
{

}


Random::Random(Random &other) : m_rng(other.m_rng)
{

}


Random::Random(Random &&other) : m_rng(std::move(other.m_rng))
{

}


Random &Random::operator==(Random &other)
{
    if (&other == this) {
        return *this;
    }
    this->m_rng = other.m_rng;
    return *this;
}


Random &Random::operator==(Random &&other)
{
    if (&other == this) {
        return *this;
    }
    this->m_rng = std::move(other.m_rng);
    return *this;
}


const void *Random::bytes(void *buffer, std::size_t length)
{
    return this->m_rng(buffer, length);
}


const void *Random::rdrand(void *buffer, std::size_t length)
{
    long long unsigned int *quad_words = reinterpret_cast<long long unsigned int *>(buffer);
    auto n_quads = length / sizeof(std::uint64_t);
    const auto r_bytes = length % sizeof(std::uint64_t);

    while (n_quads--) {
        if (!_rdrand64_step(quad_words++)) {
            buffer = nullptr;
            goto out;
        }
    }

    if (r_bytes) {
        long long unsigned int quad_word;
        if (!_rdrand64_step(&quad_word)) {
            buffer = nullptr;
            goto out;
        }
        std::memcpy(quad_words, &quad_word, r_bytes);
    }

out:
    return buffer;
}


const void *Random::softrand(void *buffer, std::size_t length)
{
    std::uint32_t *double_words = reinterpret_cast<std::uint32_t *>(buffer);
    auto n_doubles = length / sizeof(std::uint32_t);
    const auto r_bytes = length % sizeof(std::uint32_t);

    while (n_doubles--) {
        *(double_words++) = ::softrand();
    }

    if (r_bytes) {
        std::uint32_t double_word = ::softrand();
        std::memcpy(double_words, &double_word, r_bytes);
    }

    return buffer;
}
