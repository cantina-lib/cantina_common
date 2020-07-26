//
// Created by piptouque on 30/04/2020.
//

#include <cant/pan/common/Time.hpp>

namespace cant::midi
{
    std::chrono::time_point<std::chrono::steady_clock> Time::tStart = std::chrono::steady_clock::now();
}
