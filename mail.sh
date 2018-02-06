#!/bin/bash
echo "compress-then-send script"
text=$1
filename=$2
lame "$filename"

filename="${filename%.*}"

./mail.py "Call by $text recorded. Here is the file" "$filename.mp3"

