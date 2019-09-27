/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>
=======
#include <stdint.h>
#include <inttypes.>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
uint64_t MandelbrotIterations(uint64_t maxiters, ComplexNumber * point, double threshold)
{
    //YOUR CODE HERE
    if (maxiters <=0) {
        return 0;
    } else if (maxiters == 1) { 
        double distance = ComplexAbs(point);
        if (distance >= threshold) {
            return 1;
        } else {
            return 0;
        }    
    } else {
       uint64_t counter = 1;
       double distance_from_origin = ComplexAbs(point);
       double real = Re(point);
       double img = Im(point);
       ComplexNumber * complex_iter = newComplexNumber(real, img);
       ComplexNumber * complex_constant = newComplexNumber(real, img);
       ComplexNumber * temp;
       ComplexNumber * complex_product;
       ComplexNumber * complex_sum;
       while ((distance_from_origin < threshold) && (counter <= maxiters)) {
           complex_product = ComplexProduct(complex_iter, complex_iter);
           complex_sum = ComplexSum(complex_product, complex_constant);
           freeComplexNumber(complex_product);
           temp = complex_iter;
           complex_iter = complex_sum;
           freeComplexNumber(temp);
           distance_from_origin = ComplexAbs(complex_iter);
           counter++;
       }
       freeComplexNumber(complex_iter);
       freeComplexNumber(complex_constant);

       if (distance_from_origin >= threshold) {
          return counter;
       } else  {
           return 0;
       }
    }               
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, uint64_t max_iterations, ComplexNumber* center, double scale, uint64_t resolution, uint64_t * output){
    //YOUR CODE HERE
    uint64_t dimension = 2 * resolution + 1;
    double real_center = Re(center);
    double img_center = Im(center);
    double real_top = real_center + scale;
    double real_bottom = real_center - scale;
    double img_top = img_center + scale;
    double real_steps = (real_top - real_center) / (double) resolution;
    double img_steps = (img_top - img_center) / (double) resolution;
    double real_to_find;
    double img_to_find;
    int i, k;
    ComplexNumber * temp;
    for (i = 0; i < dimension; i++) {
        for (k = 0; k < dimension; k++) {
            real_to_find = real_bottom + (k * real_steps);
            img_to_find = img_top - (i * img_steps);
            temp = newComplexNumber(real_to_find, img_to_find);
            uint64_t iterations = MandelbrotIterations(max_iterations, temp, threshold);
            *output = iterations;
            output++;
            freeComplexNumber(temp);        

        }
    }
}   
/*
int main() {
    ComplexNumber * test1 = newComplexNumber(-1, 1);
    uint64_t iterations1 = 4;
    double threshold1 = 2;
    uint64_t try1 = MandelbrotIterations(iterations1, test1, threshold1);
    printf("%f\n", (double) try1);
    freeComplexNumber(test1);
    ComplexNumber * test2 = newComplexNumber(1, 0);
    uint64_t iterations2 = 4;
    double threshold2 = 2;
    uint64_t try2 = MandelbrotIterations(iterations2, test2, threshold2);
    printf("%f\n", (double) try2);
    freeComplexNumber(test2);
    ComplexNumber * test3 = newComplexNumber(5, 3);
    uint64_t iterations3 = 4;
    double threshold3 = 1000;
    uint64_t try3 = MandelbrotIterations(iterations3, test3, threshold3); 
    printf("%f\n", (double) try3);
    freeComplexNumber(test3);
    ComplexNumber * test4 = newComplexNumber(-0.5, 0);
    uint64_t iterations4 = 100;
    double threshold4 = 2;
    uint64_t try4 = MandelbrotIterations(iterations4, test4, threshold4);
    printf("%f\n", (double) try4);
    freeComplexNumber(test4);
    ComplexNumber * test5 = newComplexNumber(1, 2);
    uint64_t iterations5 = 4;
    double threshold5 = 10;
    uint64_t try5 = MandelbrotIterations(iterations5, test5, threshold5);
    printf("%f\n", (double) try5);
    freeComplexNumber(test5);
    ComplexNumber * test6 = newComplexNumber(5, 3);
    uint64_t resolution1 = 2;
    double dimension1 = 2 * resolution1 + 1;
    double threshold6 = 100;
    uint64_t iterations6 = 6;
    uint64_t * output_array1;
    double scale1 = 5.0;
    output_array1 = (uint64_t *) malloc(sizeof(uint64_t) * dimension1 * dimension1);
    Mandelbrot(threshold6, iterations6, test6, scale1, resolution1, output_array1);
    printf("%f\n", (double) *(output_array1 + 18));
    freeComplexNumber(test6);
    free(output_array1);
    ComplexNumber * test7 = newComplexNumber(3, 3);
    uint64_t resolution2 = 3;
    double dimension2 = 2 * resolution2 + 1;
    double threshold7 = 90;
    uint64_t iterations7 = 9;
    uint64_t * output_array2;
    double scale2 = 6;
    output_array2 = (uint64_t *) malloc(sizeof(uint64_t) * dimension2 * dimension2);
    Mandelbrot(threshold7, iterations7, test7, scale2, resolution2, output_array2);
    printf("%f\n", (double) *(output_array2 + 48));
    freeComplexNumber(test7);
    free(output_array2);
}*/


