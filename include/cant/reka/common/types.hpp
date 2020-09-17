//
// Created by binabik on 09/08/2020.
//

#ifndef EUREKA_TYPES_HPP
#define EUREKA_TYPES_HPP

#pragma once

#include <ratio>
#include <functional>

#include <cant/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_BEGIN_REKA_NAMESPACE

    template <size_u N, size_u D>
    using ratio_m = std::ratio<N, D>;

CANTINA_END_REKA_NAMESPACE
#include <cant/common/undef_macro.hpp>

#endif //EUREKA_TYPES_HPP
