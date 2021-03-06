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
#include "segment.h"


int main()
{

	char 
		c,
		*mychar = &c;
	int 
		myexit,
		shmid;
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
	c = '0'; /* Initialise mychar*/
	while(c == '0')
	{
		mydata = (SEG_DATA *)shm;
		fprintf(stdout, "\nSTATUS DUMP\n");
		fprintf(stdout, "RPM              = %d\n", mydata->rpm );
		fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
		fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
		fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
		fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
		fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
		fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
		fprintf(stdout, "Enter Command (1 to exit, 0 to continue): ");
		fscanf(stdin, "%[^\n]%*c", mychar);
	}
	if(c == '1')
	{
		mydata->exit = 1; /*Setting Exit Status*/
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
