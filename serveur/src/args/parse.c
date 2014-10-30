#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "argues.h"
#include "lerror.h"

static void	fillin(struct args* this,
		       enum argsType	opt, int *itt, char** args)
{
  if (opt == port)
    this->port = atoi(args[*itt]);
  if (opt == X)
    this->X = atoi(args[*itt]);
  if (opt == Y)
    this->Y = atoi(args[*itt]);
  if (opt == nByTeams)
    this->nByTeams = atoi(args[*itt]);
  if (opt == atime)
    this->time = atof(args[*itt]);  
  if (opt == names) {
    while (*itt < this->ac && strncmp(args[*itt], "-", 1)) {
      struct nameNode* next;
      if ((next = malloc(sizeof(struct nameNode))) == NULL)
	lerror(MEMORY_ERROR(sizeof(struct nameNode)));
      next->next = this->names;
      this->names = next;
      next->name = args[*itt];
      *itt += 1;
    }
    *itt -= 1;
  }
}

static void	fillArgs(struct args* this,
			 char* syntax[ARGSNUM],
			 char **av, int ac) {
  int	syntax_iterator;
  int	argues_iterator;

  this->ac = ac;
  argues_iterator = 1;
  while (argues_iterator < ac) {
    syntax_iterator = 0;
    if (argues_iterator + 1 >= ac)
      lerror(WRONG_ARGUES_NUMBER);
    while (syntax_iterator < ARGSNUM) {
      if (!strcmp(syntax[syntax_iterator], av[argues_iterator])) {
	argues_iterator += 1;
	fillin(this, syntax_iterator, &argues_iterator, av);
	(this->initialized)[syntax_iterator] = true;
	break;
      }
      syntax_iterator += 1;
    }
    if (syntax_iterator == ARGSNUM)
      printf("WARNING : arguments[%s] isn't known, will be ignored\n",
	     av[argues_iterator]);
    argues_iterator += 1 + (syntax_iterator == ARGSNUM);
  }
}

static void	  testForNonInitialized(struct args* this){
  if (!(this->initialized[port]))
    this->port = BASE_PORT;
  if (!(this->initialized[X]))
    this->X = BASE_X;
  if (!(this->initialized[Y]))
    this->Y = BASE_Y;
  if (!(this->initialized[names]))
    lerror(NAMES_UNITIALIZED);
  if (!(this->initialized[nByTeams]) || !this->nByTeams)
    this->nByTeams = BASE_NBY;
  if (this->nByTeams > 5000)
    {
      printf("WARNING: can't pass over 5000 clients by team,\
 will be maxed to 5000\n");
      this->nByTeams = 5000;
    }
  if (!(this->initialized[atime]))
    this->time = BASE_TIME;
}

struct args*	getArgs(int ac, char** av){
  char*		syntax[ARGSNUM];
  char*		pre_syntax;
  int		itt;
  struct args* this;

  if ((this = malloc(sizeof(struct args))) == NULL)
    lerror(MEMORY_ERROR(sizeof(struct args)));
  if ((pre_syntax = strdup(ARGS)) == NULL)
    lerror(MEMORY_ERROR(strlen(ARGS)));
  itt = 0;
  bzero((this->initialized), sizeof(bool) * ARGSNUM);
  while (itt < ARGSNUM) {
    syntax[itt] = strsep(&pre_syntax, "|");
    itt++;
  }
  this->names = NULL;
  fillArgs(this, syntax, av, ac);
  free(syntax[0]);
  testForNonInitialized(this);
  return (this);
};
