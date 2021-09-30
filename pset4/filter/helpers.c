#include "helpers.h"
#include "math.h"
#include "string.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   int r, g, blue;

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            r = image[a][b].rgbtRed;
            g = image[a][b].rgbtGreen;
            blue = image[a][b].rgbtBlue;


            // Calculate average
            int averages = round((r + g + blue) /(float) 3.0);

            image[a][b].rgbtRed = averages;
            image[a][b].rgbtGreen = averages;
            image[a][b].rgbtBlue = averages;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int a = 0; a < height; a++)
    {

        for (int b = 0; b < width; b++)
        {
            // Get RGB values

            int r = image[a][b].rgbtRed;
            int g = image[a][b].rgbtGreen;
            int blue = image[a][b].rgbtBlue;

            // Get sepia values based on sepia formula and round it to the nearest integer
            //sepiared
            int sr = round(0.393 * r + 0.769 * g + 0.189 * blue);

            //sepiaGreen
            int sg = round(0.349 * r + 0.686 * g + 0.168 * blue);

            //sepiaBlue
            int sb = round(0.272 * r + 0.534 * g + 0.131 * blue);

            // Cap values at 255 using fmin()
            image[a][b].rgbtRed = fmin(255, sr);
            image[a][b].rgbtGreen = fmin(255, sg);
            image[a][b].rgbtBlue = fmin(255, sb);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage
    RGBTRIPLE row[width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            row[b] = image[a][b];
        }
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = row[width - 1 - b].rgbtRed;
            image[a][b].rgbtGreen = row[width - 1 - b].rgbtGreen;
            image[a][b].rgbtBlue = row[width - 1 - b].rgbtBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{



    RGBTRIPLE temporary[height][width];
    //keeping an original copy to loop over
    memcpy(temporary, image, sizeof(RGBTRIPLE) * height * width);

    // Iterate over every row of the image
    for (int a = 0; a < height; a++)
    {
        // Iterate over every column of the image
        for (int b = 0; b < width; b++)
        {
            //in order to avoid truncating error
            float number = 0.0;
            // set RGB values to 0
            int r = 0;
            int g = 0;
            int blue = 0;


            for (int c = -1; c <= 1; c++)
            {

                for (int d = -1; d <= 1; d++)
                {
                    if (a + c != height && a + c != -1 && b + d != width && b + d != -1)
                    {

                        r += temporary[a + c][b + d].rgbtRed;
                        g += temporary[a + c][b + d].rgbtGreen;
                        blue += temporary[a + c][b + d].rgbtBlue;
                        number++;
                    }
                }
            }
            // Set each RGB values to their blurred values
            image[a][b].rgbtRed = round(r / number);
            image[a][b].rgbtGreen = round(g / number);
            image[a][b].rgbtBlue = round(blue / number);
        }
    }
}
