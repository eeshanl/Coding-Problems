#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *nextGreaterElement(int *nums, int numsSize, int *returnSize) {
    int *rv = (int *)malloc(2 * numsSize * sizeof(int));
    int *p = rv;
    for (int i = 0; i < numsSize; i++) {
        int cur_min = 0x7FFFFFFF;
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] > nums[i]) {
                if (nums[j] < cur_min) {
                    cur_min = nums[j];
                }
            }
        }
        *p = nums[i];
        if (cur_min != 0x7FFFFFFF) {
            *(p + 1) = cur_min;
        } else {
            *(p + 1) = -1;
        }
        p += 2;
    }
    *returnSize = 2 * numsSize;
    return rv;
}

// nums[i] > 0
int *twoSum(uint32_t *nums, int numsSize, int target, int *returnSize) {
    uint32_t max = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    uint32_t mappSize = sizeof(int) * (max + 1);
    uint32_t mapp[mappSize];
    for (uint32_t i = 0; i <= max; i++) {
        mapp[i] = -1;
    }

    for (uint32_t i = 0; i < numsSize; i++) {
        mapp[nums[i]] = i;
    }

    for (uint32_t i = 0; i < numsSize; i++) {
        uint32_t diff = target - nums[i];
        if (mapp[diff] != i && mapp[diff] != -1) {
            int *rv = malloc(sizeof(int) * 2);
            rv[0] = i;
            rv[1] = mapp[diff];
            *returnSize = 2;
            return rv;
        }
    }
    return NULL;
}

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void rotate_left(int *nums, int numsSize, int k);

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void flipMatrixHorizontally(int N, int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        int left = 0;
        int right = N - 1;
        while (left < right) {
            swap(&mat[i][left], &mat[i][right]);
            left++;
            right--;
        }
    }
}

void flipMatrixVertically(int N, int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        int left = 0;
        int right = N - 1;
        while (left < right) {
            swap(&mat[left][i], &mat[right][i]);
            left++;
            right--;
        }
    }
}

void transpose(int N, int mat[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            swap(&mat[i][j], &mat[j][i]);
        }
}

void rotate90Clockwise(int N, int a[N][N]) {
    // Traverse each cycle
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
            // Swap elements of each cycle
            // in clockwise direction
            int temp = a[i][j];
            a[i][j] = a[N - 1 - j][i];
            a[N - 1 - j][i] = a[N - 1 - i][N - 1 - j];
            a[N - 1 - i][N - 1 - j] = a[j][N - 1 - i];
            a[j][N - 1 - i] = temp;
        }
    }
}

void rotate90CounterClockwise(int N, int mat[N][N]) {
    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++) {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < N - x - 1; y++) {
            // Store current cell in
            // temp variable
            int temp = mat[x][y];

            // Move values from right to top
            mat[x][y] = mat[y][N - 1 - x];

            // Move values from bottom to right
            mat[y][N - 1 - x] = mat[N - 1 - x][N - 1 - y];

            // Move values from left to bottom
            mat[N - 1 - x][N - 1 - y] = mat[N - 1 - y][x];

            // Assign temp to left
            mat[N - 1 - y][x] = temp;
        }
    }
}

int bitwise_add_one(int n) {
    // if (n == 0x7FFFFFFF) {
    //     printf("ADD BIT OVERFLOW\n");
    //     return 0;

    // }
    uint64_t current_bit =
        0x1;                   // Initialize current_bit to 1 as we are adding 1
    while (n & current_bit) {  // loop through every bit from right to
                               // left until you encounter a 0
        n = n ^ current_bit;   // Perform XOR to flip current bit.
        current_bit = current_bit << 1;  // Move current_bit to the next bit
    }
    return n | current_bit;  // Perform the final addition
}
// 0111 + 0001 = 1000

int bitwise_subtract_one(int n) {
    uint32_t current_bit = 0x1;

    // Flip all the set bits
    // until we find a 1

    // if (n == 0x80000000) {
    //     printf("BIT OVERFLOW\n");
    //     return 0;
    // }

    if (n == 0) return ~0;

    while ((n & current_bit) == 0) {  // loop through bits from right to
                                      // left until you encounter a 1
        n = n ^ current_bit;          // flip the current bit
        current_bit <<= 1;            // increment current_bit
        printf("curbit: 0x%x\n", current_bit);
    }

    // flip the rightmost 1 bit, the final subtraction
    n = n ^ current_bit;
    return n;
}

int bitwise_add(int x, int y) {
    while (y) {
        // Calculate carry
        uint64_t carry = x & y;
        // Sum without carry
        x = x ^ y;
        // Shift carry left
        y = carry << 1;
    }
    return x;
}

