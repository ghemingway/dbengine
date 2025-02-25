// @author G. Hemingway, copyright 2025 - All rights reserved
#include <gtest/gtest.h>

/**
 *  Test driver. Through its associated tests, this driver aims to exercise all
 *  functionality of the classes in a clear and consistent way so that
 *  the class's interface and implementation can be easily inferred.
 */
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
