#!/bin/sh

cd c_src
if [ ! -d stats ]; then
    git clone --recursive https://github.com/kthohr/stats
fi

# pinned to 3.0.0 merge commit, no tag
(cd stats ; git reset --hard 8545bf8713d9529baa7b2e0c8eed23e6e93b9039)

if [ ! -d gcem ]; then
    git clone --recursive https://github.com/kthohr/gcem
fi

# HEAD of gcem rougly contemperaneous with stats 3.0.0 merge
(cd gcem ; git reset --hard 94443c99a7db939ac2edbba2674fdc54a8ec70c5)

make
