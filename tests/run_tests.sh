#!/bin/bash
cd tests
IFS=,
data="test_single,test_assert"
for f in $data;
do
	./$f >.out 2>/dev/null
	diff -q .out $f.expect;
	if diff -q .out $f.expect;
	then
		:
	else
		exit;
	fi
done

