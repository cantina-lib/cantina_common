
#ifndef CANTINA_TIME_TYPES_HPP
#define CANTINA_TIME_TYPES_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/functor.hpp>

#include <cant/common/macro.hpp>
CANTINA_TIME_NAMESPACE_BEGIN

    typedef Functor<time_d()> AbsoluteTimeGetter;

CANTINA_TIME_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TIME_TYPES_HPP