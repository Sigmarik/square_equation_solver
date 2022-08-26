#include "argparser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void parse_args(const int argc, const char** argv, const int action_c, const struct ActionTag* actions) {
    for (int arg_id = 1; arg_id < argc; arg_id++) {
        const char* arg = argv[arg_id];

        if (arg[0] != '-' || strlen(arg) < 2)
            continue;
        
        for (int tag_id = 0; tag_id < action_c; tag_id++) {
            if (!(arg[1] == actions[tag_id].name.short_name || 
                (arg[1] == '-' && strcmp(arg + 2, actions[tag_id].name.long_name) == 0))) continue;
            //                                  ^ number of chars in "--"
            const GenericFunctionCall* call = &actions[tag_id].action;
            if (call->function)
                call->function(call->parameters_length, 
                call->parameters, arg + 2);
        }  //   number of chars in "--" ^

        if (strcmp(arg, "--help") == 0 || strcmp(arg, "-help") == 0 || strcmp(arg, "-h") == 0 || strcmp(arg, "-H") == 0) {
            printf("Valid tags:\n\n");
            printf("-H -h -help --help - prints this message.\n\n");
            for (int tag_id = 0; tag_id < action_c; tag_id++) {
                printf("-%c --%s - %s\n\n", actions[tag_id].name.short_name, actions[tag_id].name.long_name, 
                                               actions[tag_id].description);
            }
            // Any program should stop when user only wants to know its options.
            exit(EXIT_SUCCESS);
        }
    }
}

void edit_int(const int argc, void** argv, const char* argument) {
    *(int*)argv[0] = 0;
    *(int*)argv[0] = atoi(argument);
}