#include <stdio.h>
#include <stdlib.h>

#define BMPINPUT "test.bmp"


int main(int argc, char const *argv[])
{
    FILE * inputBMP = fopen(BMPINPUT, "rb");
    unsigned char header[54] = {0};
    signed int hoogte = 0;
    signed int breedte = 0;
    unsigned char * pixels = NULL;
    int totaalAantalPixels = 0;

    if(inputBMP == NULL)
    {
        printf("%s\n", "ERROR: can't open the file");
        return -1;
    }

    fread(header, 1, 54, inputBMP);

    breedte = header[21] << 24 | header[20] << 16 | header[19] << 8 | header[18]; 
    printf("De breedte van mijn afbeelding is = %d\n", breedte);
    hoogte = header[25] << 24 | header[24] << 16 | header[23] << 8 | header[22]; 
    printf("De hoogte van mijn afbeelding is = %d\n", hoogte);

    totaalAantalPixels = breedte * hoogte;
    pixels = (unsigned char *) malloc(totaalAantalPixels*3);
    if(pixels == NULL)
    {
        printf("ERROR: memory allocation Failed\n");
        return -2;
    }

    fread(pixels, 1, totaalAantalPixels*3, inputBMP);
    printf("INFO: Heap memory allocated = %d (bytes)\n", totaalAantalPixels*3);

    fclose(inputBMP);
    printf("INFO: File %s CLOSED\n", BMPINPUT);

    //----------------------------------------

    
    
    //----------------------------------------
    free(pixels);
    printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels*3);
    return 0;
}