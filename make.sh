#!/bin/sh

cc							\
	-fPIC 	`#Only Position Independant code` 	\
	-O0 	`#Optimizations will fuck this up`	\
	-o forth					\
	forth.c
