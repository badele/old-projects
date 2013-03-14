#! /bin/sh

# This script is responsible for speaking out a date stamp.
# It should be installed in your voice directory once you got
# it working correctly.
#
# Input:  $1 - filename for which the date information should be spoken out
#         $2 - sample speed
#         $3 - modem type
#         $4 - compression type
#
# Output: rmd voice file on stdout
#
# This implementation uses GNU find and the rsynth synthesizer.

TMP=/tmp
NUMBERS_DIR=/home/b_adele/tmp/sound/numero_data

NUMBERS=""

function say_number
{
    NUMBERS="$NUMBERS $NUMBERS_DIR/$1.wav"  
}

function enum_number
