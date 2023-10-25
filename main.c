#include <stdio.h>
#include "rb.h"

int main() {
  Tree t = createTree();
  link x;
  insert(t, 99);
  insert(t, 88);
  insert(t, 77);
  insert(t, 75);
  insert(t, 74);
  insert(t, 100);
  insert(t, 101);
  

  imprime(t, "rb");

  return 0;
}
