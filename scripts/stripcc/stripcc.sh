#!/bin/env bash
#
# this shell script strips the single and multiple lines comments
# in c/c++ source files.
#
# regex-1: \s*/\*.*\*/\s matches like `    /* blablabla */ `
#          except lines such as `fprintf(fp, " /* blablabla */ \n");`
#
# regex-2: sed range expression matches like
#          ```
#          /** blablabla
#           *
#           */
#          ```
#
# regex-3: \s*//.* matches like `// blablabla` except that
#          lines such as `fprintf(fp, "//");`
#
# Note that regex-1 MUST precede regex-2
#

Help()
{
    cat - 1>& 2 << EOF
$0 [-i] [-h] [DESTDIR]

    DESTDIR             keep in mind that DESTDIR is optional but absolute. if not specified,
                        search in the current directory.


    -i, --in-place      invoke sed with -i option
    -h, --help          print this help then exit
EOF
    exit 0
}

while [ $# -gt 0 ]; do
    case "$1" in
        -h|--help)
        Help
        ;;
        -i|--in-place)
        SEDOPTS="-i"
        ;;
        *)
        DESTDIR="$1"
        ;;
    esac
    shift
done

find ${DESTDIR} -regex '.*\.[ch]c?\(pp\)?' |
    xargs sed ${SEDOPTS}                                 \
        -e '/".*\/\*.*\*\/.*"/!s;\s*/\*.*\*/\s*;;'       \
        -e '/^\s*\/\*/, /\*\//d'                         \
        -e '/".*\/\/.*"/!s;\s*//.*;;'

