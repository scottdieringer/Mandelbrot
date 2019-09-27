/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
int check_colors(unsigned int, unsigned int, unsigned int);

uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
	//YOUR CODE HERE
       uint8_t **array_of_colors = NULL;
       FILE *fileptr = fopen(colorfile, "r");
       int size_of_array;
        
       if (fileptr == NULL) {
           return array_of_colors;
       }
            
       if (fscanf(fileptr, "%d", &size_of_array) != 1 || (size_of_array < 0)) {
          return array_of_colors;
       }
        

       *colorcount = size_of_array;
       array_of_colors = (uint8_t **) malloc(sizeof(uint8_t  *) * size_of_array);
       uint8_t ** temp = array_of_colors;
       unsigned int first_color = 256;
       unsigned int second_color = 256;
       unsigned int third_color = 256;
              
       int count = 0;
       int line_read = 3;
       int correct_color_range = 1;                
       
       while ((correct_color_range) && (line_read == 3) && (count < size_of_array)) {
           line_read = fscanf(fileptr, "%u %u %u", &first_color, &second_color, &third_color);
           correct_color_range = check_colors(first_color, second_color, third_color);
           if (line_read == 3 && correct_color_range) {
               uint8_t * line = (uint8_t *) malloc(sizeof(uint8_t) * 3);
               *line = first_color;
               *(line + 1) = second_color;
               *(line + 2) = third_color;
               *temp = line;
               temp++;
               count++;
           }
       }

      char next_char = fgetc(fileptr);
      
      if ((count < size_of_array) || (correct_color_range != 1) || (line_read != 3) || (next_char == '.' && count == size_of_array)) {
           int j;
           temp = temp - count;
           for (j = 0; j < count; j++) {
               free(*temp);
               temp++;
           }
           free(array_of_colors);
           array_of_colors = NULL;
           fclose(fileptr);
           return array_of_colors;
       }
       
       fclose(fileptr);
       return array_of_colors;
}

int check_colors(unsigned int first_color, unsigned int second_color, unsigned int third_color) {
    if (first_color < 0 || first_color > 255) {
        return 0;
    }
    if (second_color < 0 || second_color > 255) {
        return 0;
    }
    if (third_color < 0 || third_color > 255) {
        return 0;
    }
        return 1;
}
/*
int main() {
    uint8_t ** test1 = NULL;
    int a = 0;
    int * array_size1;
    
    array_size1 = &a;
    test1 = FileToColorMap("test_file_to_read1.txt", array_size1);
    
    uint8_t * first_row = *test1;
    uint8_t first_item = *first_row;
    printf("%u\n", first_item);
    
    first_row +=1;
    uint8_t second_item = *first_row;
    printf("%u\n", second_item);
    
    uint8_t * third_row = *(test1 + 2);
    uint8_t third_item = *third_row;
    printf("%u\n", third_item);
    
    third_row +=1;
    third_item = *third_row;
    printf("%u\n", third_item);
    
    int z;
    for (z = 0; z < (*array_size1); z++) {
        free(*test1);
        test1++;
    }

    free(test1 - (*array_size1));
    
    uint8_t ** test2;
    int b = 0;
    int * array_size2;
    array_size2 = &b;
    test2 = FileToColorMap("test_file_to_read2.txt", array_size2);
    if (test2 == NULL) {
        printf("Test 1 passed\n");
    } else {
        printf("Try again asshole\n");
    }
    
    uint8_t ** test3;
    int c = 0;
    int * array_size3 = &c;
    test3 = FileToColorMap("test_file_to_read3.txt", array_size3);
    if (test3 == NULL) {
        printf("Test 2 passed\n");
    } else {
       printf("Test 2 failed\n");
    }

    uint8_t ** test4;
    int d = 0;
    int * array_size4 = &d;
    test4 = FileToColorMap("test_file_to_read4.txt", array_size4);
    if (test4 == NULL) {
        printf("Test 3 passed\n");
    } else {
        printf("Test 3 failed\n");
    }
    
    uint8_t ** test5;
    int e = 0;
    int *array_size5 = &e;
    test5 = FileToColorMap("test_file_to_read5.txt", array_size5);
    if (test5 == NULL) {
        printf("Test 4 passed\n");
    } else {
        printf("Test 4 failed\n");
    }
    uint8_t ** test6;
    int f = 0;
    int * array_size6 = &f;
    test6 = FileToColorMap("test_file_to_read6.txt", array_size6);
    if (test6 == NULL) {
        printf("Test 5 passed\n");
    } else {
        printf("Test 5 failed\n");
    }

    uint8_t ** test7;
    int g = 0;
    int * array_size7 = &g;
    test7 = FileToColorMap("test_file_to_read7.txt", array_size7);
    if (test7 == NULL) {
        printf("Test 6 passed\n");
    } else {
        printf("Test 6 failed\n");
    }		
    uint8_t ** test8;
    int h = 0;
    int * array_size8 = &h;
    test8 = FileToColorMap("test_file_to_read8.txt", array_size8);
    if (test8 == NULL) {
        printf("Test 7 failed\n");
    } else {
        printf("Test 7 passed\n");
    }

    uint8_t * first_row8 = *test8;
    uint8_t first_item8 = *first_row8;
    printf("Should be 1 is %u\n", first_item8);

    first_row8 +=1;
    uint8_t second_item8 = *first_row8;
    printf("Should be 2 is %u\n", second_item8);

    uint8_t * third_row8 = *(test8 + 2);
    uint8_t third_item8 = *third_row8;
    printf("Should be 2 is %u\n", third_item8);

    third_row8 +=1;
    third_item8 = *third_row8;
    printf("Should be 7 is %u\n", third_item8);
    
    int y;
    for (y = 0; y < (*array_size8); y++) {
        free(*test8);
        test8++;
    }

    free(test8 - (*array_size8));

     
    

} */

