#!/bin/bash

CMSIS_DIR=cmsis/

git clone --depth 1 -b 5.9.0 https://github.com/ARM-software/CMSIS_5 $CMSIS_DIR/cmsis_core
git clone --depth 1 -b master https://github.com/STMicroelectronics/cmsis_device_wb $CMSIS_DIR/cmsis_wb
