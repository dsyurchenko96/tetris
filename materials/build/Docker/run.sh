#!/bin/bash

cd ../../../
docker rmi -f valgrind
docker build . -t valgrind -f materials/build/Docker/Dockerfile
docker run --rm valgrind