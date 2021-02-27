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
class Event
{
   public:
    /** -- typedef -- **/
    typedef typename EventListener<Arg_T, Args...>::ListenerToken ListenerToken;

    /** -- methods -- **/
    Event();
    ~Event();
    bool
      addListener(ShPtr<ListenerToken> & listenerToken);
    bool
      removeListener(const ShPtr<ListenerToken> & listenerToken);
    /**
     * @brief Calls actions for every listener.
     * @param action: callback to be called on notification.
     * @return true if successful, false if not.
     */
    CANT_INLINE
    void
      invoke(Arg_T, Args...);

   private:
    /** -- structs -- **/
    /*
     * Note:
     * (C++17) public inheritance from std::enable_shared_from_this is compulsory.
     * see: https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
     * Otherwise you'll get a null weak_ptr when trying to construct a shared_ptr.
     */
    class EventToken : public std::enable_shared_from_this<EventToken>
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT EventToken(Event * event);
        CANT_INLINE bool removeListener(ShPtr<ListenerToken> &listenerToken);
    private:
        /** -- methods -- **/
        Event * const m_event;
    };

    /** -- fields -- **/
    ShPtr<EventToken> m_token;
    Stream<ShPtr<ListenerToken>> m_listenerTokens;

    /** -- friends -- **/
    // only for definition of EventToken.
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
    /** -- typedefs -- **/
    typedef typename Event<Arg_T, Args...>::EventToken EventToken;

    /** -- methods -- **/
    EventListener();
    virtual ~EventListener();

   private:
    /** -- structs -- **/
    class ListenerToken : public std::enable_shared_from_this<ListenerToken>
    {
       public:
        /** -- methods -- **/
        CANT_EXPLICIT ListenerToken(EventListener * listener);
        CANT_INLINE void update(Arg_T, Args...);
       private:
        /** -- fields -- **/
        EventListener * const m_listener;
    };

    /** -- methods -- **/

    void
      unsubscribeFromAllEvents();

    void
      addEvent(ShPtr<EventToken> & eventToken);
    void
      removeEvent(ShPtr<EventToken> const & eventToken);

    virtual void
      update(Arg_T, Args...)
      = 0;

    /** -- fields -- **/
    ShPtr<ListenerToken> m_token;
    Stream<ShPtr<EventToken>> m_eventTokens;

    /** -- friends -- **/
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
