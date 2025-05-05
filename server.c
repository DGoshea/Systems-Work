/*
 * Name:
 * Course-section: CS440-01
 * Assignment: Simplex server
 * Due Date:
 * Collaborators: None
 * Resources:
 * Description: A simple server that echos all text sent to it.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MAX_LINE    = 256;
const int SERVER_PORT = 5432;
const int MAX_PENDING = 5;

int
main(void)
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    socklen_t new_len;
    int s, new_s;

    /* build address data structure */
    memset(&sin, 0, sizeof sin);
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    /* setup passive open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err(1, "unable to open socket");

    if ((bind(s, (struct sockaddr*)&sin, sizeof sin)) == -1) {
        close(s);
        err(2, "unable to bind socket");
    }

    if ((listen(s, MAX_PENDING)) == -1) {
        close(s);
        err(3, "unable to listen on socket");
    }

    /* wait for a connection, then receive and print message */
    while (1) {
        new_len = sizeof sin;
        if ((new_s = accept(s, (struct sockaddr*)&sin, &new_len)) == -1) {
            close(s);
            err(4, "accept error");
        }

        memset(buf, 0, sizeof buf);
        while (recv(new_s, buf, sizeof buf, 0) > 0) {
            printf("%s", buf);
            memset(buf, 0, sizeof buf);
        }

        close(new_s);
    }

    /* NOT REACHED */
    close(s);
    return 0;
}

