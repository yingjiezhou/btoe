#!/bin/bash

mkdir production/
mkdir log_tmp/
mkdir list/
mkdir report/
mkdir csh/
mkdir err/
#
#
rm *.session.xml
rm sched*.dataset*
rm -rf list/*
rm -rf report/*
rm -rf csh/*
rm -rf err/*

rm -r LocalLibraries.package
rm LocalLibraries.zip

star-submit-template -template submit.xml -entities listOfFiles=good_pico_nfs_all_file.list

condor_q
