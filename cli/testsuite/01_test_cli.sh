#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# test simple
echo -n "" | src2srcml -l C++

check 3<<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="0.8.0" language="C++"/>
	STDOUT

