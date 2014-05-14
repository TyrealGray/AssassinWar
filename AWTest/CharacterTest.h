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

    for(int index = 0; index < 14 ; ++index)
    {
        person.updateNextPosition();
    }

    EXPECT_EQ(19, person.getCurrentGridX());

    EXPECT_EQ(19, person.getCurrentGridY());
}