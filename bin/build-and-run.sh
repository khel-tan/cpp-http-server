#!/bin/bash

source config.txt

#Create build directory if it does not exist
if [ ! -d "build" ]; then
  mkdir build
fi

#Build stage
cd build
cmake ..
make

#Run executable
./$PROJECT_NAME
