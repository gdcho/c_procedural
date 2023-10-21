+--------------------------------------+----------------------------------------+-------------------------+---------------------------------------------+---------------------+
|            Method Name               |      Memory Allocation Mechanism       | Number of malloc Calls  |           Access Mechanism                  | Number of free Calls|
+--------------------------------------+----------------------------------------+-------------------------+---------------------------------------------+---------------------+
| Single pointer and a 1D array        | Single contiguous block for all values | 1                       | ptr[i * c + j]                              | 1                   |
| Using array of pointers              | Separate block for each row            | r (number of rows)      | arr[i][j] or *(*(arr+i)+j)                  | r                   |
| Pointer to pointer                   | Separate block for each row            | r + 1 (rows + arr ptr)  | arr[i][j] or *(*(arr+i)+j)                  | r + 1               |
| Double pointer and one malloc        | One block for all (data + pointers)    | 1                       | arr[i][j] or *(*(arr+i)+j)                  | 0                   |
| Pointer to variable length array     | Single contiguous block for all values | 1                       | (*arr)[i][j]                                | 1                   |
+--------------------------------------+----------------------------------------+-------------------------+---------------------------------------------+---------------------+
