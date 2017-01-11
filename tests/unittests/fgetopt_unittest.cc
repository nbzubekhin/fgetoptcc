/**
 * fgetopt_unittest.cc
 *
 * MIT License
 *
 * Copyright (c) 2017 Nestor B. Zubekhin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../../src/fgetopt.h"
#include "gtest/gtest.h"
#include "test_kits.h"
#include "argv.h"

// We test ARGV class

TEST(ARGV, DefaultConstructor) {
    ARGV    oargv;

    // <TechnicalDetails>
    //
    // The test passed if the correct parameters are initialized
    //
    // </TechnicalDetails>

    if (oargv.m_argv == NULL)
        EXPECT_TRUE(true);
    else
        EXPECT_FALSE(true);
}

TEST(ARGV, testARGVPositive) {

    int count;
    ARGV oargv(argc_some_text, argv_some_text);

    for (count = 0; count < argc_some_text; count++)
        if (strcmp(oargv.m_argv[count], argv_some_text[count])) {
            std::cout << "oargv.m_argv[" << count << "]: " << oargv.m_argv[count] << std::endl;
            std::cout << "argv_some_text[" << count << "]: " << argv_some_text[count] << std::endl;
            break;
        }

    // If not out of the loop permaturely,
    // the test passed
    EXPECT_EQ(count, argc_some_text);
}

TEST(ARGV, testARGVNegative) {

    // <TechnicalDetails>
    //
    // ...
    //
    // </TechnicalDetails>

    int count;
    ARGV oargv(argc_some_text, argv_some_text);

    for (count = 0; count < argc_some_text; count++)
        if (strcmp(oargv.m_argv[count], argv_some_text_c[count])) {
            std::cout << "oargv.m_argv[" << count << "]: " << oargv.m_argv[count] << std::endl;
            std::cout << "argv_some_text_c[" << count << "]: " << argv_some_text_c[count] << std::endl;
            break;
        }

    // If out of the loop permaturely,
    // the test passed
    EXPECT_NE(count, argc_some_text);
}

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
