#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

int main(int argc, char **argv) {
    if (argc != 3 && argc != 5) {
        printf("Usage: %s encode message image-file new-image-file\n", argv[0]);
        printf("       %s decode image-file\n", argv[0]);
        return 1;
    }

    if (argc == 3) {
        if (strcmp(argv[1], "decode") != 0) {
            printf("Usage: %s decode image-file\n", argv[0]);
            return 2;
        }

        ImagePGM *pImagePGM = readPGM(argv[2]);
        if (pImagePGM == NULL) {
            printf("Unable to read the PGM file: %s\n", argv[2]);
            return 3;
        }

        char *msg= decode(pImagePGM);
        printf("Message embedded: %s\n", msg);
        freePGM(pImagePGM);
        free(msg);
    }
    else {	// argc == 5
        if (strcmp(argv[1], "encode")!=0) {
            printf("Usage: %s encode message image-file new-image-file\n", argv[0]);
            return 4;
        }
        ImagePGM *pImagePGM=readPGM(argv[3]);
        if (pImagePGM==NULL) {
            printf("Unable to read the PGM file: %s\n", argv[3]);
            return 5;
        }
        int res=encode(pImagePGM, argv[2]);
        if (res==0) {
            printf("%s: the image file is too small\n", argv[3]);
            freePGM(pImagePGM);
            return 6;
        }
        res=writePGM(pImagePGM, argv[4]);
        if (res==0) {
            printf("Unable to write into the PGM file: %s\n", argv[4]);
            freePGM(pImagePGM);
            return 7;
        }
        freePGM(pImagePGM);

    }
    return 0;
}
