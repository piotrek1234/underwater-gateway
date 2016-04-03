#!/bin/bash
git pull
qmake underwater-gateway.pro
make -j 8
