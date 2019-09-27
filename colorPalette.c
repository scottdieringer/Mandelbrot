/*********************
**  Color Palette generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


//You don't need to call this function but it helps you understand how the arguments are passed in 
void usage(char* argv[])
{
	printf("Incorrect usage: Expected arguments are %s <inputfile> <outputfolder> <width> <heightpercolor>", argv[0]);
}

//Creates a color palette image for the given colorfile in outputfile. Width and heightpercolor dictates the dimensions of each color. Output should be in P3 format
int P3colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE
	
        if (width < 1 || heightpercolor < 1) {
            return 1;
        }
	
        int number_of_colors = 0;
        int * b = &number_of_colors;
        uint8_t ** color_array = FileToColorMap(colorfile, b);
        
        if (color_array == NULL) {
            return 1;
        } 
        
        FILE * fileptr = fopen(outputfile, "w");
        
        char width_array[50];
        memset(&width_array[0], 0, sizeof(width_array)); 
        int holder1;
        holder1 = sprintf(width_array, "%d", width);

        int holder2;        
        int height = heightpercolor * number_of_colors;
        char height_array[50];
        memset(&height_array[0], 0, sizeof(height_array)); 
        holder2 = sprintf(height_array, "%d", height);
        
        char max[4] = {'2', '5', '5', '\0'};
        char first[3] = {'P', '3', '\0'};

        fprintf(fileptr, "%s %s %s %s\n", first, width_array, height_array, max); 
        
        uint8_t ** temp = color_array;
        uint8_t * row;
        uint8_t first_color;
        uint8_t second_color;
        uint8_t third_color;
               
        int i, j, k;
  
        for (i = 0; i < number_of_colors; i++) {
            row = *(temp + i);
            first_color = *row;
            second_color = *(row + 1);
            third_color = *(row + 2);

            for (j = 0; j < heightpercolor; j++) {
                for (k = 0; k < width; k++)  {
                    if (k == width - 1) { 
                        fprintf(fileptr, "%u %u %u\n", first_color, second_color, third_color);
                    } else {
                        fprintf(fileptr, "%u %u %u ", first_color, second_color, third_color);
                    }
                }
    
            }
        }

        int y;
        for (y = 0; y < number_of_colors; y++) {
            free(*color_array);
            color_array++;

        }
        free(color_array - number_of_colors);
        fclose(fileptr);
      
	return 0;
}

//Same as above, but with P6 format
int P6colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	//YOUR CODE HERE
        if (width < 1 || heightpercolor < 1) {
            return 1;
        }

        int number_of_colors = 0;
        int * b = &number_of_colors;
        uint8_t ** color_array = FileToColorMap(colorfile, b);
        uint8_t * uint8_array;
          

        if (color_array == NULL) {
            return 1;
        }

        FILE * fileptr = fopen(outputfile, "w");
        uint8_array = calloc(number_of_colors * 3 * width * heightpercolor, sizeof(uint8_t));
        
        if (uint8_array == NULL) {
            int y;
            for (y = 0; y < number_of_colors; y++) {
                free(*color_array);
                color_array++;
            }

            free(color_array - number_of_colors);
            return 1;
        }
        
        uint8_t * temp_uint8 = uint8_array;      

        char width_array[50];
        memset(&width_array[0], 0, sizeof(width_array));
        int holder1;
        holder1 = sprintf(width_array, "%d", width);

        int holder2;
        int height = heightpercolor * number_of_colors;
        char height_array[50];
        memset(&height_array[0], 0, sizeof(height_array)); 
        holder2 = sprintf(height_array, "%d", height);

        char max[4] = {'2', '5', '5', '\0'};
        char first[3] = {'P', '6', '\0'};

        fprintf(fileptr, "%s %s %s %s\n", first, width_array, height_array, max);
        

        uint8_t ** temp_color = color_array;
        uint8_t * row;
        uint8_t first_color;
        uint8_t second_color;
        uint8_t third_color;
        
        int i, j, k;
        int g;
        for (i = 0; i < number_of_colors; i++) {
            row = *(temp_color + i);
            first_color = *row;
            second_color = *(row + 1);
            third_color = *(row + 2);

            for (j = 0; j < heightpercolor; j++) {
                for (k = 0; k < width; k++)  {
                    *temp_uint8 = first_color;
                     temp_uint8++;
                    *temp_uint8 = second_color;
                     temp_uint8++;
                    *temp_uint8 = third_color;
                    if (k == width - 1 && j == heightpercolor - 1 && i == number_of_colors - 1) {
                        g = 1;   
                    } else {
                     temp_uint8++;
                    }          

                 }
            }

        }
        
        size_t check;
        check = fwrite(uint8_array, 1, 3 * number_of_colors * width * heightpercolor, fileptr);

        int y;
        for (y = 0; y < number_of_colors; y++) {
            free(*color_array);
            color_array++;
        }
        
        free(color_array - number_of_colors);
        free(uint8_array);
        
        fclose(fileptr);

	return 0;
}


//The one piece of c code you don't have to read or understand. Still, might as well read it, if you have time.

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		usage(argv);
		return 1;
	}
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	char* P3end = "/colorpaletteP3.ppm";
	char* P6end = "/colorpaletteP6.ppm";
	char buffer[strlen(argv[2]) + strlen(P3end)];
	sprintf(buffer, "%s%s", argv[2], P3end);
	int failed = P3colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P3colorpalette");
		return 1;
	}
	sprintf(buffer, "%s%s", argv[2], P6end);
	failed = P6colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P6colorpalette");
		return 1;
	}
	printf("P3colorpalette and P6colorpalette ran without error, output should be stored in %s%s, %s%s", argv[2], P3end, argv[2], P6end);
	return 0;
}
/*

int main() {
    int test1;
    test1 = P3colorpalette("test_file_to_read1.txt", 4, 2, "test_ppm1.ppmP3");
    int test2;
    test2 = P6colorpalette("test_file_to_read9.txt", 2, 2, "test_ppm2.ppmP6");

}*/




