#pragma once

#include <functional>
#include <unordered_map>
#include <type_traits>
#include <concepts>
#include <compare>

namespace bavil
{
	/**
	 * デリゲートハンドル
	 */
	struct DelegateHandle
	{
		size_t handle;

		static DelegateHandle Generated() noexcept
		{
			static size_t s_id = 0;
			return {++s_id};
		}

		constexpr DelegateHandle(size_t _handle) noexcept
		    : handle(_handle)
		{
		}
		constexpr DelegateHandle() noexcept
		    : DelegateHandle(0)
		{
		}

		auto operator<=>(const DelegateHandle&) const = default;
	};

} // namespace bavil

namespace std
{
	template<>
	struct hash<bavil::DelegateHandle>
	{
		size_t operator()(const bavil::DelegateHandle& _handle) const
		{
			return std::hash<size_t>()(_handle.handle);
		}
	};
} // namespace std

namespace bavil
{

	template<class T>
	class MulticastDelegate;

	template<class... Args>
	class MulticastDelegate<void(Args...)>
	{
		using FunctionType = std::function<void(Args...)>;

	public:
		/**
	 * @brief デリゲートを登録する
	 * @tparam Func デリゲート型
	 * @param func デリゲート
	 * @return 
	*/
		template<class Func>
			requires(std::constructible_from<FunctionType, Func>)
		DelegateHandle add(Func func)
		{
			DelegateHandle handle = DelegateHandle::Generated();

			m_events.emplace(handle, FunctionType(func));
			// m_events

			return handle;
		}

		/**
	 * @brief デリゲートを削除する
	 * @param _handle ハンドルの型
	*/
		void remove(DelegateHandle _handle)
		{
			m_events.erase(_handle);
		}

		bool is_valid(DelegateHandle _handle) const
		{
			auto result = m_events.find(_handle);
			return result != m_events.end();
		}

		bool has_delegates() const
		{
			return !m_events.empty();
		}

		/**
	 * @brief イベントの呼び出し
	 * @param ...args 
	*/
		void broadcast(Args... args)
		{
			for ( auto& [handle, target] : m_events )
			{
				target(std::move(args)...);
			}
		}

		/**
	 * @brief 登録したイベントをクリアする
	*/
		void clear()
		{
			m_events.clear();
		}

	private:
		std::unordered_map<DelegateHandle, FunctionType> m_events;
	};

} // namespace bavil
