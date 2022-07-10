# include <stdio.h>
# include <stdlib.h>

long int getsize(FILE* the_file){
    fseek(the_file,0L,SEEK_END);
    long int size = ftell(the_file);
    return size;
}

int main(){

    char fname[100];
    printf("enter the file name: \n");
    scanf("%s",fname);

    FILE* file = fopen(fname,"r");

    if(file == NULL){
        printf("file not found.\n");
        return -1;
    }

    long int size = getsize(file);

    printf("%lu",size);

    return 0;

}