#!/bin/sh

if [ -d c_src/stats ]; then
    rm -rf c_src/stats
fi

if [ -f c_src/erlang_stats.o ]; then
    rm c_src/erlang_stats.o
fi
