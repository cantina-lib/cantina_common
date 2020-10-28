//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_INTERPOLATIONONED_HPP
#define CANTINA_TILDE_INTERPOLATIONONED_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/common/macro.hpp>
CANTINA_BEGIN_MATHS_NAMESPACE
{
    template <typename... Ts>
    using InterpolationPoint = Tuple<Ts...>;

    template <typename Ret_T, typename... Param_Ts>
    class InterpolationOneD
    {
        /** -- internal structs -- **/
       protected:
        typedef InterpolationPoint<Ret_T, Param_Ts...> Value;

       public:
        /** -- methods -- **/
        virtual ~InterpolationOneD() = default;
        CANT_EXPLICIT
        InterpolationOneD(Stream<Value> const & values);

        InterpolationOneD(std::initializer_list<InterpolationPoint<Ret_T, Param_Ts...>> il);

        CANT_NODISCARD virtual Ret_T
          operator()(Tuple<Param_Ts> const &... args) const = 0;

       protected:
        /** -- fields -- **/
        Stream<Value> m_values;
    };

    CANTINA_END_MATHS_NAMESPACE
#include <cant/common/undef_macro.hpp>

#include <cant/maths/InterpolationOneD.inl>

#endif  // CANTINA_TILDE_INTERPOLATIONONED_HPP
