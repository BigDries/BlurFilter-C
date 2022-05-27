#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMPINPUT "test.bmp"
#define BMPOUTPUT "out.bmp"

int main(int argc, char const *argv[])
{
    FILE * inputFilePointer = fopen(BMPINPUT, "rb");

    unsigned char header[54] = {0};
    signed int hoogte = 0;
    signed int breedte = 0;
    unsigned char * pixels = NULL;
    int totaalAantalPixels = 0;
    int i;

    if(inputFilePointer == NULL)
    {
        printf("%s\n", "ERROR: can't open the file");
        return -1;
    }

    fread(header, 1, 54, inputFilePointer);

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

    fread(pixels, 1, totaalAantalPixels*3, inputFilePointer);
        printf("INFO: Heap memory allocated = %d (bytes)\n", totaalAantalPixels*3);

    fclose(inputFilePointer);
        printf("INFO: File %s CLOSED\n", BMPINPUT);

    //----------------------------------------

    FILE* outputFilePointer = fopen(BMPOUTPUT, "wb");// maak een file pointer naar een nieuwe output file
    if(outputFilePointer == NULL)  //Test of het maken van de file gelukt is!
    {
        printf("Something went wrong while trying to open %s\n", BMPOUTPUT);
        exit(EXIT_FAILURE);
    }        

    #ifdef __DEBUG   
        printf("DEBUG info: Opening File OK: %s\n", BMPOUTPUTFILE);
    #endif

    unsigned char bmpHeader[54]; // voorzie een array van 54-bytes voor de BMP Header
    fread(bmpHeader, sizeof(unsigned char), 54, inputFilePointer); // lees de 54-byte header
/*
    //Informatie uit de header (wikipedia)
    // haal de hoogte en breedte uit de header
    int breedte = *(int*)&bmpHeader[18];
    int hoogte = *(int*)&bmpHeader[22];

    #ifdef __DEBUG
        printf("DEBUG info: breedte = %d\n", breedte);
        printf("DEBUG info: hoogte = %d\n", hoogte);
    #endif
*/
    int imageSize = 3 * breedte * hoogte; //ieder pixel heeft 3 byte data: rood, groen en blauw (RGB)
    unsigned char* inputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels

    fread(inputPixels, sizeof(unsigned char), imageSize, inputFilePointer); // Lees alle pixels (de rest van de file)
    fclose(inputFilePointer);

    //BGR --> RGB
    for(i = 0; i < imageSize-3; i += 3)
    {
        unsigned char tmp = inputPixels[i];
        inputPixels[i] = inputPixels[i+2];
        inputPixels[i+2] = tmp;
    }

    //Maak de output file:
    i = 0;
    for(i = 0; i < 52; i++) //schrijf de header
    {
        putc(bmpHeader[i], outputFilePointer);
    }
    
    unsigned char* outputPixels = (unsigned char *) calloc(imageSize, sizeof(unsigned char)); // allocate een array voor alle pixels
    i = 0 ;
    for(i = 0; i < imageSize; i++)
    {
        outputPixels[i] = 255 - inputPixels[i];
        putc(outputPixels[i], outputFilePointer);
    }

    fwrite(outputFilePointer, sizeof(unsigned char), imageSize, outputFilePointer); //schrijf de pixels naar de file

    #ifdef __DEBUG
        printf("DEBUG info: output file generated\n");
    #endif

    fclose(outputFilePointer);
    fclose(inputFilePointer);
    free(inputPixels);
        
    //----------------------------------------
    free(pixels);
        printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels*3);

    return 0;
}

