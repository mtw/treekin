/*
  File autogenerated by gengetopt version 2.16
  generated with the following command:
  gengetopt --file=treekin_cmdline --unamed-opts 

  The developers of gengetopt consider the fixed text that goes in all
  gengetopt output files to be in the public domain:
  we make no copyright claims on it.
*/

/* If we use autoconf.  */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getopt.h"

#include "treekin_cmdline.h"

static
void clear_given (struct gengetopt_args_info *args_info);
static
void clear_args (struct gengetopt_args_info *args_info);

static int
cmdline_parser_internal (int argc, char * const *argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required, const char *additional_error);


struct p0_list
{
  char * p0_arg;
  char *p0_orig;
  struct p0_list * next;
};

char *cmdline_parser_method_values[] = {"A", "F", "I", 0} ;	/* Possible values for method.  */

static char *
gengetopt_strdup (const char *s);

static
void clear_given (struct gengetopt_args_info *args_info)
{
  args_info->help_given = 0 ;
  args_info->version_given = 0 ;
  args_info->absorb_given = 0 ;
  args_info->method_given = 0 ;
  args_info->t0_given = 0 ;
  args_info->t8_given = 0 ;
  args_info->Temp_given = 0 ;
  args_info->nstates_given = 0 ;
  args_info->p0_given = 0 ;
  args_info->tinc_given = 0 ;
  args_info->degeneracy_given = 0 ;
  args_info->exponent_given = 0 ;
  args_info->umatrix_given = 0 ;
  args_info->info_given = 0 ;
  args_info->verbose_given = 0 ;
}

static
void clear_args (struct gengetopt_args_info *args_info)
{
  args_info->absorb_orig = NULL;
  args_info->method_arg = gengetopt_strdup ("A");
  args_info->method_orig = NULL;
  args_info->t0_orig = NULL;
  args_info->t8_orig = NULL;
  args_info->Temp_orig = NULL;
  args_info->nstates_orig = NULL;
  args_info->p0_arg = NULL;
  args_info->p0_orig = NULL;
  args_info->tinc_orig = NULL;
  args_info->degeneracy_flag = 0;
  args_info->exponent_flag = 0;
  args_info->umatrix_flag = 0;
  args_info->info_flag = 0;
  args_info->verbose_flag = 0;
  
}

void
cmdline_parser_print_version (void)
{
  printf ("%s %s\n", CMDLINE_PARSER_PACKAGE, CMDLINE_PARSER_VERSION);
}

void
cmdline_parser_print_help (void)
{
  cmdline_parser_print_version ();
  printf("\nUsage: %s [OPTIONS]... [FILES]...\n\n", CMDLINE_PARSER_PACKAGE);
  printf("%s\n","  -h, --help           Print help and exit");
  printf("%s\n","  -V, --version        Print version and exit");
  printf("%s\n","  -a, --absorb=state   Make a state absorbing");
  printf("%s\n","  -m, --method=STRING  Select method to build transition matrix:\n                         A ==> Arrhenius-like kinetics\n                         F ==> Full process kinetics (whole subopt)\n                         I ==>use rates from barriers  (possible values=\"A\", \n                         \"F\", \"I\" default=`A')");
  printf("%s\n","      --t0=time        Start time");
  printf("%s\n","      --t8=time        Stop time");
  printf("%s\n","  -T, --Temp=FLOAT     Temperatur in Celsius");
  printf("%s\n","  -n, --nstates=INT    Read <int> states");
  printf("%s\n","      --p0=STRING      Set initial population of state <int> to <float>\n                         Can be given multiple times\n                         (NOTE: sum of <float> must equal 1)");
  printf("%s\n","      --tinc=FLOAT     Time scaling factor (for log time-scale)");
  printf("%s\n","  -d, --degeneracy     Consider degeracy in transition rates  (default=off)");
  printf("%s\n","  -e, --exponent       Use matrix-expontent routines, NO diagonalization  \n                         (default=off)");
  printf("%s\n","  -u, --umatrix        Dump transition matrix U to a binary file matrix.bin  \n                         (default=off)");
  printf("%s\n","      --info           show settings  (default=off)");
  printf("%s\n","  -v, --verbose        verbose output  (default=off)");
  
}

