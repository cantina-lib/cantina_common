//
// Created by binabik on 10/07/2020.
//

// the anti-macros, hell yeah

/*
 * Should include before the end of any header file that includes macro.hpp
 */

#ifndef CANTINA_COMMON_MACRO_HPP
#error "Macros need to be defined before being un-defined, ya thick."
#else
// Compilers
#if defined(__GNUC__)
#undef CANTINA_GCC
#elif defined(_MSC_VER)
#undef CANTINA_MSVC
#elif defined(__clang__)
#undef CANTINA_CLANG
#endif  // Compilers

// namespaces
#undef CANTINA_CANT_NAMESPACE
#undef CANTINA_PAN_NAMESPACE
#undef CANTINA_REKA_NAMESPACE
#undef CANTINA_MATHS_NAMESPACE
#undef CANTINA_PATTERN_NAMESPACE
#undef CANTINA_TIME_NAMESPACE

#undef CANTINA_CANT_NAMESPACE_BEGIN
#undef CANTINA_CANT_NAMESPACE_END
#undef CANTINA_PAN_NAMESPACE_BEGIN
#undef CANTINA_PAN_NAMESPACE_END
#undef CANTINA_REKA_NAMESPACE_BEGIN
#undef CANTINA_REKA_NAMESPACE_END
#undef CANTINA_MATHS_NAMESPACE_BEGIN
#undef CANTINA_MATHS_NAMESPACE_END
#undef CANTINA_PHYSICS_NAMESPACE_BEGIN
#undef CANTINA_PHYSICS_NAMESPACE_END
#undef CANTINA_PATTERN_NAMESPACE_BEGIN
#undef CANTINA_PATTERN_NAMESPACE_END
#undef CANTINA_TIME_NAMESPACE_BEGIN
#undef CANTINA_TIME_NAMESPACE_END

#undef CANT_CURRENT_FUNC
#undef CANT_CURRENT_FILE
#undef CANT_CURRENT_LINE

// Attributes
#undef CANT_NODISCARD
#undef CANT_MAYBEUNUSED
#undef CANT_FALLTHROUGH
#undef CANT_LIKELY
#undef CANT_UNLIKELY
#undef CANT_NODISCARD_BECAUSE

#undef CANTINA_ASSERT

// Specifiers
#undef CANT_CONSTEXPR
#undef CANT_INLINE
#undef CANT_EXPLICIT
#undef CANT_NOEXCEPT

#ifdef CANTINA_CANTINAEXCEPTION_HPP
#undef CANT_CURRENT_TRACE
#undef CANTINA_EXCEPTION
#undef CANTINA_TRY_RETHROW
#endif  // CANTINA_CANTINAEXCEPTION_HPP
#ifdef CANTINA_PANTOUFLEEXCEPTION_HPP
#undef PANTOUFLE_EXCEPTION
#undef PANTOUFLE_TRY_RETHROW
#endif  // CANTINA_PANTOUFLEEXCEPTION_HPP

#undef CANTINA_COMMON_MACRO_HPP

#endif  // not def CANTINA_MACRO_HPP

/*
 *
 *                        z
 *                      zzz
 *              A___A   z?
 *      _____ /  _ o \ /
 * ___/~____     ='= /
 *   (______)___m_m_)
 *
 * - Awesome, you found the cat! It looks like it has noticed you.
 *
 */