/* Steven Nunes
 * I pledge my honor that I have abided by the Stevens Honor System.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* prints the given array of strings on a single line seperated by whitespace */
void printArray(char** arr)
{
	int i;
	for (i = 0; arr[i] != NULL; i++)
	{
		printf("%s ", arr[i]);
	}
	printf("\n");
}

/* returns the index where the string appears in the array, -1 if it does not appear */
int contains(char* str, char** arr)
{
	int i;
	int index = -1;
	for (i = 0; arr[i] != NULL; i++)
	{
		if (strcmp(str, arr[i]) == 0)
		{
			index = i;
		}
	}
	return index;
}

int main(int argc, char** argv)
{
	int i;
	char* dir = NULL; //the directory to copy from
	int count = NULL; //the number of instances to create
	char* inst_id;

	if (argc < 2)
	{
		printf("Please provide an EC2 instance id to launch. Example: ./afewmore ami-1234567\n");
		return 0;
	}
	if ((i = contains("-h", argv)) != -1)
	{
		printf("Provide an EC2 instance id as an argument to duplicate it.\n");
		printf("Options:\n");
		printf("-d dir: copy the contents in this directory from the source instance to the new instances\n");
		printf("-n num: specify the number of new instances to create (default = 10) \n");
		printf("-v: provide verbose output\n");
		return 0;
	}
	inst_id = argv[1];
	if ((i = contains("-d", argv)) != -1)
	{
		if (argv[i+1] == NULL)
		{
			printf("No directory specified after -d\n");
			return 0;
		}
		dir = argv[i+1];
	}
	if ((i = contains("-n", argv)) != -1)
	{
		if (argv[i+1] == NULL)
		{
			printf("No value specified after -n\n");
			return 0;
		}
		/* TODO: check that the given argument is in fact a number value */
		/* currently assumes that the user will provide a number after -n */
		count = atoi(argv[i+1]);
	}

	/* if the key does not already exist, create it and configure the security group*/
	if (!(access("key.pem", F_OK) != -1))
	{
		system("aws ec2 create-key-pair --key-name key --query 'KeyMaterial' --output text > key.pem");
		system("aws ec2 create-security-group --group-name sg --description \"default\"");
	}
	return 0;
}
