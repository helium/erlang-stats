#!/bin/sh

cd c_src
if [ ! -d stats ]; then
    git clone --recursive https://github.com/kthohr/stats
fi

# pinned to 2.2.0 commit, no tag
(cd stats ; git reset --hard 659b1d9af2208de32fa17bcee9e4f3b0c5063a22)

make
