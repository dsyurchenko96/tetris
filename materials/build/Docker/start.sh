#!/bin/bash

export TERM=xterm
make test
make replay
# make test_leaks
# make gcov_report
