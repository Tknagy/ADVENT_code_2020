#!/bin/bash

for dir in cpp/*; do [ -d "${dir}" ] && ${dir}/test.sh; done
