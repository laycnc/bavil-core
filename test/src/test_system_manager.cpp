#include <gtest/gtest.h>
#include <core/bavil_system.h>
#include <core/bavil_system_manager.h>

// TESTマクロを使う場合

namespace
{

	class test_system : public bavil::core::system_interface
	{
	public:
		virtual void initialize(
			bavil::core::system_manager& _system_manager) override
		{
			//
		}

		virtual void finalize() override
		{
			//
		}
		virtual size_t get_system_id() const override
		{
			return GetSystemId();
		}

		static size_t GetSystemId()
		{
			return bavil::core::system_manager::GetneratedSystemId<test_system>();
		}
	};

}

// 第1引数がテストケース名、第2引数がテスト名
TEST(SystemManagerTest, Function1Test) {
	//

	bavil::core::system_manager system_manager = {};

	test_system* result = system_manager.get_system<test_system>();

	ASSERT_EQ(result != nullptr, true);

	ASSERT_EQ(result->get_system_id(), test_system::GetSystemId());

}
