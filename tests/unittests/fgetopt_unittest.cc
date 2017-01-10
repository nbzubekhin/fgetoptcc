#include "../../src/fgetopt.h"
#include "gtest/gtest.h"

// We test the GETOPT class (parser command line).

// Tests the default c'tor.
TEST(GETOPT, DefaultConstructor) {
    const GETOPT d;

    // <TechnicalDetails>
    //
    // ...
    //
    // </TechnicalDetails>

    ASSERT_TRUE(true);
}

// Tests the copy c'tor.
TEST(GETOPT, CopyConstructor) {
    GETOPT opt_obj1;
    GETOPT opt_obj2 = opt_obj1;

    // <TechnicalDetails>
    //
    // ...
    //
    // </TechnicalDetails>

    ASSERT_TRUE(true);
}

TEST(GETOPT, ParsingHelp) {

    // <TechnicalDetails>
    //
    // ...
    //
    // </TechnicalDetails>

    char *argv_0[] = {
        "program-name"
        "-a",
        "-h",
        "-m"
    };

    int                 argc_0 = sizeof(argv_0)/sizeof(char *);

    GETOPT              obj_getopt;
    OutParam_t          *param;

    /** Parse arguments */
    for ( ; ; ) {
        param = obj_getopt.GetOpt(argc_0, argv_0, (char *)"-ha:m::");

        if (param->c == -1)
            break;

        switch (param->c) {
        case 'h':
            EXPECT_TRUE(true);
            return;
            break;
        }
    }

    EXPECT_FALSE(true);
}

