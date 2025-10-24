/*  --------------------- sparse vectors ---------------------
* x, y are two vectors of size 10000 each
*
* generate 'm' random points in [0, 9999] and put the coo in x
* do the same with y 
*
* Calculate the sum 'z' of the two vectors
* count the elements in 'z' != 1
*
* Hint: use recursive memory release
*
* Use Linked Lists!
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_IDX 10

typedef struct Vector {
    int index;
    int value;
    struct Vector* next;
} Vector;

// ordered makes sense to optimize operations such as the sum
int add_sorted(Vector** vec, int index, int value) {
    Vector* prev = NULL;
    Vector* curr = *vec;

    // tTraverse to find the place to insert
    while (curr && curr->index < index) {
        prev = curr;
        curr = curr->next;
    }

    // Already exists
    if (curr && curr->index == index) {
        return 1;
    }

    // Allocate new node
    Vector* new_node = (Vector*) malloc(sizeof(Vector));
    if (!new_node) {
        perror("malloc failed");
        return 1;
    }
    new_node->index = index;
    new_node->value = value;
    new_node->next = curr;

    if (prev) {
        prev->next = new_node;
    } else {
        *vec = new_node;
    }
    return 0;
}

Vector* add_next(Vector** tail, int index, int value) {
    Vector* new_node = (Vector*) malloc(sizeof(Vector));
    if (!new_node) {
        perror("malloc failed");
        return NULL;
    }
    new_node->index = index;
    new_node->value = value;
    new_node->next = NULL;

    if (*tail) {
        (*tail)->next = new_node;
    }
    *tail = new_node;
    return new_node;
}

void populate_vec(Vector** vec, int m) {
    for (int i = 0; i < m; i++) {
        int index = rand() % MAX_IDX;
        // Only add if not already present
        if (add_sorted(vec, index, 1) == 1) {
            i--; // Try again
        }
    }
}

Vector* sum_vecs(Vector* x, Vector* y) {
    Vector* z = NULL;
    Vector* z_tail = NULL;
    Vector* curr_x = x;
    Vector* curr_y = y;
    int curr_value;
    int curr_index;

    // since the lists are ordered we can easily 
    while (curr_x && curr_y) {
        if (curr_x->index == curr_y->index) {
            curr_index = curr_x->index;
            curr_value = curr_x->value + curr_y->value;
            curr_x = curr_x->next;
            curr_y = curr_y->next;
        } else if (curr_x->index < curr_y->index) {
            curr_index = curr_x->index;
            curr_value = curr_x->value;
            curr_x = curr_x->next;
        } else {
            curr_index = curr_y->index;
            curr_value = curr_y->value;
            curr_y = curr_y->next;
        }
        Vector* new_node = add_next(&z_tail, curr_index, curr_value);
        if (!z) z = new_node; // Here should enter only the first time
    }
    // only x values remain
    while (curr_x) {
        Vector* new_node = add_next(&z_tail, curr_x->index, curr_x->value);
        curr_x = curr_x->next;
    }
    // only y values remain
    while (curr_y) {
        Vector* new_node = add_next(&z_tail, curr_y->index, curr_y->value);
        curr_y = curr_y->next;
    }
    return z;
}

// didn't understand, including zeros (?)
int count_non_one_incl_zeros(Vector* vec) {
    // it's easier to count the ones and subtract from the total
    int count = 0;
    for (Vector* curr = vec; curr; curr = curr->next) {
        if (curr->value == 1) {
            count++;
        }
    }
    return MAX_IDX - count;
}

// didn't understand, including zeros (?)
int count_non_one(Vector* vec) {
    // it's easier to count the ones and subtract from the total
    int count = 0;
    for (Vector* curr = vec; curr; curr = curr->next) {
        if (curr->value != 1) {
            count++;
        }
    }
    return count;
}

// recursive memory release
void free_vec(Vector* vec) {
    if (!vec) return;
    free_vec(vec->next);
    free(vec);
}

#ifdef DEBUG
    void print_vec(Vector* vec) {
        for (Vector* curr = vec; curr; curr = curr->next) {
            printf("  idx: %d\t val: %d\n", curr->index, curr->value);
        }
        printf("\n");
    }
#endif

int main(int argc, char* argv[]) {

    if (argc < 2 || argc > 4) {
        printf("Usage: %s <#points x> <#points y>\n", argv[0]);
        printf("If only one argument is provided, it will be used for both x and y\n");
        return 1;
    }

    int m_x, m_y;
    
    m_x = atoi(argv[1]);
    if (argc == 3)
        m_y = atoi(argv[2]);
    else
        m_y = m_x;

    if (m_x < 1 || m_x > MAX_IDX || m_y < 1 || m_y > MAX_IDX) {
        printf("Provide 1 <= #points <= %d\n", MAX_IDX);
        return 1;
    }

    srand(time(0));

    Vector* vec_x = NULL;
    Vector* vec_y = NULL;

    populate_vec(&vec_x, m_x);
    populate_vec(&vec_y, m_y);

    Vector* vec_z = sum_vecs(vec_x, vec_y);

    #ifdef DEBUG
        printf("Vector X:\n");
        print_vec(vec_x);
        printf("Vector Y:\n");
        print_vec(vec_y);
        printf("Vector Z (sum):\n");
        print_vec(vec_z);
    #endif

    printf("Number of elements in z != 1 (including zeros): %d\n", count_non_one_incl_zeros(vec_z));
    printf("Number of elements in z != 1 (excluding zeros): %d\n", count_non_one(vec_z));

    free_vec(vec_x);
    free_vec(vec_y);
    free_vec(vec_z);

    return 0;
}
