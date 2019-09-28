/*Mandelbrot fractal movie generator
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include <sys/types.h>
#include <string.h>

int iteration_to_color(uint64_t iteration, int size_of_colormap); 

void printUsage(char* argv[])
{
  printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
  printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so 
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, uint64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, uint64_t resolution, uint64_t ** output){
    //YOUR CODE HERE

    double a = (1/(framecount - 1)) * log10(finalscale / initialscale);
    double common_ratio = pow(10, a);
    double scale;
    int i;
    uint64_t * array_iter;
    
    for (i = 0; i <= framecount - 1; i++) {
        array_iter = *output;
        scale = initialscale * pow(common_ratio, i);
        Mandelbrot(threshold, max_iterations, center, scale, resolution, array_iter);
        output++;  
    }

}

/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
	//Tips on how to get started on main function: 
	//MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
	//Mayke you complete the steps below in order. 

	//STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
	/*
	Check the spec for examples of invalid inputs.
	Remember to use your solution to B.1.1 to process colorfile.
	*/

	//YOUR CODE HERE 
        if (argc != 11) {
            return 1;
        }
        double threshold, initialscale, finalscale;
        ComplexNumber* center;
        uint64_t max_iterations, resolution, length_of_mandelbrot;
        int framecount;
        char * outputfolder;
        char * colorfile;
        
        uint8_t ** colormap;             //map of colors each element is array of 3 colors        
        uint8_t ** colormap_tracker;
        uint8_t * colortracker;          // arrays of 3 colors
        
        uint8_t * color_to_output;      //1-D array of colors to output to file
        uint8_t * color_to_output_tracker;
        
        uint64_t ** output;           // array of arrays of iteration numbers
        uint64_t ** output_tracker;   
        uint64_t * iter_tracker;     // array of iteration numbers of dimension (2 * resoltion + 1) * (2 * resoltion + 1)
        uint64_t * array_iter;

        uint64_t iter;   // iteration number from array of iterations
        uint8_t first_color;
        uint8_t second_color;
        uint8_t third_color;
        int place_on_colormap; // location on colormap to get color
        int i, k;
        FILE *outputfileptr;
        size_t check;


        char filenames[50];
        char frame[6] = {'f', 'r', 'a', 'm', 'e', '\0'};
        char ppm[4] = {'p', 'p', 'm', '\0'};
        char p6[3] = {'P', '6', '\0'};
        char bytesize[4] = {'2', '5', '5', '\0'};
        char width[50];
        
        threshold = atof(argv[1]);
        max_iterations = (uint64_t )atoi(argv[2]);
        center = newComplexNumber(atof(argv[3]), atof(argv[4]));
        if (center == NULL) {
            return 1;
        }
        initialscale = atof(argv[5]);
        finalscale = atof(argv[6]);
        framecount = atoi(argv[7]);
        resolution = (uint64_t)(atoi(argv[8]));
        outputfolder = argv[9];
        colorfile = argv[10];
        
        int colorcount = 0;
        int * a = &colorcount;
        colormap = FileToColorMap(colorfile, a);  //array where each element is an array of three colors
        colormap_tracker = colormap;
        
        if (colormap == NULL) 
           return 1;
        if (threshold <= 0 || max_iterations <= 0 || initialscale <= 0 || finalscale <= 0) 
            return 1;
        
        if (framecount <= 0 || framecount > 10000) 
            return 1;
        
        if (resolution < 0) 
             return 1;
        if (framecount == 1 && initialscale != finalscale) 
             return 1;
       
        length_of_mandelbrot = (2 * resolution + 1) * (2 * resolution + 1);
        sprintf(width, "%lu", 2 * resolution + 1);
      
        color_to_output = (uint8_t *) malloc(sizeof(uint8_t) * 3 * length_of_mandelbrot);
     
        if (color_to_output == NULL) {
            int y;
            for (y = 0; y < colorcount; y++) {
               free(*colormap);
               colormap++;
            }
            free(colormap - colorcount);
            freeComplexNumber(center);
            return 1;
        }

        color_to_output_tracker = color_to_output;
        
        
        
	//STEP 2: Run MandelMovie on the correct arguments.
	/*
	MandelMovie requires an output array, so make sure you allocate the proper amount of space. 
	If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
	*/

	//YOUR CODE HERE 
        
        output = (uint64_t **) malloc(sizeof(uint64_t *) * framecount);
        
        if (output == NULL) {                       // if output allocation fails free everything so far, ie colormap and its subarrays
            int y;
            for (y = 0; y < colorcount; y++) {
               free(*colormap);
               colormap++;
            }
            free(colormap - colorcount);
            free(color_to_output);
            freeComplexNumber(center);
            return 1;
        }
        
        output_tracker = output;

        int r;
        for (r = 0; r < framecount; r++) {
            array_iter = (uint64_t *) malloc(sizeof(uint64_t) * length_of_mandelbrot);  // if any array_iter fails to allocate must free colormap and array_iters 
            if (array_iter == NULL) {                           // that have so far been allocated
                break;
            }
            *output_tracker = array_iter;
            output_tracker++;
        }

        output_tracker = output;

        if (r < framecount) {
            int f;
            for (f = 0; f < colorcount; f++) {
               free(*colormap);
               colormap++;
            }
            free(colormap - colorcount);
            free(color_to_output);
            freeComplexNumber(center);
            
            int s;
            for (s = 0; s <= r - 1; s++) {
                free(*output_tracker);
                output_tracker++;
            } 
            free(output);
            
            return 1;
        }
        
        
        

        MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, output);

        


	//STEP 3: Output the results of MandelMovie to .ppm files.
	/*
	Convert from iteration count to colors, and output the results into output files.
	Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
	Feel free to create your own helper function to complete this step.
	As a reminder, we are using P6 format, not P3.
	*/

	//YOUR CODE HERE 
        
        for (i = 0; i < framecount; i++) {
            
            snprintf(filenames, sizeof(filenames),"./%s/%s%05d.%s", outputfolder, frame, i, ppm);
            outputfileptr = fopen(filenames, "w+"); 
            fprintf(outputfileptr, "%s %s %s %s\n", p6, width, width, bytesize);

            iter_tracker = *(output_tracker + i);
            
            for (k = 0; k < length_of_mandelbrot; k++) {
                
                iter = *(iter_tracker + k);
                place_on_colormap = iteration_to_color(iter, colorcount);
                
                if (place_on_colormap == 0) {
                    first_color = 0;
                    second_color = 0;
                    third_color = 0;
                } else {
                    place_on_colormap = place_on_colormap - 1;
                    colortracker = *(colormap_tracker + place_on_colormap);
                    first_color = *colortracker;
                    second_color = *(colortracker + 1);
                    third_color = *(colortracker + 2);
                } 
               
                *color_to_output_tracker = first_color;
                color_to_output_tracker++;
                *color_to_output_tracker = second_color;
                color_to_output_tracker++;
                *color_to_output_tracker = third_color;
                color_to_output_tracker++;
               
            }
           
            

            color_to_output_tracker = color_to_output;

            size_t check;
            check = fwrite(color_to_output, 1, 3 * length_of_mandelbrot, outputfileptr);

            fclose(outputfileptr);
          
        }

	//STEP 4: Free all allocated memory
	/*
	Make sure there's no memory leak.
	*/
	//YOUR CODE HERE 

        int z;
 
        for (z = 0; z < colorcount; z++) {
            free(*colormap);
            colormap++;
        }
        
        free(colormap - colorcount);
        
        free(color_to_output);
        
        freeComplexNumber(center);

        int q;
        for (q = 0; q < framecount; q++) {
            free(*output);
            output++;
        }

        free(output - framecount);

	return 0;
}

int iteration_to_color(uint64_t iteration, int size_of_colormap) {
    if (iteration == 0) {
        return 0;
    } else if ((iteration % size_of_colormap) == 0) {
        return size_of_colormap;
    } else {
        return iteration % size_of_colormap;
    } 
}


