/* instance_costs.c */
#include <stdio.h>
#include <string.h>

// Alias macro
#define F_OUT() fflush(stdout)

typedef struct {
    char ec2_instance_size[32];
    float cost_of_server_by_hour;
} EC2InstanceInfo;

// Function handling the prompts using any stream (stdin or file)
void get_ec2_info(FILE *stream, EC2InstanceInfo *info)
{
    // -> is used to access members when you have a pointer
    // Note: info->ec2_instance_size is an array, so it doesn't need a '&'
    
    // 1. Get Instance Size
    printf("What is the EC2 instance size? ");
    F_OUT(); // Flush is out
    fscanf(stream, "%31s", info->ec2_instance_size);

    // Note: &info->cost_of_server_by_hour DOES need '&' to get the addr
    // of the int

    // 2. Get Cost (using %f for decimals)
    printf("Cost per hour for %s? ", info->ec2_instance_size);
    F_OUT(); // Flush is out
    fscanf(stream, "%f", &info->cost_of_server_by_hour);
}

int main()
{
    // Declare the struct on the stack
    EC2InstanceInfo my_instance;

    // PRODUCTION: Pass 'stdin'
    get_ec2_info(stdin, &my_instance);

    /* TESTING: Pass a file pointer instead
       FILE *test_data = fopen("test.txt", "r");
       get_ec2_data(test_data, &my_instance);
    */

    printf("\n--- Infrastructure Report ---\n");
    printf("Instance Type: %s\n", my_instance.ec2_instance_size);
    printf("Hourly Rate: $%.2f\n", my_instance.cost_of_server_by_hour);

    return 0; // exit out of here
 }