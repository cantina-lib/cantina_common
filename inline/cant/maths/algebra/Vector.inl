
#ifndef CANTINA_MATHS_VECTOR_INL
#define CANTINA_MATHS_VECTOR_INL

#pragma once

#include <algorithm>
#include <numeric>

#include <cant/maths/approx.hpp>

#include <cant/common/CantinaException.hpp>

#include <cant/common/macro.hpp>
#include <cant/maths/algebra/Vector.hpp>

CANTINA_MATHS_NAMESPACE_BEGIN

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR
  Vector<Dim_T, dim>::Vector()
    : m_fields()
{}

template <typename Dim_T, size_u dim>
template <typename T, typename... Ts>
CANT_CONSTEXPR
  Vector<Dim_T, dim>::Vector(T t, Ts... ts)
    : m_fields({t, ts...})
{
    static_assert(std::is_same_v<T, Dim_T>);
    static_assert(sizeof...(Ts) == dim - 1, "Wrong number of arguments there, mate.");
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Dim_T
  Vector<Dim_T, dim>::getDistance(Vector const & other) const
{
    return (other - *this).getNorm();
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Dim_T
  Vector<Dim_T, dim>::getNorm() const
{
    return std::sqrt(this->dot(*this));
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Dim_T
  Vector<Dim_T, dim>::dot(Vector const & other) const
{
    return std::inner_product(this->m_fields.begin(),
                              this->m_fields.end(),
                              other.m_fields.begin(),
                              static_cast<Dim_T>(0.),
                              std::plus<Dim_T>(),
                              std::multiplies<Dim_T>());
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
  Vector<Dim_T, dim>::operator-(Vector const & other) const
{
    Vector vec{};
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   vec.m_fields.begin(),
                   [](Dim_T x1, Dim_T x2) -> Dim_T { return x1 - x2; });
    return vec;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
  Vector<Dim_T, dim>::operator+(Vector const & other) const
{
    Vector vec{};
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   vec.m_fields.begin(),
                   [](Dim_T x1, Dim_T x2) -> Dim_T { return x1 + x2; });
    return vec;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
  Vector<Dim_T, dim>::operator-() const
{
    Vector negated{};
    std::transform(
      this->m_fields.begin(), this->m_fields.end(), negated.m_fields.begin(), [](Dim_T x) -> Dim_T { return -x; });
    return negated;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
  Vector<Dim_T, dim>::operator*(Dim_T scalar) const
{
    Vector vec{};
    std::transform(
      this->m_fields.begin(), this->m_fields.end(), vec.m_fields.begin(), [scalar](Dim_T x) { return x * scalar; });
    return vec;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
  Vector<Dim_T, dim>::operator/(Dim_T scalar) const
{
    if (approx<Dim_T>::equal(scalar, static_cast<Dim_T>(0.)))
    {
        throw CANTINA_EXCEPTION("division by zero.");
    }
    return this->operator*(1 / scalar);
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
               Vector<Dim_T, dim>::getNormalised() const
{
    Dim_T norm = getNorm();
    CANTINA_ASSERT(!approx<Dim_T>::equal(norm, static_cast<Dim_T>(0.)), "Noooo");
    if (approx<Dim_T>::equal(norm, static_cast<Dim_T>(0.)))
    {
        throw CANTINA_EXCEPTION("Trying to normalise a null vector!");
    }
    return operator/(norm);
}

template <typename Dim_T, size_u dim>
template <size_u i>
CANT_CONSTEXPR Dim_T
  Vector<Dim_T, dim>::get() const
{
    static_assert(i < dim);
    return m_fields.at(i);
}

template <typename Dim_T, size_u dim>
template <size_u i>
CANT_CONSTEXPR void
  Vector<Dim_T, dim>::set(Dim_T val)
{
    static_assert(i < dim);
    m_fields.at(i) = val;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR const Array<Dim_T, dim> &
Vector<Dim_T, dim>::getArray() const
{
    return m_fields;
}

    template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Dim_T
  Vector<Dim_T, dim>::get(size_u i) const
{
    // static_assert(i < dim);
    return m_fields.at(i);
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR void
  Vector<Dim_T, dim>::set(size_u i, Dim_T val)
{
    // static_assert(i < dim);
    m_fields.at(i) = val;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim> &
  Vector<Dim_T, dim>::operator+=(Vector const & other)
{
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   this->m_fields.begin(),
                   [](Dim_T x1, Dim_T x2) -> Dim_T { return x1 + x2; });
    return *this;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim> &
  Vector<Dim_T, dim>::operator-=(Vector const & other)
{
    std::transform(this->m_fields.begin(),
                   this->m_fields.end(),
                   other.m_fields.begin(),
                   this->m_fields.begin(),
                   [](Dim_T x1, Dim_T x2) -> Dim_T { return x1 - x2; });
    return *this;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim> &
  Vector<Dim_T, dim>::operator*=(Dim_T scalar)
{
    std::transform(m_fields.begin(), m_fields.end(), m_fields.begin(), [scalar](Dim_T x) { return x * scalar; });
    return *this;
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim> &
  Vector<Dim_T, dim>::operator/=(Dim_T scalar)
{
    if (approx<Dim_T>::equal(scalar, static_cast<Dim_T>(0.)))
    {
        throw CANTINA_EXCEPTION("division by zero.");
    }
    return this->operator*=(static_cast<Dim_T>(1) / scalar);
}

template <typename Dim_T, size_u dim>
CANT_CONSTEXPR Vector<Dim_T, dim>
               Vector<Dim_T, dim>::fill(Dim_T t)
{
    Vector v{};
    std::fill(v.m_fields.begin(), v.m_fields.end(), t);
    return v;
}
CANTINA_MATHS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_MATHS_VECTOR_INL