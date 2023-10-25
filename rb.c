#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int id = 0;

link novoNo(int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->id = id++;
  t->altura = 1;
  t->cor = RED; // Novo no inicialmente vermelho
  return t;
}

Tree createTree() {
  Tree t = malloc(sizeof(struct tree));
  t->z = malloc(sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  t->z->altura = 0;
  t->z->cor = BLACK; 
  return t;
}

int altura(link h) {
  if (h == NULL) {
    return 0;
  }
  return h->altura;
}

int atualizaAltura(link h) {
  int hl = altura(h->l);
  int hr = altura(h->r);
  return (hl > hr ? hl : hr) + 1;
}

link rotR(Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  x->cor = h->cor;
  h->cor = RED;
  h->altura = atualizaAltura(h);
  x->altura = atualizaAltura(x);
  return x;
}

link rotL(Tree t, link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  x->cor = h->cor;
  h->cor = RED;
  h->altura = atualizaAltura(h);
  x->altura = atualizaAltura(x);
  return x;
}


link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if (h->item == query)
    return h;
  if (h->item >= query)
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
}

link search(Tree t, int query) {
  return searchR(t, t->head, query);
}

void inverteCores(link h) {
  h->cor = !h->cor;
  if (h->l != NULL)
    h->l->cor = !h->l->cor;
  if (h->r != NULL)
    h->r->cor = !h->r->cor;
}

link insertR(Tree t, link h, link n) {
  if (h == t->z) {
    n->cor = RED;
    return n;
  }

  if (h->item >= n->item) {
    h->l = insertR(t, h->l, n);
  } else {
    h->r = insertR(t, h->r, n);
  }

  // Correção da árvore rubro-negra
  if (h->r->cor == RED && h->l->cor == BLACK) {
    h = rotL(t, h);
  }
  if (h->l->cor == RED && h->l->l->cor == RED) {
    h = rotR(t, h);
  }
  if (h->l->cor == RED && h->r->cor == RED) {
    inverteCores(h);
  }

  return h;
}

link insert(Tree t, int item) {
  if (t->head == t->z) {
    link new_node = novoNo(item, t->z, t->z);
    new_node->cor = BLACK; //raiz deve ser sempre preta
    t->head = new_node;
    return t->head;
  }

  t->head = insertR(t, t->head, novoNo(item, t->z, t->z));
  t->head->cor = BLACK; //raiz deve ser sempre preta
  return t->head;
}


void imprimeEmOrdem(Tree t, link h) {
  if (h == t->z) return;
  imprimeEmOrdem(t, h->l);
  printf("<chave: %d N: %d Height: %d>", h->item, h->N, h->altura);
  imprimeEmOrdem(t, h->r);
}

void imprimePosOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimePosOrdem (t, h->l);
  imprimePosOrdem (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}
void imprimePreOrdem (Tree t, link h, int k) {
  if(h == t->z) return;
  for(int i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  imprimePreOrdem (t, h->l, k + 1); 
  imprimePreOrdem (t, h->r, k + 1);
}


void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}

int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}


