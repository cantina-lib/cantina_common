//
// Created by binabik on 10/07/2020.
//

#ifndef CANTINA_MACRO_HPP
#define CANTINA_MACRO_HPP

// not this time!
// #pragma once

#include <cassert>

#define CANT_CURRENT_FUNC CANT_IMPL_FUNCTION
#define CANT_CURRENT_FILE __FILE__
#define CANT_CURRENT_LINE __LINE__

// Attributes
#define CANT_NODISCARD   [[nodiscard]]
#define CANT_MAYBEUNUSED [[maybe_unused]]
#define CANT_FALLTHROUGH [[fallthrough]]
#define CANT_LIKELY      [[likely]]
#define CANT_UNLIKELY    [[unlikely]]

#define CANTINA_ASSERT(pred, message) assert((pred) && (message))

// Specifiers
#define CANT_CONSTEXPR constexpr
#define CANT_INLINE    inline
#define CANT_EXPLICIT  explicit

#endif //CANTINA_MACRO_HPP













/*
 *
 *                        zzz
 *                      zzzzz
 *              A___A   zzz
 *      _____ /  _ _ \ /
 * ___/~____     ='= /
 *   (______)___m_m_)
 *
 * - Awesome, you found the cat! But it's sleeping now.
 *
 */