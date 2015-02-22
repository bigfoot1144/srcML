#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# test on compressed files with .gz.bz2 extension
define src <<- 'STDOUT'

	a;
	STDOUT

define foutput <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++" filename="archive/a.cpp.gz.bz2">
	<expr_stmt><expr><name>a</name></expr>;</expr_stmt>
	</unit>
	STDOUT

define output <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++">
	<expr_stmt><expr><name>a</name></expr>;</expr_stmt>
	</unit>
	STDOUT

createfile archive/a.cpp "$src"
gzip -c archive/a.cpp > archive/a.cpp.gz
bzip2 -c archive/a.cpp.gz > archive/a.cpp.gz.bz2

src2srcml archive/a.cpp.gz.bz2 -o archive/a.cpp.xml
check archive/a.cpp.xml 3<<< "$foutput"

srcml archive/a.cpp.gz.bz2
check 3<<< "$foutput"

srcml -l C++ < archive/a.cpp.gz.bz2
check 3<<< "$output"

srcml -l C++ -o archive/a.cpp.xml < archive/a.cpp.gz.bz2
check archive/a.cpp.xml 3<<< "$output"

rmfile archive/a.cpp
rmfile archive/a.cpp.gz
rmfile archive/a.cpp.gz.bz2
