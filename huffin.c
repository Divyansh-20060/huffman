# include <stdio.h>
# include <stdlib.h>

struct node
{
    char data;
    int freq;
    struct node* left;
    struct node* right;
};

struct min_heap
{
    struct node* arr;
    int heap_len;
    int arr_len;
    int size;

};

struct min_heap* allocate_heap(struct node* arr, int size)
{
    struct min_heap* heap = (struct min_heap*) malloc(sizeof(struct min_heap));

    heap -> arr = arr;
    heap -> heap_len = size;
    heap -> arr_len = size;
    heap -> size = size;

    return heap;
}

void swap(struct node* a, struct node* b)
{
    struct node temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void heapifyat(struct node* arr, int n, int i)
{
    int left = 2*i;
    int right = left + 1;
    int smallest = i;

    if (left < n && (arr + smallest) -> freq > (arr + left) -> freq)
    {
        smallest = left;
    }

    if (right < n && (arr + smallest) -> freq > (arr + right) -> freq)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap((arr + i), (arr + smallest));
        heapifyat(arr,n,smallest);
    }
}

void min_heapify(struct min_heap *h,int i){
    heapifyat(h -> arr, h -> heap_len,i);
}


void build_min_heap(struct min_heap *h){
    int i;
    int n = h -> arr_len;
    for(i  = n/2; i >= 0; i--){
        min_heapify(h,i);
    }
}

struct node allocate_leaf_node(char data,int freq){
    struct node new_node;
    new_node.data  = data;
    new_node.freq = freq;
    new_node.left = NULL;
    new_node.right = NULL;
    
    return new_node;
}

struct node allocate_node(){
    struct node new_node;
    new_node.left = NULL;
    new_node.right = NULL;
    return new_node;
}

int InDataArr(char data_arr[], int size, char dv){
    for(int i = 0; i < size; i++){
        if(data_arr[i] == dv){
            return 1;
        }
    }

    return 0;
}

struct node* find_frequecncy(char text[], int size, int* leaf_node_len){   
    char data_arr[size];
    int len = 0;


    data_arr[0] = text[0];
    len++;


    for(int i = 1; i< size; i++){
        int idx = InDataArr(data_arr,len,text[i]);
        if(idx == 0){
            data_arr[len] = text[i];
            len++;
        }
        
    }

    int freq_arr[len];
    int counter;

    for(int i = 0; i < len; i++){
        counter = 0;
        char DV = data_arr[i];

        for(int j = 0; j < size; j++){
            if(text[j] == DV){
                counter++;
            }
        }
        freq_arr[i] = counter;
    }

    for(int i = 0; i < len; i++){
        printf("%c -> %d\n", data_arr[i], freq_arr[i]);
    }

    struct node* leaf_node = (struct node*) malloc(len * sizeof(struct node));

    for(int i = 0; i <len; i++){
        leaf_node[i] = allocate_leaf_node(data_arr[i], freq_arr[i]);
    }

    *leaf_node_len = len;

    return leaf_node;
}


struct node* extract_min(struct min_heap* h){
    swap(&(h -> arr[0]), &(h -> arr[ h -> heap_len - 1]));
    h -> heap_len = h -> heap_len - 1;
    min_heapify(h,0);

    printf("%d ",((h -> arr) + h ->heap_len - 1)->freq);
    return(&(h -> arr[ h ->heap_len - 1]));
}

void insert_at(struct node* arr,int idx){
    if(idx == 0){
        return;
    }

    int parent = idx/2;

    if((arr + parent) -> freq < (arr + idx) -> freq){
        swap((arr + parent),(arr + idx));
        insert_at(arr,parent);
    }

}

void insert(struct min_heap* h, struct node* nd){
    int n = h -> heap_len;
    (h -> arr[n])  = *nd;
    insert_at(h-> arr, n+1);

    h -> heap_len = h -> heap_len + 1; 
}

struct node* huffman_encoding(struct min_heap* h, int n){
    for( int i = 0; i< n-1; i++){
        struct node new = allocate_node();
        struct node* x = extract_min(h);
        struct node* y = extract_min(h);

        new.left = x;
        new.right = y;

        new.freq = (x -> freq) + (y -> freq);

        insert(h,&new);

    }

    return extract_min(h);
}

FILE* verfy_file(){
    char fname[100];
    printf("enter the file name: \n");
    scanf("%s",fname);

    FILE* file = fopen(fname,"r");

    if(file == NULL){
        printf("file not found.\n");
        exit(1);
    }

    return file;

}

long int getsize(FILE* the_file){
    fseek(the_file,0L,SEEK_END);
    long int size = ftell(the_file);
    fseek(the_file,0,SEEK_SET);
    return size;
}

int main(){
    FILE* file = verfy_file();
    long int size = getsize(file);

    char text[size];
    fgets(text,size + 1,file);

    int leaf_node_len;

    struct node* leaf_nodes = find_frequecncy(text, size, &leaf_node_len);

    for(int i = 0; i< leaf_node_len; i++)
    {
        printf("%c -> %d\n", (leaf_nodes + i) -> data, (leaf_nodes + i) -> freq);
    }

    

    struct min_heap* heap = allocate_heap(leaf_nodes, leaf_node_len);


    build_min_heap(heap);

    for(int i = 0; i< leaf_node_len; i++){
        printf("%d ", ((heap -> arr)+i)->freq);
    }

    printf("\n");

    struct node* huff_tree = huffman_encoding(heap,leaf_node_len);

    return 0;

}