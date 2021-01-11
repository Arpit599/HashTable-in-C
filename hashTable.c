#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 10

int size = 0;

struct dataItem *search(int);
void delete (int);
void display();
void initArray();
int hashFun(int);
void insert(int, int);

struct dataItem
{
    int key;
    int data;
};

struct dataItem* hashArray[MAX];

void initArray()
{
    for (int i = 0; i < MAX; i++)
        hashArray[i] = NULL;
}

int hashFun(int key)
{
    return key % MAX;
}

void insert(int key, int data)
{
    if (size == MAX)
    {
        printf("Hash table is already full\n");
        return;
    }
    struct dataItem *new = (struct dataItem *)malloc(sizeof(struct dataItem));
    new->data = data;
    new->key = key;

    int hashCode = hashFun(key);
    while (hashArray[hashCode] != NULL && hashArray[hashCode]->key != -1)
    {
        if (hashArray[hashCode]->key == key)
        {
            printf("Element already present, therefore updating the value\n");
            break;
        }
        hashCode++;
        hashCode %= MAX;
    }
    hashArray[hashCode] = new;
    size++;
}

void delete (int key)
{
    struct dataItem *item = search(key);
    if (item == NULL)
    {
        printf("Element not present for deletion\n");
        return;
    }
    item->data = -1;
    item->key = -1;
    size--;
    printf("Element deleted successfully\n");
}

struct dataItem* search(int key)
{
    if(size == 0)
    {
        printf("Hash table is empty");
        return NULL;
    }
    int hashIndex = hashFun(key);

    while (hashArray[hashIndex] != NULL)
    {
        if (hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];
        hashIndex++;
        hashIndex %= MAX;
    }
    return NULL;
}

void display()
{
    for (int i = 0; i < MAX; i++)
    {
        if (hashArray[i] != NULL && hashArray[i]->key != -1)
        {
            printf("(key = %d, value = %d) ", hashArray[i]->key, hashArray[i]->data);
        }
        else if (hashArray[i] == NULL || hashArray[i]->key == -1)
        {
            printf("~~ ");
        }
    }
    printf("\n");
}

int main(void)
{
    initArray();
    while (true)
    {
        printf("Search an element : 1\n");
        printf("Delete an element : 2\n");
        printf("Insert an element : 3\n");
        printf("Display the table : 4\n");
        printf("Enter your choice : ");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (size == 0)
            {
                printf("Hash table is already empty\n");
                break;
            }
            printf("Enter the key to be searched : ");
            int searchKey;
            scanf("%d", &searchKey);
            struct dataItem *item = search(searchKey);
            if (item == NULL)
                printf("Element not found\n");
            else
                printf("Element is present in the hash table\n");
            break;

        case 2:
            if (size == 0)
            {
                printf("Hash table is already empty\n");
                break;
            }
            printf("Enter the key to be deleted : ");
            int deleteKey;
            scanf("%d", &deleteKey);
            delete (deleteKey);
            break;

        case 3:
            printf("Enter the key, value to be inserted : ");
            int key, value;
            scanf("%d %d", &key, &value);
            insert(key, value);
            break;

        case 4:
            display();
            break;

        default:
            break;
        }
    }
    return 0;
}