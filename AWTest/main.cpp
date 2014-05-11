#include <gtest/gtest.h>
#include <QtCore/QCoreApplication>

#include "CommentLib.h"
#include "CommentGTestLib.h"

#include "UnderGridTest.h"


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}