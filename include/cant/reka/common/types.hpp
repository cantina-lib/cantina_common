//
// Created by binabik on 09/08/2020.
//

#ifndef EUREKA_TYPES_HPP
#define EUREKA_TYPES_HPP

#pragma once

#include <ratio>
#include <functional>

#include <cant/common/types.hpp>

namespace cant::reka
{
    template <size_m N, size_m D>
    using ratio_m = std::ratio<N, D>;
}

#endif //EUREKA_TYPES_HPP
