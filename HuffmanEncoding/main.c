#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 50

struct Node {
    char item;
    int freq;
    struct Node *left, *right;
};

struct Heap {
    int size;
    int capacity;
    struct Node **array;
};

struct Node *init(char item, int freq) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->left = NULL;
    n->right = NULL;
    n->item = item;
    n->freq = freq;

    return n;
}

struct Heap *createHeap(int capacity) {
    struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct Node **)malloc(heap->capacity * sizeof(struct Node *));
    return heap;
}

void Heapify(struct Heap *h, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < h->size && h->array[left]->freq < h->array[smallest]->freq)
        smallest = left;

    if (right < h->size && h->array[right]->freq < h->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        struct Node *temp = h->array[smallest];
        h->array[smallest] = h->array[idx];
        h->array[idx] = temp;
        Heapify(h, smallest);
    }
}

struct Node *extractMin(struct Heap *h) {
    struct Node *temp = h->array[0];
    h->array[0] = h->array[h->size - 1];
    --h->size;
    Heapify(h, 0);
    return temp;
}

void insertHeap(struct Heap *Heap, struct Node *HeapNode) {
    ++Heap->size;
    int i = Heap->size - 1;

    while (i && HeapNode->freq < Heap->array[(i - 1) / 2]->freq) {
        Heap->array[i] = Heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    Heap->array[i] = HeapNode;
}

void buildHeap(struct Heap *h) {
    int n = h->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        Heapify(h, i);
}

int isLeaf(struct Node *root) {
    return !(root->left) && !(root->right);
}

struct Heap *createAndBuildHeap(char item[], int freq[], int size) {
    struct Heap *Heap = createHeap(size);

    for (int i = 0; i < size; ++i)
        Heap->array[i] = init(item[i], freq[i]);

    Heap->size = size;
    buildHeap(Heap);

    return Heap;
}

struct Node *buildHuffmanTree(char item[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct Heap *Heap = createAndBuildHeap(item, freq, size);

    while (Heap->size != 1) {
        left = extractMin(Heap);
        right = extractMin(Heap);

        top = init('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertHeap(Heap, top);
    }
    return extractMin(Heap);
}

void printHCodes(struct Node *root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printHCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printHCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("  %c   | ", root->item);
        int i;
        for (i = 0; i < top; ++i)
            printf("%d", arr[i]);
            printf("\n");
    }
}

void HuffmanCodes(char item[], int freq[], int size) {
    struct Node *root = buildHuffmanTree(item, freq, size);

    int arr[MAX_TREE_HT], top = 0;

    printHCodes(root, arr, top);
}


int main() {
    char arr[] = {'A', 'B', 'C', 'D'};
    int freq[] = {8, 5, 3, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Text  = ABCCDABDADADBCADBADABA\n");
    printf("Before Compress = 10111100011101000101001001001111111101111000101110001000110011000010110010010"
           "110101001100000011000110001110111110100111111010001000000011100011001\n");
    printf(" Char - code \n");
    printf("--------------------\n");
    HuffmanCodes(arr, freq, size);
    printf("After Compress = 01111101101001111001001011111001011101001110");
    return 0;
}