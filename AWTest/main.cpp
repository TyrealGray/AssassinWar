#include <gtest/gtest.h>
#include <QtCore/QCoreApplication>

#include "CommentLib.h"
#include "CommentGTestLib.h"

#include "CharacterTest.h"
#include "UnderGridTest.h"
#include "PixelCoordinateTransferTest.h"


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    system("pause");
    return result;
}