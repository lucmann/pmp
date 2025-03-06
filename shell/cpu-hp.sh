#!/bin/bash
# CPU cores hotplug

help()
{
    echo "Usage: $0 [on|off] [-c|--cpu <cpu>] [-h|--help]"
    echo "  -c|--cpu <cpu>  CPU core to hotplug"
    echo "  -h|--help       Display this help message"
    exit 1
}

hotplug()
{
    if [ "$1" == "on" ]; then
        state=1
        operation="hotplugged"
        color=$(printf '\033[32m')
    elif [ "$1" == "off" ]; then
        state=0
        operation="hotunplugged"
        color=$(printf '\033[31m')
    else
        echo "Invalid state: $1"
        help    
    fi

    local i=$(($2 - 1))
    
    for c in $(seq 1 $i); do
        echo $state > /sys/devices/system/cpu/cpu$c/online
    done

    echo "${color}CPU core(s) cpu1 - cpu$i have been $operation (Note: we never touch cpu0)$(printf '\033[0m')"
}

# /sys/devices/system/cpu/cpu0/online does exist on some systems
# but doesn't on others
cpu_default=$(ls /sys/devices/system/cpu/cpu[0-9]* -d | wc -l)

main()
{
    if [ $# -eq 0 ]; then
        help
    fi

    while [ "$1" != "" ]; do
        case $1 in
            on)
                state="on"
                call_with_default=1
                ;;
            off)
                state="off"
                call_with_default=1
                ;;
            -c | --cpu)
                shift
                cpu=$1
                call_with_default=0
                ;;
            -h | --help)
                help
                ;;
            *)
                help
                ;;
        esac
        shift
    done

    if [ $call_with_default -eq 1 ]; then
        hotplug $state $cpu_default
    else
        # since we always start from cpu1 to operate on 
        hotplug $state $((cpu + 1))
    fi
}

main $@
