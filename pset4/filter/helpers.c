#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average_color = (float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            image[i][j].rgbtBlue = (int) (round(average_color));
            image[i][j].rgbtGreen = (int) (round(average_color));
            image[i][j].rgbtRed = (int) (round(average_color));
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
            float gx_red = 0;
            float gx_green = 0;
            float gx_blue = 0;
            float gy_red = 0;
            float gy_green = 0;
            float gy_blue = 0;

            int gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            //  i ✖️ j(現在のマス）から3✖️3の範囲を取得
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    int new_row = i + row;
                    int new_col = j + col;

                    if (new_row < 0 || new_row >= height || new_col < 0 || new_col >= width)
                    { // 画像の端にある場合、次のループへスキップする
                        continue;
                    }

                    gx_red += gx_kernel[row + 1][col + 1] * image[new_row][new_col].rgbtRed;
                    gx_green += gx_kernel[row + 1][col + 1] * image[new_row][new_col].rgbtGreen;
                    gx_blue += gx_kernel[row + 1][col + 1] * image[new_row][new_col].rgbtBlue;
                    gy_red += gy_kernel[row + 1][col + 1] * image[new_row][new_col].rgbtRed;
                    gy_green += gy_kernel[row + 1][col + 1] * image[new_row][new_col].rgbtGreen;
                    gy_blue += gy_kernel[row + 1][col + 1] * image[new_row][new_col].rgbtBlue;
                }
            }

            int calculated_red = integer_control(sqrt(gx_red * gx_red + gy_red * gy_red));
            int calculated_green = integer_control(sqrt(gx_green * gx_green + gy_green * gy_green));
            int calculated_blue = integer_control(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            temp[i][j].rgbtRed = calculated_red;
            temp[i][j].rgbtGreen = calculated_green;
            temp[i][j].rgbtBlue = calculated_blue;
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
