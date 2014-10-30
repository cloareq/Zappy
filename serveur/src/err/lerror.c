#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "lerror.h"

void	lerror(const char* s, ... )
{
  va_list	ap;

  va_start(ap, s);
  vfprintf(stderr, s, ap);
  va_end(ap);
  exit(1);
}

