#include <stdio.h>
#include <stdlib.h>
#include "fgetopt.h"

void help();

int main(int argc,char **argv) {
    opts_alias_t options[] = {
        {"-h", "--help"},
        {"-v", "--verbose"},
        {"-d", "--device-name"},
        {"-p", "--port"}
    };

    size_t num_opts = sizeof(options)/sizeof(opts_alias_t);

    OutParam_t          *param;
    char                *device_name = (char *)"Not set name";
    int                 verb = -1, port = -1;

    (void)set_alias_for_options_line(argc, argv, options, num_opts);

    /** Parse arguments */
    for ( ; ; ) {
        param = GetOpt(argc, argv, (char *)"-hv:d:p:");

        if (param->c == -1)
            break;

        switch (param->c) {
        case 'v':
            verb = atoi(param->optarg);
            break;
        case 'h':
            help();
            exit (EXIT_SUCCESS);
        case 'd':
            device_name = param->optarg;
            break;
        case 'p':
            port = atoi(param->optarg);
            break;
        }
    }

    printf("-d device_name = %s\n", device_name);
    printf("-v verb = %d\n", verb);
    printf("-p port = %d\n", port);
}

void help() {
    printf("Program use_fgetopt_alias_c\n");
    printf("Usage: use_fgetopt_alias_c [OPTIONS]\n");
    printf("   -h or --help         help menu (this screen)\n");
    printf("   -v or --verbose      verbose mode on\n");
    printf("   -d or --device-name  device name for Pulsar (default name '/dev/pulsar')\n");
    printf("   -p or --port         set port (default value 2021)\n");
}
