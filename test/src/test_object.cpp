#include <gtest/gtest.h>
#include <core/bavil_object_system.h>

// TESTマクロを使う場合

namespace
{
	const char* TEST_MESSAGE = "hogehoge";
}

class TestObject : public bavil::ObjectBase
{
public:
	const char* get_str() const
	{
		return m_str;
	}

protected:
	void construct() override
	{
		m_str = TEST_MESSAGE;
	}

	void destruct() override {}
private:
	const char* m_str = nullptr;
};

// 第1引数がテストケース名、第2引数がテスト名
TEST(ObjectTest, ObjectSystemTest)
{

	bavil::core::SystemManager system_manager = {};

	auto& object_system = bavil::ObjectSystem::Get();

	ASSERT_EQ(object_system.get_system_id(), bavil::ObjectSystem::GetSystemId());

	ASSERT_EQ(object_system.get_object_num(), 0);

	{
		auto test_object = object_system.create_object<TestObject>();

		ASSERT_EQ(object_system.get_object_num(), 1);

		ASSERT_EQ(test_object.get_reference_count(), 1);

		ASSERT_TRUE(test_object.get_object() != nullptr);

		ASSERT_STREQ(test_object->get_str(), TEST_MESSAGE);

		bavil::ObjectHandleBase temp = test_object;

		ASSERT_EQ(test_object.get_reference_count(), 2);

		ASSERT_TRUE(temp.is_valid());

		bavil::ObjectHandle<TestObject> temp2 = test_object;

		ASSERT_EQ(temp2.get_reference_count(), 3);

		ASSERT_TRUE(temp2.is_valid());

		bavil::ObjectHandleBase temp3 = std::move(test_object);

		ASSERT_TRUE(temp3.is_valid());

		ASSERT_EQ(temp3.get_reference_count(), 3);

		ASSERT_TRUE(!test_object.is_valid());
	}

	// スコープ外で破棄されているので0のはず
	ASSERT_EQ(object_system.get_object_num(), 0);

	int a = 0;
}
