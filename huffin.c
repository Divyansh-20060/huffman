# include <stdio.h>
# include <stdlib.h>

struct node
{
    char data;
    int freq;
    struct node* left;
    struct node* right;
};
struct node allocate_leaf_node(char data,int freq)

{
    struct node new_node;
    new_node.data  = data;
    new_node.freq = freq;
    new_node.left = NULL;
    new_node.right = NULL;
    
    return new_node;
}

int InDataArr(char data_arr[], int size, char dv)
{
    for(int i = 0; i < size; i++)
    {
        if(data_arr[i] == dv)
        {
            return 1;
        }
    }

    return 0;
}

struct node* find_frequecncy(char text[], int size, int* leaf_node_len)
{   
    char data_arr[size];
    int len = 0;


    data_arr[0] = text[0];
    len++;


    for(int i = 1; i< size; i++)
    {
        int idx = InDataArr(data_arr,len,text[i]);
        if(idx == 0)
        {
            data_arr[len] = text[i];
            len++;
        }
        
    }

    int freq_arr[len];
    int counter;

    for(int i = 0; i < len; i++)
    {
        counter = 0;
        char DV = data_arr[i];

        for(int j = 0; j < size; j++)
        {
            if(text[j] == DV)
            {
                counter++;
            }
        }
        freq_arr[i] = counter;
    }

    for(int i = 0; i < len; i++)
    {
        printf("%c -> %d\n", data_arr[i], freq_arr[i]);
    }

    struct node* leaf_node = (struct node*) malloc(len * sizeof(struct node));

    for(int i = 0; i <len; i++)
    {
        leaf_node[i] = allocate_leaf_node(data_arr[i], freq_arr[i]);
    }

    *leaf_node_len = len;

    return leaf_node;
}

FILE* verfy_file()
{
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

long int getsize(FILE* the_file)
{
    fseek(the_file,0L,SEEK_END);
    long int size = ftell(the_file);
    fseek(the_file,0,SEEK_SET);
    return size;
}

int main()
{
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



    return 0;

}