void
cmdline_parser_init (struct gengetopt_args_info *args_info)
{
  clear_given (args_info);
  clear_args (args_info);

  args_info->inputs = NULL;
  args_info->inputs_num = 0;
}

static void
cmdline_parser_release (struct gengetopt_args_info *args_info)
{
  
  unsigned int i;
  if (args_info->absorb_orig)
    {
      free (args_info->absorb_orig); /* free previous argument */
      args_info->absorb_orig = 0;
    }
  if (args_info->method_arg)
    {
      free (args_info->method_arg); /* free previous argument */
      args_info->method_arg = 0;
    }
  if (args_info->method_orig)
    {
      free (args_info->method_orig); /* free previous argument */
      args_info->method_orig = 0;
    }
  if (args_info->t0_orig)
    {
      free (args_info->t0_orig); /* free previous argument */
      args_info->t0_orig = 0;
    }
  if (args_info->t8_orig)
    {
      free (args_info->t8_orig); /* free previous argument */
      args_info->t8_orig = 0;
    }
  if (args_info->Temp_orig)
    {
      free (args_info->Temp_orig); /* free previous argument */
      args_info->Temp_orig = 0;
    }
  if (args_info->nstates_orig)
    {
      free (args_info->nstates_orig); /* free previous argument */
      args_info->nstates_orig = 0;
    }
  if (args_info->p0_arg)
    {
      for (i = 0; i < args_info->p0_given; ++i)
        {
          if (args_info->p0_arg [i])
            {
              free (args_info->p0_arg [i]); /* free previous argument */
              args_info->p0_arg [i] = 0;
            }
          if (args_info->p0_orig [i])
            {
              free (args_info->p0_orig [i]); /* free previous argument */
              args_info->p0_orig [i] = 0;
            }
        }
      if (args_info->p0_arg [0])
        free (args_info->p0_arg [0]); /* free default string */
      free (args_info->p0_arg); /* free previous argument */
      args_info->p0_arg = 0;
      free (args_info->p0_orig); /* free previous argument */
      args_info->p0_orig = 0;
    }
  if (args_info->tinc_orig)
    {
      free (args_info->tinc_orig); /* free previous argument */
      args_info->tinc_orig = 0;
    }
  
  for (i = 0; i < args_info->inputs_num; ++i)
    free (args_info->inputs [i]);
  
  if (args_info->inputs_num)
    free (args_info->inputs);
  
  clear_given (args_info);
}

int
cmdline_parser_file_save(const char *filename, struct gengetopt_args_info *args_info)
{
  FILE *outfile;
  int i = 0;

  outfile = fopen(filename, "w");

  if (!outfile)
    {
      fprintf (stderr, "%s: cannot open file for writing: %s\n", CMDLINE_PARSER_PACKAGE, filename);
      return EXIT_FAILURE;
    }

  if (args_info->help_given) {
    fprintf(outfile, "%s\n", "help");
  }
  if (args_info->version_given) {
    fprintf(outfile, "%s\n", "version");
  }
  if (args_info->absorb_given) {
    if (args_info->absorb_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "absorb", args_info->absorb_orig);
    } else {
      fprintf(outfile, "%s\n", "absorb");
    }
  }
  if (args_info->method_given) {
    if (args_info->method_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "method", args_info->method_orig);
    } else {
      fprintf(outfile, "%s\n", "method");
    }
  }
  if (args_info->t0_given) {
    if (args_info->t0_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "t0", args_info->t0_orig);
    } else {
      fprintf(outfile, "%s\n", "t0");
    }
  }
  if (args_info->t8_given) {
    if (args_info->t8_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "t8", args_info->t8_orig);
    } else {
      fprintf(outfile, "%s\n", "t8");
    }
  }
  if (args_info->Temp_given) {
    if (args_info->Temp_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "Temp", args_info->Temp_orig);
    } else {
      fprintf(outfile, "%s\n", "Temp");
    }
  }
  if (args_info->nstates_given) {
    if (args_info->nstates_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "nstates", args_info->nstates_orig);
    } else {
      fprintf(outfile, "%s\n", "nstates");
    }
  }
  if (args_info->p0_orig)
    {
      for (i = 0; i < args_info->p0_given; ++i)
        {
          if (args_info->p0_orig [i])
            {
              fprintf(outfile, "%s=\"%s\"\n", "p0", args_info->p0_orig [i]);
            }
        }
    }
  if (args_info->tinc_given) {
    if (args_info->tinc_orig) {
      fprintf(outfile, "%s=\"%s\"\n", "tinc", args_info->tinc_orig);
    } else {
      fprintf(outfile, "%s\n", "tinc");
    }
  }
  if (args_info->degeneracy_given) {
    fprintf(outfile, "%s\n", "degeneracy");
  }
  if (args_info->exponent_given) {
    fprintf(outfile, "%s\n", "exponent");
  }
  if (args_info->umatrix_given) {
    fprintf(outfile, "%s\n", "umatrix");
  }
  if (args_info->info_given) {
    fprintf(outfile, "%s\n", "info");
  }
  if (args_info->verbose_given) {
    fprintf(outfile, "%s\n", "verbose");
  }
  
  fclose (outfile);

  i = EXIT_SUCCESS;
  return i;
}

