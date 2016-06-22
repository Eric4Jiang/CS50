/* strrchr example */
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef char BYTE;
void parse(const char* line, char* abs_path, char* query) {
    char* firstSpace = strchr(line, ' ');
    char* lastSpace = strrchr(line, ' ');
    char* CRLF = strrchr(line, '\r');
    if(firstSpace == NULL || lastSpace == NULL || CRLF == NULL) {
        printf("400");
        return;
    }
    char method[4];
    strncpy(method, line, 3);
    //if method is not GET, 405 bad request
    if(strncasecmp(method, "GET", 3) != 0) {
        printf("405");
        return;
    }

    int requestTargetLength = (int)(strlen(firstSpace) - strlen(lastSpace)) - 1; //-1 to not include the first space
    char requestTarget[requestTargetLength + 1];
    requestTarget[requestTargetLength] = '\0';
    strncpy(requestTarget, firstSpace + 1, requestTargetLength);
    //if request-target does not begin with /, respond to the browser with 501 Not Implemented and return false;
    if(requestTarget[0] != '/') {
        printf("501");
        return;
    }

    int httpVersionLength = (int)(strlen(lastSpace) - strlen(CRLF) - 1);
    printf("Http version length %i\n", httpVersionLength);
    char httpVersion[httpVersionLength + 1];
    httpVersion[httpVersionLength] = '\0';
    strncpy(httpVersion, lastSpace + 1, httpVersionLength);

    //if request-target contains a ", respond to the browser with 400 Bad Request and return false;
    char* quotePosition = strchr(requestTarget, '\"');
    if(quotePosition != NULL) {
        printf("400");
        return;
    }
    //if HTTP-version is not HTTP/1.1, respond to the browser with 505 HTTP Version Not Supported and return false;
    if(strncasecmp(httpVersion, "HTTP/1.1", 8) != 0) {
        printf("HttpVersion - %s\n", httpVersion);
        printf("505");
        return;
    }

    //if all cases are checked, store values into query and abs_path
    char* questionMark = strchr(line, '?'); // string of words after ? (including)

    // if no query
    if(questionMark == NULL) {
        strcpy(abs_path, requestTarget);
        strcpy(query, "");
    }
    else {
        //store everything to the left of questionMArk into absPath
        int absPathLength = (int) (strlen(requestTarget) - strlen(questionMark));
        strncpy(abs_path, requestTarget, absPathLength);
        abs_path[strlen(abs_path)] = '\0';
        //store everything to right of question mark in query
        if ((questionMark + 1) != NULL) {
            int queryLength =
            query[strlen(query)] = '\0';
            strcpy(query, questionMark + 1);  // +1 does not include ?
            //query[strlen(query)] = '\0';
        }
        else {
            strcpy(query, ""); // if there is nothing after ? --> "/index.html?"
            //query[strlen(query)] = '\0';
        }
    }

    printf("Method - %s\n", method);
    printf("Request Target - %s\n", requestTarget);
    printf("HttpVersion - %s\n", httpVersion);
}

int main ()
{
   parse("GET /index.php HTTP/1.1\r\n");
}