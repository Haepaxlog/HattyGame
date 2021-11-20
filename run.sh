#!/bin/bash

#Name : run.sh

make Player
make Letter
make Main

make install
cd build
./main
