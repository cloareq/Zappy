#ifndef __CIRULAR_BUFFER_H__
# define __CIRULAR_BUFFER_H__

#include "bool.h"

typedef struct s_circularBuffer		circularBuffer;
typedef struct s_circularNode		circularNode;

struct s_circularNode{
  circularNode* next;
  char*		value;
};

struct s_circularBuffer{
  circularNode*	queue;
  circularNode*	endQueue;
  size_t	size;
};

void	pushNode(circularBuffer*, char* value);
char*	popNode(circularBuffer*);

circularBuffer*		createBuffer();
void			destroyBuffer(circularBuffer*, bool);

#endif
