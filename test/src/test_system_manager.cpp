#include <gtest/gtest.h>
#include <core/bavil_system.h>
#include <core/bavil_system_manager.h>

// TESTマクロを使う場合

namespace
{

	class TestSystem : public bavil::core::SystemBase<TestSystem>
	{
	public:
		virtual void initialize(
			bavil::core::SystemManager& _system_manager) override
		{
			//
		}

		virtual void finalize() override
		{
			//
		}
	};

}

// 第1引数がテストケース名、第2引数がテスト名
TEST(SystemManagerTest, Function1Test) {
	//

	bavil::core::SystemManager system_manager = {};

	TestSystem* result = system_manager.get_system<TestSystem>();

	auto* f = (bavil::core::SystemBase<TestSystem>*)result;

	ASSERT_EQ(result != nullptr, true);

	ASSERT_EQ(result->get_system_id(), TestSystem::GetSystemId());

}
