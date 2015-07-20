#include <sys/ioctl.h>
#include <errno.h>                                                              
#include <string.h>                                                             
#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <unistd.h>                                                             
#include <fcntl.h>                                                              
#include <time.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

int main ()
{
	int ln;
	char buf[2]={0x0,0x0};
	int file;
	
	struct i2c_msg msg[2];
		
	struct i2c_ioctl_rdwr_data {
	
	 		struct i2c_msg *msgs;  
	    	int nmsgs;           
	} msgst;

	file = open("/dev/i2c-0", O_RDWR);
	if (file < 0) {
		printf("Error open /dev/i2c-0\n");
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, 0x50) < 0) {
		printf("ERROR I2C_SLAVE\n");
		exit(1);
	}

	msg[0].addr = 0x50;
	msg[0].flags = 0;
	msg[0].len = 2;
	msg[0].buf = 0x00;
	
	
	msg[1].addr = 0x50;
	msg[1].flags = 1;
	msg[1].len = 1;
	msg[1].buf = buf;

	msgst.msgs = msg;
	msgst.nmsgs = 2;
	
	ioctl(file, I2C_RDWR, &msgst);
	printf("BUFF:%d, %d\n", buf[0], buf[1]);

	return 0;
}
