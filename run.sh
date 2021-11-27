#!/bin/bash

#Name : run.sh

make Player
make Letter
make Main

make link
cd build
./main
