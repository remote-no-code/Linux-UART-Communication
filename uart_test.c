#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/select.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <serial_port>\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        perror("Error opening serial port");
        return 1;
    }
    fcntl(fd, F_SETFL, 0); 


    struct termios tty;
    tcgetattr(fd, &tty);
    
    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    tty.c_cflag &= ~PARENB; 
    tty.c_cflag &= ~CSTOPB; 
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;     
    tty.c_cflag &= ~CRTSCTS; 
    tty.c_cflag |= CREAD | CLOCAL; 

    // Make it raw mode
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    tty.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &tty);

    
    char *msg = "LFX Mentorship Test!\r\n";
    write(fd, msg, strlen(msg));
    printf("Sent: %s", msg);

    fd_set read_fds;
    struct timeval timeout;
    char buffer[256];

    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);
    timeout.tv_sec = 2; 
    timeout.tv_usec = 0;

    printf("Waiting for response...\n");
    int result = select(fd + 1, &read_fds, NULL, NULL, &timeout);

    if (result > 0 && FD_ISSET(fd, &read_fds)) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            printf("Received: %s\n", buffer);
        }
    } else {
        printf("Timeout! No data received.\n");
    }

    close(fd);
    return 0;
}
