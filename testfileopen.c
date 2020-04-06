//opens file from command line input and writes each line out to the console
//to run: ./testfileopen myconfig.json

#include <stdio.h>

int main(int argc, char **argv)
{
    char *filename;
    FILE *fp;

    if (argc >= 2){
        filename = argv[1];
        printf("File name: %s\n", filename);
         fp = fopen(argv[1], "r");
    }
    else {
        perror("fopen");
    }
    
    char chunk[128];

    printf("File contents:\n");
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
        fputs(chunk, stdout);
    }

    fclose(fp);

    return 0;
}
