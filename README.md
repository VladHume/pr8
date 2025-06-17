# pr8

## Завдання 8.1  
**Питання:** Чи може виклик `count = write(fd, buffer, nbytes);` повернути в змінній `count` значення, відмінне від `nbytes`?  

**Відповідь:** Так, таке можливо. Наприклад, при записі в канали, сокети, файли з обмеженням буфера, або якщо запис переривається сигналом. У таких випадках `write` може записати менше байтів, ніж було запрошено.  

**Приклад програми:**
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd[2];
    char buffer[] = "Test write to pipe with limited read side";
    ssize_t nbytes = sizeof(buffer);
    ssize_t count;

    pipe(fd);
    if (fork() == 0) {
        close(fd[1]);
        sleep(2);
        char read_buf[10];
        read(fd[0], read_buf, sizeof(read_buf));
        return 0;
    } else {
        close(fd[0]);
        count = write(fd[1], buffer, nbytes);
        printf("Запитували записати %zd байтів, записано %zd байтів\n", nbytes, count);
        return 0;
    }
}
```

---

## Завдання 8.2  
**Умова:** Вміст файлу: `4, 5, 2, 2, 3, 3, 7, 9, 1, 5`  
Виконуються:
```c
lseek(fd, 3, SEEK_SET);
read(fd, &buffer, 4);
```
**Результат:** Буфер міститиме: `2 3 3 7`  

**Приклад програми:**
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("testfile.bin", O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    unsigned char buffer[4];
    lseek(fd, 3, SEEK_SET);
    read(fd, buffer, 4);

    printf("Buffer: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
```
Створення файлу:
```bash
printf "\x04\x05\x02\x02\x03\x03\x07\x09\x01\x05" > testfile.bin
```

---

## Завдання 8.3  
**Мета:** Знайти найгірші випадки для `qsort` та автоматизувати тестування.  

**Висновок:** Найгірші випадки: вже відсортовані масиви, обернено відсортовані масиви, масиви з однаковими елементами.  

**Приклад програми:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void generate_descending(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void test_sort(int *arr, int size) {
    int *copy = malloc(size * sizeof(int));
    memcpy(copy, arr, size * sizeof(int));
    clock_t start = clock();
    qsort(copy, size, sizeof(int), compare);
    clock_t end = clock();
    printf("Time: %lf sec\n", (double)(end - start) / CLOCKS_PER_SEC);
    free(copy);
}

int main() {
    int size = 100000;
    int *arr = malloc(size * sizeof(int));

    printf("Testing worst case (descending order)...\n");
    generate_descending(arr, size);
    test_sort(arr, size);

    printf("Testing best case (random)...\n");
    srand(time(NULL));
    for (int i = 0; i < size; i++) arr[i] = rand();
    test_sort(arr, size);

    free(arr);
    return 0;
}
```

---

## Завдання 8.4  
**Умова:** Виклик `fork()` та виведення PID.  

**Висновок:**  
- У батьківському процесі виводиться PID дочірнього процесу (значення > 0).
- У дочірньому процесі виводиться `0`.

**Приклад програми:**
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    printf("pid = %d, process id = %d\n", pid, getpid());

    return 0;
}
```

---

## Завдання 8.5  
**Мета:** Знайти випадки, коли `read()` повертає менше байтів, ніж запрошено.  

**Висновок:** Таке трапляється, коли:  
- Кінець файлу.
- Доступно менше байтів, ніж було запрошено.
- При читанні з каналу чи сокета, де дані надходять порціями.

**Приклад програми:**
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("testfile_small.bin", O_RDONLY);
    if (fd == -1) {
        perror("Open failed");
        return 1;
    }

    char buffer[100];
    ssize_t count = read(fd, buffer, sizeof(buffer));

    printf("Requested: %ld bytes, Read: %zd bytes\n", sizeof(buffer), count);

    close(fd);
    return 0;
}
```
Створення тестового файлу:
```bash
echo "Hello" > testfile_small.bin
```

---
