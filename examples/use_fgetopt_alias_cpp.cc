#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fgetopt.h>

using std::cout;
using std::endl;

void help();

int main(int argc,char **argv) {
    opts_alias_t options[] = {
        {"-h", "--help"},
        {"-v", "--verbose"},
        {"-d", "--device-name"},
        {"-p", "--port"}
    };
    
    size_t num_opts = sizeof(options)/sizeof(opts_alias_t);
    
    GETOPT              obj_getopt(argc, argv, options, num_opts);
    OutParam_t          *param;
    char                *device_name = (char *)"Not set name";
    int                 verb = -1, port = -1;

	/** Parse arguments */
	for ( ; ; ) {
		    param = obj_getopt.GetOpt(argc, argv, (char *)"-hv:d:p:");
 
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

      cout << "-d device_name = " << device_name << endl;
      cout << "-v verb = " << verb << endl;
      cout << "-p port = " << port << endl;
}

void help()
{
    cout << "Program recv_msod" << endl;
    cout << "Usage: recv_msod [OPTIONS]" << endl;
    cout << "   -h     help menu (this screen)" << endl;
    cout << "   -v     verbose mode on" << endl;
    cout << "   -d     device name for Pulsar (default name '/dev/pulsar')" << endl;
    cout << "   -p     set port (default value 2021)" << endl;
}
