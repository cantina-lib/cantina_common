//
// Created by piptouque on 23/04/2020.
//

#ifndef CANTINA_BASETYPES_HPP
#define CANTINA_BASETYPES_HPP

#pragma once

#include <cstddef>
#include <cstdint>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

    typedef ::std::size_t size_u;
    typedef ::std::int32_t type_i;
    typedef double type_d;

    typedef type_d time_d;

    typedef float sample_f;

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_BASETYPES_HPP
