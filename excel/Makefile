
compose: raw/CPos.h raw/CExpression.h  raw/CMyBuilder.h raw/CSpreadsheet.h raw/CPos.cpp raw/CExpression.cpp raw/CDouble.cpp raw/CString.cpp raw/CPosition.cpp raw/COperator.cpp raw/CMyBuilder.cpp raw/CSpreadsheet.cpp includes.cpp raw/main.txt
	cat includes.cpp  raw/CPos.h raw/CExpression.h  raw/CMyBuilder.h raw/CSpreadsheet.h raw/CPos.cpp raw/CExpression.cpp raw/CDouble.cpp raw/CString.cpp raw/CPosition.cpp raw/COperator.cpp raw/CMyBuilder.cpp raw/CSpreadsheet.cpp raw/main.txt > all_in_one.cpp

raw/%.cpp: %.cpp
	grep -vhe '^\#include' -e $<  > $@

raw/%.h: %.h
	grep -vhe '^\#include' -e $<  > $@

includes.cpp: main.cpp
	#grep -he '^\#include' -e '^using namespace' main.cpp > includes.cpp
	sed -n '1,47p' main.cpp > includes.cpp
	echo 'using namespace std;'	>> includes.cpp

raw/main.txt: main.cpp
	sed -n '52,60000p' main.cpp > raw/main.txt

clean:
	rm raw/* includes.cpp
