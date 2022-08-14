#pragma once

#include <cstddef>
#include <concepts>

namespace bavil::core
{

	class SystemManager;

	class SystemInterface
	{
	public:
		virtual ~SystemInterface() {}

		virtual void initialize(SystemManager &_system_manager) = 0;
		virtual void finalize() = 0;
		virtual size_t get_system_id() const = 0;
	};

	template <class T>
	concept SystemConcepts = requires(T system)
	{
		{
			T::GetSystemId()
			} -> std::convertible_to<size_t>;

		std::derived_from<T, SystemInterface>;
	};

} // namespace bavil::core
