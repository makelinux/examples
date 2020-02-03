#!/bin/sh

make
export LD_PROFILE=libdemo.so.1
export LD_PROFILE_OUTPUT=.
profile=$LD_PROFILE_OUTPUT/libdemo.so.1.profile
rm -f $profile
LD_LIBRARY_PATH=. ./prog
ls prof_data
sprof -p libdemo.so.1 $profile
sprof -c libdemo.so.1 $profile
