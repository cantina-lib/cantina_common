
#ifndef CANTINA_MATHS_VECTOR_INL
#define CANTINA_MATHS_VECTOR_INL

#pragma once

#include <algorithm>
#include <numeric>

#include <cant/maths/approx.hpp>
#include <cant/maths/algo.hpp>

#include <cant/common/CantinaException.hpp>

#include <cant/common/macro.hpp>
CANTINA_MATHS_NAMESPACE_BEGIN

template <size_u dim, typename T>
CANT_CONSTEXPR
  Vector<dim, T>::Vector()
    : m_fields()
{}

template <size_u dim, typename T>
template <typename U, typename... Us>
CANT_CONSTEXPR
  Vector<dim, T>::Vector(U u, Us... us)
    : m_fields({u, us...})
{
    static_assert(std::is_convertible_v<U, T>);
    static_assert(sizeof...(Us) == dim - 1, "Wrong number of arguments there, mate.");
}

template <size_u dim, typename T>
template <type_i order>
CANT_CONSTEXPR T
  Vector<dim, T>::getDistance(Vector const & other) const
{
    return (other - *this).template getNorm<order>();
}

template <size_u dim, typename T>
template <type_i order>
CANT_CONSTEXPR T
  Vector<dim, T>::getNorm() const
{
    return algo<T>::template norm<order>(m_fields.begin(), m_fields.end());
}

template <size_u dim, typename T>
CANT_CONSTEXPR T
  Vector<dim, T>::dot(Vector const & other) const
{
    return std::inner_product(this->m_fields.begin(),
                              this->m_fields.end(),
                              other.m_fields.begin(),
                              static_cast<T>(0.),
                              std::plus<T>(),
                              std::multiplies<T>());
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T>
  Vector<dim, T>::operator-(Vector const & other) const
{
    Vector vec{};
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   vec.m_fields.begin(),
                   [](T x1, T x2) -> T { return x1 - x2; });
    return vec;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T>
  Vector<dim, T>::operator+(Vector const & other) const
{
    Vector vec{};
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   vec.m_fields.begin(),
                   [](T x1, T x2) -> T { return x1 + x2; });
    return vec;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T>
  Vector<dim, T>::operator-() const
{
    Vector negated{};
    std::transform(
      this->m_fields.begin(), this->m_fields.end(), negated.m_fields.begin(), [](T x) -> T { return -x; });
    return negated;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T>
  Vector<dim, T>::operator*(T scalar) const
{
    Vector vec{};
    std::transform(
      this->m_fields.begin(), this->m_fields.end(), vec.m_fields.begin(), [scalar](T x) { return x * scalar; });
    return vec;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T>
  Vector<dim, T>::operator/(T scalar) const
{
    if (approx<T>::equal(scalar, static_cast<T>(0.)))
    {
        throw CANTINA_EXCEPTION("division by zero.");
    }
    return this->operator*(1 / scalar);
}

template <size_u dim, typename T>
template <type_i order>
CANT_CONSTEXPR Vector<dim, T>
               Vector<dim, T>::getNormalised() const
{
    T norm = getNorm<order>();
    CANTINA_ASSERT(!approx<T>::equal(norm, static_cast<T>(0.)), "Noooo");
    if (approx<T>::equal(norm, static_cast<T>(0.)))
    {
        throw CANTINA_EXCEPTION("Trying to normalise a null vector!");
    }
    return operator/(norm);
}

template <size_u dim, typename T>
template <size_u i>
CANT_CONSTEXPR T
  Vector<dim, T>::get() const
{
    static_assert(i < dim);
    return m_fields.at(i);
}

template <size_u dim, typename T>
template <size_u i>
CANT_CONSTEXPR void
  Vector<dim, T>::set(T val)
{
    static_assert(i < dim);
    m_fields.at(i) = val;
}

template <size_u dim, typename T>
CANT_CONSTEXPR const Array<T, dim> &
Vector<dim, T>::getArray() const
{
    return m_fields;
}

    template <size_u dim, typename T>
CANT_CONSTEXPR T
  Vector<dim, T>::get(size_u i) const
{
    // static_assert(i < dim);
    return m_fields.at(i);
}

template <size_u dim, typename T>
CANT_CONSTEXPR void
  Vector<dim, T>::set(size_u i, T val)
{
    // static_assert(i < dim);
    m_fields.at(i) = val;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T> &
  Vector<dim, T>::operator+=(Vector const & other)
{
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   this->m_fields.begin(),
                   [](T x1, T x2) -> T { return x1 + x2; });
    return *this;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T> &
  Vector<dim, T>::operator-=(Vector const & other)
{
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   this->m_fields.begin(),
                   [](T x1, T x2) -> T { return x1 - x2; });
    return *this;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T> &
  Vector<dim, T>::operator*=(T scalar)
{
    std::transform(m_fields.begin(), m_fields.end(), m_fields.begin(), [scalar](T x) { return x * scalar; });
    return *this;
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T> &
  Vector<dim, T>::operator/=(T scalar)
{
    if (approx<T>::equal(scalar, static_cast<T>(0.)))
    {
        throw CANTINA_EXCEPTION("division by zero.");
    }
    return this->operator*=(static_cast<T>(1) / scalar);
}

template <size_u dim, typename T>
CANT_CONSTEXPR Vector<dim, T>
               Vector<dim, T>::fill(T t)
{
    Vector v{};
    std::fill(v.m_fields.begin(), v.m_fields.end(), t);
    return v;
}
CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_MATHS_VECTOR_INL