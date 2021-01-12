FROM ubuntu:20.04

WORKDIR /usr/src/app

COPY . ./

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/London

RUN apt-get update -y && \
    apt-get install -y tzdata

RUN apt-get install -y --no-install-recommends \
      gcc-9 \
      g++ \
      clang-10 \
      build-essential \
      cmake \
      ca-certificates \
      freeglut3-dev \
      libglfw3-dev \
      libglew-dev && \
    apt-get autoclean && \
    apt-get autoremove && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN rm -rf build; mkdir build; cd build; cmake ../; make
