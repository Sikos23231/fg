#!/bin/bash

modified=$(git ls-files --modified ..)

if [[ $modified ]]; then
	echo "The following files are not following a guideline:"
	echo $modified

	git diff
	exit -1
fi
