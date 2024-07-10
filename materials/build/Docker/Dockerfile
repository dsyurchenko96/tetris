FROM ubuntu:22.04

RUN apt-get -y update; 
RUN apt-get -y install valgrind \
 libsubunit-dev \
 check \
 gcc \
 make \
 lcov \
 xdg-utils \
 libncurses-dev \
 libncursesw5-dev \
 libncurses5-dev
RUN mkdir -p /usr/src/;

WORKDIR /usr/src/

COPY ./src /usr/src/
COPY ./materials/build/Docker/start.sh /usr/src

USER root

ENTRYPOINT ["/bin/bash", "start.sh"]

