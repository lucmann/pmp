#!/usr/bin/env bash

PREFERRED_FONT="AR PL KaitiM GB"
CJK_MAIN_FONT=
zh_fonts_file=$(mktemp -t fonts.XXXXXX)

# save fonts family into a temp file to avoid the trouble with spaces among font family string
fc-list :lang=zh --format "%{family[0]}\n" > $zh_fonts_file

if [[ ! -s $zh_fonts_file ]]; then
    echo "No available zh-cn font found"
    exit 1
fi

while read ft
do
    CJK_MAIN_FONT="$ft"

    if [[ "$ft" = "$PREFERRED_FONT" ]]; then
        break
    fi
done < $zh_fonts_file

if command -v pandoc > /dev/null 2>&1; then
    pandoc --pdf-engine=xelatex \
        --resource-path=${1%%.*} \
        --toc \
        -V CJKmainfont="$CJK_MAIN_FONT" \
        -V colorlinks=true \
        -V linkcolor=blue \
        -N \
        -o ${1/%md/pdf} \
        $1
else
    echo "pandoc not found"
    exit 2
fi

