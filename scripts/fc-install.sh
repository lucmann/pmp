#!/bin/bash

TEMPFILE=`mktemp -t Fira_Code_v6.2.XXXXXXXXXX`
wget -q -O $TEMPFILE https://github.com/tonsky/FiraCode/releases/download/6.2/Fira_Code_v6.2.zip \
    --tries=10 --show-progress

unzip -n $TEMPFILE -d ~/.fonts *.ttf

if [ $? -eq 0 ]; then
    echo "FiraCode v6.2 installed, run fc-list to check"
else
    fc-cache
fi

