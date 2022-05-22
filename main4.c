#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[]) // головна функція
{
    int rank; // допоміжна змінна для збереження номера процесу
    MPI_Init(&argc,&argv); // ініціалізуємо MPI
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); // записуємо номер процесу у змінну

    MPI_Request request; // допоміжна змінна типу "запит"
    MPI_File fh; // допоміжна змінна для зберігання файлу

    if (!rank) // якщо поточний процес нульовий 
    { 
    	// відкриваємо або створюємо і відкриваємо файл "test.txt" для запису
    	MPI_File_open(MPI_COMM_SELF, "test.txt",MPI_MODE_CREATE | MPI_MODE_WRONLY,MPI_INFO_NULL,&fh);
            char buf[42]; // допоміжний масив - буфер
            snprintf(buf,42,"%s \n","Hello from qubeet"); // записуємо в буфер повідомлення
            MPI_File_iwrite_all(fh,buf,strlen(buf), MPI_CHAR, &request); // записуємо у файл 
        MPI_File_close(&fh); // закриваємо файл
    }

    MPI_Finalize(); // завершуємо роботу з MPI
    return 0;
}