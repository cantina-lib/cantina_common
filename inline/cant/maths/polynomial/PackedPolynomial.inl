//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_PACKEDPOLYNOMIAL_INL
#define CANTINA_TILDE_PACKEDPOLYNOMIAL_INL

#pragma once

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_BEGIN_MATHS_NAMESPACE

    template <typename... Param_Ts>
    PackedPolynomial<Param_Ts...>::
    PackedPolynomial(Stream<Coefficient> const& coefficients)
            : m_coefficients(coefficients), // just be mindful that this init is order-dependant (m_coefficient before m_degree).
            // so m_coefficients must be declared before m_degree in the class.
              m_degree(computeDegree(m_coefficients))
    {
        static_assert(std::is_arithmetic<Coefficient>::value);
    }

    template <typename... Param_Ts>
    PackedPolynomial<Param_Ts...>::
    PackedPolynomial(std::initializer_list<Coefficient> ls)
            : m_coefficients(ls), // just be mindful that this init is order-dependant (m_coefficient before m_degree).
            // so m_coefficients must be declared before m_degree in the class.
              m_degree(computeDegree(m_coefficients))
    {
    }

    template<typename... Param_Ts>
    CANT_INLINE
    void
    PackedPolynomial<Param_Ts...>::
    negate()
    {
        std::transform
                (
                        m_coefficients.begin(),
                        m_coefficients.end(),
                        m_coefficients.begin(),
                        [](Coefficient const& coef) { return - coef; }
                );
    }

    template<typename... Param_Ts>
    CANT_INLINE
    void
    PackedPolynomial<Param_Ts...>::
    add(PackedPolynomial const& other)
    {
        applyCoefficientwise
        (
                other,
                [](Coefficient const& coef1, Coefficient const& coef2)
                {
                    return coef1 + coef2;
                }
        );
    }

    template<typename... Param_Ts>
    CANT_INLINE
    void
    PackedPolynomial<Param_Ts...>::
    substract(PackedPolynomial const& other)
    {
        applyCoefficientwise
        (
                other,
                [](Coefficient const& coef1, Coefficient const& coef2)
                {
                    return coef1 - coef2;
                }
        );
    }

    template<typename... Param_Ts>
    void
    PackedPolynomial<Param_Ts...>::
    multiply(PackedPolynomial const& other)
    {
        const size_u d1 = this->getDegree();
        const size_u d2 = other.getDegree();

        // we know the resulting degree from the start.
        m_degree = d1 + d2;
        this->fitToDegree();
        for (auto const& coef : other.m_coefficients)
        {
            this->multiply(coef);
        }
    }

    template <typename... Param_Ts>
    CANT_INLINE
    void
    PackedPolynomial<Param_Ts...>::
    multiply(Coefficient const& coef)
    {
        std::transform(
                m_coefficients.begin(),
                m_coefficients.end(),
                m_coefficients.begin(),
                [&coef](Coefficient const& thisCoef)
                {
                    return thisCoef * coef;
                }
        );
    }

    template<typename... Param_Ts>
    CANT_NODISCARD CANT_INLINE
    size_u
    PackedPolynomial<Param_Ts...>::
    getDegree() const
    {
        return m_degree;
    }

    template<typename... Param_Ts>
    CANT_INLINE
    void
    PackedPolynomial<Param_Ts...>::
    fitToDegree()
    {
        m_coefficients.resize(getDegree());
    }

    template<typename... Param_Ts>
    CANT_NODISCARD
    size_u
    PackedPolynomial<Param_Ts...>::
    computeDegree(Stream<PackedPolynomial::Coefficient> const& coefficients)
    {
        size_u rcounter = coefficients.size();
        for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it)
        {
            if (it->operator!=(static_cast<Coefficient>(0)))
            {
                return rcounter;
            }
            --rcounter;
        }
    }

    template<typename... Param_Ts>
    PackedPolynomial<Param_Ts...>
    PackedPolynomial<Param_Ts...>::
    operator-() const
    {
        Stream<Coefficient> coefficients(m_coefficients.size());
        std::transform
                (
                        coefficients.begin(),
                        coefficients.end(),
                        coefficients.begin(),
                        [](Coefficient const& coef) { return - coef; }
                );
        return PackedPolynomial<Param_Ts...>(coefficients);
    }

    template<typename... Param_Ts>
    CANT_INLINE
    PackedPolynomial<Param_Ts...>&
    PackedPolynomial<Param_Ts...>::
    operator+(PackedPolynomial const& other)
    {
        return add(other);
    }

    template<typename... Param_Ts>
    CANT_INLINE
    PackedPolynomial<Param_Ts...>&
    PackedPolynomial<Param_Ts...>::
    operator-(PackedPolynomial const& other)
    {
        return substract(other);
    }

    template<typename... Param_Ts>
    CANT_INLINE
    PackedPolynomial<Param_Ts...>&
    PackedPolynomial<Param_Ts...>::
    operator*(PackedPolynomial const& other)
    {
        return multiply(other);
    }

    template<typename... Param_Ts>
    void PackedPolynomial<Param_Ts...>::
    applyCoefficientwise(PackedPolynomial const& other, CoefficientwiseOp op)
    {
        const size_u d1 = this->getDegree();
        const size_u d2 = other.getDegree();

        // resizing vector of coefficients to fit new size.
        // we now that the new degree will be inferior.
        m_coefficients.resize(std::max(d1, d2));
        bool degreeFound = false;
        size_u index = m_coefficients.size();
        size_u degree = 0;
        std::transform
                (
                        other.m_coefficients.rbegin(),
                        other.m_coefficients.rend(),
                        this->m_coefficients.rbegin(),
                        this->m_coefficients.rbegin(),
                        [&degree, &index, &degreeFound, op](Coefficient const& coef1, Coefficient const& coef2)
                        {
                            const Coefficient res = op(coef1, coef2);
                            if (!degreeFound)
                            {
                                if (res != static_cast<Coefficient>(0))
                                {
                                    degree = index;
                                    degreeFound = true;
                                }
                                --index;
                            }
                            return res;
                        }
                );
        m_degree = degree;
    }

CANTINA_END_MATHS_NAMESPACE
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_PACKEDPOLYNOMIAL_INL
