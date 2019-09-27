/*********************
**  Complex Numbers
**  This file contains a few functions that will be useful when performing computations with complex numbers
**  It is advised that you work on this part first.
**********************/

#include "ComplexNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct ComplexNumber
{
	double real;
	double imaginary;
}ComplexNumber;

//Returns a pointer to a new Complex Number with the given real and imaginary components
ComplexNumber* newComplexNumber(double real_component, double imaginary_component)
{
    //YOUR CODE HERE
    ComplexNumber * complex_ptr;
    complex_ptr = (ComplexNumber*) malloc(sizeof(ComplexNumber));
    complex_ptr->real = real_component;
    complex_ptr->imaginary = imaginary_component;
    return complex_ptr;
}

//Returns a pointer to a new Complex Number equal to a*b
ComplexNumber* ComplexProduct(ComplexNumber* a, ComplexNumber* b)
{
    //YOUR CODE HERE
    
    double first_real = a->real;
    double second_real = b->real;
    double first_img = a->imaginary;
    double second_img = b->imaginary;
    double reala = first_real * second_real;
    double realb = first_img * second_img;
    double real = reala - realb;
    double imga = first_real * second_img;
    double imgb = first_img * second_real;
    double img = imga + imgb;
    ComplexNumber * complex_ptr = newComplexNumber(real, img);
    return complex_ptr;
}

//Returns a pointer to a new Complex Number equal to a+b
ComplexNumber* ComplexSum(ComplexNumber* a, ComplexNumber* b)
{
    //YOUR CODE HERE
    double first_real = a->real;
    double second_real = b->real;
    double first_img = a->imaginary;
    double second_img = b->imaginary;
    double real = first_real + second_real;
    double img = first_img + second_img;
    ComplexNumber * complex_ptr = newComplexNumber(real, img);
    return complex_ptr;
    
}

//Returns the absolute value of Complex Number a
double ComplexAbs(ComplexNumber* a)
{
    //YOUR CODE HERE
    double real = a->real;
    double img = a->imaginary;
    double modulus = sqrt(real * real + img * img);
    return modulus;

}

void freeComplexNumber(ComplexNumber* a)
{
    //YOUR CODE HERE
    free(a);
}

double Re(ComplexNumber* a)
{
    //YOUR CODE HERE
    double real = a->real;
    return real;
}
double Im(ComplexNumber* a)
{
    //YOUR CODE HERE
    double img = a->imaginary;
    return img;
}


//Contains a few tests.
int test_complex_number()
{
	ComplexNumber* a = newComplexNumber(2.0, 1.0);
	if (a == NULL)
	{
		printf("Creation of complex numbers not implemented\n");
		return 0;
	}
	ComplexNumber* b = ComplexProduct(a, a);
	if (b == NULL)
	{
		printf("Multiplication of complex numbers not implemented\n");
		free(a);
		return 0;
	}
	ComplexNumber* c = ComplexSum(b, b);
	if (c == NULL)
	{
		printf("Addition of complex numbers not implemented\n");
		free(a);
		free(b);
		return 0;
	}
	float d = ComplexAbs(c);
	if (d == 0)
	{
		printf("Absolute Value of complex numbers not implemented\n");
		free(a);
		free(b);
		free(c);
		return 0;
	}
	else if (fabsf(d - 10) < 0.0001)
	{
		printf("Sample tests for complex numbers all passed\n");
	}
	else
	{
		printf("At least one of your functions is incorrect\n");
	}
	free(a);
	free(b);
	free(c);
	return 0;
}

/*int main() {
    test_complex_number();
    return 0;

}*/
