#!/bin/sh

set -e

echo $(pwd)
echo $GITHUB_WORKSPACE
make -j$(nproc)
pwd
ls -la
