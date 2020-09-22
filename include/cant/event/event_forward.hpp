
#ifndef CANTINA_EVENT_EVENT_FORWARD_HPP
#define CANTINA_EVENT_EVENT_FORWARD_HPP

#pragma once

#include <cant/common/macro.hpp>
CANTINA_EVENT_NAMESPACE_BEGIN

    class Lecturer;
    template <class DerivedLecturerInterface>
    class Listener;


    template <class DerivedListener>
    class LecturerTrait;
    template <class DerivedLecturer>
    class ListenerTrait;

    /** -- structs -- **/
    template <class C>
    using Ptr = C*;
    template <class C>
    using CPtr = C const *;

CANTINA_EVENT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_EVENT_EVENT_FORWARD_HPP