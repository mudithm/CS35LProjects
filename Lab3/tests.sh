#!/bin/bash

#./shuf.py tests
echo "./shuf.py tests"

./shuf.py -i 0-5

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

echo =========================================================
#         dddddddddd 

python shuf.py -i 0-5

python shuf.py -i 5-1

python shuf.py -i 5-4

python shuf.py -i 5-5

python shuf.py -i

python shuf.py -i 1

python shuf.py -i 1-1-1

python shuf.py -n patch.diff

python shuf.py -n 8 patch.diff

python shuf.py -n -8 patch.diff

python shuf.py -n 0 patch.diff

python shuf.py -i 1-5 -n 3

python shuf.py -i 5 -n -3

python shuf.py -n -3 -i 5

python shuf.py -n 8 -r patch.diff

python shuf.py -n 0 -r patch.diff

python shuf.py -n 8 -i 1-10 -r

echo ===========================================================
#         dddddddddd 

python3 shuf.py -i 0-5

python3 shuf.py -i 5-1

python3 shuf.py -i 5-4

python3 shuf.py -i 5-5

python3 shuf.py -i

python3 shuf.py -i 1

python3 shuf.py -i 1-1-1

python3 shuf.py -n patch.diff

python3 shuf.py -n 8 patch.diff

python3 shuf.py -n -8 patch.diff

python3 shuf.py -n 0 patch.diff

python3 shuf.py -i 1-5 -n 3

python3 shuf.py -i 5 -n -3

python3 shuf.py -n -3 -i 5

python3 shuf.py -n 8 -r patch.diff

python3 shuf.py -n 0 -r patch.diff

python3 shuf.py -n 8 -i 1-10 -r

