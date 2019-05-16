#!/bin/sh

cd c_src
if [ ! -d stats ]; then
    git clone --recursive https://github.com/kthohr/stats
fi

make
