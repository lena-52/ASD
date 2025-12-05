#include <gtest/gtest.h>
#include "vector.h"


TEST(VectorIteratorTest, empty_vector_iteration) {
	TVector<int> vec;

	EXPECT_TRUE(vec.begin() == vec.end());

	int iteration_count = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		iteration_count++;
	}
	EXPECT_EQ(iteration_count, 0);
}

TEST(VectorIteratorTest, iterator_write_operations) {
	TVector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	int new_value = 10;
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		*it = new_value;
		new_value += 10;
	}

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 20);
	EXPECT_EQ(vec[2], 30);

	auto it = vec.begin();
	*it = 100;
	EXPECT_EQ(vec[0], 100);

	++it;
	*it = 200;
	EXPECT_EQ(vec[1], 200);
}

TEST(VectorIteratorTest, iterator_read_operations) {
	TVector<int> vec;
	vec.push_back(5);
	vec.push_back(10);
	vec.push_back(15);

	auto it = vec.begin();
	EXPECT_EQ(*it, 5);

	++it;
	EXPECT_EQ(*it, 10);

	it++;
	EXPECT_EQ(*it, 15);

	++it;
	EXPECT_TRUE(it == vec.end());
}