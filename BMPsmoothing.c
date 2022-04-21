#include <stdio.h>
#include <math.h>
#include <string.h>


public class ConvolutionMatrix  
{  
    public int MatrixSize = 3;  
  
    public double[,] Matrix;  
    public double Factor = 1;  
    public double Offset = 1;  
  
    public ConvolutionMatrix(int size)  
    {  
        MatrixSize = 3;  
        Matrix = new double[size, size];  
    }  
  
    public void SetAll(double value)  
    {  
        for (int i = 0; i < MatrixSize; i++)  
        {  
            for (int j = 0; j < MatrixSize; j++)  
            {  
                Matrix[i, j] = value;  
            }  
        }  
    }  
} 

public Bitmap Convolution3x3(Bitmap b, ConvolutionMatrix m)  
{  
    Bitmap newImg = (Bitmap)b.Clone();  
    Color[,] pixelColor = new Color[3, 3];  
    int A, R, G, B;  
  
    for (int y = 0; y < b.Height - 2; y++)  
    {  
        for (int x = 0; x < b.Width - 2; x++)  
        {  
            pixelColor[0, 0] = b.GetPixel(x, y);  
            pixelColor[0, 1] = b.GetPixel(x, y + 1);  
            pixelColor[0, 2] = b.GetPixel(x, y + 2);  
            pixelColor[1, 0] = b.GetPixel(x + 1, y);  
            pixelColor[1, 1] = b.GetPixel(x + 1, y + 1);  
            pixelColor[1, 2] = b.GetPixel(x + 1, y + 2);  
            pixelColor[2, 0] = b.GetPixel(x + 2, y);  
            pixelColor[2, 1] = b.GetPixel(x + 2, y + 1);  
            pixelColor[2, 2] = b.GetPixel(x + 2, y + 2);  
  
            A = pixelColor[1, 1].A;  
  
            R = (int)((((pixelColor[0, 0].R * m.Matrix[0, 0]) +  
                         (pixelColor[1, 0].R * m.Matrix[1, 0]) +  
                         (pixelColor[2, 0].R * m.Matrix[2, 0]) +  
                         (pixelColor[0, 1].R * m.Matrix[0, 1]) +  
                         (pixelColor[1, 1].R * m.Matrix[1, 1]) +  
                         (pixelColor[2, 1].R * m.Matrix[2, 1]) +  
                         (pixelColor[0, 2].R * m.Matrix[0, 2]) +  
                         (pixelColor[1, 2].R * m.Matrix[1, 2]) +  
                         (pixelColor[2, 2].R * m.Matrix[2, 2]))  
                                / m.Factor) + m.Offset);  
  
            if (R < 0)  
            {  
                R = 0;  
            }  
            else if (R > 255)  
            {  
                R = 255;  
            }  
  
            G = (int)((((pixelColor[0, 0].G * m.Matrix[0, 0]) +  
                         (pixelColor[1, 0].G * m.Matrix[1, 0]) +  
                         (pixelColor[2, 0].G * m.Matrix[2, 0]) +  
                         (pixelColor[0, 1].G * m.Matrix[0, 1]) +  
                         (pixelColor[1, 1].G * m.Matrix[1, 1]) +  
                         (pixelColor[2, 1].G * m.Matrix[2, 1]) +  
                         (pixelColor[0, 2].G * m.Matrix[0, 2]) +  
                         (pixelColor[1, 2].G * m.Matrix[1, 2]) +  
                         (pixelColor[2, 2].G * m.Matrix[2, 2]))  
                                / m.Factor) + m.Offset);  
  
            if (G < 0)  
            {  
                G = 0;  
            }  
            else if (G > 255)  
            {  
                G = 255;  
            }  
             
            B = (int)((((pixelColor[0, 0].B * m.Matrix[0, 0]) +  
                         (pixelColor[1, 0].B * m.Matrix[1, 0]) +  
                         (pixelColor[2, 0].B * m.Matrix[2, 0]) +  
                         (pixelColor[0, 1].B * m.Matrix[0, 1]) +  
                         (pixelColor[1, 1].B * m.Matrix[1, 1]) +  
                         (pixelColor[2, 1].B * m.Matrix[2, 1]) +  
                         (pixelColor[0, 2].B * m.Matrix[0, 2]) +  
                         (pixelColor[1, 2].B * m.Matrix[1, 2]) +  
                         (pixelColor[2, 2].B * m.Matrix[2, 2]))  
                                / m.Factor) + m.Offset);  
  
            if (B < 0)  
            {  
                B = 0;  
            }  
            else if (B > 255)  
            {  
                B = 255;  
            }  
            newImg.SetPixel(x+1, y+1, Color.FromArgb(A, R, G, B));  
        }  
    }  
    return newImg;  
} 

public void ApplySmooth(double weight)  
{  
    ConvolutionMatrix matrix = new ConvolutionMatrix(3);  
    matrix.SetAll(1);  
    matrix.Matrix[1,1] = weight;  
    matrix.Factor = weight + 8;  
    bitmapImage = Convolution3x3(bitmapImage, matrix);  
  
} 