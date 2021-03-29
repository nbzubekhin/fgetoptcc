/**
 * fgetopt.c - competent and free getopt library.
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
#include "fgetopt.h"

#define OPTARG out_param.optarg
#define OPTIND out_param.optind
#define OPTERR out_param.opterr
#define OPTOPT out_param.optopt
#define C out_param.c
#define PREV_ARGV var_param->prev_argv
#define PREV_ARGC var_param->prev_argc
#define ARGV_INDEX var_param->argv_index
#define ARGV_INDEX2 var_param->argv_index2
#define OPT_OFFSET var_param->opt_offset
#define DASHDASH var_param->dashdash
#define NONOPT var_param->nonopt

static void increment_index(VarParam_t *var_param) {
    /* Move onto the next option */
    if (ARGV_INDEX < ARGV_INDEX2) {
	while (PREV_ARGV[++ARGV_INDEX] && PREV_ARGV[ARGV_INDEX][0] != '-' && ARGV_INDEX < ARGV_INDEX2 + 1)
	    ;
    } else
	ARGV_INDEX++;

    OPT_OFFSET = 1;
}

/**
 * Permutes argv[] so that the argument currently being processed is moved
 * to the end.
 */
static int permute_argv_once(VarParam_t *var_param) {
    /** Movability check */
    if (ARGV_INDEX + NONOPT >= PREV_ARGC)
	return 1;
    /** Move the current option to the end, bring the others to front */
    else {
	char *tmp = PREV_ARGV[ARGV_INDEX];

	/** Move the data */
	memmove(&(PREV_ARGV[ARGV_INDEX]), &(PREV_ARGV[ARGV_INDEX + 1]), sizeof(char **) * (PREV_ARGC - ARGV_INDEX - 1));

	PREV_ARGV[PREV_ARGC - 1] = tmp;
	NONOPT++;
	return 0;
    }
}

