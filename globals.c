/*=================================================================*/
/*=   globals.c                                                   =*/
/*=   global routines for treekin                                 =*/
/*=   ---------------------------------------------------------   =*/
/*=   Last changed Time-stamp: <2006-11-25 17:19:02 mtw>          =*/
/*=   $Id: globals.c,v 1.16 2006/11/27 13:48:34 mtw Exp $        =*/
/*=   ---------------------------------------------------------   =*/
/*=                 (c) Michael Thomas Wolfinger                  =*/
/*=                      mtw@tbi.univie.ac.at                     =*/
/*=                             treekin                           =*/
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include <getopt.h>

#include "globals.h"
#include "treekin_cmdline.h"

static void ini_globs(void);
static void set_parameters(void);
static void display_settings(void);
static void to_basename(char *arg);

static struct gengetopt_args_info args_info;

/*==============================*/
void
parse_commandline(int argc, char **argv)
{
  ini_globs();
  if (cmdline_parser (argc, argv, &args_info) != 0) {
    fprintf(stderr, "error while parsing command-line options\n");
    exit(EXIT_FAILURE);
  }

  //input file:
  if (args_info.inputs_num) {
    char *infile=NULL;
    to_basename(args_info.inputs[0]);
    infile = (char *)calloc(strlen(opt.basename)+5, sizeof(char));
    strncpy(infile, opt.basename, strlen(opt.basename));
    if (opt.method == 'F') strcat(infile, ".sub");
    else strcat(infile, ".bar");
    opt.INFILE = fopen(infile, "r");
    if (opt.INFILE == NULL) {
      fprintf(stderr, "Error opening input file \"%s\".\n", infile);
      free(infile);
      exit(EXIT_FAILURE);
    }
    free(infile);
  } else {
    opt.INFILE = stdin;
  }

  // rate file?
  if (args_info.ratesfile_given) {
    opt.RATFILE = fopen(args_info.ratesfile_arg, "r");
    if (opt.RATFILE == NULL) {
      if (!opt.quiet) fprintf(stderr, "Cannot open rate file %s!\n", args_info.ratesfile_arg);
    }
  } else {
    opt.RATFILE = NULL;
  }

  set_parameters();
}

void free_gengetopt()
{
  cmdline_parser_free(&args_info);
}

/*==============================*/
static void
to_basename(char *arg)
{
  int len;
  char *s=NULL, *t=NULL;

  s = strdup(arg);
  len = strlen(s);
  t = rindex(s, '/');
  if (t != NULL) memmove(s, t+1, (len-(t-s))*sizeof(char));
  t = NULL;
  t = index(s, '.');
  if (t != NULL) *t = '\0';
  opt.basename = strdup(s);
  free(s);
}

