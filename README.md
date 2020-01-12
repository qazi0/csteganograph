# csteganograph
### Message encoding and decoding in the PGM image format

From [Wikipedia](https://en.wikipedia.org/wiki/Steganography), steganography is the practice of concealing a file, message, image, or video within another file, message, image, or video.
This simple tool allows embedding a text message into a .PGM Image file, using reversed bit encoding.


### Compiling
To compile with gcc
```
gcc image.c main.c -o csteganograph
```

### Usage

## Encoding
To encode a text message, use syntax:
```
user@domain:~# ./csteganograph encode <text-message-to-encode> <input-image-filename.pgm> <output-image-filename.pgm>
```
For example, to encode "This is the secret message (not really)" into file balloons.pgm, use:
```
user@domain:~# ./csteganograph encode "This is the secret message (not really)" balloons.pgm balloons-encoded.pgm
```

## Decoding
To decode an image and show the hidden message, use:
```
user@domain:~# ./csteganograph decode <encoded-image-filename.pgm>
```
