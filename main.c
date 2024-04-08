#include <stdio.h>
#include <stdlib.h>

typedef struct int_array
{
    int* ptr;
    size_t length;
    size_t capacity;
}
int_array;

int_array int_array_create(void);
void int_array_append(int_array*, int new_value);
int int_array_get(int_array* array, int index);
int int_array_pop_last(int_array* array);

int main()
{
    int_array array = int_array_create();
    int_array_append(&array, 3);
    printf("%i\n", int_array_get(&array, 0));

    for(int i = 0; i < 300; i++)
    {
        int_array_append(&array, i);
    }

    int_array_pop_last(&array);
    int_array_pop_last(&array);

    int_array_append(&array, 33);
    int_array_append(&array, 22);

    for(int i = 0; i < array.length; i++)
    {
        printf("%i ", int_array_get(&array, i));
    }
    return 0;
}

int_array int_array_create(void)
{
    int_array array;
    array.length = 0;
    array.capacity = 0;
    array.ptr = NULL;
    return array;
}

void int_array_append(int_array* array, int new_value)
{
    if (array->ptr == NULL)
    {
        int* ptr = malloc(sizeof(int));
        array->length = 1;
        array->capacity = 1;
        array->ptr = ptr;
        *ptr = new_value;
    }
    else
    {
        if (array->length == array->capacity)
        {
            array->capacity *= 2;
            int* new_ptr = malloc(sizeof(int) * (array->capacity));
            printf("Reallocation happened. Capacity is: %li\n", array->capacity);

            for (int i = 0; i < array->length; i++)
            {
                new_ptr[i] = array->ptr[i];
            }

            free(array->ptr);
            array->ptr = new_ptr;
            new_ptr[array->length] = new_value;
            array->length++;
        }
        else
        {
            array->ptr[array->length] = new_value;
            array->length++;
        }

    }
}

int int_array_get(int_array* array, int index)
{
    if (index < 0 || index >= array->length)
    {
        printf("Fatal Error. Index out of bounds.\n");
        exit(1);
    }
    else
    {
        int *ptr = array->ptr;
        int element = ptr[index];
        return element;
    }
}

int int_array_pop_last(int_array* array)
{
    int last_element = array->ptr[array->length - 1];
    array->length--;
    return last_element;
}

