#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
/**
 * @brief Illustrate how to create a window.
 * @details This application consists of two MPI processes. MPI process 1
 * exposes a window containing 2 integers. The first one is initialised to 0 and
 * will be overwritten by MPI process 0 via MPI_Put to become 12345. The second
 * will be initialised to 67890 and will be read by MPI process 0 via MPI_Get.
 * After these two commands are issued, synchronisation takes place via
 * MPI_Win_fence and each MPI process prints the value that came from the other
 * peer.
 **/
int main(int argc, char* argv[]) // головна функція
{
    MPI_Init(&argc, &argv);  // починаємо MPI область
 
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);  // отримуємо кількість процесів
    if(comm_size != 2) // якщо процесів не 2
    { 
        printf("Програма написана для запуску на 2 процесах, а не на %d.\n", comm_size);
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE); // повертаємо код помилки 
    }
 // інакше
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // записуємо у змінну номер поточного процесу
 
    // створюємо вікно процесу
    const int ARRAY_SIZE = 2;
    int window_buffer[ARRAY_SIZE];
    MPI_Win window;
    if(my_rank == 1)  // якщо працюємо з першим процесом
    {
        window_buffer[1] = 67890; // записуємо значення в масив
    }// створюємо вікно на основі масиву. Параметр same_disp_unit йде у виклику функції третім і рівний sizeof(int)
    MPI_Win_create(window_buffer, ARRAY_SIZE * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &window);
    MPI_Win_fence(0, window); // для синхронізації доступу до вікна віддаленими процесами
 
    int remote_value; // допоміжна змінна
    if(my_rank == 0) // якщо працюємо з нульовим процесом
    {
        // зчитуємо значення з вікна першого процесу
        MPI_Get(&remote_value, 1, MPI_INT, 1, 1, 1, MPI_INT, window);
 
        // змінюємо значення у вікні першого потоку
        int my_value = 12345;
        MPI_Put(&my_value, 1, MPI_INT, 1, 0, 1, MPI_INT, window);
    }
 
    // синхронізація
    MPI_Win_fence(0, window);
 
    if(my_rank == 0) // виводимо поточний стан у контексті нульового процесу
    {
        printf("[MPI процес 0] Значення, отримане з вікна процесу 1: %d.\n", remote_value);
    }
    else // виводимо поточний стан у контексті першого процесу
    {
        printf("[MPI процес 1] Значення, яке записав в моє вікно процес 0: %d.\n", window_buffer[0]);
    }
 
    // знищуємо вікно для звільнення ресурсів
    MPI_Win_free(&window);
 
    MPI_Finalize(); // завершуємо MPI область
  
    return EXIT_SUCCESS; // повертаємо значення успішного виконання програми
}
