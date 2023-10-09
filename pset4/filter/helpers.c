#include "helpers.h"
#include <math.h>

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
        return (int)round(value);
    }
}

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            image[i][j].rgbtBlue = integer_control(sepiaBlue);
            image[i][j].rgbtGreen = integer_control(sepiaGreen);
            image[i][j].rgbtRed = integer_control(sepiaRed);
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
    // 各ピクセルに対してぼかしを計算
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tempRed = 0;
            int tempGreen = 0;
            int tempBlue = 0;
            int count = 0;

            // 3x3のグリッド内のピクセルを処理
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int newRow = i + row;
                    int newCol = j + col;

                    // 画像の範囲内かどうかを確認
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        tempRed += image[newRow][newCol].rgbtRed;
                        tempGreen += image[newRow][newCol].rgbtGreen;
                        tempBlue += image[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            // 平均値を計算して元の画像に格納
            image[i][j].rgbtRed = round((float)tempRed / count);
            image[i][j].rgbtGreen = round((float)tempGreen / count);
            image[i][j].rgbtBlue = round((float)tempBlue / count);
        }
    }
}
