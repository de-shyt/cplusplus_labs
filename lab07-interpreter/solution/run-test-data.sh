#!/bin/bash

# run command ./run-test-data.sh ./interpreter

set -euo pipefail
[ "$#" -ge 1 ] || (echo "Expected at least one argument: command to run" && exit 1)

CMD="$@"
echo "Command to run: $CMD"

FAIL=0
for tn in $(cat tests.txt); do
    tn=$(echo $tn)  # To remove \r from tests.txt on Windows
    echo ===== $tn =====
    { $CMD <test-data/$tn.in >test-data/$tn.out && diff test-data/$tn.{sol,out} && echo PASS; } || { echo -e "\e[31;1mFAIL\e[0m" && FAIL=1; }
done
if [[ "$FAIL" == "0" ]]; then
    echo -e "===== \e[32;1mALL PASS\e[0m ====="
else
    echo -e "===== \e[31;1mSOME FAIL\e[0m ====="
fi
exit $FAIL
