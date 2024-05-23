import matplotlib.pyplot as plt
import numpy as np


with open('out.txt', 'r') as f:
    lines = f.readlines()

numthread = 0
time_map = {}
for line in lines:
    data = line.strip().split()
    if len(data) == 0:
        continue
    
    numthread = int(data[0])
    N = int(data[1])
    time = float(data[2])
    if N not in time_map:
        time_map[N] = []
    time_map[N].append(time)


avg_time_map = {}

for N in time_map:
    x = np.log2(N)
    x = int(x)
    time_map[N].sort()
    time_map[N] = time_map[N][1:-1]
    avg_time_map[x] = np.mean(time_map[N])


plt.figure()
plt.plot(avg_time_map.keys(), avg_time_map.values(), 'ro-')
plt.xlabel('log_N')
plt.ylabel('Time')
plt.title('log_N vs Time')
plt.savefig(f'thread {numthread} log_N_vs_Time.png')
