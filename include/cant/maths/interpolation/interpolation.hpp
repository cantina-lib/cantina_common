//
// Created by binabik on 18/08/2020.
//

#ifndef CANTINA_INTERPOLATION_HPP
#define CANTINA_INTERPOLATION_HPP

#pragma once


#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/common/macro.hpp>
namespace cant::maths
{


    template <typename... Ts>
    using InterpolationPoint = Tuple<Ts...>;

    template <typename Ret_T, typename... Param_Ts>
    class InterpolationOneD
    {
        /** -- internal structs -- **/
        using Values = Stream<InterpolationPoint<Ret_T, Param_Ts...>>;
    public:
        /** -- methods -- **/
        virtual ~InterpolationOneD() = default;
        CANT_EXPLICIT InterpolationOneD(const Values& values);

        InterpolationOneD(std::initializer_list<InterpolationPoint<Ret_T, Param_Ts...>> il);

        CANT_NODISCARD virtual Ret_T operator()(const Param_Ts&... args) const  = 0;
    private:
        /** -- fields -- **/
        Values m_values;
    };



    template <typename Ret_T, typename... Param_Ts>
    class BrokenLinesInterpolation : public InterpolationOneD<Ret_T, Param_Ts...>
    {
    public:
        CANT_NODISCARD Ret_T operator()(const Param_Ts&... args) const override;
    };

}
#include <cant/common/undef_macro.hpp>

#include "interpolation.inl"

#endif //CANTINA_INTERPOLATION_HPP
