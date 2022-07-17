#pragma once

#include <functional>
#include <unordered_map>
#include <type_traits>
#include <concepts>
#include <compare>

namespace bavil
{

  struct delegate_handle
  {
	size_t handle;

	static delegate_handle Generated()
	{
	  static size_t s_id = 0;
	  return {++s_id};
	}

	constexpr delegate_handle(size_t _handle) noexcept : handle(_handle) {}

	auto operator<=>(const delegate_handle&) const = default;
  };

}  // namespace bavil

namespace std
{
  template <>
  struct hash<bavil::delegate_handle>
  {
	size_t operator()(const bavil::delegate_handle& _handle) const
	{
	  return std::hash<size_t>()(_handle.handle);
	}
  };
}  // namespace std

namespace bavil
{

  template <class T>
  class multicast_delegate;

  template <class... Args>
  class multicast_delegate<void(Args...)>
  {
	using function_t = std::function<void(Args...)>;

   public:
	template <class Func>
	requires(std::constructible_from<function_t, Func>) delegate_handle
	    add(Func func)
	{
	  delegate_handle handle = delegate_handle::Generated();

	  m_events.emplace(handle, function_t(func));
	  // m_events

	  return handle;
	}

	void remove(delegate_handle _handle)
	{
	  m_events.erase(_handle);
	}

	void broadcast(Args... args)
	{
	  for (auto& [handle, target] : m_events)
		{
		  target(std::move(args)...);
		}
	}

	void clear()
	{
	  m_events.clear();
	}

   private:
	std::unordered_map<delegate_handle, function_t> m_events;
  };

}  // namespace bavil
