#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute average
            float avg =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Update values
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Iterate through half of the image width
        for (int j = 0; j < width / 2; j++)
        {
            // Swap two halves
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Compute the average of 3x3 box pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Total of each color
            float sum_red = 0, sum_blue = 0, sum_green = 0;
            float pixels_count = 0;

            // Pixels before and after
            for (int k = i - 1; k <= i + 1; k++)
            {
                // Pixels up and down
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // Check pixels within valid range
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        sum_blue += image[k][l].rgbtBlue;
                        sum_green += image[k][l].rgbtGreen;
                        sum_red += image[k][l].rgbtRed;
                        pixels_count++;
                    }
                }
            }

            // Blur copy image
            copy[i][j].rgbtBlue = round(sum_blue / pixels_count);
            copy[i][j].rgbtGreen = round(sum_green / pixels_count);
            copy[i][j].rgbtRed = round(sum_red / pixels_count);
        }
    }

    // Write copy to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    // Create a copy of the image.
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;
            int index = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    // Check pixel within valid range.
                    if (!(k < 0 || k >= height || l < 0 || l >= width))
                    {
                        gx_red += image[k][l].rgbtRed * gx[index];
                        gx_green += image[k][l].rgbtGreen * gx[index];
                        gx_blue += image[k][l].rgbtBlue * gx[index];
                        gy_red += image[k][l].rgbtRed * gy[index];
                        gy_green += image[k][l].rgbtGreen * gy[index];
                        gy_blue += image[k][l].rgbtBlue * gy[index];
                    }
                    index++;
                }
            }

            // Update channels
            int red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // Write copy with new channels values.
            copy[i][j].rgbtRed = red > 255 ? 255 : red;
            copy[i][j].rgbtGreen = green > 255 ? 255 : green;
            copy[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }

    // Write copy image to the original image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
