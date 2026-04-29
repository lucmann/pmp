#!/usr/bin/env python3
"""
将整数转换为二进制并按 4 位分组，同时输出对应的十六进制数字。
用法: python script.py <整数>
示例: python script.py 16
输出:
0001 0000
1 0
"""

import sys
import argparse

WIDTH = 4
LENGTH = 14

def main():
    global WIDTH
    parser = argparse.ArgumentParser(description="Convert integer to binary and hexadecimal.")
    parser.add_argument('number', type=lambda x: int(x, 0), help="The integer to convert.")
    parser.add_argument('--shift-right', '-r', default=0, type=int, help="Shift right by NUM positions.")
    parser.add_argument('--shift-left',  '-l', default=0, type=int, help="Shift left by NUM positions.")

    args = parser.parse_args()

    num = args.number
    WIDTH = max(WIDTH, num.bit_length() + args.shift_left)
    format_binary_and_hex(num)

    if args.shift_right:
        format_binary_and_hex(num >> args.shift_right, f">> {args.shift_right:4} bits: ")

    if args.shift_left:
        format_binary_and_hex(num << args.shift_left, f"<< {args.shift_left:4} bits: ")

def format_binary_and_hex(num, preamble=" " * LENGTH):
    bin_str = bin(num)[2:].zfill(WIDTH)

    # 补齐到 4 的倍数（高位添 0）
    padding = (4 - len(bin_str) % 4) % 4
    padded_bin = '0' * padding + bin_str

    # 每 4 位一组
    groups = [padded_bin[i:i+4] for i in range(0, len(padded_bin), 4)]

    # 每组转换为十六进制数字（大写）
    hex_digits = [format(int(g, 2), 'X') for g in groups]

    # 输出
    print(preamble + ' '.join(groups) + f" ({num})")
    print(preamble + ' '.join(hex_digits))

if __name__ == "__main__":
    main()