#!/usr/bin/env python3

import matplotlib.pyplot as plt
from subprocess import run, PIPE
import os
import re
import sys

os.environ['LD_LIBRARY_PATH'] = "."

x = []
y = []

for i in range(1, 80, 2):
    size = 30011
    len_min = 0.5
    len_max = i / 10
    file = sys.argv[1]
    run(['make', 'clean'])
    run(['make', '-j6', "CPPFLAGS=-DHTAB_SIZE={} -DAVG_LEN_MIN={} -DAVG_LEN_MAX={}".format(size, len_min, len_max)])
    mem = run(["/bin/bash", "-c", "valgrind ./wordcount-dynamic <{}".format(file)],
              stderr=PIPE, stdout=PIPE).stderr.decode('utf-8')
    time = run(
        ["/bin/bash", "-c", "time ./wordcount-dynamic <{}".format(file)], stderr=PIPE, stdout=PIPE).stderr.decode('utf-8')
    mem = re.findall(
        r"total heap usage: ([\d,]+) allocs, ([\d,]+) frees, ([\d,]+) bytes allocated", mem)[0]
    mem = [int(x.replace(',', '')) for x in mem]
    time = float(re.findall(r"\dm\d.\d\d\ds", time)[0][2:7])
    x.append(len_max)
    y.append(time)

    print(mem)
    print(time)

plt.plot(x, y)

plt.xlabel('AVG_LEN_MAX')
plt.ylabel('Time (s)')
plt.title('Initial size: {}'.format(size))

plt.savefig("plot.png")
plt.show()
