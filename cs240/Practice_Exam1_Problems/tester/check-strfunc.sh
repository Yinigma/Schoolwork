#!/bin/bash

prog=$(echo "problem*") 

sym=`grep -c "strlen(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "strdup(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "strcpy(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "strncpy(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "strcmp(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "strstr(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "strcat(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE ANY STRING FUNCTION in $prog
    exit 1
fi

sym=`grep -c "memcpy(" $prog`
if [ "$sym" != "0" ]; then
    echo DO NOT USE MEMCPY IN $prog
    exit 1
fi

exit 0
