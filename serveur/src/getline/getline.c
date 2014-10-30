#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_line.h"

char*	_get_socket(_fd fd) {
  char* buff;
  int	itt;
  char	c;

  itt = 0;
  buff = NULL;
  c = -1;
  while ((c != 0 && c != '\n') && read(fd, &c, 1) > 0)
    {
      if (c == '0' && itt == 1)
	return (strdup("msz"));
      buff = realloc(buff, itt + 1);
      buff[itt] = c;
      itt += 1;
      if (c == '\n' || c == 0)
	buff = realloc(buff, itt + 1);
      if (c == '\n' || c == 0)
	buff[itt] = 0;
    }
  return (buff);
}