void
cmdline_parser_free (struct gengetopt_args_info *args_info)
{
  cmdline_parser_release (args_info);
}

/*
 * Returns:
 * - the index of the matched value
 * - -1 if no argument has been specified
 * - -2 if more than one value has matched
 */
static int
check_possible_values(const char *val, char *values[])
{
  int i, found, last;
  size_t len;

  if (!val)   /* otherwise strlen() crashes below */
    return -1; /* -1 means no argument for the option */

  found = last = 0;

  for (i = 0, len = strlen(val); values[i]; ++i)
    {
      if (strncmp(val, values[i], len) == 0)
        {
          ++found;
          last = i;
          if (strlen(values[i]) == len)
            return i; /* exact macth no need to check more */
        }
    }

  if (found == 1) /* one match: OK */
    return last;

  return (found ? -2 : -1); /* return many values are matched */
}


/* gengetopt_strdup() */
/* strdup.c replacement of strdup, which is not standard */
char *
gengetopt_strdup (const char *s)
{
  char *result = NULL;
  if (!s)
    return result;

  result = (char*)malloc(strlen(s) + 1);
  if (result == (char*)0)
    return (char*)0;
  strcpy(result, s);
  return result;
}

static char *
get_multiple_arg_token(const char *arg)
{
  char *tok, *ret;
  size_t len;

  if (!arg)
    return NULL;

  tok = strchr (arg, ',');

  if (tok)
    len = (size_t)(tok - arg + 1);
  else
    len = strlen (arg) + 1;

  ret = (char *) malloc (len);
  strncpy (ret, arg, len-1);
  ret[len-1] = '\0';

  return ret;
}

static char *
get_multiple_arg_token_next(const char *arg)
{
  char *tok;

  if (!arg)
    return NULL;

  tok = strchr (arg, ',');

  if (! tok || strlen(tok) == 1)
    return 0;

  return tok+1;
}

int
cmdline_parser (int argc, char * const *argv, struct gengetopt_args_info *args_info)
{
  return cmdline_parser2 (argc, argv, args_info, 0, 1, 1);
}

int
cmdline_parser2 (int argc, char * const *argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required)
{
  int result;

  result = cmdline_parser_internal (argc, argv, args_info, override, initialize, check_required, NULL);

  if (result == EXIT_FAILURE)
    {
      cmdline_parser_free (args_info);
      exit (EXIT_FAILURE);
    }
  
  return result;
}

int
cmdline_parser_required (struct gengetopt_args_info *args_info, const char *prog_name)
{
  return EXIT_SUCCESS;
}

