#ifndef ARGV_H_
#define ARGV_H_

/**
 * argv.h - headerfile
 * Argument vector contains the arguments passed in from the command
 * line when starting a program
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

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class ARGV {
    int m_argc, m_count;
    size_t  m_str_len;
    char *m_ptr_str;

  public:
    char **m_argv;

    ARGV(): m_argc(0), m_argv(NULL), m_count(0),
        m_str_len(0), m_ptr_str(NULL) {
    }

    ARGV(int argc, char *argv[]): m_argc(argc), m_argv(NULL), m_count(0),
        m_str_len(0), m_ptr_str(NULL) {
        if (m_argc != 0) {
            m_argv = new char *[m_argc];
            for (m_count = 0; m_count < m_argc; m_count++) {
                m_str_len = strlen(argv[m_count]) + 1;
                m_ptr_str = new char[m_str_len];
                strncpy(m_ptr_str, argv[m_count], m_str_len);
                m_argv[m_count] = m_ptr_str;
            }
        }
    }

    ~ARGV() {
        for (m_count = 0; m_count < m_argc; m_count++)
            delete[] m_argv[m_count];
        delete[] m_argv;
    }
};

#endif // ARGV_H_
