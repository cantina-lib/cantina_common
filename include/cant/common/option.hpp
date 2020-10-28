//
// Created by binabik on 15/09/2020.
//

#ifndef CANTINA_TILDE_OPTION_HPP
#define CANTINA_TILDE_OPTION_HPP

#pragma once

#include <optional>

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

template <typename T>
using Optional = std::optional<T>;

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_TILDE_OPTION_HPP