int
cmdline_parser_internal (int argc, char * const *argv, struct gengetopt_args_info *args_info, int override, int initialize, int check_required, const char *additional_error)
{
  int c;	/* Character of the parsed option.  */
  char *multi_token, *multi_next; /* for multiple options */

  int i;        /* Counter */

  struct p0_list * p0_list = NULL,* p0_new = NULL;
  int error = 0;
  struct gengetopt_args_info local_args_info;

  if (initialize)
    cmdline_parser_init (args_info);

  cmdline_parser_init (&local_args_info);

  optarg = 0;
  optind = 0;
  opterr = 1;
  optopt = '?';

  while (1)
    {
      int found = 0;
      int option_index = 0;
      char *stop_char;

      static struct option long_options[] = {
        { "help",	0, NULL, 'h' },
        { "version",	0, NULL, 'V' },
        { "absorb",	1, NULL, 'a' },
        { "method",	1, NULL, 'm' },
        { "t0",	1, NULL, 0 },
        { "t8",	1, NULL, 0 },
        { "Temp",	1, NULL, 'T' },
        { "nstates",	1, NULL, 'n' },
        { "p0",	1, NULL, 0 },
        { "tinc",	1, NULL, 0 },
        { "degeneracy",	0, NULL, 'd' },
        { "exponent",	0, NULL, 'e' },
        { "umatrix",	0, NULL, 'u' },
        { "info",	0, NULL, 0 },
        { "verbose",	0, NULL, 'v' },
        { NULL,	0, NULL, 0 }
      };

      stop_char = 0;
      c = getopt_long (argc, argv, "hVa:m:T:n:deuv", long_options, &option_index);

      if (c == -1) break;	/* Exit from `while (1)' loop.  */

      switch (c)
        {
        case 'h':	/* Print help and exit.  */
          cmdline_parser_print_help ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'V':	/* Print version and exit.  */
          cmdline_parser_print_version ();
          cmdline_parser_free (&local_args_info);
          exit (EXIT_SUCCESS);

        case 'a':	/* Make a state absorbing.  */
          if (local_args_info.absorb_given)
            {
              fprintf (stderr, "%s: `--absorb' (`-a') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->absorb_given && ! override)
            continue;
          local_args_info.absorb_given = 1;
          args_info->absorb_given = 1;
          args_info->absorb_arg = strtol (optarg, &stop_char, 0);
          if (!(stop_char && *stop_char == '\0')) {
            fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
            goto failure;
          }
          if (args_info->absorb_orig)
            free (args_info->absorb_orig); /* free previous string */
          args_info->absorb_orig = gengetopt_strdup (optarg);
          break;

        case 'm':	/* Select method to build transition matrix:\nA ==> Arrhenius-like kinetics\nF ==> Full process kinetics (whole subopt)\nI ==>use rates from barriers.  */
          if (local_args_info.method_given)
            {
              fprintf (stderr, "%s: `--method' (`-m') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if ((found = check_possible_values(optarg, cmdline_parser_method_values)) < 0)
            {
              fprintf (stderr, "%s: %s argument, \"%s\", for option `--method' (`-m')%s\n", argv[0], (found == -2) ? "ambiguous" : "invalid", optarg, (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->method_given && ! override)
            continue;
          local_args_info.method_given = 1;
          args_info->method_given = 1;
          if (args_info->method_arg)
            free (args_info->method_arg); /* free previous string */
          args_info->method_arg = gengetopt_strdup (cmdline_parser_method_values[found]);
          if (args_info->method_orig)
            free (args_info->method_orig); /* free previous string */
          args_info->method_orig = gengetopt_strdup (optarg);
          break;

        case 'T':	/* Temperatur in Celsius.  */
          if (local_args_info.Temp_given)
            {
              fprintf (stderr, "%s: `--Temp' (`-T') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->Temp_given && ! override)
            continue;
          local_args_info.Temp_given = 1;
          args_info->Temp_given = 1;
          args_info->Temp_arg = (float)strtod (optarg, &stop_char);
          if (!(stop_char && *stop_char == '\0')) {
            fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
            goto failure;
          }
          if (args_info->Temp_orig)
            free (args_info->Temp_orig); /* free previous string */
          args_info->Temp_orig = gengetopt_strdup (optarg);
          break;

        case 'n':	/* Read <int> states.  */
          if (local_args_info.nstates_given)
            {
              fprintf (stderr, "%s: `--nstates' (`-n') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->nstates_given && ! override)
            continue;
          local_args_info.nstates_given = 1;
          args_info->nstates_given = 1;
          args_info->nstates_arg = strtol (optarg, &stop_char, 0);
          if (!(stop_char && *stop_char == '\0')) {
            fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
            goto failure;
          }
          if (args_info->nstates_orig)
            free (args_info->nstates_orig); /* free previous string */
          args_info->nstates_orig = gengetopt_strdup (optarg);
          break;

        case 'd':	/* Consider degeracy in transition rates.  */
          if (local_args_info.degeneracy_given)
            {
              fprintf (stderr, "%s: `--degeneracy' (`-d') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->degeneracy_given && ! override)
            continue;
          local_args_info.degeneracy_given = 1;
          args_info->degeneracy_given = 1;
          args_info->degeneracy_flag = !(args_info->degeneracy_flag);
          break;

        case 'e':	/* Use matrix-expontent routines, NO diagonalization.  */
          if (local_args_info.exponent_given)
            {
              fprintf (stderr, "%s: `--exponent' (`-e') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->exponent_given && ! override)
            continue;
          local_args_info.exponent_given = 1;
          args_info->exponent_given = 1;
          args_info->exponent_flag = !(args_info->exponent_flag);
          break;

        case 'u':	/* Dump transition matrix U to a binary file matrix.bin.  */
          if (local_args_info.umatrix_given)
            {
              fprintf (stderr, "%s: `--umatrix' (`-u') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->umatrix_given && ! override)
            continue;
          local_args_info.umatrix_given = 1;
          args_info->umatrix_given = 1;
          args_info->umatrix_flag = !(args_info->umatrix_flag);
          break;

        case 'v':	/* verbose output.  */
          if (local_args_info.verbose_given)
            {
              fprintf (stderr, "%s: `--verbose' (`-v') option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
              goto failure;
            }
          if (args_info->verbose_given && ! override)
            continue;
          local_args_info.verbose_given = 1;
          args_info->verbose_given = 1;
          args_info->verbose_flag = !(args_info->verbose_flag);
          break;


        case 0:	/* Long option with no short option */
          /* Start time.  */
          if (strcmp (long_options[option_index].name, "t0") == 0)
          {
            if (local_args_info.t0_given)
              {
                fprintf (stderr, "%s: `--t0' option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
                goto failure;
              }
            if (args_info->t0_given && ! override)
              continue;
            local_args_info.t0_given = 1;
            args_info->t0_given = 1;
            args_info->t0_arg = (float)strtod (optarg, &stop_char);
            if (!(stop_char && *stop_char == '\0')) {
              fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
              goto failure;
            }
            if (args_info->t0_orig)
              free (args_info->t0_orig); /* free previous string */
            args_info->t0_orig = gengetopt_strdup (optarg);
          }
          /* Stop time.  */
          else if (strcmp (long_options[option_index].name, "t8") == 0)
          {
            if (local_args_info.t8_given)
              {
                fprintf (stderr, "%s: `--t8' option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
                goto failure;
              }
            if (args_info->t8_given && ! override)
              continue;
            local_args_info.t8_given = 1;
            args_info->t8_given = 1;
            args_info->t8_arg = (float)strtod (optarg, &stop_char);
            if (!(stop_char && *stop_char == '\0')) {
              fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
              goto failure;
            }
            if (args_info->t8_orig)
              free (args_info->t8_orig); /* free previous string */
            args_info->t8_orig = gengetopt_strdup (optarg);
          }
          /* Set initial population of state <int> to <float>\nCan be given multiple times\n(NOTE: sum of <float> must equal 1).  */
          else if (strcmp (long_options[option_index].name, "p0") == 0)
          {
            local_args_info.p0_given++;
          
            multi_token = get_multiple_arg_token(optarg);
            multi_next = get_multiple_arg_token_next (optarg);
          
            while (1)
              {
                p0_new = (struct p0_list *) malloc (sizeof (struct p0_list));
                p0_new->next = p0_list;
                p0_list = p0_new;
                p0_new->p0_arg = gengetopt_strdup (multi_token);
                p0_new->p0_orig = multi_token;
          
                if (multi_next)
                  {
                    multi_token = get_multiple_arg_token(multi_next);
                    multi_next = get_multiple_arg_token_next (multi_next);
                    local_args_info.p0_given++;
                  }
                else
                  break;
              }
            break;
          }
          /* Time scaling factor (for log time-scale).  */
          else if (strcmp (long_options[option_index].name, "tinc") == 0)
          {
            if (local_args_info.tinc_given)
              {
                fprintf (stderr, "%s: `--tinc' option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
                goto failure;
              }
            if (args_info->tinc_given && ! override)
              continue;
            local_args_info.tinc_given = 1;
            args_info->tinc_given = 1;
            args_info->tinc_arg = (float)strtod (optarg, &stop_char);
            if (!(stop_char && *stop_char == '\0')) {
              fprintf(stderr, "%s: invalid numeric value: %s\n", argv[0], optarg);
              goto failure;
            }
            if (args_info->tinc_orig)
              free (args_info->tinc_orig); /* free previous string */
            args_info->tinc_orig = gengetopt_strdup (optarg);
          }
          /* show settings.  */
          else if (strcmp (long_options[option_index].name, "info") == 0)
          {
            if (local_args_info.info_given)
              {
                fprintf (stderr, "%s: `--info' option given more than once%s\n", argv[0], (additional_error ? additional_error : ""));
                goto failure;
              }
            if (args_info->info_given && ! override)
              continue;
            local_args_info.info_given = 1;
            args_info->info_given = 1;
            args_info->info_flag = !(args_info->info_flag);
          }
          
          break;
        case '?':	/* Invalid option.  */
          /* `getopt_long' already printed an error message.  */
          goto failure;

        default:	/* bug: option not considered.  */
          fprintf (stderr, "%s: option unknown: %c%s\n", CMDLINE_PARSER_PACKAGE, c, (additional_error ? additional_error : ""));
          abort ();
        } /* switch */
    } /* while */


  if (local_args_info.p0_given && p0_list)
    {
      struct p0_list *tmp;
      args_info->p0_arg = (char * *) realloc (args_info->p0_arg, (args_info->p0_given + local_args_info.p0_given) * sizeof (char *));
      args_info->p0_orig = (char **) realloc (args_info->p0_orig, (args_info->p0_given + local_args_info.p0_given) * sizeof (char *));
      for (i = (local_args_info.p0_given - 1); i >= 0; --i)
        {
          tmp = p0_list;
          args_info->p0_arg [i + args_info->p0_given] = p0_list->p0_arg;
          args_info->p0_orig [i + args_info->p0_given] = p0_list->p0_orig;
          p0_list = p0_list->next;
          free (tmp);
        }
    }
  

  args_info->p0_given += local_args_info.p0_given;
  local_args_info.p0_given = 0;
  

  cmdline_parser_release (&local_args_info);

  if ( error )
    return (EXIT_FAILURE);

  if (optind < argc)
    {
      int i = 0 ;

      args_info->inputs_num = argc - optind ;
      args_info->inputs =
        (char **)(malloc ((args_info->inputs_num)*sizeof(char *))) ;
      while (optind < argc)
        args_info->inputs[ i++ ] = gengetopt_strdup (argv[optind++]) ;
    }

  return 0;

failure:
  if (p0_list)
    {
      struct p0_list *tmp;
      while (p0_list)
        {
          tmp = p0_list;
          free (p0_list->p0_arg);
          free (p0_list->p0_orig);
          p0_list = p0_list->next;
          free (tmp);
        }
    }
  
  cmdline_parser_release (&local_args_info);
  return (EXIT_FAILURE);
}
