#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averageColor = (float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            image[i][j].rgbtBlue = (int) (round(averageColor));
            image[i][j].rgbtGreen = (int) (round(averageColor));
            image[i][j].rgbtRed = (int) (round(averageColor));
        }
    }

    return;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0.0;
            float totalGreen = 0.0;
            float totalBlue = 0.0;
            int count = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        totalRed += image[newRow][newCol].rgbtRed;
                        totalGreen += image[newRow][newCol].rgbtGreen;
                        totalBlue += image[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            temp[i][j].rgbtRed = (int) round(totalRed / count);
            temp[i][j].rgbtGreen = (int) round(totalGreen / count);
            temp[i][j].rgbtBlue = (int) round(totalBlue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

int integer_control(float value)
{
    if (value < 0)
    {
        return 0;
    }
    else if (value > 255)
    {
        return 255;
    }
    else
    {
        return (int) round(value);
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxRed = 0;
            float gxGreen = 0;
            float gxBlue = 0;
            float gyRed = 0;
            float gyGreen = 0;
            float gyBlue = 0;

            int gxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            //  i ✖️ j(現在のマス）から3✖️3の範囲を取得
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width)
                    { // 画像の端にある場合、次のループへスキップする
                        continue;
                    }

                    gxRed += gxKernel[row + 1][col + 1] * image[newRow][newCol].rgbtRed;
                    gxGreen += gxKernel[row + 1][col + 1] * image[newRow][newCol].rgbtGreen;
                    gxBlue += gxKernel[row + 1][col + 1] * image[newRow][newCol].rgbtBlue;
                    gyRed += gyKernel[row + 1][col + 1] * image[newRow][newCol].rgbtRed;
                    gyGreen += gyKernel[row + 1][col + 1] * image[newRow][newCol].rgbtGreen;
                    gyBlue += gyKernel[row + 1][col + 1] * image[newRow][newCol].rgbtBlue;
                }
            }

            int calculatedRed = integer_control(sqrt(gxRed * gxRed + gyRed * gyRed));
            int calculatedGreen = integer_control(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int calculatedBlue = integer_control(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            temp[i][j].rgbtRed = calculatedRed;
            temp[i][j].rgbtGreen = calculatedGreen;
            temp[i][j].rgbtBlue = calculatedBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
