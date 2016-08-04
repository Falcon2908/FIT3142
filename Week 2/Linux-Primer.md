# Linux Primer

## Help

1. Which text based command provides information on the use of other Linux commands and utilities? List at least two.
    * `man`
    * `apropos`

2. List the command-line for finding help on the usage of 'ssh'
    * `man ssh`

3. How do you access the linux manual pages? List the full command line for accessing a particular section?
    * `man 1 printf`

4. Where would you generally look for help on the web? List 3 major sites.
    * [Stackoverflow](http://stackoverflow.com/)
    * [Linux Command](http://linuxcommand.org/)
    * [Ubuntu Help](https://help.ubuntu.com/)

## File and Directory Manipulation

5. List the command-lines for creating and deleting sub-directories
    * `mkdir [path]`
    * `rmdir -r [path]`

6. List the command-line for creating a zzero length file
    * `touch [filename]`

## Users and Access Control

7. Create a user account for yourself and assign it to a unique group. List the command-line
    * `useradd vgoe4`
    * `useradd -G monash vgoe4`

8. Set the permissions for your home directory such that no one besides yourself can read your home directory’s contents. List the command line.
    * `chmod 400 ~/`

9. What does `chmod 4775 [filename]` do?
    * It sets the file to run with the users's permissions (SUID bit is set) such that if anyone else accesses the file they can run with the user's permission set by 755 which is fll permission to owner, rw permission to group and others.
    * It is so that the file can be executes as root even though the user is not root.

10. How do you set the executable permission on a file? List the command line.
    * `chmod ugo+x [filename]` makes everyone be able to execute the file

11. List the command-line for inspecting the permissions assigned to a file.
    * `ls -l [filename]`

12. List the command line for inspecting the permissions assigned to a directory.
    * `ls -l [directory path]`

## Linux Shell

13. What is your default Linux shell? Read the manual pages on your shell and then answer the following questions.
    * bash

14. How do you get the last command-line re-displayed?
    * `history 2 | head -n1`

15. Which key-stroke invokes filename completion?
    * `tab`

16. Which file in your home directory contains the PATH variable, what does it do, and how do you inspect its value?
    * `~/.bashrc`
    * PATH varibale stores the location of binaries and scripts that can be executed without providing the complete location of the executable.
    * `echo $PATH`

17. What does the shell function ‘alias’ do? Add an alias to your shell configuration file and test that it works. List the command-lines.
    * alias assigns a command to another command in bash. 
    * `echo alias g=\'git\' >> ~/.bashrc`
    * `g` shows git commands

18. How does ‘which’ command work? List a command-line demonstrating its function.
    * which shows the location of an executable in the path
    * `which bash` shows `/bin/bash`

19. How do you execute a program file in the shell? List the command-line.
    * `[path-to-file]` eg `/bin/bash`
    * Type the command if in path

20. Why it’s sometime necessary to prefix `./` to run an executable file?
    * if the `./` is not included it will search for the program in the path.

21. How are the contents of a text file displayed? List the command-line.
    * `less [filename]`

22. List the command-line for search all files with an extension ‘.html’ on the system. 
    * `find / -type f -name "*.html"`

23. Create a simple shell script for listing the contents of your directory and make it executable. List the script and the command-line for changing it into an executable file.
    * `touch ./list.sh`
    * `echo #!/bin/bash > ./list.sh`
    * `echo ls >> ./list.sh`
    * `chmod +x ./list.sh`

##Networking

24. Using ‘ifconfig’ list the following networking parameters for ‘eth0’:
    * IP Address: 192.168.109.130
    * Hardware Address: 00:0c:29:81:ed:6f
    * Netmask: 255.255.255.0

25. What is the function of ‘/etc/hosts’ file?
    * it is an address book to check the IP address of a particular domain which can be used to overwrite DNS setting and block certain IP addresses

26. What is the function of ‘/etc/resolv.conf’?
    * resolv.conf stores the nameservers for looking up hosts and IP addresses. If it is not found in the locak hosts file.

27. Using ‘netstat’ display the routing table in the numeric format. List the command line and default route. 
    * `netstat -r`

## Programming Tools

1. Confirm the following programming utilities are available:
    * It exists