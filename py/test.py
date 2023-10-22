import matplotlib.pyplot as plt
import numpy as np

# index = np.arange(5)
# values1 = [5,7,3,4,6]
# std1 = [0.8, 1, 0.4, 0.9, 1.3]
# plt.title("geek-docs.com", fontsize=20, fontname="Times New Roman")
# plt.barh(index, values1, xerr=std1, error_kw={'ecolor':'0.1', 'capsize':6}, alpha=0.7, label='First')
# plt.yticks(index,['A', 'B', 'C', 'D', 'E'])
# plt.legend(loc=5)
# plt.show()

# import fileinput

# for line in fileinput.input():
#     print(line)


data = {'A' : [[0, 3]],
        'B' : [[3, 7], [15, 17]],
        'C' : [[7, 11]],
        'D' : [[11, 15], [19, 20]],
        'E' : [[17,19]]
        }

# fig, ax = plt.subplots()
# ax.invert_yaxis()
# ax.broken_barh([(0, 3)], (10, 5), facecolors='tab:blue')
# ax.broken_barh([(3, 4), (15, 2)], (20, 5), facecolors='tab:blue')
# ax.broken_barh([(7, 4)], (30, 5), facecolors='tab:blue')
# ax.broken_barh([(11, 4), (19, 1)], (40, 5), facecolors='tab:blue')
# ax.broken_barh([(17, 2)], (50, 5), facecolors='tab:blue')

#ax.set_xticks(np.arange(21))
#ax.set_yticks([12.5, 22.5, 32.5, 42.5, 52.5])
#ax.set_yticklabels(['A', 'B', 'C', 'D', 'E'])

# plt.show()

import matplotlib.pyplot as plt
import numpy as np

# 创建数据
x = np.linspace(0, 2 * np.pi, 100)
y1 = np.sin(x)
y2 = np.cos(x)

# 创建第一个子图
plt.figure(1)
plt.subplot(2, 1, 1)  # 2行1列，第1个子图
plt.plot(x, y1)
plt.title('Sine Function')

# 创建第二个子图
plt.subplot(2, 1, 2)  # 2行1列，第2个子图
plt.plot(x, y2)
plt.title('Cosine Function')

# 显示图形
plt.tight_layout()  # 自动调整子图布局
plt.show()


