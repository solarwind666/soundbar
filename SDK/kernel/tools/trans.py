import sys
import re
import os

pattern = re.compile('\[\<(\w+)\>\]')
pattern2 = re.compile('caller=(\w+)')

inp = sys.stdin
if len(sys.argv) > 1:
    inp = open(sys.argv[-1], 'r')

def tran_one_func(line):
    line = line.strip()
    print line
    res = pattern.search(line)
    if not res:
        res = pattern2.search(line)
    if not res:
        return
    addr = res.group(1)
    print os.popen('csky-elf-addr2line -f -e yunos 0x' + addr).read()

for l in inp:
    tran_one_func(l)
