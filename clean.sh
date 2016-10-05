#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
if [ -d bin ]; then
	rm -r bin
fi
if [ -d obj ]; then
	rm -r obj
fi
if [ -e run ]; then
	rm run
fi
