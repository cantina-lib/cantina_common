//
// Created by binabik on 19/09/2020.
//

#ifndef CANTINA_PATTERN_EVENT_HPP
#define CANTINA_PATTERN_EVENT_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/common/traits.hpp>

#include <cant/common/macro.hpp>
CANTINA_PATTERN_NAMESPACE_BEGIN

template <typename Arg_T, typename... Args>
class EventListener;
template <typename Arg_T, typename... Args>
class Event;

namespace
{
    template <typename Arg_T, typename... Args>
    class ListenerToken;

    /*
     * Note:
     * (C++17) public inheritance from std::enable_shared_from_this is compulsory.
     * see: https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
     * Otherwise you'll get a null weak_ptr when trying to construct a shared_ptr.
     */
    template <typename Arg_T, typename... Args>
    class EventToken : public std::enable_shared_from_this<EventToken<Arg_T, Args...>>
    {
       public:
        /** -- methods -- **/
        CANT_EXPLICIT
          EventToken(Event<Arg_T, Args...> * event);

        CANT_INLINE bool
          removeListener(ShPtr<ListenerToken<Arg_T, Args...>> & listenerToken);

       private:
        /** -- methods -- **/
        Event<Arg_T, Args...> * const m_event;
    };

    template <typename Arg_T, typename... Args>
    class ListenerToken : public std::enable_shared_from_this<ListenerToken<Arg_T, Args...>>
    {
       public:
        /** -- methods -- **/
        CANT_EXPLICIT
          ListenerToken(EventListener<Arg_T, Args...> * listener);

        CANT_INLINE void
          update(Arg_T, Args...);

        CANT_INLINE void
          addEvent(ShPtr<EventToken<Arg_T, Args...>> & eventToken);
        CANT_INLINE void
          removeEvent(ShPtr<EventToken<Arg_T, Args...>> const & eventToken);

       private:
        /** -- fields -- **/
        EventListener<Arg_T, Args...> * const m_listener;
    };
}  // namespace

template <typename Arg_T, typename... Args>
class Event
{
   public:
    /** -- methods -- **/
    Event();
    ~Event();

    bool
      addListener(ShPtr<EventListener<Arg_T, Args...>> & listener);
    bool
      removeListener(ShPtr<EventListener<Arg_T, Args...>> const & listener);

    /**
     * @brief Calls actions for every listener.
     * @param action: callback to be called on notification.
     * @return true if successful, false if not.
     */
    CANT_INLINE
    void
      invoke(Arg_T, Args...);

   private:
    /** -- methods -- **/
    bool
      addListener(ShPtr<ListenerToken<Arg_T, Args...>> & listenerToken);
    bool
      removeListener(ShPtr<ListenerToken<Arg_T, Args...>> const & listenerToken);

    /** -- fields -- **/
    ShPtr<EventToken<Arg_T, Args...>>            m_token;
    Stream<ShPtr<ListenerToken<Arg_T, Args...>>> m_listenerTokens;

    /** -- friends -- **/
    friend class EventToken<Arg_T, Args...>;
    friend class EventListener<Arg_T, Args...>;
};

/**
 * Event listener. SHOULD BE STORED IN A ShPtr!!
 * see: https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
 * @tparam Arg_T
 * @tparam Args
 */
template <typename Arg_T, typename... Args>
class EventListener
{
   public:
    /** -- methods -- **/
    EventListener();
    virtual ~EventListener();

   private:
    /** -- methods -- **/
    void
      unsubscribeFromAllEvents();

    void
      addEvent(ShPtr<EventToken<Arg_T, Args...>> & eventToken);
    void
      removeEvent(ShPtr<EventToken<Arg_T, Args...>> const & eventToken);

    virtual void
      update(Arg_T, Args...)
      = 0;

    /** -- fields -- **/
    ShPtr<ListenerToken<Arg_T, Args...>>      m_token;
    Stream<ShPtr<EventToken<Arg_T, Args...>>> m_eventTokens;

    /** -- friends -- **/
    friend class ListenerToken<Arg_T, Args...>;
    friend class Event<Arg_T, Args...>;
};

/**
 * An interface for classes needing to subscribe to Events
 * called by a specific class.
 * @tparam EventHolder_T A class aggregating Events.
 */
template <class EventHolder_T>
class EventSubscriber
{
   public:
    /** -- methods -- **/
    virtual ~EventSubscriber() = default;

    virtual void subscribe(EventHolder_T&) = 0;
    virtual void unsubscribe(EventHolder_T&) = 0;
};


template <class C, typename Arg_T, typename... Args>
class SelfEventListener : public EventListener<Arg_T, Args...>
{
   public:
    /** -- typedefs -- **/
    typedef void (C::*Method)(Arg_T, Args...);

    /** -- methods -- **/
    // Conversion
    CANT_EXPLICIT
    SelfEventListener(C * a_this, Method method);

   private:
    /** -- methods -- **/
    void
      update(Arg_T, Args...) override;

    /** -- fields -- **/
    // dangerous,
    // We have to make sure that this listener's lifecycle is managed by the owner.
    C * const    m_this;
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
      update(Arg_T, Args...) override;

    /** -- fields -- **/
    UPtr<Action> m_action;
};

CANTINA_PATTERN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pattern/Event.inl>

#endif  // CANTINA_PATTERN_EVENT_HPP