// filter formula 
void blurfilter()
{
    
    return 0;
}
/*
void BlackAndWhitefilter()
{
    #include<stdio.h>
    #include<stdlib.h>

    #include "image.h"

    int main(int argc,char *argv[])
    {
        char filename[100];
        scanf("%s",filename);

        FILE *fp = fopen(filename,"rb");
        BMP_Header bmp_header = getBMP_Header(fp);
        imageHeader imgHeader = getImageHeader(fp);
        Image img = getImage(fp,bmp_header.offset,imgHeader.width,imgHeader.height);


        //createBlackAndWhiteImage(img,bmp_header,imgHeader);
        createFlippedImage(img,bmp_header,imgHeader);
        freeImage(img);
        return 0;
    }

    BMP_Header getBMP_Header(FILE *fp)
    {

    imageHeader getImageHeader(FILE *fp)
    {
        imageHeader imageHeader;
        fread(&imageHeader,1*sizeof(struct imageHeader),1,fp);

        if(imageHeader.headerSize!=124 || imageHeader.colorPanes!=1){
            fclose(fp);
            printf("Header size not correct!\n");
            exit(-1);
        }
        return imageHeader;
    }
    Image getImage(FILE *fp,int offset,int width,int height)
    {

        fseek(fp,offset,SEEK_SET);
        Image image = newImage(fp,width,height);
        fclose(fp);
        return image;
    }


    Image newImage(FILE *fp,int width,int height)
    {
        Image image;
        image.height = height;
        image.width = width;
        image.rgb =(struct RGB**) malloc(height*sizeof(void *));
        for(int i =height-1; i >=0 ;i--){
            image.rgb[i] = (struct RGB*) malloc(width*sizeof(struct RGB));
            fread(image.rgb[i],width,sizeof(struct RGB),fp);
    }

        return image;
    }

    unsigned char greyScalePixel(RGB rgb)
    {
        return ((rgb.red*0.3)+(rgb.green*0.6)+(rgb.blue*0.1));
    }

    void imageToGrayScale(Image image)
    {
        for(int i = 0;i<image.height;i++)
        {
            for(int j=0;j<image.width;j++)
            {
                image.rgb[i][j].red = greyScalePixel(image.rgb[i][j]);
                image.rgb[i][j].blue = greyScalePixel(image.rgb[i][j]);
                image.rgb[i][j].green = greyScalePixel(image.rgb[i][j]);
            }
        }

    }

    void flipImage(Image image)
    {
        for(int i=0;i<image.height;i++)
        {
            for(int j =0;j<image.width/2;j++)
            {
                RGB temp = image.rgb[i][j];
                image.rgb[i][j] = image.rgb[i][image.width-j-1];
                image.rgb[i][image.width-j-1] = temp;
            }
        }
    }

    void createBlackAndWhiteImage(Image image,BMP_Header bmp_header,imageHeader image_header)
    {
        FILE *fpw = fopen("bw-pic.bmp","wb");
        if(fpw == NULL)
        {
            return;
        }

        imageToGrayScale(image);

        fwrite(bmp_header.name,2*sizeof(char),1,fpw);
        fwrite(&bmp_header.size,3*sizeof(int),1,fpw);

        fwrite(&image_header,sizeof(struct imageHeader),1,fpw);


        for(int i=image.height-1; i>=0;i--)
        {
            fwrite(image.rgb[i],image.width,sizeof(struct RGB),fpw);
        }
        fclose(fpw);
    }

    void freeImage(Image image)
    {
        for(int i=image.height-1;i>=0;i--)
        {
            free(image.rgb[i]);
        }
        free(image.rgb);
    }

    void createFlippedImage(Image image,BMP_Header bmp_header,imageHeader image_header)
    {
         FILE *fpw = fopen("flipped.bmp","wb");

        if(fpw == NULL)
        {
            return ;
        }
        flipImage(image);

        fwrite(bmp_header.name,2*sizeof(char),1,fpw);
        fwrite(&bmp_header,3*sizeof(int),1,fpw);

        fwrite(&image_header,sizeof(struct imageHeader),1,fpw);

        for(int i=image.height-1; i>=0;i--)
        {
            fwrite(image.rgb[i],image.width,sizeof(struct RGB),fpw);
        }
        fclose(fpw);
    }
}

void flipbmpfilter(image image)
{
    for(int i=0;i<image.height;i++)
    {
        for(int j =0;j<image.width/2;j++)
        {
            RGB temp = image.rgb[i][j];
            image.rgb[i][j] = image.rgb[i][image.width-j-1];
            image.rgb[i][image.width-j-1] = temp;
        }
    }

    void createFlippedImage(Image image,BMP_Header bmp_header,imageHeader image_header)
    {
        FILE *fpw = fopen("flipped.bmp","wb");

        if(fpw == NULL)
        {
            return ;
        }
    }
}

    flipImage(image);

    fwrite(bmp_header.name,2*sizeof(char),1,fpw);
    fwrite(&bmp_header,3*sizeof(int),1,fpw);

    fwrite(&image_header,sizeof(struct imageHeader),1,fpw);

    for(int i=image.height-1; i>=0;i--){
        fwrite(image.rgb[i],image.width,sizeof(struct RGB),fpw);
    }
    fclose(fpw);

    */