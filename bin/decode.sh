#!/bin/sh

echo $1
echo $2
flac -d --force-raw-format --endian=little --sign=signed "$1" -o "$2"
