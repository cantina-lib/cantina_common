
#ifndef CANTINA_MATHS_MAGNETISEDFUNCTION_HPP
#define CANTINA_MATHS_MAGNETISEDFUNCTION_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/common/functor.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

    template <typename Ret_T, typename Par_T, typename Scalar_T>
    class MagnetisedFunction
    {
    public:
        /* -- methods -- **/
        MagnetisedFunction();

        Ret_T operator()() const;

        void stepDelta(const Par_T& delta);

        void setPull(Scalar_T pull);
        void setPosition(const Ret_T& position);

        void setTarget(const Ret_T& target);


    private:
        /** -- methods -- **/


        /** -- structs -- **/
        struct State
        {
            // using physics analogy to wrap my head around this template business.
            // Par_T time;
            Ret_T position;
        };
        /** -- fields -- **/
        State m_state;
        /*
         * todo? Pull could be a function of time and position! (state)
         * todo will be in a related class.
         * typedef Functor<Ret_T(Par_T)> KineticFunctor;
         * void setKineticFunctor(KineticFunctor func);
         * KineticFunctor m_func;
         */
        Ret_T m_target;
        Scalar_T m_pull;

        /*
         * INTERESTING
         * If position was not set manually,
         * and the kinetic function was convergent,
         * we wouldn't need to update once it was close enough to target.
         */
    };

CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/maths/physics/MagnetisedFunction.inl>

#endif //CANTINA_MATHS_MAGNETISEDFUNCTION_HPP