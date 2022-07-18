
#ifndef STEGANOGRAPH_IMAGE_H
#define STEGANOGRAPH_IMAGE_H


typedef struct _imagePGM {
    char magic[3];  // magic identifier, "P2" for PGM
    int width;      // number of columns
    int height;     // number of rows
    int max_value;  // maximum grayscale intensity
    int **pixels;   // the actual grayscale pixel data, a 2D array
} ImagePGM;

// Given a filename of a pgm image, read in the image and
// store it in the ImagePGM structure. Return the address of
// the ImagePGM structure if the file can be opened or
// NULL otherwise.
ImagePGM *readPGM(char *filename);

// Write out a pgm image stored in a ImagePGM structure into
// the specified file. Return 1 if the file can be opened or
// 0 otherwise.
int writePGM(ImagePGM *pImagePGM, char *filename);

// Encode/embed a message into a PGM image.
// Return 0 if the image is too small or
// 1 otherwise.
int encode(ImagePGM *pImagePGM, char *msg);

// Decode/extract and return the message embedded in a PGM image
char *decode(ImagePGM *pImagePGM);

// Free the space used by a pgm image.
void freePGM(ImagePGM *pImagePGM);


#endif //STEGANOGRAPH_IMAGE_H
