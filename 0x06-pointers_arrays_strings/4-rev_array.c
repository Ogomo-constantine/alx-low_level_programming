#include "main.h"

/**
 * reverse_array - function that reverses the content of an array of integers
 * @a: array
 * @n: no. of element
 * Return: void
 */

void reverse_array(int *a, int n)

{

	int temp, i;

	for (i = n - 1; i >= n / 2; i--)
	{
		tmp = a[n - 1 - i];
		a[n - 1 - i] = a[i];
		a[i] = tmp;
	}

}
