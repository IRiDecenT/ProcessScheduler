import matplotlib.pyplot as plt
from matplotlib.ticker import FixedFormatter, FixedLocator, MaxNLocator
import numpy as np
import fileinput

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

