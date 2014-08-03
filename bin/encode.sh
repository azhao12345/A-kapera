#!/bin/sh

flac --force-raw-format --endian=little --sign=signed --channels=2 --bps=16 --sample-rate=44100 "out.raw"
