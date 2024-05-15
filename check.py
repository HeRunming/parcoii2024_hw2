import os
import numpy as np
import pandas as pd
import math

# 按行读取文件，并将每一行保存为一个字符串，返回一个字符串列表
def read_file(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()
    return lines

lines = read_file('out.txt')

data = lines[1].split()[1:]

data = [int(i) for i in data]

result = lines[2].split()
result = [int(i) for i in result]

if len(data) != len(result):
    print('Length not equal')
    exit(0)
if data[0] != result[0]:
    print("Error at Index: 0")
for i in range(1,len(data)):
    if result[i] - result[i-1] != data[i]:
        print("Error at Index: ", i)
        exit(0)

print("Correct")

print(lines[3])