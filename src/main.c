//-----=[ascii-converter]----/o/--->
//
// Command-line utitity for ascii-coversions. 
// Supports: ascii - decimal
// 	     decimal - ascii 
// 	     ascii - hex
// 	     hex - ascii
//
// INPUT:    user supplied string 
// 	     user supplied file
//
// Options: -a (convert ascii to decimal)
// 	    -d (convert decimal to ascii)
// 	    -x (use hex instead of decimal)
//
// 	    -f (Use a file for input)
// 	    [Defualt is a supplied command-line string]
//
// Default Usage: ascii-convert "this-string" 
// 		  -- coverts string to decimal values
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
struct options_flags { 
	int a2d;
	int d2a;
	int hex;
	int file;
};

//Function Prototypes
void dump_opts_struct(struct options_flags* opts);
void inital_opts_struct(struct options_flags* opts); 
int process_args(struct options_flags*, int argc, char *argv[]); 
char *get_file_name(int argc, char *argv[]); 
int check_file(char *filename); 

int main(int argc, char *argv[]) { 
	struct options_flags opts; 
	char *filename; 

	inital_opts_struct(&opts);
	process_args(&opts, argc, argv); 

	dump_opts_struct(&opts); 

	if(opts.file) {
		// alloc filename in func
		filename = get_file_name(argc, argv); 
		printf("in main()| filename: \'%s\'\n", filename); 
	}


}; 

// Function Definitons 
// ========================================================[*]
// Argument Processing Functions
// --------------------------------->
//
// [DEBUG] Function
void dump_opts_struct(struct options_flags *opts) {
	printf("\n");
	printf("a2d @ (%p): %d\n", &opts->a2d, opts->a2d); 
	printf("d2a @ (%p); %d\n", &opts->d2a, opts->d2a);
	printf("hex @ (%p): %d\n", &opts->hex, opts->hex); 
	printf("file@ (%p): %d\n", &opts->file, opts->file); 
}

void inital_opts_struct(struct options_flags *opts) {
        opts->a2d=0;
	opts->d2a=0;
	opts->hex=0; 
	opts->file=0; 
}

// Process the command line arguments and build options struct.  
int process_args(struct options_flags* opts, int argc, char *argv[]) {
	char *arg_ptr; 
	char first_char; 
	char secon_char;

	// Loop through arg list and find options.
	for(int i=1; i < argc; i++) {
		arg_ptr = argv[i]; 
		first_char = arg_ptr[0]; 
		secon_char = arg_ptr[1]; 

		if(first_char == '-') { 
			// Check if argument has been used already.
			if(opts->a2d == 1 || opts->d2a == 1)
				if(secon_char == 'a' || secon_char == 'd')
					continue;

			switch (secon_char)
			{
				case 'a': opts->a2d=1;
					  break;
			        case 'd': opts->d2a=1; 
					  break;
			 	case 'x': opts->hex=1; 
					  break;
				case 'f': opts->file=1;
					  break;
			}
	
		}

	}
	
}
//------------------------------------------------------------------------o
//Implemnt Functions
char *get_file_name(int argc, char *argv[]) {
	char *arg_ptr;
	char fir_char;
	char sec_char;

#define MAX_FNAME 128

	char *fname_ptr; 
	fname_ptr = (char *) malloc(MAX_FNAME);

	for(int i=0; i < argc; i++) { 
		arg_ptr = argv[i];
		fir_char = arg_ptr[0];

		if(fir_char == '-') {
			sec_char = arg_ptr[1];
			if(sec_char == 'f') {
				// Get Next Argv and store as filename.
				arg_ptr = argv[(i+1)]; 
				strcpy(fname_ptr, arg_ptr); 

				return fname_ptr;
			}
		}
	}
}

// Checks for valid file and opens file for reading. 
int check_file(char *filename) {
	int fh; // File Handle

	fh = open(filename, O_RDONLY); 
	if(fh == -1) {
		printf("[ERROR] Opening File | may not exist\n"); 
		exit(-1);
	}

	return fh; 
};



