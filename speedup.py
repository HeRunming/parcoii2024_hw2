threads = [1,2,4,8,16]
Ns = [32,64,128,256,512,1024,2048,4096,8192,16384]
def filename(thread):
    return "thread" + str(thread) + "avg_time.txt"


full_data = []
for thread in threads:
    with open(filename(thread), 'r') as f:
        datas = f.readlines()
        for data in datas:
            data = data.strip().split()
            full_data.append((thread, int(data[0]), float(data[1])))


with open("speedup.txt", 'w') as f:
    for thread in threads:
        f.write("thread" + str(thread) + ":\n")
        for N in Ns:
            base_time = 0
            for data in full_data:
                if data[0] == 1 and data[1] == N:
                    base_time = data[2]
                    break
            for data in full_data:
                if data[0] == thread and data[1] == N:
                    speedup = base_time / data[2]
                    f.write("N=" + str(N) + ", speedup=" + str(speedup) + "\n")
        f.write("\n")




