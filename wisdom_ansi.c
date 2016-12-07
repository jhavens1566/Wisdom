/* ANSI/POSIX command line version */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getQuotes(const char *fn);
void parseQuotes();
int GetNewlineCount(const char *s);
const char *newQuote();

int main(int argc, char *argv[])
{
    srand(time(0)); //randomize the randomizer with not so random current time
    rand(); //throw away first rand, for some reason the first is always about the same
    getQuotes("THEMETER"); //populate the quote_array and set quote_count
    getQuotes("QUOTES"); //populate the quote_array and set quote_count
    getQuotes("/usr/lib/Wisdom/THEMETER"); //populate the quote_array and set quote_count
    // printf("END METER %d %s\n", quote_count, quote_array[30]);
    getQuotes("/usr/lib/Wisdom/QUOTES"); //populate the quote_array and set quote_count
    // printf("END QUOTES %d %s\n", quote_count, quote_array[100]);
    parseQuotes();
    const char *q = newQuote();
    if(!q)
    {
        puts("nothing to report - no wisdom today!\n");
        return 1;
    }
    puts(q);
    return 0;
}
