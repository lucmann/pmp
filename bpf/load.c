#include <bpf/bpf.h>
#include <bpf/libbpf.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }   

    char *path = argv[1];

    struct bpf_object *obj;
    struct bpf_link *link = NULL;

    int err = -1;

    obj = bpf_object__open_file(path, NULL);
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "Failed to open BPF object file: %s\n", path);
        return err;
    }

    struct bpf_program *prog =
        bpf_object__find_program_by_name(obj, "kill_example");
    if (!prog) {
        fprintf(stderr, "Failed to find program in BPF object file: %s\n", path);
        goto cleanup;
    }

    if (bpf_object__load(obj)) {
        fprintf(stderr, "Failed to load BPF object file: %s\n", path);
        goto cleanup;
    }

    link = bpf_program__attach(prog);
    if (libbpf_get_error(link)) {
        fprintf(stderr, "Failed to attach BPF program: %s\n", path);
        goto cleanup;
    }

    err = 0;

    while (1) sleep(1);

cleanup:
    bpf_link__destroy(link);
    bpf_object__close(obj);

    return err;
}
