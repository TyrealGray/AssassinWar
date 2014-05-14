#pragma once
#include <gtest/gtest.h>

#include "PixelCoordinateTransfer.h"

TEST(PixelCoordinateTransferTest, toGridTest)
{
    int iPixel = 0;
    unsigned int uiGrid = PixelCoordinateTransfer::toGrid(iPixel);

    EXPECT_EQ(1, uiGrid);

    iPixel = 1;

    uiGrid = PixelCoordinateTransfer::toGrid(iPixel);

    EXPECT_EQ(1, uiGrid);

    iPixel = 15;

    uiGrid = PixelCoordinateTransfer::toGrid(iPixel);

    EXPECT_EQ(2, uiGrid);
}

TEST(PixelCoordinateTransferTest, toPixelTest)
{
    unsigned int uiGrid = 1;
    int iPixel  = PixelCoordinateTransfer::toPixel(uiGrid);

    EXPECT_EQ(0, iPixel);

    uiGrid = 2;
    iPixel  = PixelCoordinateTransfer::toPixel(uiGrid);

    EXPECT_EQ(15, iPixel);

    uiGrid = 61;
    iPixel  = PixelCoordinateTransfer::toPixel(uiGrid);

    EXPECT_EQ(900, iPixel);
}