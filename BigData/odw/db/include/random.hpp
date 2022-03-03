#ifndef DATABASE_RANDOM_HPP
#define DATABASE_RANDOM_HPP

#include "TypeUtil.hpp"
#include <iostream>
#include <chrono>
#include <random>

using namespace util;

namespace rnd {
    struct seeder_default {
        std::seed_seq &operator()() {
            return seed_seq;
        }

    private:
        std::seed_seq seed_seq{{
                                       static_cast<std::uintmax_t >(std::random_device{}()),
                                       static_cast<std::uintmax_t >(std::chrono::steady_clock::now().time_since_epoch().count()),
                               }};
    };

}

#endif //DATABASE_RANDOM_HPP
