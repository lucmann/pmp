#!/usr/bin/env python3

# Copyright (C) 2024 Luc Ma
#
# SPDX-License-Identifier: GPL-2.0

import re
import subprocess
import sys
from rich import print as rprint


def search_fps(regex, text, matched=0):
    r = re.compile(regex)
    m = r.search(text)

    if m is None:
        return 0.0

    return float(m.group(0))


def run(args):
    try:
        process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

        n = 0
        score = 0.0
        while True:
            output = process.stdout.readline().decode('utf-8')

            # When child process is terminated, still continue to read until I/O
            # buffer is empty, then stop real-time output
            if output == '' and process.poll() is not None:
                break

            if output:
                n += 1
                score += search_fps(' \d+.\d{3,} ', output)

            # print(n) # debugging
            sys.stdout.write(output)
            sys.stdout.flush()


    except OSError as e:
        if e.errno != errno.ENOENT and e.errno != errno.EACCESS:
            raise
    except subprocess.CalledProcessError:
        pass

    return score / n


def show_fps(fps):
    rprint("[bold green]Average FPS:[/bold green] %.3f" % fps)


if __name__ == '__main__':
    show_fps(run(sys.argv[1:]))

