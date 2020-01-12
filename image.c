#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "image.h"

void skip_comment_lines(FILE *);

ImagePGM *readPGM(char *filename) {
    ImagePGM *data = (ImagePGM *) malloc(sizeof(ImagePGM));

    FILE *pgmFile = fopen(filename, "r");
    if (pgmFile == NULL) {
        printf("\n Cannot open file to read.");
        return NULL;
    }
    fscanf(pgmFile, "%s", data->magic);
    if (strcmp(data->magic, "P2")) {
        printf("\n Wrong file type!\n");
        exit(1);
    }

    skip_comment_lines(pgmFile);
    //fscanf(pgmFile, "%d", &data->width);
    //skip_comment_lines(pgmFile);
    //fscanf(pgmFile, "%d", &data->height);
    //skip_comment_lines(pgmFile);
    fscanf(pgmFile, "%d %d %d", &data->width, &data->height, &data->max_value);
    //fgetc(pgmFile);

    printf("\n PGM File reading...\n Format: %s\n Height: %d\n Width: %d\n ", data->magic, data->height, data->width);

    data->pixels = (int **) malloc(data->height * sizeof(int *));
    for (int i = 0; i < data->height; ++i)
        data->pixels[i] = (int *) malloc(data->width * sizeof(int));

    //printf("\n Malloc'ed.\n");

    //int* data2 = (int*)malloc((data->width)*(data->height)*sizeof(int));
    /*
    for(int i=0;i<(data->height)*(data->width);i++) {
        fscanf(pgmFile, "%d", &data2[i]);
    }

     */
    printf("\n data->height = %d data->width = %d\n", data->height, data->width);
    //printf("\n Gonna enter for-loop zoneZ\n");
    for (int i = 0; i < data->height; ++i) {
        //printf("\n In da hood..");
        for (int j = 0; j < data->width; ++j)
            fscanf(pgmFile, "%d", &data->pixels[i][j]);
    }

    fclose(pgmFile);
    printf("\n File read and closed.\n");
    /*
     //If for max val < 255 its 1 byte else 2 bytes
     if(data->max_value<256)
     {
         for(i=0;i<data->height;i++)
             for(j=0;j<data->width;j++)
                 data2[ j + i * (data->width)] = (int) get_num(pgmFile);
     }

     else {
         for(i=0;i<data->height;i++)
             for(j=0;j<data->width;j++)
                 //most significant byte first
                 data2[ j + i * (data->width) ] = (int) get_num(pgmFile);

     }

     */


    //DEBUG

    printf("\n DEBUG OUTPUT\n");
    printf("\n Reading from file %s\n\n", filename);
    printf("%s\n", data->magic);
    printf("%d  %d\n", data->width, data->height);
    printf("%d\n", data->max_value);

    /*
    for (int i = 0; i < data->width; ++i)
        for (int j = 0; j < data->height; ++j)
        {
            printf("%d ", data->pixels[i][j]);
            if (j % 23 == 0 && j != 0)
                printf("\n");
        }
        */

    //DEBUG

    printf("\n PGM File read successfully.\n");

    return data;
}

int writePGM(ImagePGM *data, char *filename) {
    FILE *pgmFile = fopen(filename, "w+");
    if (pgmFile == NULL) {
        printf("\n cannot open file to write.");
        return 0;
    }

    //DEBUG

    printf("\n DEBUG OUTPUT\n");
    printf("\n writing to file %s\n\n", filename);
    printf("%s\n", data->magic);
    printf("%d  %d\n", data->width, data->height);
    printf("%d\n", data->max_value);

    fprintf(pgmFile, "%s\n", data->magic);
    fprintf(pgmFile, "%d %d %d\n", data->width, data->height, data->max_value);


    for (int i = 0; i < data->height; ++i)
        for (int j = 0; j < data->width; ++j)
            fprintf(pgmFile, "%d ", data->pixels[i][j]);


    fclose(pgmFile);

    printf("\n File written successfully.\n");
    return 1;
    // Deallocate now
}

int encode(ImagePGM *data, char msg_text[]) {

    if (data->width + 1 < 10 || data->height < 10)
        return 0;


    int msg_len = strlen(msg_text);

    printf("Encoding '%s' into PGM File...\n", msg_text);

    int width = data->width - 1;
    int height = data->height - 1;
    for (int k = 0; k <= msg_len; ++k) {
        char toEncode = msg_text[k];
        //printf("\n Char to encode: %c\n",toEncode);
        for (int i = 0; i < 8; ++i) {
            int bitToEncode = toEncode & (int) (pow(2, 7-i));
            if (bitToEncode)
                bitToEncode=1;
            //printf("%d (%c:%d  ANDed with %d)",bitToEncode,toEncode,toEncode,(int) (pow(2, i)) );
            if (bitToEncode == 0)
                data->pixels[height][width] &= 11111110;
            else
                data->pixels[height][width] |= 00000001;

            //printf(" -> Written at data->pixels[%d][%d]\n",height,width);
            width--;
            if (width < 0) {
                height--;
                width = data->width - 1;
            }
        }

        //printf("\n\n ------------- '%c' written successfully. -----------\n",toEncode);
    }

    return 1;
}

char *decode(ImagePGM *data)
{
    char* msg_text = (char*)malloc(100 * sizeof(char));
    int msgIndex = 0;

    printf("\nDecoding PGM File...\n");

    bool decrypted = false;
    int hidden_pixels[8];
    int width = data->width - 1;
    int height = data->height - 1;
    while(!decrypted) {
        int hidden = 0;
        //printf("\n Decrypting bits: ");
        for (int k = 0; k < 8; ++k) {
            hidden_pixels[k] = data->pixels[height][width] & 00000001;
            //printf("%d ",hidden_pixels[k]);
            hidden += (int) (pow(2,7-k) * hidden_pixels[k]);
            width--;
            if (width < 0) {
                height--;
                width = data->width - 1;
            }
        }

        //printf("\n Decoded char = %c",(char)hidden);

        msg_text[msgIndex++] = (char) hidden;

        if (hidden == 0)
            decrypted = true;

    }
    //printf("\n Decrypted PGM to: %s\n",msg_text);
    printf("\n\n");
    return msg_text;

}

void freePGM(ImagePGM *data) {
    printf("\n Freeing up memory...\n");
    free(data->pixels);
}


void skip_comment_lines(FILE *fp) {
    int ch;
    char line[100];
    while ((ch = fgetc(fp)) != EOF && isspace(ch)) {}

    if (ch == '#') {
        fgets(line, sizeof(line), fp);
        skip_comment_lines(fp);
    } else {
        fseek(fp, -1, SEEK_CUR);
    }
}


