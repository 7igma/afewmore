Steven Nunes
--You can add your part here--

Bryana Atkinson

Commentary on Program:
	-Our program was written using C. We chose this language because it was the only language that we had experience in using 
	to execute commands programatically. We ended up doing a lot more string parsing and manipulation than we originally 
	thought we woud, which made C very difficult to use. At one point, we considered switching to C++ for better string methods 
	but by that point it was difficult to change things.
	-Both of us were confused on the .ssh/config file, so our program checks for a file called "key.pem" and creates a security group by 
	default called "sg"
	-Our program requires the user to manually type "yes" in order to add each new instance to known-hosts list
	-Our program creates all instances and then goes to sleep for 2 minutes. This is to allow the new instances to start up

Problems We Ran Into:
	-We originally tried to use system() to run commands. However, we needed to be able to store the output of commands within 
	the program. We thought about piping the output to a file and using the program to read the file, but that felt incredible 
	wasteful. We eventually found popen() which could run commands and store the input.
	-As mentioned earlier, our program requires the user to manually type "yes" for each instance before it will send the dir. 
	We thought about changing the ssh/config file so that it doesn't ask permission. However, that felt like too big of a 
	security risk. Even if we switched it back after, a user with malicious intent might be able to take advantage of that
	-As mentioned earlier, our program goes to sleep for 2 minutes to give the new instances time to start up. This felt like a 
	waste of resources, but we couldn't think of a better wway to ensure that we weren't sending before it could be received