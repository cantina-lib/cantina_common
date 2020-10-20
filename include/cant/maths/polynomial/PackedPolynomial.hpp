//
// Created by binabik on 13/09/2020.
//

#ifndef CANTINA_TILDE_PACKEDPOLYNOMIAL_HPP
#define CANTINA_TILDE_PACKEDPOLYNOMIAL_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_BEGIN_MATHS_NAMESPACE
    template <typename... Param_Ts>
    class PackedPolynomial
    {
    public:
        /** -- internal structs -- **/
        typedef Tuple<Param_Ts...> Coefficient;
        typedef std::binary_function<const Coefficient&, const Coefficient&, Coefficient> CoefficientwiseOp;

        /** -- methods -- **/
        CANT_EXPLICIT PackedPolynomial(const Stream<Coefficient>& coefficients);
        PackedPolynomial(std::initializer_list<Coefficient> ls);

        // operators
        PackedPolynomial operator-() const;

        PackedPolynomial& operator+(const PackedPolynomial& other);
        PackedPolynomial& operator-(const PackedPolynomial& other);

        PackedPolynomial& operator*(const PackedPolynomial& other);
        PackedPolynomial& operator/(const PackedPolynomial& other) = delete;

        // polynomial stuff
        CANT_NODISCARD size_u getDegree() const;
    private:
        /** -- methods -- **/
        void negate();

        void add      (const PackedPolynomial& other);
        void substract(const PackedPolynomial& other);
        void multiply (const PackedPolynomial& other);

        void multiply (const Coefficient& coef);

        void fitToDegree();

        // static
        CANT_NODISCARD static size_u computeDegree(const Stream<Coefficient>& coefficients);

        void applyCoefficientwise(
                const PackedPolynomial& other,
                CoefficientwiseOp op
        );

        /** -- fields -- **/
        // stored in sorta little-endian order (lower terms first)
        // more natural to shrink this way (for filled-up polynomials, anyway.)
        Stream<Coefficient> m_coefficients;
        // degree's cached.
        size_u m_degree;
    };
CANTINA_END_MATHS_NAMESPACE
#include <cant/common/undef_macro.hpp>

#include <cant/maths/polynomial/PackedPolynomial.inl>

#endif //CANTINA_TILDE_PACKEDPOLYNOMIAL_HPP
