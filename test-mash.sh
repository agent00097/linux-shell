#! /bin/bash

if ! [[ -x mash ]]; then
    echo "mash executable does not exist"
    exit 1
fi

./tester/run-tests.sh $*


