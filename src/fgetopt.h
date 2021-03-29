/**
 * fgetopt.h - competent and free getopt library.
 *
 * Redistribution with modification
 * Copyright (c)2011-2012 Nestor B. Zubekhin
 * All rights reserved.
 *
 * Copyright (c)2002-2003 Mark K. Kim
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *   * Neither the original author of this software nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef FGETOPT_H_
#define FGETOPT_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct opts_alias {
    char *dash_opt;
    char *dash_dash_opt;
} opts_alias_t;

typedef struct VarParam {
    char **prev_argv;	/** Keep a copy of argv and argc to */
    int	   prev_argc;	/** tell if getopt params change    */
    int	   argv_index;	/** Option we're checking           */
    int	   argv_index2; /** Option argument we're checking  */
    int	   opt_offset;	/** Index into compounded "-option" */
    int	   dashdash;	/** True if "--" option reached     */
    int	   nonopt;	/** How many nonopts we've found    */
} VarParam_t;

typedef struct OutParam {
    char *optarg;
    int	  optind;
    int	  opterr;
    int	  optopt;
    int	  c;
} OutParam_t;

#ifdef __cplusplus

extern "C" {
extern OutParam_t *fgetopt(VarParam_t *, int, char **, char *);
extern void	   set_alias_for_options_line(int, char **, opts_alias_t *, size_t);
};

class GETOPT {
public:
    GETOPT() : prev_argv(NULL), prev_argc(0), argv_index(0), argv_index2(0), opt_offset(0), dashdash(0), nonopt(0) {}

    GETOPT(int argc, char **argv, opts_alias_t *alias_opts, size_t num_opts)
	: prev_argv(NULL), prev_argc(0), argv_index(0), argv_index2(0), opt_offset(0), dashdash(0), nonopt(0) {
	(void)set_alias_for_options_line(argc, argv, alias_opts, num_opts);
    }

    OutParam_t *GetOpt(int argc, char **argv, char *optstr) { return fgetopt((VarParam_t *)this, argc, argv, optstr); }

private:
    char **prev_argv;
    int	   prev_argc;
    int	   argv_index;
    int	   argv_index2;
    int	   opt_offset;
    int	   dashdash;
    int	   nonopt;
};

#else

extern OutParam_t *GetOpt(int, char **, char *);
extern void	   set_alias_for_options_line(int, char **, opts_alias_t *, size_t);

#endif

#endif	// FGETOPT_H_
