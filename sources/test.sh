#!/bin/bash
#command to do is :
cmd="./projet -f $1 -h"

#test of reading the header
testCmd="readelf -h $1"

#test classe du fichier
testPat=`$testCmd | sed -n '/Classe/s/ \+/ /gp' | cut -f 3 -d " " `
result=`$cmd | grep Class | grep -c $testPat`
if [ $result -eq 1 ] ; then 
	$testCmd | sed -n '/Classe/s/ \+/ /gp'
        echo "  OK"
else
	$testCmd | sed -n '/Classe/s/ \+/ /gp'
        echo "  FAILED"
	exit
fi
#test data big ou little
testPat=`$testCmd | sed -n '/Donn/s/ \+/ /gp' | cut -f 13 -d " " |sed 's/[()]//g'`
testPat=`echo $testPat | sed -e "s/\b\(.\)/\u\1/g"`
result=`$cmd | grep Data | grep -c $testPat`
if [ $result -eq 1 ] ; then
	$testCmd |  sed -n '/Donn/s/ \+/ /gp'
        echo "  OK"
else
	$testCmd |  sed -n '/Donn/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test verion ELF
testPat=`$testCmd |head -5 | tail -1 |sed -n '/Version/s/ \+/ /gp' | cut -f 3 -d " " `
result=`$cmd | head -3 | tail -1 | grep -c $testPat`
if [ $result -eq 1 ] ; then
        $testCmd | head -5 |sed -n '/Version/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -5 |sed -n '/Version/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test OS / ABI
testPat=`$testCmd | sed -n '/OS/s/ \+/ /gp' | cut -f 5- -d " "`
result=`$cmd | grep OS | grep -c "$testPat"`
if [ $result -eq 1 ] ; then
        $testCmd |  sed -n '/OS/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd |  sed -n '/OS/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test version ABI
testPat=`$testCmd | grep "Version ABI:" |sed -n 's/ \+/ /gp' | cut -f 4 -d " "`
result=`$cmd | grep "ABI Version" | grep -c "$testPat"`
if [ $result -eq 1 ] ; then
        $testCmd |  grep "Version ABI" | sed -n 's/ \+/ /gp'
        echo "  OK"
else
        $testCmd |  grep "Version ABI" | sed -n 's/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test type
testPat=`$testCmd | sed -n '/Type/s/ \+/ /gp' | cut -f 3 -d " "`
testPat=`echo $testPat | tr [A-Z] [a-z] |sed -e "s/\b\(.\)/\u\1/g"`
result=`$cmd | grep Type | grep -c "$testPat"`
if [ $result -eq 1 ] ; then
        $testCmd |  sed -n '/Type/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd |  sed -n '/Type/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test target achitecture
testPat=`$testCmd | sed -n '/Machine/s/ \+/ /gp' | cut -f 3 -d " "`
result=`$cmd | grep architecture | grep -c "$testPat"`
if [ $result -eq 1 ] ; then
        $testCmd |  sed -n '/Machine/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd |  sed -n '/Machine/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test addr entry point
testPat=`$testCmd | sed -n '/point/s/ \+/ /gp' | cut -f 2 -d x`
result=`$cmd | grep address | cut -f 2 -d x`
if [ $result -eq $testPat ] ; then
        $testCmd |  sed -n '/point/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd |  sed -n '/point/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test start of hte program header table
testPat=`$testCmd | head -12 | sed -n '/programme/s/ \+/ /gp' | cut -f 7 -d " "`
result=`$cmd | grep "Start of the program header table" | grep -c $testPat`
if [ $result -eq 1 ] ; then
        $testCmd | head -12 |sed -n '/programme/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -12 |sed -n '/programme/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test Start of the section header table
testPat=`$testCmd | head -13 | sed -n '/section/s/ \+/ /gp' | cut -f 7 -d " "`
result=`$cmd | grep "Start of the section header table" | grep -c $testPat`
if [ $result -eq 1 ] ; then
        $testCmd | head -13 |sed -n '/section/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -13 |sed -n '/section/s/ \+/ /gp'
        echo FAILED 
        exit
fi
#test Start of the section header table
testPat=`$testCmd | sed -n '/Fanions/s/ \+/ /gp' | cut -f 2 -d x | cut -f 1 -d ,`
result=`$cmd | grep Flags | cut -f 2 -d x`
if [ $result -eq $testPat ] ; then
        $testCmd |sed -n '/Fanions/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd |sed -n '/Fanions/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test header size
testPat=`$testCmd | sed -n '/cet/s/ \+/ /gp' | cut -f 6 -d " "`
result=`$cmd | grep "Size of the header" | sed -n '/header/s/ \+/ /gp' | cut -f 6 -d " " `
if [ $result -eq $testPat ] ; then
        $testCmd |sed -n '/cet/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd |sed -n '/cet/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test size of programe header entry
testPat=`$testCmd | head -16 | tail -1 | sed -n '/programme/s/ \+/ /gp' | cut -f 7 -d " "`
result=`$cmd | grep "Size of a program header table entry" | sed -n '/header/s/ \+/ /gp' | cut -f 9 -d " "`
if [ $result -eq $testPat ] ; then
	$testCmd | head -16 | tail -1 | sed -n '/programme/s/ \+/ /gp'
        echo "  OK"
else
	$testCmd | head -16 | tail -1 | sed -n '/programme/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test number of entry
testPat=`$testCmd | head -17 | sed -n '/nombre/s/ \+/ /gp' | cut -f 6 -d " "`
result=`$cmd | grep "Number of entries in the program header table" | sed -n '/header/s/ \+/ /gp' | cut -f 11 -d " "`
if [ $result -eq $testPat ] ; then
        $testCmd | head -17 | sed -n '/Nombre/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -17 | sed -n '/Nombre/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test Size of a section header table entry
testPat=`$testCmd | head -18 | tail -1 | sed -n '/section/s/ \+/ /gp' | cut -f 7 -d " "`
result=`$cmd | grep "Size of a section header table entry" | sed -n '/header/s/ \+/ /gp' | cut -f 9 -d " "`
if [ $result -eq $testPat ] ; then
        $testCmd | head -18 | tail -1 | sed -n '/section/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -18 | tail -1 | sed -n '/section/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#testt Number of entries in the section header table
testPat=`$testCmd | head -19 | tail -1 | sed -n '/section/s/ \+/ /gp' | cut -f 6 -d " "`
result=`$cmd | grep "Number of entries in the section header table" | sed -n '/header/s/ \+/ /gp' | cut -f 10 -d " "`
if [ $result -eq $testPat ] ; then
        $testCmd | head -19 | tail -1 | sed -n '/section/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -19 | tail -1 | sed -n '/section/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi
#test Index of the section header table entry
testPat=`$testCmd | head -20 | tail -1 | sed -n '/section/s/ \+/ /gp' | cut -f 9 -d " "`
result=`$cmd | grep "Index of the section header table entry" | sed -n '/header/s/ \+/ /gp' | cut -f 9 -d " "`
if [ $result -eq $testPat ] ; then
        $testCmd | head -20 | tail -1 | sed -n '/section/s/ \+/ /gp'
        echo "  OK"
else
        $testCmd | head -20 | tail -1 | sed -n '/section/s/ \+/ /gp'
        echo "  FAILED"
        exit
fi



