//
// Created by binabik on 10/07/2020.
//

#ifdef CANTINA_MACRO_HPP
#error "Macros oughtn't be included twice in the same translation unit, ya thick."
#else
#define CANTINA_MACRO_HPP

// not this time!
// #pragma once

#include <cassert>

#define CANT_CURRENT_FILE __FILE__
#define CANT_CURRENT_LINE __LINE__

#define CANT_IMPL_FUNCTION __PRETTY_FUNCTION__
#define CANT_CURRENT_FUNC CANT_IMPL_FUNCTION

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


/* EXCEPTION SPECIFICS */
#define CANT_CURRENT_TRACE            ::cant::Trace(CANT_CURRENT_FUNC, CANT_CURRENT_FILE, CANT_CURRENT_LINE)
#define CANTINA_EXCEPTION_ADD_TRACE() _addTrace_(CANT_CURRENT_TRACE)

#define CANTINA_EXCEPTION(msg)        ::cant::CantinaException(CANT_CURRENT_TRACE, msg)
/*
 * todo: should it be internal? In that case, remove namespace specifier.
 */
#define CANTINA_TRY_RETHROW(expression) {                                                  \
                                                 try {                                     \
                                                    expression                             \
                                                 } catch(::cant::CantinaException& e) {    \
                                                    e.CANTINA_EXCEPTION_ADD_TRACE();       \
                                                    throw;                                 \
                                                 }                                         \
                                         }

#define PANTOUFLE_EXCEPTION(msg) ::cant::pan::MidiException(CANT_CURRENT_TRACE, msg)
#define PANTOUFLE_TRY_RETHROW(expression) {                                                \
                                                 try {                                     \
                                                     expression                            \
                                                 } catch (::cant::pan::MidiException& e) { \
                                                    e.CANTINA_EXCEPTION_ADD_TRACE();       \
                                                    throw;                                 \
                                                 }                                         \
                                           }
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