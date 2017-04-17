/* Steven Nunes
 * I pledge my honor that I have abided by the Stevens Honor System.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//turns a string into an array of strings deliminated by spaces 
char** my_str2vect(char* arr)
{
	char** vect;
	int i, j, k, num_words, wordlen;
	i = 0;
	num_words=0;


	if(arr == NULL || arr[i] == '\0')
		return NULL;
	/*Finds the number of words in the string*/
	while(arr[i] != '\0')
	{
		if(arr[i] == ' ' && (arr[i+1] != ' ' || arr[i+1] == '\0'))
		{
			num_words++;
		}
		i++;
	}

	/*Allocates space for each word*/
	vect = (char**) malloc(sizeof(char*) * (num_words + 1));

	/*Finds the number of letters in each word and allocates space for it*/
	i=0;
	j=0;
	while(arr[i] != '\0')
	{
		if(arr[i] == ' ' && arr[i+1] != ' ')
		{
			vect[j] = (char*)malloc(sizeof(char) * wordlen);
			wordlen = 0;
			j++;
		}

		if(arr[i] != ' ')
			wordlen++;
		i++;
	}
	vect[j] = (char*)malloc(sizeof(char) * wordlen);

	 i=0;
	 j=0;
	 k=0;
	/*Adds the letters to the vector*/
	while(arr[i] != '\0')
	{
		if(arr[i] == ' ' && arr[i+1] != ' ')
		{
			j++;
			k = 0;
		}
		if(arr[i] != ' ')
		{
			vect[j][k] = arr[i];
			k++;
		}
		i++;
	}

	vect[j+1] = (char*)NULL;
	return vect;
}

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
	int verbose = 0;
	char dir[200]; //the directory to copy from
	int count = 1; //FOR THE SAKE OF TESTING
									//the number of instances to create
									//since the default is 10, I think it should initially be set to 10
	char* inst_id;
	char** insts;
	char** dnss;
	char* all_instances= malloc(sizeof(char) * 1028); //array of all instances
	char* all_dns= malloc(sizeof(char) * 1028);
	char* curr_instance = malloc(sizeof(char) * 100); //id of the most recently created instance
	char* ip= malloc(sizeof(char) * 100); //dns of the most recently created instance
	char* curr_dns= malloc(sizeof(char) * 100);


	char addresses[50][100];

	char* token;
	const char s[2] = ".";

	FILE* fp;
	char path[1035];
	//char* output= malloc(sizeof(char) * 1035);

	/*
	char ipaddr[1024];
	fp = popen("curl ipinfo.io/ip", "r");
	fgets(ipaddr, sizeof(ipaddr)-1, fp);
	printf("IP addr: %s\n", ipaddr);
	pclose(fp);
	*/

	char command1[200];
	char command2[200];
	char command3[200];

	if (argc < 2)
	{
		printf("Please provide an EC2 instance id to launch. Example: ./afewmore i-1234567\n");
		return 0;
	}
	if ((i = contains("-h", argv)) != -1)
	{
		printf("Provide an EC2 instance id as an argument to duplicate it.\n");
		printf("Options:\n");
		printf("-d dir: copy the contents in this directory from the source instance to the new instances (default is ./data)\n");
		printf("-n num: specify the number of new instances to create (default = 10) \n");
		printf("-v: provide verbose output\n");
		return 0;
	}
	if ((i = contains("-v", argv)) != -1)
	{
		verbose = 1;
	}

	inst_id = argv[1];
	sprintf(dir, "data");

	if ((i = contains("-d", argv)) != -1)
	{
		if (argv[i+1] == NULL)
		{
			printf("No directory specified after -d\n");
			return 0;
		}
		sprintf(dir, "%s", argv[i+1]);
		//dir = argv[i+1];
	}
	if ((i = contains("-n", argv)) != -1)
	{
		if (argv[i+1] == NULL)
		{
			printf("No value specified after -n\n");
			return 0;
		}
		/* currently assumes that the user will provide a number after -n */
		count = atoi(argv[i+1]);
	}

	/* if the key does not already exist, create it and configure the security group */
	if (!(access("key.pem", F_OK) != -1))
	{
		system("aws ec2 create-key-pair --key-name key --query 'KeyMaterial' --output text > key.pem");
		system("aws ec2 create-security-group --group-name sg --description \"default\"");
		system("chmod 400 key.pem");
	}
	
	sprintf(command1, "aws ec2 run-instances --image-id am%s --security-groups sg --count 1 --instance-type t1.micro --key-name key --query \'Instances[0].InstanceId\'", inst_id);
	//printf("%s\n", command1);
	
	for(i=0; i< count; i++)
	{
		if (verbose) {printf("%s\n", command1);}
		fp = popen(command1, "r");
		if (fp == NULL)
		{
			printf("Error opening pipe\n");
			exit(1);
		}
		//memset(output, '\0', sizeof(path));
		//printf("1");
		while (fgets(path, sizeof(path)-1, fp) != NULL)
		{
			//printf("2");
			//printf("%s", path);
			strcpy(curr_instance, path);
			//printf("%s", output);
		}
		printf("%s", curr_instance);
		if(i==0)
		{
			strcpy(all_instances, curr_instance);
		}
		else
		{
			//strcat(all_instances, " ");
			strcat(all_instances, curr_instance);
		}
		if (verbose){
			printf("All instance ids: %s", all_instances);
		}
		//strcpy(curr_instance, output);
		//strcpy(output, "");
		//printf("%s", curr_instance);
		// close
		pclose(fp);

		path[0]='\0';
		curr_instance[strlen(curr_instance) - 1] = '\0';

		sprintf(command2, "aws ec2 describe-instances --instance-ids %s --query \'Reservations[0].Instances[0].PublicIpAddress\'", curr_instance);
		if (verbose) {printf("%s\n", command2);}
		fp = popen(command2, "r");
		if (fp == NULL)
		{
			printf("Error opening pipe\n");
			exit(1);
		}
		//memset(output, '\0', sizeof(path));
		//printf("1");
		while (fgets(path, sizeof(path)-1, fp) != NULL)
		{
			//printf("2");
			//printf("%s", path);
			strcpy(ip, path);
			//printf("%s", output);
		}
		if (verbose) {printf("%s", ip);}
		pclose(fp);

		path[0]='\0';
		ip[strlen(ip) - 1] = '\0';

		strcpy(curr_dns, "ec2");
		token = strtok(ip, s);
		while( token != NULL ) 
		{
			strcat(curr_dns, "-");
			strcat(curr_dns, token);
		
			token = strtok(NULL, s);
		}
		strcat(curr_dns, ".compute-1.amazonaws.com");
		if(verbose){printf("%s\n", curr_dns);}
		if(i==0)
		{
			strcpy(all_dns, curr_dns);
			strcpy(addresses[i], curr_dns);
		}
		else
		{
			strcat(all_dns, " ");
			strcat(all_dns, curr_dns);
			strcpy(addresses[i], curr_dns);
		}
	}
	if(verbose){printf("%s\n", all_dns);}

	insts = my_str2vect(all_instances);
	dnss = my_str2vect(all_dns);

	if(verbose){printf("Waiting for instances to start up...\n");}

	sleep(30);

	for(i=0; i<count; i++)
	{
		sprintf(command3, "scp -i key.pem -r %s ubuntu@%s", dir, addresses[i]);
		if (verbose) {printf("Running command: %s\n", command3);}
		fp = popen(command3, "w");
		if (fp == NULL)
		{
			printf("Error opening pipe\n");
			exit(1);
		}
		//memset(output, '\0', sizeof(path));
		//printf("1");
		//sleep(3);
		//fwrite("yes\n", 1, 4, fp);
		pclose(fp);
	}

	//printf("%s", all_instances);
	if (verbose) {printf("Transfer complete.\n");}
	
	return 0;
}
