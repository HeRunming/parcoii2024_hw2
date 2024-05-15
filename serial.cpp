/*
 * Foundations of Parallel Computing II, Spring 2024.
 * Instructor: Chao Yang, Xiuhong Li @ Peking University.
 * This is a serial implementation of prefix sum.
 */
// Usage: ./serial <N>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
  long N;

  if (argc != 2)
    N = 32;

  N = std::atol(argv[1]);

  std::cout << "Executing serial version with N = " << N << "\n";

  // 初始化数据
  std::srand(0);
  long* a = (long*)malloc(sizeof(long) * N);
  for (long i = 0; i < N; i++) {
    a[i] = std::rand() % 100;
  }
  // 打印数据
  for (long i = 0; i < N; i++) {
    std::cout << a[i] << " ";
  }
  std::cout << "\n";

  // 计算prefix sum
  long* prefix_sum = (long*)malloc(sizeof(long) * N);
  prefix_sum[0] = a[0];
  for (long i = 1; i < N; i++) {
    prefix_sum[i] = prefix_sum[i - 1] + a[i];
  }

  // 打印结果
  for (long i = 0; i < N; i++) {
    std::cout << prefix_sum[i] << " ";
  }
  std::cout << "\n";

  // 释放内存
  free(a);
  free(prefix_sum);

  return 0;
}
