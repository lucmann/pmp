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

# Hammers

- $ sudo bpftrace -lv 'tracepoint:drm:*'
tracepoint:drm:drm_vblank_event
    int crtc
    unsigned int seq
    ktime_t time
    bool high_prec
tracepoint:drm:drm_vblank_event_delivered
    struct drm_file * file
    int crtc
    unsigned int seq
tracepoint:drm:drm_vblank_event_queued
    struct drm_file * file
    int crtc
    unsigned int seq
