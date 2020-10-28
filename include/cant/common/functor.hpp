
#ifndef CANTINA_CANT_FUNCTOR_HPP
#define CANTINA_CANT_FUNCTOR_HPP

#pragma once

#include <functional>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

template <class Sig_Ts>
using Functor = ::std::function<Sig_Ts>;

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_CANT_FUNCTOR_HPP