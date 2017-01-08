#include <stdio.h>
#include <stdlib.h>
#include <fgetopt.h>

void help();

int main(int argc,char **argv) {
    OutParam_t          *param;
    //VarParam_t          vparam;
    char                *device_name = (char *)"Not set name";
    int                 verb = -1, port = -1;

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

void help()
{
    printf("Program recv_msod\n");
    printf("Usage: recv_msod [OPTIONS]\n");
    printf("   -h     help menu (this screen)\n");
    printf("   -v     verbose mode on\n");
    printf("   -d     device name for Pulsar (default name '/dev/pulsar')\n");
    printf("   -p     set port (default value 2021)\n");
}
