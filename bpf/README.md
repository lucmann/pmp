Learning Berkeley Packet Filter
===============================

# Requirements

- LLVM/Clang
- libbpf (Either [linux/tools/lib/bpf](https://elixir.bootlin.com/linux/v6.13.7/source/tools/lib/bpf) or [github.com/libbpf](https://github.com/libbpf/libbpf))

# Howto

- $ make
- $ sudo cat /sys/kernel/debug/tracing/trace_pipe
- $ sudo ./loader kill.o &
- $ kill -9 PID
