#include <stdlib.h>

#include "lerror.h"
#include "circularBuffer.h"

void	pushNode(circularBuffer* this, char* value) {
  circularNode* node;

  if ((node = malloc(sizeof(circularNode))) == NULL)
    lerror(MEMORY_ERROR(sizeof(circularNode)));
  node->next = NULL;
  if (!this->endQueue)
    this->endQueue = node;
  else
    this->endQueue->next = node;
  if (!this->queue)
    this->queue = node;
  this->endQueue = node;
  node->value = value;
  this->size += 1;
}

char*	popNode(circularBuffer* this) {
  circularNode*	node;
  char* txt;

  if (!this->queue)
    return (NULL);
  txt = this->queue->value;
  node = this->queue;
  if (node == this->endQueue)
    this->endQueue = NULL;
  this->queue = this->queue->next;
  free(node);
  this->size -= 1;
  return (txt);
}

void	destroyBuffer(circularBuffer* this, bool freeNodeVal) {
  char* k;

  while (this->size > 0) {
  k = popNode(this);
  if (freeNodeVal)
    free(k);
}
  free(this);
}

circularBuffer*	createBuffer(){
  circularBuffer* this;

  if ((this = malloc(sizeof(circularBuffer))) == NULL)
    lerror(MEMORY_ERROR(sizeof(circularBuffer)));
  this->queue = this->endQueue = NULL;
  this->size = 0;
  return (this);
}
