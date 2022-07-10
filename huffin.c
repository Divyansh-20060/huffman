# include <stdio.h>
# include <stdlib.h>

struct node
{
    char data;
    int freq;
    struct node* left;
    struct node* right;
};
struct node* allocate_leaf_node(char data)

{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node -> data  = data;
    new_node -> freq = 1;
    new_node -> left = NULL;
    new_node -> right = NULL;
    
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
void find_frequecncy(char text[], int size, int* leaf_node_len)
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

    for(int i = 0; i < len; i++)
    {
        printf("%c", data_arr[i]);
    }

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

    find_frequecncy(text, size, &leaf_node_len);



    return 0;

}