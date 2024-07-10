#!/bin/bash

cd ../../../
docker rmi -f ereva/valgrind/string
docker build . -t ereva/valgrind/string -f materials/build/Valgrind/Dockerfile
docker exec -ti -e TERM ereva/valgrind/string /bin/bash
docker run --rm ereva/valgrind/string -d