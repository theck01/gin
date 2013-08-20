#!/bin/bash

# Shell script prepares the bin/ directory structure, which needs to be created
# after removing compiled objects and cloning in git


mesgstr="Setup"
folders=(bin bin/base bin/geom bin/physics bin/tests bin/tests/base \
				 bin/tests/geom bin/tests/physics)

# for each folder, check if present, if not make it
for f in ${folders[*]}
do
  if [[ ! -d "$f" ]]
  then
    mkdir "$f"
    mesgstr+=" $f"
  fi
done

# print result message
if [[ "$mesgstr" == "Setup" ]]
then
  echo "bin/ directory tree present"
else
  echo "$mesgstr directories"
fi
