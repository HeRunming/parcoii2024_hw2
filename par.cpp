#include <cstdlib>
#include <iostream>

#include <mpi.h>

int main(int argc, char *argv[])
{
    long N;
    int rank, size;
    MPI_Init(&argc, &argv); // 初始化MPI环境
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // 获取当前进程的rank,rank: 进程的唯一标识
    MPI_Comm_size(MPI_COMM_WORLD, &size); // 获取进程总数

    if (argc < 2)
        N = 32;
    N = std::atol(argv[1]);

    if (rank == 0)
    {
        std::cout << "Executing with N = " << N << ", comm size = " << size << "\n";
    }

    // 任务划分
    long local_length = N / size;
    long start = rank * local_length;
    long end = (rank == size - 1) ? N : (rank + 1) * local_length;

    // 初始化数据
    std::srand(rank);
    long *a = (long *)malloc(sizeof(long) * local_length);
    for (long i = 0; i < local_length; i++)
    {
        a[i] = std::rand() % 100; // 保持和串行代码一致的数据生成方式
    }

    // 打印数据
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (i == rank)
            {
                for (long j = 0; j < local_length; j++)
                {
                    std::cout << a[j] << " ";
                }
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
        std::cout << "\n";
    }

    // 计算prefix sum局部和
    long *prefix_sum = (long *)malloc(sizeof(long) * local_length);
    prefix_sum[0] = a[0];
    for (long i = 1; i < local_length; i++)
    {
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    // 全局前缀和通信
    long *global_sums = (long *)malloc(sizeof(long) * size);
    MPI_Allgather(&prefix_sum[local_length - 1], 1, MPI_LONG, global_sums, 1, MPI_LONG, MPI_COMM_WORLD);

    // 调整局部前缀和
    long offset = 0;
    for (int i = 0; i < rank; i++)
    {
        offset += global_sums[i];
    }
    for (long i = 0; i < local_length; i++)
    {
        prefix_sum[i] += offset;
    }

    // 打印结果
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (i == rank)
            {
                for (long j = 0; j < local_length; j++)
                {
                    std::cout << prefix_sum[j] << " ";
                }
            }
            MPI_Barrier(MPI_COMM_WORLD);
        }
        std::cout << "\n";
    }

    // 释放内存
    free(a);
    free(prefix_sum);
    free(global_sums);

    MPI_Finalize();

    return 0;
}