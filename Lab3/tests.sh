#!/bin/bash

#./shuf.py tests
echo "./shuf.py tests"

./shuf.py -i 1-5

./shuf.py -i 5-1

./shuf.py -i 5-4

./shuf.py -i 5-5

./shuf.py -i

./shuf.py -i 1

./shuf.py -i 1-1-1

./shuf.py -n patch.diff

./shuf.py -n 8 patch.diff

./shuf.py -n -8 patch.diff

./shuf.py -n 0 patch.diff

./shuf.py -i 1-5 -n 3

./shuf.py -i 5 -n -3

./shuf.py -n -3 -i 5

./shuf.py -n 8 -r patch.diff

./shuf.py -n 0 -r patch.diff

./shuf.py -n 8 -i 1-10 -r


