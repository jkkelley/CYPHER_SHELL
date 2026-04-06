/* triangle.c */
#include <stdio.h>

/* Get the area of a triangle */
int area_triangle(int base, int height)
{
    int area;

    area = (base * height) / 2;

    return area;
}

int main()
{
    int base, height, area;

    printf("Base: ");
    // This flushes the buffer
    fflush(stdout);
    scanf("%d", &base);

    printf("Height: ");
    fflush(stdout);
    scanf("%d", &height);

    area = area_triangle(base, height);
    printf("The area is %d\n", area);

    return 0;
}