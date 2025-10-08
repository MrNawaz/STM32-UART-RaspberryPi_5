#include<stdio.h>
#include<fcntl.h>
#include<termios.h>
#include<unistd.h>

int main(void)
{
	int serial_port = open("/dev/ttyUSB0", O_RDWR);

	if(serial_port < 0)
	{
		perror("open");
		return 1;
	}

	struct termios tty;
	tcgetattr(serial_port, &tty);

	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS);
	tty.c_iflag = tty.c_oflag = tty.c_lflag = 0;

	tcsetattr(serial_port, TCSANOW, &tty);

	printf("Listening on /dev/ttyUSB0....\n");

	char buf[100];
	while(1){
		int n = read(serial_port, buf, sizeof(buf)-1);
		if(n > 0){
			buf[n] = '\0';
			printf("%s", buf);
			fflush(stdout);
		}
	}
}


