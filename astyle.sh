#!/bin/sh
#
# This script helps with the library fgetoptcc coding style, but
# remember: "astyle" is not a fix for bad programming.
# 
# Rules:
#   - Google Style Guide, https://github.com/google/styleguide
#   - Don't touch comment content/formatting, only placement.
# 

rm -f src/*.orig
rm -f examples/*.orig
rm -f tests/unittests/*.orig
astyle --style=google src/*
astyle --style=google examples/*
astyle --style=google tests/unittests/*
