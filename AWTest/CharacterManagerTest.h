#pragma once
#include <gtest/gtest.h>

#include "CharacterManager.h"

TEST(CharacterManagerTest, getNumberOfCharacterTest)
{
    CharacterManager manager;

    EXPECT_EQ(0, manager.getNumberOfCharacter());

    manager.addPlayer("test1");

    EXPECT_EQ(1, manager.getNumberOfCharacter());

    manager.addCivilian();

    EXPECT_EQ(2, manager.getNumberOfCharacter());

    manager.addPlayer("test1");

    EXPECT_EQ(2, manager.getNumberOfCharacter());

    manager.addPlayer("test2");

    EXPECT_EQ(3, manager.getNumberOfCharacter());
}