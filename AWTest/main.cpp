#include <gtest/gtest.h>
#include <QtCore/QCoreApplication>

#include "CommentLib.h"
#include "CommentGTestLib.h"

#include "UnderGrid.h"

TEST(UnderGridTest, setSizeTest)
{
    UnderGrid underGrid;
    EXPECT_EQ(true, underGrid.setSize(10, 10));
    EXPECT_EQ(false, underGrid.setSize(10, 12));
    EXPECT_EQ(false, underGrid.setSize(10, 10));
}

TEST(UnderGridTest, getGridTest)
{
    UnderGrid underGrid;
    underGrid.setSize(10, 10);

    EXPECT_EQ(3, underGrid.getGrid(3, 4)->getX());
    EXPECT_EQ(4, underGrid.getGrid(3, 4)->getY());

    underGrid.disableGrids(5, 5, 10, 10);

    EXPECT_EQ(true, underGrid.getGrid(3, 4)->isAble());
    EXPECT_EQ(false, underGrid.getGrid(8, 8)->isAble());

}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}