OutParam_t *fgetopt(VarParam_t *var_param, int argc, char **argv, char *optstr) {
    static OutParam_t out_param = {NULL, 0, 1, '?', 0};

    /** If we have new argv, reinitialize */
    if (PREV_ARGV != argv || PREV_ARGC != argc) {
	/** Initialize variables */
	PREV_ARGV   = argv;
	PREV_ARGC   = argc;
	ARGV_INDEX  = 1;
	ARGV_INDEX2 = 1;
	OPT_OFFSET  = 1;
	DASHDASH    = 0;
	NONOPT	    = 0;
    }

    /** Jump point in case we want to ignore the current argv_index */
getopt_top:

    /** Misc. initializations */
    OPTARG = NULL;

    /** Dash-dash check */
    if (argv[ARGV_INDEX] && !strcmp(argv[ARGV_INDEX], "--")) {
	DASHDASH = 1;
	increment_index(var_param);
    }

    /** If we're at the end of argv, that's it. */
    if (argv[ARGV_INDEX] == NULL) {
	C = -1;

	/** Are we looking at a string? Single dash is also a string */
    } else if (DASHDASH || argv[ARGV_INDEX][0] != '-' || !strcmp(argv[ARGV_INDEX], "-")) {
	/** If we want a string... */
	if (optstr[0] == '-') {
	    C	   = 1;
	    OPTARG = argv[ARGV_INDEX];
	    increment_index(var_param);

	    /** If we really don't want it (we're in POSIX mode), we're done */
	} else if (optstr[0] == '+' || getenv("POSIXLY_CORRECT")) {
	    C = -1;

	    /** Everything else is a non-opt argument */
	    NONOPT = argc - ARGV_INDEX;

	    /** If we mildly don't want it, then move it back */
	} else {
	    if (!permute_argv_once(var_param))
		goto getopt_top;
	    else
		C = -1;
	}

	/** Otherwise we're looking at an option */
    } else {
	char *opt_ptr = NULL;

	/** Grab the option */
	C = argv[ARGV_INDEX][OPT_OFFSET++];

	/** Is the option in the optstr? */
	if (optstr[0] == '-')
	    opt_ptr = strchr(optstr + 1, C);
	else
	    opt_ptr = strchr(optstr, C);

	/** Invalid argument */
	if (!opt_ptr) {
	    if (OPTERR) {
		fprintf(stderr, "%s: invalid option -- %c\n", argv[0], C);
	    }

	    OPTOPT = C;
	    C	   = '?';

	    /** Move onto the next option */
	    increment_index(var_param);

	    /* Option takes argument */
	} else if (opt_ptr[1] == ':') {
	    /** ie, -oARGUMENT, -xxxoARGUMENT, etc. **/
	    if (argv[ARGV_INDEX][OPT_OFFSET] != '\0') {
		OPTARG = &argv[ARGV_INDEX][OPT_OFFSET];
		increment_index(var_param);

		/** ie, -o ARGUMENT (only if it's a required argument) */
	    } else if (opt_ptr[2] != ':') {
		/** One of those "you're not expected to understand this" moment */
		if (ARGV_INDEX2 < ARGV_INDEX)
		    ARGV_INDEX2 = ARGV_INDEX;

		while (argv[++ARGV_INDEX2] && argv[ARGV_INDEX2][0] == '-')
		    ;

		OPTARG = argv[ARGV_INDEX2];

		/** Don't cross into the non-option argument list */
		if (ARGV_INDEX2 + NONOPT >= PREV_ARGC)
		    OPTARG = NULL;

		/** Move onto the next option */
		increment_index(var_param);

	    } else {
		/** Move onto the next option */
		increment_index(var_param);
	    }

	    /** In case we got no argument for an option with required argument */
	    if (OPTARG == NULL && opt_ptr[2] != ':') {
		OPTOPT = C;
		C      = '?';

		if (OPTERR) {
		    fprintf(stderr, "%s: option requires an argument -- %c\n", argv[0], OPTOPT);
		}
	    }

	} else { /** Option does not take argument */

	    /** Next argv_index */
	    if (argv[ARGV_INDEX][OPT_OFFSET] == '\0')
		increment_index(var_param);
	}
    }

    /** Calculate optind */
    if (C == -1) {
	OPTIND = argc - NONOPT;
    } else {
	OPTIND = ARGV_INDEX;
    }

    return (&out_param);
}

static VarParam_t var_param;

OutParam_t *GetOpt(int argc, char **argv, char *optstr) { return fgetopt(&var_param, argc, argv, optstr); }

static void compact_string(char *str) {
    size_t i = 0, k = 0;

    while (str[i + k] != '\0') {
	if (str[i + k] == ' ')
	    k++;
	else {
	    str[i] = str[i + k];
	    i++;
	}
    }

    str[i] = '\0';
}

static char *create_str_space(size_t num_space) {
    size_t i;
    char * p_str_space = (char *)malloc(num_space);
    for (i = 0; i < num_space; i++) p_str_space[i] = ' ';

    return (p_str_space);
}

static void rep_substr_rep_space(char *source_str, const char *that_replace, const char *replace_what) {
    char * desired_substring, *ptr_space_str;
    size_t len_replace_what = strlen(replace_what), len_that_replace = strlen(that_replace);
    if ((desired_substring = strstr(source_str, that_replace)) != NULL)
	if (len_replace_what < len_that_replace) {
	    strncpy(desired_substring, replace_what, len_replace_what);
	    ptr_space_str = create_str_space(len_that_replace - len_replace_what);
	    strncpy(desired_substring + len_replace_what, ptr_space_str, len_that_replace - len_replace_what);
	    free(ptr_space_str);
	}
}

void set_alias_for_options_line(int arg_num, char **arg_param, opts_alias_t *options, size_t num_opts) {
    size_t i, j;
    char **argv = arg_param;
    int	   argc = arg_num;

    for (i = 1; i < argc; i++)
	for (j = 0; j < num_opts; j++) {
	    (void)rep_substr_rep_space(argv[i], options[j].dash_dash_opt, options[j].dash_opt);
	    (void)compact_string(argv[i]);
	}
}

