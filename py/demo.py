import matplotlib.pyplot as plt
from matplotlib.ticker import FixedFormatter, FixedLocator, MaxNLocator
import numpy as np
import fileinput



# FCFS|8.6|2.56333
# A|0-3
# B|3-9
# C|9-13
# D|13-18
# E|18-20
# \n
# HRRF|8|2.14333
# A|0-3
# B|3-9
# C|9-13
# D|15-20
# E|13-15

class package:
    algo_name = ''
    processName = []
    time = []
    avg_time = 0.0
    avg_time_with_weight = 0.0
    def __init__(self, name, t1, t2):
        self.algo_name = name
        self.avg_time = t1
        self.avg_time_with_weight = t2

    def appendProcessName(self, name):
        self.processName.append(name)

    def appendTimePeriod(self, period):
        self.time.append(period)


processName = []
time = []

for line in fileinput.input():
    #print(line)
    s = line.strip().split('|')
    if len(s) > 1:
        processName.append(s[0])
        t = []
        for i in range(1, len(s)):
            period = s[i].split('-')
            t.append((int(period[0]), int(period[1]) - int(period[0])))
        time.append(t)

print(processName)
print(time)



fig, ax = plt.subplots()
ax.invert_yaxis()

# plt.rcParams["font.family"]=["PingFang"] #设置字体
# plt.rcParams["axes.unicode_minus"]=False #正常显示负号

plt.title("RR scheduling, time period = 4")

yticks = []
for i in range(0, len(time)):
    ax.broken_barh(time[i], ((i+1) * 10, 5), facecolors='tab:blue')
    yticks.append((i+1)*10 + 2.5)

ax.yaxis.set_major_locator(FixedLocator(yticks))
ax.yaxis.set_major_formatter(FixedFormatter(processName))
ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.set_yticklabels(processName)
ax.set_yticks(yticks)

plt.show()



# data = {'A' : [[0, 3]],
#         'B' : [[3, 7], [15, 17]],
#         'C' : [[7, 11]],
#         'D' : [[11, 15], [19, 20]],
#         'E' : [[17,19]]
#         }

