// Copyright (c) 2020 - 2021 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "iceoryx_hoofs/posix_wrapper/thread.hpp"
#include "test.hpp"

namespace
{
using namespace ::testing;
using namespace iox::posix;
using namespace iox::cxx;

class Thread_test : public Test
{
  public:
    Thread_test()
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

    ~Thread_test()
    {
    }

    uint32_t test_function(const uint32_t val)
    {
        return val;
    }

    optional<Thread> sut;
};

TEST_F(Thread_test, CreateThread)
{
    constexpr uint64_t MY_FAVORITE_UINT = 13;
    function<void()> callable = [&] { EXPECT_THAT(test_function(MY_FAVORITE_UINT), Eq(MY_FAVORITE_UINT)); };
    ASSERT_FALSE(ThreadBuilder().create(sut, callable).has_error());
}

TEST_F(Thread_test, CreateThreadWithEmptyCallable)
{
    function<void()> callable;
    auto result = ThreadBuilder().create(sut, callable);
    ASSERT_TRUE(result.has_error());
    EXPECT_THAT(result.get_error(), Eq(ThreadError::EMPTY_CALLABLE));
}

TEST_F(Thread_test, SetAndGetWithEmptyThreadNameIsWorking)
{
    function<void()> callable = []() {};
    ASSERT_FALSE(ThreadBuilder().create(sut, callable).has_error());
    ThreadName_t emptyString = "";

    sut->setThreadName(emptyString);
    auto getResult = sut->getThreadName();

    EXPECT_THAT(getResult, StrEq(emptyString));
}

TEST_F(Thread_test, SetAndGetWithThreadNameCapacityIsWorking)
{
    function<void()> callable = []() {};
    ASSERT_FALSE(ThreadBuilder().create(sut, callable).has_error());
    ThreadName_t stringEqualToThreadNameCapacitiy = "123456789ABCDEF";
    EXPECT_THAT(stringEqualToThreadNameCapacitiy.capacity(), Eq(stringEqualToThreadNameCapacitiy.size()));

    sut->setThreadName(stringEqualToThreadNameCapacitiy);
    auto getResult = sut->getThreadName();

    EXPECT_THAT(getResult, StrEq(stringEqualToThreadNameCapacitiy));
}

TEST_F(Thread_test, SetAndGetSmallStringIsWorking)
{
    function<void()> callable = []() {};
    ASSERT_FALSE(ThreadBuilder().create(sut, callable).has_error());
    char stringShorterThanThreadNameCapacitiy[] = "I'm short";

    sut->setThreadName(stringShorterThanThreadNameCapacitiy);
    auto getResult = sut->getThreadName();

    EXPECT_THAT(getResult, StrEq(stringShorterThanThreadNameCapacitiy));
}
} // namespace
