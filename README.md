[![Build Status](https://travis-ci.org/nbzubekhin/fgetoptcc.svg?branch=master)](https://travis-ci.org/github/nbzubekhin/fgetoptcc)

# fgetoptcc
The library fgetoptcc is a fork of the Free Getopt (http://freegetopt.sourceforge.net/), but MIT-licensed rather than BSD-licensed. It also adds C wrapper API for Object-Oriented C++ code.

## An example of using C code
Here is a listing of C code used to parse command line such as
```
$./program -v 10 -p "Example string"
```

```
int main(int argc, char **argv) {

    OutParam_t          *param;
    char                *parameter = (char *)"Not set parameter";
    int                 verb = -1;

    /** Parse arguments */
    for ( ; ; ) {
        param = GetOpt(argc, argv, (char *)"-v:p:");
 
        if (param->c == -1)
            break;
 
        switch (param->c) {
            case 'v':
                verb = atoi(param->optarg);
                break;
            case 'p':
                parameter = param->optarg;
                break;
        }
    }
    ...
}
```
## An example of using C++ code
Here is a listing of C++ code used to parse command line such as
```
$ ./program -v 10 --parameter "Example string"
```

```
int main(int argc, char *argv[]) {

    opts_alias_t options[] = {
        {"-v", "--verbose"},
        {"-p", "--parameter"}
    };

    size_t num_opts = sizeof(options)/sizeof(opts_alias_t);

    GETOPT              obj_getopt(argc, argv, options, num_opts);
    OutParam_t          *param;
    char                *parameter = (char *)"Not set parameter";
    int                 verb = -1;

    /** Parse arguments */
    for ( ; ; ) {
        param = obj_getopt.GetOpt(argc, argv, (char *)"-v:p:");
 
        if (param->c == -1)
            break;
 
        switch (param->c) {
            case 'v':
                verb = atoi(param->optarg);
                break;
            case 'p':
                parameter = param->optarg;
                break;
        }
    }
    ...
}
```
## Build project
```
$ mkdir build/ && cd build/
$ cmake .. -DCMAKE_INSTALL_PREFIX=../_install
```
## Enable build examples (by default not build)

### Build c code examples
```
$ cmake .. -Dbuild_examples_c=YES
```
### Build C++ code examples
```
$ cmake .. -Dbuild_examples_cxx=YES
```
## Enable build shared library fgetopt (by default build only static)
```
$ cmake .. -Dbuild_share_lib=YES
```
## Build tests using Google Test

## Build tests from avaible sources Google Test
```
$ export GTEST_ROOT=/path-to-gtest/
$ cmake .. -Dtest=YES
```
## Build tests using  avaible net-sources Google Test
Don`t set GTEST_ROOT
```
$ unset GTEST_ROOT
$ cmake .. -Dtest=YES
```
## Start tests
```
$ ctest -VVV
```
## Contributing

I will always merge *working* bug fixes. However, if you want to add something new to the API, please create an "issue"
on github for this first so we can discuss if it should end up in the library before you start implementing it.

## License
[The MIT License (MIT)](http://opensource.org/licenses/mit-license.php)
