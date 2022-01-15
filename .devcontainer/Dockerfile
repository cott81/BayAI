# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.205.2/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
#ARG VARIANT="bullseye"
#FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}
#FROM cott81/vsc-cpp-dc
FROM ubuntu

# cpp basics
 RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends \
        git \ 
        build-essential \
        gdb \
        cmake

# unit testing
 RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends \
        libgtest-dev \
        google-mock

# install gtest
RUN cd /usr/src/gtest && cmake CMakeLists.txt && make && ln -s /usr/src/gtest/libgtest.a /usr/lib/libgtest.a 

# install gmock
RUN cd /usr/src/gmock && cmake CMakeLists.txt && make && ln -s /usr/src/gmock/libgmock.a /usr/lib/libgmock.a 

# application specific
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
       graphviz