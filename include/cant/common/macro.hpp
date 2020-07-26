//
// Created by binabik on 10/07/2020.
//

#ifndef CANTINA_MACRO_HPP
#define CANTINA_MACRO_HPP

#pragma once

#include <cassert>

#define CANT_CURRENT_FUNC CANT_IMPL_FUNCTION
#define CANT_CURRENT_FILE __FILE__
#define CANT_CURRENT_LINE __LINE__

// Attributes
#define CANT_NODISCARD [[nodiscard]]
#define CANT_MAYBEUNUSED [[maybe_unused]]
#define CANT_FALLTHROUGH [[fallthrough]]
#define CANT_LIKELY [[likely]]
#define CANT_UNLIKELY [[unlikely]]

#define CANTINA_ASSERT(pred) assert(pred);
#define CANTINA_ASSERT_STATIC(pred) static_assert(pred);


// Specifiers
#define CANT_CONSTEXPR constexpr
#define CANT_INLINE inline
#define CANT_EXPLICIT explicit

#define CANT_VARIABLE_NAME(var) (#var)
#define CANT_RUNTIME_TYPE_NAME(var) (typeid(var).name())

// todo: Doesn't work because __FUNCTION__ etc. are not actually macros!
#   define CANT_FUNCTION_MACRO_PRESENT
// #     define CANT_IMPL_FUNCTION __PRETTY_FUNCTION__
#        define CANT_IMPL_FUNCTION __FUNCTION__
/*
#   if defined(__PRETTY_FUNCTION__)
#     define CANT_IMPL_FUNCTION __PRETTY_FUNCTION__
#   elif defined (__FUNCSIG__)
#     define CANT_IMPL_FUNCTION __FUNCSIG__
#   elif defined (__FUNCTION__)
#     define CANT_IMPL_FUNCTION __FUNCTION__
#   else
#     define CANT_IMPL_FUNCTION "NOSUPPORT"
#     undef CANT_FUNCTION_MACRO_PRESENT // no function macro after all
#   endif // __PRETTY_FUNCTION
 */


#endif //CANTINA_MACRO_HPP
