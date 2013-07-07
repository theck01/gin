#!/bin/bash

# Shell script prepares the bin/ directory structure, which needs to be created
# after removing compiled objects and cloning in git


mesgstr="Made"

# check for directories, make non-existant
if [[ ! -d "bin" ]]
then
  mkdir bin
  mesgstr="$mesgstr bin"
fi

if [[ ! -d "bin/base" ]]
then
  mkdir bin/base
  mesgstr="$mesgstr bin/base"
fi

if [[ ! -d "bin/tests" ]]
then
  mkdir bin/tests
  mesgstr="$mesgstr bin/tests"
fi

# print result message
if [[ "$mesgstr" == "Made" ]]
then
  echo "bin/ directories present"
else
  echo "$mesgstr directories"
fi
