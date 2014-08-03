#!/bin/bash

# Process all .flac files in $indir
# Should be run with ./process in the A-kapera dir

# Definitions
workdir=$(pwd)
bindir=$workdir/bin
indir=$workdir/input
outdir=$workdir/output

logfile="process.log"
infile="vocal.raw"
outfile="out.raw"
encodeout="out.flac"
files="$infile $outfile $encodeout"

cd $workdir
mkdir -p $indir $outdir

echo "Input files:"
ls $indir/*.flac
if [ $? != 0 ]; then
  echo "Error: no input files"
  exit 1
fi

rm -f $files
rm -f $logfile

rename 's/\ /_/g' $indir/*.flac

for i in $(ls $indir/*.flac)
do
  echo ">> Processing $(basename $i)"
  $bindir/decode.sh $i $infile &>> $logfile
  $bindir/akapera &>> $logfile
  if [ $? != 0 ]; then
    echo "Error: akapera failure"
    exit 1
  fi
  $bindir/encode.sh &>> $logfile
  mv $workdir/$encodeout $outdir/$(basename $i)
  rm -f $files
done
