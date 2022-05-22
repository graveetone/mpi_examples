#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) // головна функція
{
    MPI_Init(&argc, &argv);  // починаємо паралельне виконання  
    
    int a[10];               // масив цілих чисел

    MPI_Aint address1;      // порожня змінна, в яку запишемо адресу третього числа з масиву а
    MPI_Get_address(&a[2], &address1);  // записуємо адресу числа
    
    MPI_Aint address2;         // порожня змінна, в яку запишемо адресу дев'ятого числа з масиву а  
    MPI_Get_address(&a[8], &address2);  // записуємо адресу числа
    
    MPI_Aint address_diff;            // змінна для збереження різниці адрес
    address_diff = MPI_Aint_diff(address2, address1);  // виконуємо віднімання однієї адреси від іншої і зберігаємо в масив
    
    printf("Різниця між адресами третього і дев'ятого цілих чисел з масиву а рівна %ld байтів\n", address_diff); // виводимо знаходжену різницю в байтах
    
    MPI_Finalize();  // завершуємо роботу MPI
    
    return EXIT_SUCCESS;  // повертаємо код успішного виконання програми
}
