#include "config.h"
#include "dbg.h"

int globerr(const char *path, int eerrno){
    fprintf(stderr, "%s: %s\n", path, strerror(errno));
    return 0;
}

int ReadConfig(glob_t* results) {

    FILE * fp;
    char line[MAX_FILE_NAME_LENGTH];
    int flags = 0;
    int ret;
    int call = 0;

    fp = fopen("logfind.ini", "r");
    check_mem(fp);

    while(fgets(line, sizeof(line), fp)){
        char c = 1;
        for(int i = 0;c;++i){
            c=line[i];

            if (c == '\n') {
                line[i] = '\0';
                break;
            }
        }

        debug("line at the config: '%s'",line);

        flags |= (call > 0 ? GLOB_APPEND : 0);
        ret = glob(line, flags, globerr, results);
        if(ret){
            fprintf(stderr, "problem with %s (%s), stopping early\n",
				line,
		/* ugly: */	(ret == GLOB_ABORTED ? "filesystem problem" :
				 ret == GLOB_NOMATCH ? "no match of pattern" :
				 ret == GLOB_NOSPACE ? "no dynamic memory" :
				 "unknown problem"));
			break;
        }

        call++;
    }

    fclose(fp);
    return 1;

    error: 
    if(fp) fclose(fp);

    return 0;
}