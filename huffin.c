# include <stdio.h>
# include <stdlib.h>

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
    return size;
}

int main()
{
    FILE* file = verfy_file();
    long int size = getsize(file);

    char text[size];

    fgets(text,size,file);
    printf("%s\n",file);

    return 0;

}