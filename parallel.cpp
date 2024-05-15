/*
 * Foundations of Parallel Computing II, Spring 2024.
 * Instructor: Chao Yang, Xiuhong Li @ Peking University.
 * This is a TEMPLATE for MPI parallel implementation of prefix sum.
 * Usage: ./parallel <N>
 */

#include <cstdlib>
#include <iostream>

#include <mpi.h>

int main(int argc, char *argv[])
{
  long N;
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc < 2)
    N = 32;

  N = std::atol(argv[1]);

  if (rank == 0)
  {
    std::cout << "Executing with N = " << N << ", comm size = " << size << "\n";
  }

  // 任务划分
  long start = /* Fill in your code */;
  long end = /* Fill in your code */;
  long local_length = /* Fill in your code */;

  // 初始化数据
  std::srand(rank);
  long *a = (long *)malloc(sizeof(long) * local_length);
  for (long i = 0; i < local_length; i++)
  {
    a[i] = std::rand();
  }

  // 打印数据
  /* Fill in your code*/

  // 计算prefix sum
  long *prefix_sum = (long *)malloc(sizeof(long) * local_length);
  /* Fill in your code*/

  // 打印结果
  /* Fill in your code*/

  // 释放内存
  free(a);
  free(prefix_sum);

  MPI_Finalize();

  return 0;
}
