+--------------------------------------+----------------------------------------+-------------------------+---------------------------------------------+---------------------+
|            Method Name               |      Memory Allocation Mechanism       | Number of malloc Calls  |           Access Mechanism                  | Number of free Calls|
+--------------------------------------+----------------------------------------+-------------------------+---------------------------------------------+---------------------+
| Single pointer and a 1D array        | Single contiguous block for all values | 1                       | ptr[i * c + j]                              | 1                   |
| Using array of pointers              | Separate block for each row            | r (number of rows)      | arr[i][j] or *(*(arr+i)+j)                  | r                   |
| Pointer to pointer                   | Separate block for each row            | r + 1 (rows + arr ptr)  | arr[i][j] or *(*(arr+i)+j)                  | r + 1               |
| Double pointer and one malloc        | One block for all (data + pointers)    | 1                       | arr[i][j] or *(*(arr+i)+j)                  | 0                   |
| Pointer to variable length array     | Single contiguous block for all values | 1                       | (*arr)[i][j]                                | 1                   |
+--------------------------------------+----------------------------------------+-------------------------+---------------------------------------------+---------------------+


```c
//// single pointer and a 1D array
int main(void)
{
    int r = 3, c = 4;

    int* ptr = malloc((r * c) * sizeof(int));

    /* Putting 1 to 12 in the 1D array in a sequence */
    for (int i = 0; i < r * c; i++)
        ptr[i] = i + 1; // ptr[i] is equivalent to *(ptr + i), we can rewrite this as *(ptr + i) = i + 1

    /* Accessing the array values as if it was a 2D array */
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%d ", ptr[i * c + j]); // ptr[i*c + j] is equivalent to *(ptr + i*c + j)
        printf("\n");
    }

    free(ptr);

    return 0;
}
```

```c
//// using array of pointers
int main()
{
    int r = 3, c = 4, i, j, count;

    int* arr[r]; // pointer to an array of r integers
    for (i = 0; i < r; i++)
        arr[i] = (int*)malloc(c * sizeof(int));

    // Note that arr[i][j] is same as *(*(arr+i)+j)
    count = 0;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            arr[i][j] = ++count; // Or *(*(arr+i)+j) = ++count

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            printf("%d ", arr[i][j]);

    /* Code for further processing and free the
      dynamically allocated memory */

    for (int i = 0; i < r; i++)
        free(arr[i]);

    return 0;
}
```

```c
//// pointer to pointer
int main()
{
    int r = 3, c = 4, i, j, count;

    int** arr = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        arr[i] = (int*)malloc(c * sizeof(int));

    // Note that arr[i][j] is same as *(*(arr+i)+j)
    count = 0;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            printf("%d ", arr[i][j]);

    /* Code for further processing and free the
       dynamically allocated memory */

    for (int i = 0; i < r; i++)
        free(arr[i]);

    free(arr);

    return 0;
}
```

```c
//// double pointer and one malloc
int main()
{
    int r=3, c=4, len=0;
    int *ptr, **arr;
    int count = 0,i,j;

    len = sizeof(int *) * r + sizeof(int) * c * r;
    arr = (int **)malloc(len);

    // ptr is now pointing to the first element in of 2D array
    ptr = (int *)(arr + r);

    // for loop to point rows pointer to appropriate location in 2D array
    for(i = 0; i < r; i++)
        arr[i] = (ptr + c * i);

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            printf("%d ", arr[i][j]);

    return 0;
}
```

```c
//// pointer to variable length array
int main()
{
    int row = 3, col = 4, i, j, count;

    int (*arr)[row][col] = malloc(sizeof *arr);

    count = 0;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            (*arr)[i][j] = ++count;

    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            printf("%d ", (*arr)[i][j]);

    free(arr);

    return 0;
}
```