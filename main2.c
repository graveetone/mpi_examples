#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) // головна функція
{
    int provided; // ціле число для запису порядкового номера рівня
    MPI_Init_thread(NULL, NULL, MPI_THREAD_MULTIPLE, &provided);  // починаємо багатопотокову програму
    if(provided < MPI_THREAD_MULTIPLE) // перевіряємо, чи почалося багатопотокове виконання коду
    {
        printf("Рівень підтримки потоків нижчий за необхідний.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE); // виходимо з програми і повертаємо помилку
    }
    else
    {
        int flag, len, v1, v2;  // допоміжні змінні
        char version[MPI_MAX_LIBRARY_VERSION_STRING]; // допоміжна змінна
        printf("Рівень підтримки потоків відповідає необхідному.\n"); 
        MPI_Get_version(&v1, &v2); // отримуємо версію MPI
        printf("Версія MPI (багатопотокове виконання): (%d, %d)\n", v1, v2);
        printf("Потік є: "); 
        MPI_Is_thread_main(&flag); // отримуємо булеве значення - чи знаходимось ми у головному потоці
        flag ? printf("головним\n") : printf("другорядним\n");
        MPI_Get_library_version(version, &len); // отримуємо версію бібліотеки MPI
        printf("Версія бібліотеки MPI (багатопотокове виконання): %s\n", version);
        printf("___________________________________"); // виводимо роздільник для читабельності 
    }
    
    MPI_Finalize(); // завершуємо MPI область

    return EXIT_SUCCESS; // повертаємо код успішного завершення програми
}
