//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_BROKENLINESINTERPOLATION_HPP
#define CANTINA_TILDE_BROKENLINESINTERPOLATION_HPP

#pragma once

#include <cant/maths/interpolation/InterpolationOneD.hpp>

#include <cant/common/macro.hpp>
CANTINA_BEGIN_MATHS_NAMESPACE
    template <typename... Param_Ts>
    class PackedPolynomials;

    template <typename Ret_T, typename... Param_Ts>
    class BrokenLinesInterpolation : public InterpolationOneD<Ret_T, Param_Ts...>
    {
    public:
        /** -- internal structs -- **/
        typedef PackedPolynomials<Ret_T, Tuple<Param_Ts...>> Line;
        /** -- methods -- **/
        CANT_EXPLICIT BrokenLinesInterpolation(const typename InterpolationOneD<Ret_T, Param_Ts...>::Values& values);
        CANT_NODISCARD Ret_T operator()(const Tuple<Param_Ts>&... args) const override;
    private:
        /** -- methods -- **/

        // static
        CANT_NODISCARD static Stream<Line> computeLines(const Stream<typename InterpolationOneD<Ret_T, Param_Ts>::Value>& values);

        /** -- fields -- **/
        Stream<Line> m_lines;
    };

}
CANTINA_END_MATHS_NAMESPACE
#include <cant/common/undef_macro.hpp>

#include <cant/maths/interpolation/BrokenLinesInterpolation.inl>

#endif //CANTINA_TILDE_BROKENLINESINTERPOLATION_HPP