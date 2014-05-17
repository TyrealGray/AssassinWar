#pragma once
#include <gtest/gtest.h>

#include "Character.h"

TEST(CharacterTest, setPositionTest)
{
    Character person(0, 10);
    person.setPosition(10, 10);

    person.goTo(20, 20);

    EXPECT_EQ(10, person.getCurrentGridX());

    EXPECT_EQ(10, person.getCurrentGridY());

    person.setPosition(20, 10);

    EXPECT_EQ(20, person.getCurrentGridX());

    EXPECT_EQ(10, person.getCurrentGridY());

    person.setPosition(20, 20);

    EXPECT_EQ(20, person.getCurrentGridX());

    EXPECT_EQ(20, person.getCurrentGridY());

    person.setPosition(1, 1);

    EXPECT_EQ(1, person.getCurrentGridX());

    EXPECT_EQ(1, person.getCurrentGridY());

}

TEST(CharacterTest, getNextPositionTest)
{
    Character person(0, 10);

    person.setPosition(11, 11);

    person.goTo(20, 20);

    person.updateNextPosition();

    person.updateNextPosition();

    EXPECT_EQ(12, person.getCurrentGridX());
}

TEST(CharacterTest, updatePositionTest)
{
    Character person(0, 10);
    person.setPosition(10, 10);

    person.goTo(20, 20);

    EXPECT_EQ(10, person.getCurrentGridX());

    EXPECT_EQ(10, person.getCurrentGridY());

    for(int index = 0; index < 14 ; ++index)
    {
        person.updateNextPosition();
    }

    EXPECT_EQ(19, person.getCurrentGridX());

    EXPECT_EQ(19, person.getCurrentGridY());
}