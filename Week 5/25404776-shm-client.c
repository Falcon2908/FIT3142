/*
 * Shared Memory Client Process as per D.A. Curry `Using C on the Unix System'
 * shm-clinet-test.c
 * Author: C. Kopp
 * (c) 2004, Monash University, SCCSE
 *
 * $Id: MyID-client-template.c,v 1.2 2015/08/17 06:53:03 carlo Exp carlo $
 *
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "segment.h"


int main()
{
	char
		buf[10], 
		c,
		*mychar = &c;
	int 
		/*myexit,*/
		shmid,
		clientid;
	key_t 
		mykey;
	void *
    	shmat(int shmid, const void *addr, int flag);
	int 
		shmdt(const void *shmaddr);
	SEG_DATA
		*shm, *mydata;


	/*
	 * The shared memory segment is identified by SEGMENTID
	 */
	mykey = SEGMENTID;

	/*
	 * here we create the shared memory segment using the `shmget' system call.
	 */
	if( (shmid = shmget( mykey, sizeof(SEG_DATA), IPC_CREAT | 0666)) < 0 )
	{
		perror("shmget: cannot create shared memory segment; exiting now");
		exit(1);
	}

	/*
	 * We must now map the segment into our process address space using the
	 * `shmat' [attach] system call.
	 */
	if( (shm = (SEG_DATA *)shmat( shmid, NULL, 0)) == ((SEG_DATA *)-1) )
	{
		perror("shmat: cannot attach shared memory segment; exiting now");
		exit(1);
	}

	/*
	 * Test Code - read from segment
	 */
	mydata = (SEG_DATA *)shm;

	if(mydata -> present == (CLIENT_1 + CLIENT_2 + CLIENT_3 + CLIENT_4))
	{
		fprintf(stdout, "Maximum Number of Clients reached");
		exit(1);
	}
	clientid = 0;
	switch(mydata -> present)
	{
		case 0:
		case 2:
		case 4:
		case 6:
		case 8:
		case 10:
		case 12:
		case 14:	
			clientid = CLIENT_1;
			break;
		case 1:
		case 5:
		case 9:
		case 13:
			clientid = CLIENT_2;
			break;
		case 3:
		case 11:
			clientid = CLIENT_3;
			break;
		case 7:
			clientid = CLIENT_4;
			break;
	}

	while(mydata -> mylock == 1)
	{
		sleep(1);
	}

	if(mydata->mylock == 0)
	{
		mydata->mylock = 1;
		mydata->present = mydata->present + clientid;
		mydata->mylock = 0;
	}

	c = '0'; /* Initialise mychar*/
	while(c == '0')
	{
		fprintf(stdout, "\nSTATUS DUMP\n");
		fprintf(stdout, "Client           = %d\n", clientid);
		fprintf(stdout, "RPM              = %d\n", mydata->rpm );
		fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
		fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
		fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
		fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
		fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
		fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
		fprintf(stdout, "Enter Command (1 to exit, 0 to continue): ");
		fscanf(stdin, "%s", buf);
		*mychar = buf[0];
	}

	if(c == '1')
	{
		while(mydata->mylock == 1)
		{
			sleep(1);
		}

		if(mydata->mylock == 0)
		{
			mydata->mylock = 1;
			mydata->present = mydata->present - clientid; /*Subtracting Client*/
			mydata->exit = 1; /*Setting Exit Status*/
			mydata-> mylock = 0;
		}
	}
	/*
	 * We must now unmap the segment into our process address space using the
	 * `shmdt' [detach] system call.
	 */
	if( (shmid = shmdt( shm )) == (-1) )
	{
	perror("shmdt: cannot detach shared memory segment; exiting now");
	exit(1);
	}

	fprintf(stdout, "Task completed\n");
	exit(0);
	
}