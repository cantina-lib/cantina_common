//
// Created by binabik on 10/07/2020.
//

// the anti-macros, hell yeah

/*
 * Should include before the end of any header file that includes macro.hpp
 */

#ifndef CANTINA_MACRO_HPP
#error "Macros need to be defined before being un-defined, ya thick."
#else

    #undef CANT_CURRENT_FUNC
    #undef CANT_CURRENT_FILE
    #undef CANT_CURRENT_LINE

    // Attributes
    #undef CANT_NODISCARD
    #undef CANT_MAYBEUNUSED
    #undef CANT_FALLTHROUGH
    #undef CANT_LIKELY
    #undef CANT_UNLIKELY

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
    #endif // CANTINA_CANTINAEXCEPTION_HPP
    #ifdef CANTINA_PANTOUFLEEXCEPTION_HPP
        #undef PANTOUFLE_EXCEPTION
        #undef PANTOUFLE_TRY_RETHROW
    #endif // CANTINA_PANTOUFLEEXCEPTION_HPP

    #undef CANTINA_MACRO_HPP

#endif //not def CANTINA_MACRO_HPP












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