/*==============================*/
static void
set_parameters(void)
{
  if(strncmp(args_info.method_arg, "F", 1)==0)
    opt.method = 'F';
  else if (strncmp(args_info.method_arg, "A", 1)==0)
    opt.method = 'A';

  if(strncmp(args_info.num_err_arg, "I", 1)==0)
    opt.num_err = 'I';
  else if (strncmp(args_info.num_err_arg, "R", 1)==0)
    opt.num_err = 'R';

  opt.FEPS = args_info.feps_arg;
  // determines double precision machine parameters
  extern double dlamch_(char *cmach);
  if (opt.FEPS<0.0) opt.FEPS = 2*dlamch_("S");

  opt.useplusI = args_info.useplusI_flag;

  if (args_info.fptfile_given) {
    opt.fpt_file = strdup(args_info.fptfile_arg);
  } else opt.fpt_file = NULL;

  if (args_info.equil_file_given) {
    opt.equil_file = args_info.equil_file_arg;
  } else opt.equil_file = NULL;

  if (args_info.p0_given) {
    int i, j=1, lmintmp;
    double poptmp = 0., probtmp = 0., *pinitmp=NULL;
    pinitmp = (double *)calloc(2*args_info.p0_given+1, sizeof(double));
    *pinitmp = 1;
    for (i=0; i<args_info.p0_given; i++,j+=2) {
      if (sscanf(args_info.p0_arg[i], "%d=%lg",&lmintmp, &poptmp) == 0)
        exit(EXIT_FAILURE);
      if(lmintmp <1) {
        fprintf(stderr, "States in --p0 must be >=1\n");
        exit (EXIT_FAILURE);
      }
      else if (poptmp >0. && poptmp < 1.01) {
        *(pinitmp + j)     = (double) lmintmp;
        *(pinitmp + j + 1) = poptmp;
        *pinitmp += 2;
      }
    }

    for (i = 2; i < *pinitmp; i +=2)
      probtmp += pinitmp[i];
    if (probtmp <= 0.99 || probtmp >= 1.01) {
      fprintf(stderr, "Values of --p0 must sum up to 1 (currently %5.2f)\n",
              probtmp);
      /* normalize input */
      for (i = 2; i < *pinitmp; i +=2)
        pinitmp[i] /= probtmp;

      probtmp = 0.0;
      for (i = 2; i < *pinitmp; i +=2)
        probtmp += pinitmp[i];
      if (!opt.quiet) fprintf(stderr, "WARNING:  --p0 values normalized sum up to %5.2f\n",
              probtmp);
    }
    opt.pini = pinitmp;
  } else opt.pini = NULL;

  if (args_info.absorb_given) {
    if( (opt.real_abs = opt.absrb = args_info.absorb_arg) <= 0 ) {
      fprintf(stderr, "Value of --absorb must be >= 0\n");
      exit (EXIT_FAILURE);
    }
  }

  if( (opt.t0 = args_info.t0_arg) < 0.0 ) {
    fprintf(stderr, "Value of --t0 must be >= 0.\n");
    exit (EXIT_FAILURE);
  }

  if( (opt.t8 = args_info.t8_arg) <= 0.0 ) {
    fprintf(stderr, "Value of --t8 must be > 0.\n");
    exit (EXIT_FAILURE);
  }

  if (args_info.tinc_given) {
    if( (opt.tinc = args_info.tinc_arg) <= 0. ) {
      fprintf(stderr, "Value of --tinc must be > 0.\n");
      exit (EXIT_FAILURE);
    }
  }

  if (args_info.Temp_given) {
    if( (opt.T = args_info.Temp_arg) < -273.15 ) {
      fprintf(stderr, "Value of --Temp must be > -273.15\n");
      exit (EXIT_FAILURE);
    }
  }
  if (args_info.visualize_given) {
    opt.vis_file = args_info.visualize_arg;
  }

  // use input as rate matrix if rate matrix is not specified
  if (!args_info.ratesfile_given && opt.method=='I') {
    if (!opt.quiet) fprintf(stderr, "Using input as a rate file!\n");
    opt.RATFILE = opt.INFILE;
    opt.INFILE = NULL;
  }

  if (args_info.minimal_rate_given) {
    if( (opt.minimal_rate = args_info.minimal_rate_arg) <= 0. ) {
      fprintf(stderr, "Value of --minimal-rate must be > 0.\n");
      exit (EXIT_FAILURE);
    }
  }

  if (args_info.hard_rescale_given) {
    if( (opt.hard_rescale = args_info.hard_rescale_arg) <= 0. ) {
      fprintf(stderr, "Value of --hard-rescale must be > 0.\n");
      exit (EXIT_FAILURE);
    }
  }

  if (args_info.times_given) {
    if( (opt.times = args_info.times_arg) <= 0. ) {
      fprintf(stderr, "Value of --times must be > 0.\n");
      exit (EXIT_FAILURE);
    }
  }

  if (args_info.nstates_given) {
    if( (opt.n = args_info.nstates_arg) <= 1 ) {
      fprintf(stderr, "Value of --nstates must be >= 1\n");
      exit (EXIT_FAILURE);
    }
  } else {
    // set opt.n to infinity
    opt.n = INT_MAX;
  }
  if (args_info.just_shorten_flag) {
    opt.just_sh = 1;
  }
  opt.max_decrease = args_info.max_decrease_arg;
  if (args_info.degeneracy_given) opt.want_degenerate = 1;
  if (args_info.quiet_flag) opt.quiet = 1;
  if (args_info.verbose_given) opt.want_verbose = 1;
  if (args_info.umatrix_given) opt.dumpU = 1;
  if (args_info.mathematicamatrix_given) opt.dumpMathematica = 1;
  if (args_info.bin_given) opt.binrates = 1;
  if (args_info.warnings_flag) opt.warnings = 1;
  if (args_info.exponent_given) opt.matexp = 1;
  if (args_info.fpt_given) {
    opt.fpt = 1;
    if (strcmp(args_info.fpt_arg, "all") == 0) {
      opt.fpt_num = -1;
    } else {
      if (sscanf(args_info.fpt_arg, "%d", &opt.fpt_num) != 1 || opt.fpt_num<=0) {
        fprintf(stderr, "Value of --fpt (-t) must be either \"all\" or positive number. (it is \"%s\")\n", args_info.fpt_arg);
        exit (EXIT_FAILURE);
      }
    }
  }
  if (args_info.recover_given) opt.rrecover = 1;
  if (args_info.wrecover_given) opt.wrecover = 1;
  if (args_info.info_given) {
    display_settings();
    if (opt.pini != NULL) free(opt.pini);
    exit(EXIT_SUCCESS);
  }
  if (opt.rrecover && opt.wrecover) {
    opt.wrecover = 0;
    if (!opt.quiet) fprintf(stderr, "WARNING: both options -w and -r were given\n");
    if (!opt.quiet) fprintf(stderr, "         disabling -w now, since they are mutually exclusive !\n");
  }
}

