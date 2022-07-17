#pragma once

#include <cstddef>
#include <concepts>

namespace bavil::core
{

	class system_manager;

	class system_interface
	{
	public:
		virtual ~system_interface() {}

		virtual void initialize(system_manager& _system_manager) = 0;
		virtual void finalize() = 0;
		virtual size_t get_system_id() const = 0;
	};

	template <class T>
	concept system_concepts = requires(T system)
	{
		{
			T::GetSystemId()
		} -> std::convertible_to<size_t>;

		std::derived_from<T, system_interface>;
	};

}  // namespace bavil::core
