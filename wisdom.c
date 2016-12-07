#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *quote_array[1024];
int quote_count = -1;
char quotes[51200] = "";
    
void getQuotes(const char *fn)
{
    FILE *stream = fopen(fn, "r");
    if(!stream)
        return;

    char line[1024] = "";
    
    while (fgets(line, 1024, stream)) {
        strcat(quotes, line);
    }
    fclose(stream);
}

void parseQuotes()
{
    char *token;
    token = strtok(quotes, "\"");
    for( int count = 0; token != NULL; count++ ) {
        if (count%2 == 0)
            quote_array[++quote_count] = token;
        // printf("%s",token); // Every other token is a quote, odd tokens are just a comma, maybe some whitespace and a newline
        token = strtok(NULL, "\"");
    }
}

int GetNewlineCount(const char *s)
{
    int count;
    char *pch = strchr(s, '\n');
    for ( count = 0; pch != NULL; count++ ) {
        pch = strchr(pch+1, '\n');
    }
    return count;
}

const char *newQuote()
{
    // some systems have RAND_MAX=2^32-1 and we have overflow
    // if rand() == RAND_MAX, don't exceed array size by one
    int random = (double)rand() * quote_count / ((double)RAND_MAX+1);
    return quote_array[random];
}
