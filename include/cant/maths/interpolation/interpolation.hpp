//
// Created by binabik on 18/08/2020.
//

#ifndef CANTINA_INTERPOLATION_HPP
#define CANTINA_INTERPOLATION_HPP

#pragma once

#include <cmath>
#include <functional>
#include <tuple>

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
    private:
        using Values = Stream<InterpolationPoint<Ret_T, Param_Ts...>>;
        Values _values;
    public:
        virtual ~InterpolationOneD() = default;
        CANT_EXPLICIT InterpolationOneD(const Values& values)
        : _values(values)
        {
            static_assert(std::is_arithmetic<Param_Ts...>::value);
        }

        InterpolationOneD(std::initializer_list<InterpolationPoint<Ret_T, Param_Ts...>> il)
        : _values(il)
        {}

        CANT_NODISCARD virtual Ret_T operator()(const Param_Ts&... args) const  = 0;
    };

    template <typename Ret_T, typename... Param_Ts>
    class BrokenLinesInterpolation : public InterpolationOneD<Ret_T, Param_Ts...>
    {
    private:
    public:
        CANT_NODISCARD Ret_T operator()(const Param_Ts&... args) const override
        {

        }
    };
}

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_INTERPOLATION_HPP
