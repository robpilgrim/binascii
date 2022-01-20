#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


void bin_to_char(char* string) {
    int len=0;
    for(int i=0; i<strlen(string); i++) {
        if(string[0] == '1') {
            if(i%6==0) { 
                int nstring = strtol(&string[len], NULL, 2);
                printf("%c", nstring);
                len+=8;
                continue;
            }
        }
        else if(string[0] == '0') {
            if(i%7==0) { 
                int nstring = strtol(&string[len], NULL, 2);
                printf("%c", nstring);
                len+=9;
                continue;
            }

        }
    }
}

void char_to_bin(char* string) {
    const char *bit[16] = {
        [0] = "0000", [1] = "0001", [2] = "0010", [3] = "0011",
        [4] = "0100", [5] = "0101", [6] = "0110", [7] = "0111",
        [8] = "1000", [9] = "1001", [10] = "1010", [11] = "1011",
        [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
    };

    int nstring=0;
    for(char* c = string; *c; c++) {
        nstring=(int)*c;
        printf("%s%s ", bit[nstring >> 4], bit[nstring & 0x0F]);
    }

}

int main(int argc, char**argv) {

    FILE* fp;

    if(argv[1]==NULL) errx(1, "no operation provided");
    else if(strcmp(argv[1],"bc")==0) {

        if((fp=fopen(argv[2], "r"))==NULL) {

            if(argv[2]==NULL) errx(1, "no file/input provided");
            bin_to_char(argv[2]);
            printf("\n");
            

        }

        else {
            if(argv[2]==NULL) errx(1, "no file/input provided");
            fseek(fp, 0L, SEEK_END);
            size_t fsz = ftell(fp);
            rewind(fp);

            char* buffer = malloc(fsz);
            fread(buffer, 1, fsz, fp);

            bin_to_char(buffer);
            printf("\n");
        }
    }

    else if(strcmp(argv[1],"cb")==0) {
        if((fp=fopen(argv[2], "r"))==NULL) {

            if(argv[2]==NULL) errx(1, "no file/input provided");
            char_to_bin(argv[2]);
            printf("\n");

        }

        else {
            if(argv[2]==NULL) errx(1, "no file/input provided");
            fseek(fp, 0L, SEEK_END);
            size_t fsz = ftell(fp);
            rewind(fp);

            char* buffer = malloc(fsz);
            fread(buffer, 1, fsz, fp);

            char_to_bin(buffer);
            printf("\n");

        }
    }

    else if(strcmp(argv[1],"--help")==0 || (strcmp(argv[1], "-h")==0)) {
        printf("cb: turns a string into a binary representation\n");
        printf("bc: converts a binary number into a string\n");
        printf("--help | -h: shows this page\n");
    }


}
