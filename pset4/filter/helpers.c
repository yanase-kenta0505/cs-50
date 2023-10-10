#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average_color = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            image[i][j].rgbtBlue = (int)(round(average_color));
            image[i][j].rgbtGreen = (int)(round(average_color));
            image[i][j].rgbtRed = (int)(round(average_color));
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // 元の値を保管しておく
            RGBTRIPLE origin_image = image[i][j];

            // 行の最後はwidth - 1 - jで計算できる
            image[i][j] = image[i][width - 1 - j];

            image[i][width - 1 - j] = origin_image;
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
                    int new_row = i + row;
                    int new_col = j + col;
                    
                    if (new_row >= 0 && new_row < height && new_col >= 0 && new_col < width)
                    {
                        totalRed += image[new_row][new_col].rgbtRed;
                        totalGreen += image[new_row][new_col].rgbtGreen;
                        totalBlue += image[new_row][new_col].rgbtBlue;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