/*==============================*/
static void
ini_globs(void)
{
  opt.absrb           =          0;
  opt.real_abs        =          0;
  opt.T               =         37.;
  opt.t0              =         TZERO;
  opt.t8              = 1000000000.;
  opt.want_degenerate =          0;
  opt.tinc            =          1.02;
  opt.method          =          'I';
  opt.dumpU           =          0;
  opt.dumpMathematica =          0;
  opt.matexp          =          0;
  opt.binrates        =          0;
  opt.fpt             =          0;
  opt.fpt_num         =          -1;
  opt.rrecover        =          0;
  opt.wrecover        =          0;
  opt.basename        =          NULL;
  opt.vis_file        =          NULL;
  opt.just_sh         =          0;
  opt.num_err         =          'H';
  opt.FEPS            =          1E-15;
  opt.useplusI        =          0;
  opt.minimal_rate    =          0.0;
  opt.hard_rescale    =          1.0;
  opt.equil_file      =          NULL;
  opt.times           =          1.0;
  opt.warnings        =          0;
}

/*==============================*/
static void
display_settings(void)
{
  int i,j;
  fprintf(stderr,
          "Settings:\n"
          "--absorb   = %3i\n"
          "--t0       = %8.4f\n"
          "--t8       = %7.2g\n"
          "--tinc     = %6.2f\n"
          "--Temp     = %6.2f\n"
          "--method   = %c\n"
          "--nstates  = %d\n"
          "--fpt      = %d\n"
          "-d         = %d\n"
          "-e         = %d\n"
          "-u         = %d\n"
          "-x         = %d\n"
          "-b         = %d\n"
          "-r         = %d\n"
          "-w         = %d\n"
          "-v         = %d\n",
          opt.absrb,
          opt.t0,
          opt.t8,
          opt.tinc,
          opt.T,
          opt.method,
          opt.n,
          opt.fpt,
          opt.want_degenerate,
          opt.matexp,
          opt.dumpU,
          opt.dumpMathematica,
          opt.binrates,
          opt.rrecover,
          opt.wrecover,
          opt.want_verbose);
  for (i=0,j=1; i<args_info.p0_given; i++,j+=2) {
    fprintf(stderr,
            "--p0      %4i=%.2f\n",
            (int)opt.pini[j],opt.pini[j+1]);
  }
}

/* End of file */


