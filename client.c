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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int SERVER_PORT = 5432;
const int MAX_LINE    = 256;

int
main(int argc, char* argv[])
{
    char buf[MAX_LINE];
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    int s;
    size_t len;

    if (argc == 2)
        host = argv[1];
    else {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    /* translate the hostname into an IP address */
    hp = gethostbyname(host);
    if (!hp)
        errx(1, "unknown host %s", host);

    /* build address data structure */
    memset(&sin, 0, sizeof sin);
    sin.sin_family = AF_INET;
    memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        err(2, "unable to open socket");

    if ((connect(s, (struct sockaddr*)&sin, sizeof sin)) == -1) {
        close(s);
        err(3, "connect failed");
    }

    /* main loop, get text from stdin and send over the network */
    memset(buf, 0, sizeof buf);
    while (fgets(buf, sizeof buf, stdin)) {
        len = strnlen(buf, sizeof buf);
        send(s, buf, len, 0);
        memset(buf, 0, sizeof buf);
    }

    /* NOT REACHED */
    close(s);
    return 0;
}

