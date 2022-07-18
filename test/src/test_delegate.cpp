#include <gtest/gtest.h>
#include <core/bavil_multicast_delegate.h>

// TESTマクロを使う場合

namespace
{
	const char* SEND_MESSAGE = "[hogehoge]";
}

// 第1引数がテストケース名、第2引数がテスト名
TEST(MulticastDelegateTest, Function1Test) {
	//

	bavil::multicast_delegate<void(const char* message)> events;

	ASSERT_EQ(events.has_delegates(), false);

	auto handle = events.add([](const char* _message)
		{
			ASSERT_STREQ(_message, SEND_MESSAGE);
		});

	ASSERT_EQ(events.has_delegates(), true);

	events.broadcast(SEND_MESSAGE);

	ASSERT_EQ(events.is_valid(handle), true);

	events.remove(handle);

	ASSERT_EQ(events.is_valid(handle), false);
	ASSERT_EQ(events.has_delegates(), false);

}
