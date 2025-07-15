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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sepia formulas
            // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

            int sepia_red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                  .189 * image[i][j].rgbtBlue);

            int sepia_green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                    .168 * image[i][j].rgbtBlue);

            int speia_blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                   .131 * image[i][j].rgbtBlue);

            // Update values
            image[i][j].rgbtRed = sepia_red > 255 ? 255 : sepia_red;
            image[i][j].rgbtGreen = sepia_green > 255 ? 255 : sepia_green;
            image[i][j].rgbtBlue = speia_blue > 255 ? 255 : speia_blue;
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
