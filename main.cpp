#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <getopt.h>

#include "common.h"
#include "parse.h"
#include "ir.h"

static struct option long_options[] = {
  {"trace", no_argument,  &g_trace, 1},
  {"out", required_argument, NULL, 'o'},
  {"help", no_argument, NULL, 'h'}
};

typedef struct {
  char* infile;
} args_t;

args_t parse_args(int argc, char* argv[]) {
  int opt;
  args_t args = {0};
  optind = 0;
  while ((opt = getopt_long_only(argc, argv, ":h", long_options, NULL)) != -1) {
    switch(opt) {
      case 0: break;
      case 'h':
      default:
        ERR("Usage: %s input-file\n", argv[0]);
        exit(opt != 'h');
    }
  }

  if ( ((optind + 1) != argc)) {
    ERR("Executable takes one positional argument \"filename\"\n");
    exit(1);
  }

  args.infile = strdup(argv[optind]);
  return args;
}

void free_args (args_t args) {
  free(args.infile);
}


// Main function.
// Parses arguments and either runs a file with arguments.
//  -trace: enable tracing to stderr
int main(int argc, char *argv[]) {
  args_t args = parse_args(argc, argv);
    
  byte* start = NULL;
  byte* end = NULL;

  ssize_t r = load_file(args.infile, &start, &end);
  if (r < 0) {
    ERR("failed to load: %s\n", args.infile);
    return 1;
  }

  TRACE("loaded %s: %ld bytes\n", args.infile, r);
  WasmModule module = parse_bytecode(start, end);
  unload_file(&start, &end);
  
  /* Interpreter here */
  /* */

  free_args(args);

  return 0;
}




