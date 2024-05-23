#include <cstdlib>
#include <iostream>
#include <chrono>
#include <fstream>

#include <mpi.h>

int cal(long num, std::ofstream &outFile){
    long N = num;
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  // 任务划分
  long local_length = N / size;
  long start = rank * local_length;
  long end = (rank == size - 1) ? N : (rank + 1) * local_length;
  long true_length = end - start;

  // 初始化数据: 在每个进程中生成对应数量的随机数
  std::srand(rank);
  long *a = (long *)malloc(sizeof(long) * true_length);
  for (long i = 0; i < true_length; i++)
  {
    a[i] = std::rand();
  }

  // 打印数据
  long *full_data = nullptr;

  if (rank == 0)
  {
    // 为full_data分配内存
    full_data = (long *)malloc(sizeof(long) * N);
    // 将rank 0的数据存储到full_data中
    for (long i = 0; i < local_length; i++)
    {
      full_data[i] = a[i];
    }
    // 接受数据
    for (int j = 1; j < size; j++)
    {
      long start = j * local_length;
      long end = (j == size - 1) ? N : (j + 1) * local_length;
      long true_length = end - start;
      // 存储到full_data中
      MPI_Recv(full_data + start, true_length, MPI_LONG, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }
  else
  {
    // 发送数据
    MPI_Send(a, true_length, MPI_LONG, 0, 0, MPI_COMM_WORLD);
  }
    // 初始化计时器
    auto start_time = std::chrono::high_resolution_clock::now();
  // 计算prefix sum
  // 计算每组组内的前缀和:并行计算
  long *prefix_sum = (long *)malloc(sizeof(long) * true_length);
  long recv;
  prefix_sum[0] = a[0];
  for (long i = 1; i < true_length; i++)
  {
    prefix_sum[i] = prefix_sum[i - 1] + a[i];
  }
  // 更新每一组的最后一个数：穿行计算
  for (int j = 0; j < size; j++)
  {
    if (rank == j)
    {
      // 接收上一组的最后一个数
      if (j != 0)
      {
        MPI_Recv(&recv, 1, MPI_LONG, j - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // 更新本组最后一个数
        prefix_sum[true_length - 1] += recv;
      }
      // 发送更新后的最后一个数
      if (j != size - 1)
      {
        MPI_Send(&prefix_sum[true_length - 1], 1, MPI_LONG, j + 1, 0, MPI_COMM_WORLD);
      }
    }
  }

  // 在本组内除了最后一个数外加上recv：并行计算
  if (rank != 0)
  {
    for (int i = 0; i < true_length - 1; i++)
    {
      prefix_sum[i] += recv;
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();


    // 输出时间
    if (rank == 0)
    {
    outFile << std::endl;
    std::chrono::duration<double> diff = end_time - start_time;
    outFile << size << " " << N << " " << diff.count() << std::endl;
    }

  // 释放内存
  free(a);
  free(prefix_sum);
  if (rank == 0)
    free(full_data);

  return 0;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    std::ofstream outFile("out.txt");
    int n_lst[10] = {32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    for(int j = 0 ; j < 10; j++){
    for(int i = 0; i < 10; i++){
        cal(n_lst[i], outFile);
    }}
    MPI_Finalize();
}