
#ifndef CANTINA_MATHS_MAGNETISEDFUNCTION_INL
#define CANTINA_MATHS_MAGNETISEDFUNCTION_INL

#pragma once

#include <cant/maths/utils.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN


    template <typename Ret_T, typename Par_T, typename Scalar_T>
    MagnetisedFunction<Ret_T, Par_T, Scalar_T>::
    MagnetisedFunction()
        : m_state(),
        m_pull()
    {
        static_assert(std::is_arithmetic_v<Par_T>, "Parameter type should be arithmetic.");
        static_assert(std::is_arithmetic_v<Ret_T>, "Return type should be arithmetic.");
        static_assert(std::is_floating_point_v<Scalar_T>, "Pull type should be scalar.");
    }

    template<typename Ret_T, typename Par_T, typename Scalar_T>
    void
    MagnetisedFunction<Ret_T, Par_T, Scalar_T>::
    stepDelta(const Par_T &timeDelta)
    {

        const Ret_T currentPosition = m_state.position;
        const Ret_T& targetPosition = m_target;
        const bool isApproximatelyOkay = maths::approx<Ret_T>::equal(currentPosition, targetPosition);
        // if current ratio is not approximately equal to target
        // we override varying state and change it regardless.
        // this is done to avoid accumulating artifacts.
        if (!isApproximatelyOkay)
        {
            // todo: this method is dangerous
            // if timeDelta is too large it will stutter
            // same thing if currentPosition and targetPosition are too different
            // that is, if there are on different orders of magnitudes.
            // Combine the two eventuality, and you can kiss your ears goodbye.
            const Scalar_T sign = targetPosition > currentPosition
                    ? static_cast<Scalar_T>(1.)
                    : static_cast<Scalar_T>(-1.);
            const Ret_T positionDelta = sign * m_pull * timeDelta;
            m_state.position += positionDelta;
        }
    }

    template<typename Ret_T, typename Par_T, typename Scalar_T>
    Ret_T
    MagnetisedFunction<Ret_T, Par_T, Scalar_T>::
    operator()() const
    {
        return m_state.position;
    }


    template<typename Ret_T, typename Par_T, typename Scalar_T>
    void
    MagnetisedFunction<Ret_T, Par_T, Scalar_T>::
    setPull(Scalar_T pull)
    {
        m_pull = pull;
    }

    template<typename Ret_T, typename Par_T, typename Scalar_T>
    void
    MagnetisedFunction<Ret_T, Par_T, Scalar_T>::
    setPosition(const Ret_T &position)
    {
        m_state.position = position;
    }

    template<typename Ret_T, typename Par_T, typename Scalar_T>
    void MagnetisedFunction<Ret_T, Par_T, Scalar_T>::
    setTarget(const Ret_T &target)
    {
        m_target = target;
    }



CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MATHS_MAGNETISEDFUNCTION_INL