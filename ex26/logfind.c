#define _GNU_SOURCE
#include "dbg.h"
#include "config.h"
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024

int orLogic = 0;

void MatchOcurrence(char* filename, char** words, int wordc);

int main(int argc, char** argv){
    if(argc < 2) {
        printf("Uso: logfind word word ... [-o]\n");

        return 1;
    }

    int wordOffset = 1;

    //check for the optional -o switch
    if(!strcmp(argv[argc-1], "-o")){
        ++wordOffset;
        orLogic = 1;
    }

    //moving argv one spot so we remove the name from it
    ++argv;
    

    glob_t files;
    check_mem(ReadConfig(&files));

    for(int i = 0; i < files.gl_pathc; i++){
        MatchOcurrence(files.gl_pathv[i], argv, argc-wordOffset);
    }

    globfree(&files);

    return 0;


    error:
    globfree(&files);

    return 1;
}

// as parameters sent from the console are all nullterminated :'v
void MatchOcurrence(char* filename, char** words, int wordc){
    debug("searching in file: %s", filename);
    FILE * fp;
    fp = fopen(filename, "r");
    check_mem(fp);

    
    char* line = calloc(MAX_LINE,1);
    check_mem(line);

    unsigned long lineNumber = 0;
    char* found;

    int* wordFound = calloc(wordc,sizeof(int));
    int matches = 0;

    while(fgets(line, MAX_LINE - 1, fp)){
        ++lineNumber;
        for(int i = 0; i < wordc; ++i){
            if((found = strcasestr(line, words[i]))){
                wordFound[i] = 1;
                
                char* start = line;
                int col = 1;
                while(start != found){
                    col++;
                    start++;
                }
                log_info("Found: %s. In: %s. Line: %lu, Col: %d", words[i], filename, lineNumber, col);
                
            }
        }
    }
    
    for(int i = 0; i < wordc; ++i){
        if(wordFound[i]){
            matches++;
        }
    }

    if(orLogic){
        if(matches > 0){
            log_info("Found any ocurrence in file: %s.", filename);
        }
    } else {
        if(matches == wordc){
            log_info("Found all ocurrences in file: %s.", filename);
        }
    }

    free(line);
    fclose(fp);

    return;

    error:
    if(line) free(line);
    if(fp) fclose(fp);
}