int stringToInteger(const char *strNum) {
    const char *ptr = strNum;
    int num = 0;
    if (*strNum == '-') ptr++;
    while (*ptr) {
        if (*ptr > '9' || *ptr < '0') {
            return -1;
        } else {
            num *= 10;
            num += *ptr - '0';
            ptr++;
        }
    }
    if (*strNum == '-') {
        return ~num + 1;
    }
    return num;
}

char *integerToString(int x, int *size) {
    *size = 0;
    int temp = x;
    while (temp) {
        temp = temp / 10;
        *size = *size + 1;
    }

    char *rv;
    temp = x;

    if (x == 0) {
        *size = 1;
        rv = (char *)calloc(*size + 1, sizeof(char));
        *rv = '0';
        return rv;
    }
    if (x < 0) {
        *size = *size + 1;  // for sign
        temp = ~x + 1;      // turn it into a positive for following loop
    }

    rv = (char *)calloc(*size + 1, sizeof(char));
    // find last index of string and build string backwards
    char *ptr = rv + *size - 1;

    while (temp) {
        *ptr = temp % 10 + '0';
        temp = temp / 10;
        ptr--;
    }
    if (x < 0) *ptr = '-';

    return rv;
}

void print2DArray(int rows, int cols, int arr[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {  // Second dimension must be specified
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void reverse_bytes_uint32(uint32_t *x) {  // no bit masking
    uint8_t *left = (uint8_t *)x;
    uint8_t *right = (left + 3);
    printf("value at left 0x%x right 0x%x\n", *left, *right);
    while (left < right) {
        uint8_t temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

void reverse_bytes_uint32_bitmask(uint32_t *x) {  // with bit masking
    *x = ((*x & 0xFF) << 24) | ((*x & 0xFF00) << 8) | ((*x & 0xFF0000) >> 8) |
         ((*x & 0xFF000000) >> 24);
}

void swap_nibbles(uint8_t *bytes, uint32_t N) {
    uint32_t i = 0;
    uint8_t *ptr = bytes;
    while (i < N) {
        *ptr = (*ptr & 0xF) << 4 | (*ptr & 0xF0) >> 4;
        ptr++;
        i++;
    }
}

uint32_t reverseBits(uint32_t n) {
    uint32_t rev = 0;
    uint8_t shift = sizeof(n) * 8 - 1;

    // traversing bits of 'n' from the right
    while (n) {
        rev |= (n & 0x1) << shift;

        shift--;

        n >>= 1;
    }

    // required number
    return rev;
}

// reverse array
void reverse(int nums[], int start, int end) {
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

// rotate right

// [0, 1, 2, 3] k = 2 -> [2, 3, 0, 1]
void rotate_right(int *nums, int numsSize, int k) {
    k = k % numsSize;  // 2
    // [0, 1, 2, 3]
    reverse(nums, 0, numsSize - 1);  // reverse whole array
    // [3, 2, 1, 0]
    reverse(nums, 0, k - 1);  // reverse first k elements
    // [2, 3, 1, 0]
    reverse(nums, k, numsSize - 1);  // reverse [k:numSize-1]
    // [2, 3, 0, 1]
    // rotate_left(nums, numsSize, numsSize - k);
}

void rotate_matrix_rows_right(int N, int mat[][N], int k) {
    for (int i = 0; i < N; i++) {
        rotate_right(mat[i], N, k);
    }
}

// rotate left
void rotate_left(int *nums, int numsSize, int k) {
    // [0, 1, 2, 3] k = 3 -> [3, 0, 1, 2]
    // rotate_right(nums, numsSize, numsSize - k);
    k = k % numsSize;
    for (int x = 0; x < k; x++) {
        int temp = nums[0];
        for (int i = 0; i < numsSize - 1; i++) {
            nums[i] = nums[i + 1];
        }
        nums[numsSize - 1] = temp;
    }
}

int binary_search(int array[], int start_index, int end_index, int element) {
    while (start_index <= end_index) {
        int middle = start_index + (end_index - start_index) / 2;
        if (array[middle] == element) return middle;
        if (array[middle] < element)
            start_index = middle + 1;
        else
            end_index = middle - 1;
    }
    return -1;
}

/**
 * Partitions an array around a pivot element and returns the index of
 * the pivot element in the partitioned array.
 *
 * @param arr The array to be partitioned.
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 *
 * @return The index of the pivot element in the partitioned array.
 *
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Sorts an array in non-decreasing order using the quicksort algorithm.
//
// @param arr The array to be sorted.
// @param low The starting index of the array to be sorted.
// @param high The ending index of the array to be sorted.
//
// @return None.
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Linked List

Node *reverseLinkedList(Node *front) {
    Node *prev = NULL;
    Node *current = front;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

Node *findMiddle(Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

int detectCycle(struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;  // Cycle detected
    }
    return 0;  // No cycle
}

// malloc

// Define the size of each memory block
#define BLOCK_SIZE 1024

// Define the structure for a memory block
typedef struct Block {
    size_t size;         // Size of the memory block
    struct Block *next;  // Pointer to the next block in the free list
} Block;

// Global pointer to the head of the free list
Block *free_list = NULL;

// Custom memory allocation function
void *my_malloc(size_t size) {
    Block *block = free_list;
    Block *prev = NULL;

    // Search the free list for a suitable block
    while (block != NULL) {
        // If the block size is greater than or equal to the requested
        // size
        if (block->size >= size) {
            // If the block size is larger than the requested size plus
            // the size of the Block structure
            if (block->size > size + sizeof(Block)) {
                // Create a new block with the remaining size
                Block *new_block =
                    (Block *)((char *)block + size + sizeof(Block));
                new_block->size = block->size - size - sizeof(Block);
                new_block->next = block->next;

                // Update the size of the current block
                block->size = size;
                block->next = new_block;
            }

            // If the block is not the head of the free list
            if (prev != NULL) {
                // Remove the block from the free list by updating the
                // previous block's next pointer
                prev->next = block->next;
            } else {
                // If the block is the head of the free list, update the
                // free_list pointer
                free_list = block->next;
            }

            // Return the address of the allocated memory (after the
            // Block structure)
            return (void *)((char *)block + sizeof(Block));
        }

        // Move to the next block in the free list
        prev = block;
        block = block->next;
    }

    // If no suitable block is found, request memory from the system
    // using sbrk
    block = (Block *)sbrk(size + sizeof(Block));
    printf("SBRK CALLED");
    if (block == (void *)-1) {
        // If sbrk fails, return NULL to indicate allocation failure
        return NULL;
    }

    // Initialize the new block
    block->size = size;
    block->next = NULL;

    // Return the address of the allocated memory (after the Block
    // structure)
    return (void *)((char *)block + sizeof(Block));
}

// Custom memory deallocation function
void my_free(void *ptr) {
    // Get the address of the Block structure (before the allocated
    // memory)
    Block *block = (Block *)((char *)ptr - sizeof(Block));

    // Add the block to the head of the free list
    block->next = free_list;
    free_list = block;
}

void *mem_alligned_malloc(unsigned long size, unsigned long align) {
    void *rv = malloc(size + align);
    uint64_t mod = (uint64_t)rv % (uint64_t)align;
    if (mod == 0) {
        return rv;
    } else {
        rv = (void *)((uint64_t)rv + (uint64_t)align - mod);
        return rv;
    }
}

// #pragma pack(push, 1)  // Set packing to 1 byte
typedef struct MyStruct {
    char c;    // 1 byte
    double d;  // 8 bytes
    int i;     // 4 bytes
} MyStruct;
// #pragma pack(pop)      // Restore default packing

// ATOMIC QUEUE

#include <semaphore.h>
#include <stdatomic.h>

typedef struct {
    int *buffer;
    atomic_size_t head;
    atomic_size_t tail;
    size_t size;
    sem_t empty_slots;   // Semaphore for available empty slots
    sem_t filled_slots;  // Semaphore for available filled slots
} atomic_ring_buffer_t;

void init_atomic_ring_buffer(atomic_ring_buffer_t *arb, size_t size) {
    arb->buffer = malloc(size * sizeof(int));
    atomic_init(&arb->head, 0);
    atomic_init(&arb->tail, 0);
    arb->size = size;
    sem_init(&arb->empty_slots, 0,
             size);  // Initially, all slots are empty
    sem_init(&arb->filled_slots, 0,
             0);  // Initially, no slots are filled
}

void destroy_atomic_ring_buffer(atomic_ring_buffer_t *arb) {
    free(arb->buffer);
    sem_destroy(&arb->empty_slots);
    sem_destroy(&arb->filled_slots);
}

void enqueue(atomic_ring_buffer_t *arb, int value) {
    sem_wait(&arb->empty_slots);  // Wait until there is an empty slot
    size_t head = atomic_load(&arb->head);

    arb->buffer[head] = value;

    atomic_store(&arb->head, (head + 1) % arb->size);
    sem_post(&arb->filled_slots);  // Signal that there is a filled slot
}

void dequeue(atomic_ring_buffer_t *arb, int *value) {
    sem_wait(&arb->filled_slots);  // Wait until there is a filled slot
    size_t tail = atomic_load(&arb->tail);

    *value = arb->buffer[tail];

    atomic_store(&arb->tail, (tail + 1) % arb->size);
    sem_post(&arb->empty_slots);  // Signal that there is an empty slot
}

void test_atomic_ring_buffer() {
    atomic_ring_buffer_t arb;
    init_atomic_ring_buffer(&arb, 4);  // Size 4 for simplicity

    enqueue(&arb, 10);
    printf("Enqueued 10\n");

    enqueue(&arb, 20);
    printf("Enqueued 20\n");

    int value;
    dequeue(&arb, &value);
    printf("Dequeued %d\n", value);

    dequeue(&arb, &value);
    printf("Dequeued %d\n", value);

    // Clean up
    destroy_atomic_ring_buffer(&arb);
}

int main() {
    int nums[7] = {1, 2, 3, 4, 5, 6, 7};
    // printf("size: %lu\n", sizeof(int));
    // int number = 0x80000000;
    // printf("OG: 0x%x\n", number);
    // int result = bitwise_add_one(number);
    // printf("The result of adding 1 to %d using bitwise operations is
    // %d\n", number, result);

    // result = bitwise_subtract_one(number);
    // printf("The result of subtracting 1 from %d using bitwise
    // operations is %d\n", number, result);

    // result = bitwise_add(840, -420);
    // printf("Full adder = %d\n", result);

    // char* number = "123456789\0";
    // printf("%d\n", stringToInteger(number));
    printf("mystruct size: %lu\n", sizeof(MyStruct));
    int matrix[4][4] = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}

    };
    rotate90Clockwise(4, matrix);
    print2DArray(4, 4, matrix);
    int matrix2[4][4] = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}

    };
    printf("\n\n");
    rotate90CounterClockwise(4, matrix2);
    print2DArray(4, 4, matrix2);

    int matrix3[4][4] = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}

    };
    printf("\n\n");
    transpose(4, matrix3);
    print2DArray(4, 4, matrix3);

    int matrix4[4][4] = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}

    };
    printf("\n\n");
    // matrix3 now same as matrix2 which is rotate90CounterClockwise !
    flipMatrixVertically(4, matrix3);
    print2DArray(4, 4, matrix3);

    int matrix5[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    printf("\n\n");
    rotate_matrix_rows_right(4, matrix5, 1);
    print2DArray(4, 4, matrix5);
    // rotate_right(nums, 7, 2);
    // rotate_left(nums, 7, 3);
    // printArray(nums, 7);
    uint32_t x = 0xAA0102BB;
    reverse_bytes_uint32(&x);
    printf("rev: %x\n", x);
    x = 0xAA0102BB;

    reverse_bytes_uint32_bitmask(&x);
    printf("rev: %x\n", x);

    uint8_t m = -1;
    printf("hex: 0x%x\n", m);
    printf("%lu\n", sizeof(const char *));

    int stoi = stringToInteger("-69420");
    int s = 0;
    char *itos = integerToString(-420, &s);
    printf("%s, size: %d\n", itos, s);
    free(itos);

    // Allocate memory for an integer
    int *num1 = (int *)my_malloc(sizeof(int));
    // Use the allocated memory
    *num1 = 10;
    // Print the values stored in the allocated memory
    printf("num1: %d\n", *num1);
    my_free(num1);

    // Allocate memory for another integer
    int *num2 = (int *)my_malloc(sizeof(int));
    *num2 = 20;
    printf("num2: %d\n", *num2);
    // Free the allocated memory
    my_free(num2);

    int c = 0;
    Block *cur = free_list;
    while (cur != NULL) {
        c++;
        cur = cur->next;
    }

    printf("free list coun: %d\n", c);
    int z = 0x80000000;
    z = z >> 1;

    test_atomic_ring_buffer();
    printf("%x\n", z);  // top bit still one, means still negative
    size_t ss = 0xFFFFFFFFFFFFFFFF;
    printf("size_t size: %lu and value: %zu\n", sizeof(size_t), ss);

    for (int i = 0; i < 10; i++) {
        void *p = mem_alligned_malloc(100, 4);
        if ((uint64_t)p % 4 != 0) {
            printf("p: %p\n", p);
        } else {
            printf("mem_alligned works: %d\n", i);
        }
    }

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s = 0;
    int *p = nextGreaterElement(arr, 10, &s);
    for (int i = 0; i < s; i += 2) {
        printf("%d -> %d\n", p[i], p[i + 1]);
    }
    printf(" atomic_size_t: %lu\n", sizeof(atomic_size_t));
    printf(" atomic_size_t: %lu\n", sizeof(atomic_uint));

    return 0;
}