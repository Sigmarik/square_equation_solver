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
            if (!(arg[1] == actions[tag_id].short_name || 
                (arg[1] == '-' && !strcmp(arg + 2, actions[tag_id].long_name)))) continue;
            if (actions[tag_id].action)
                actions[tag_id].action(actions[tag_id].arg_count, actions[tag_id].parameters, arg + 2);
        }

        if (!strcmp(arg, "--help") || !strcmp(arg, "-help") || !strcmp(arg, "help")) {
            printf("Valid tags:\n\n");
            for (int tag_id = 0; tag_id < action_c; tag_id++) {
                printf("-%c or --%s - %s\n\n", actions[tag_id].short_name, actions[tag_id].long_name, actions[tag_id].description);
            }
            // Any program should stop when user only wants to know its options.
            exit(EXIT_SUCCESS);
        }
    }
}