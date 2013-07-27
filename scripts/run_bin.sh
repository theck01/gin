#!/bin/bash

function usage {
  echo "$(basename $0): runs all binary files in a given directory"
  echo
  echo "Usage:"
  echo "$(basename $0) [test directory]"
  echo "Runs all executable files in the required directory argument"
}

if [[ $# -ne 1 ]]
then
  usage
  exit 1
fi

if [[ $1 == "-h" ]] || [[ $1 == "--help" ]]
then
  usage
  exit 1
fi

if [[ ! -d $1 ]]
then
  echo "$1 is not a valid directory"
fi


for test in $(ls $1)
do
  test_path="$(dirname $1)/$(basename $1)/$test"
  if [[ -x $test_path ]] 
  then
		# if the file is not a directory, run it
		if [[ ! -d $test_path ]]
		then
			$(dirname $1)/$(basename $1)/$test
		# if the file is a directory, recursivly call self on that directory
		else
			$0 $test_path
		fi
  fi
done
