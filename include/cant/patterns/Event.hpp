//
// Created by binabik on 19/09/2020.
//

#ifndef CANTINA_PATTERN_EVENT_HPP
#define CANTINA_PATTERN_EVENT_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/common/traits.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERNS_NAMESPACE_BEGIN

template <typename Arg_T, typename... Args>
class EventListener;

template <typename Arg_T, typename... Args>
class Event
{
   public:
    /** -- typedef -- **/
    typedef EventListener<Arg_T, Args...> Listener;

    /** -- methods -- **/
    Event();
    bool
      addListener(ShPtr<Listener>& listener);
    bool
      removeListener(ShPtr<Listener> const& listener);
    bool
    removeListener(Listener const* listener);
    /**
     * @brief Calls actions for every listener.
     * @param action: callback to be called on notification.
     * @return true if successful, false if not.
     */
    CANT_INLINE
    void
      notify(Arg_T arg, Args ... args);

   private:
    /** -- fields -- **/
    Stream<ShPtr<Listener>> m_listeners;
};

template <typename Arg_T, typename... Args>
class EventListener
{
   public:
    /** -- typedefs -- **/
    typedef Event<Arg_T, Args...>       E;

    /** -- methods -- **/
    EventListener();
    virtual ~EventListener();

   private:
    /** -- methods -- **/
    void
      unsubscribeFromAllEvents();

    void
      addEvent(E * event);
    void
      removeEvent(E const * event);

    virtual
    void
      invoke(Arg_T , Args ...) = 0;

    /** -- fields -- **/

    Stream<E *> m_events;

    friend class Event<Arg_T, Args...>;
};

template <class C, typename Arg_T, typename... Args>
class SelfEventListener : public EventListener<Arg_T, Args...>
{
   public:
    /** -- typedefs -- **/
    typedef void(C::*Method)(Arg_T , Args...);

    /** -- methods -- **/
    // Conversion
    CANT_EXPLICIT
    SelfEventListener(C * a_this, Method method);

   private:
    /** -- methods -- **/
    void
      invoke(Arg_T , Args ...) override;

    /** -- fields -- **/
    // dangerous,
    // We have to make sure that this listener's lifecycle is managed by the owner.
    C * const m_this;
    const Method m_method;
};

template <typename Arg_T, typename... Args>
class StaticEventListener : public EventListener<Arg_T, Args...>
    {
       public:
        /** -- typedefs -- **/
        typedef void(Action)(Arg_T, Args...);

        /** -- methods -- **/

       private:
        /** -- methods -- **/
        void
        invoke(Arg_T , Args ...) override;

        /** -- fields -- **/
        UPtr<Action> m_action;

    };

    CANTINA_PATTERNS_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/patterns/Event.inl>

#endif  // CANTINA_PATTERN_EVENT_HPP
