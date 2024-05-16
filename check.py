import os

def read_file(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()
    return lines

lines = read_file('out.txt')


data_line = lines[1].strip().split()[1:] 
data = [int(i) for i in data_line]


result_line = lines[2].strip().split()
result = [int(i) for i in result_line]


if len(data) != len(result):
    print('Length not equal')
    exit(0)


if data[0] != result[0]:
    print("Error at Index: 0")


for i in range(1, len(data)):
    if result[i] - result[i-1] != data[i]:
        print("Error at Index: ", i)
        exit(0)


print("Correct")
