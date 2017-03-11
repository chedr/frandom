/**
 * Random number generator class declarations.
 * @file   Random.h
 * @author Charles Roydhouse
 */

#pragma once

#include <cstddef>
#include <functional>
#include <memory>

namespace frandom
{
    /**
     * Template wrapper around std::shared_ptr to allow array allocation.
     * @tparam T
     * @param size
     * @return
     */
    template<typename T>
    std::shared_ptr<T> make_shared_array(std::size_t size)
    {
        return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
    }

    /**
     * RNG wrapper class.
     */
    class Random
    {
    public:

        /**
         * Constructor.
         * @param force_software Force software RNG.
         */
        Random(bool force_software=false);


        /**
         * Destructor.
         */
        ~Random();


        /**
         * Copy constructor.
         * @param other
         */
        Random(Random &other);


        /**
         * Move constructor.
         * @param other
         */
        Random(Random &&other);


        /**
         * Copy assignment.
         * @param other
         * @return
         */
        Random &operator==(Random &other);


        /**
         * Move assignment.
         * @param other
         * @return
         */
        Random &operator==(Random &&other);


        /**
         * Generate random bytes with the best available RNG.
         * @param bytes
         * @param length
         * @return supplied buffer, nullptr on error
         */
        const void *bytes(void *buffer, std::size_t length);

    protected:

        /** RNG function definition */
        using randfunc_t = std::function<const void *(void *bytes, std::size_t length)>;

        /**
         * Generate random bytes with Intel RDRAND instruction.
         * @param buffer
         * @param length
         * @return supplied buffer, nullptr on error
         */
        static const void *rdrand(void *buffer, std::size_t length);


        /**
         * Generate random bytes with Intel fast RNG algorithm.
         * @param buffer
         * @param length
         * @return supplied buffer, nullptr on error
         */
        static const void *softrand(void *buffer, std::size_t length);

        /** RNG function to use when bytes() is called */
        randfunc_t   m_rng;
    };
}
