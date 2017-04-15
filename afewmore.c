/* Steven Nunes
 * I pledge my honor that I have abided by the Stevens Honor System.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
									//since the default is 10, I think it should initially be set to 10
	char* inst_id;
	char** new_instances; //array of all instances
	char* curr_instance; //id of the most recently created instance
	char* curr_dns;
	char ip[80]= "54.90.120.43"; //dns of the most recently created instance
	char* token;
	const char s[2] = ".";

	strcpy(curr_dns, "ec2");
	printf("%s\n", ip);
	printf("%s\n", curr_dns);
	token = strtok(ip, s);
	printf("%s\n", token);
  while( token != NULL ) 
  {
		strcat(curr_dns, "-");
		strcat(curr_dns, token);
		printf("%s\n", curr_dns);
  
  	token = strtok(NULL, s);
		//printf("%s\n", token);
  }
	strcat(curr_dns, ".compute-1.amazonaws.com");
	printf("%s\n", curr_dns);

	/*if (argc < 2)
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
		/* currently assumes that the user will provide a number after -n /
		count = atoi(argv[i+1]);
	}

	/* if the key does not already exist, create it and configure the security group/
	if (!(access("key.pem", F_OK) != -1))
	{
		system("aws ec2 create-key-pair --key-name key --query 'KeyMaterial' --output text > key.pem");
		system("aws ec2 create-security-group --group-name sg --description \"default\"");
		//system("chmod 400 key.pem")
	}

	/*create new instances
	for(int i=0; i<count; i++)
	{
		//creates a new instance and outputs its id
		//how does the output look? is it still printed to command line? how to save it to array?
		system("aws ec2 run-instances --image-id ami-6de0dd04 --security-group-ids sg-db97cfa4 --count 1 --instance-type t1.micro --key-name key --query 'Instances[0].InstanceId'");
		//caputure all public DNS and transform it
		system("aws ec2 run-instances ID --query \"Reservations[*].Instances[*].PublicIpAddress\"");
		
		strcpy(curr_dns, "ec2-");
		token = strtok(ip, ".");
   	while( token != NULL ) 
   	{
			 strcat(curr_dns, token)
    
      token = strtok(NULL, ".");
   }
	 strcat(curr_dns, ".compute-1.amazonaws.com") 

	 strcpy(curr_dns, "ec2");
		token = strtok(ip, s);
		while( token != NULL ) 
		{
			strcat(curr_dns, "-");
			strcat(curr_dns, token);
		
			token = strtok(NULL, s);
		}
		strcat(curr_dns, ".compute-1.amazonaws.com");
		printf("%s\n", curr_dns);

	 //put it to sleep while we wait for the new instance to initialize
	 sleep(number)
	 system("scp -i key.pem -r DIR ubuntu@CURR_DNS") 
	}
	*/
	return 0;
}
