/* 2DPathfinder -- library for pathfinding in 2D maps
 * heap_t.h
 * Copyright (c) 2005 Alessandro Presta <alessandro.presta@gmail.com>
 * Released under the GNU Lesser General Public License */

#ifndef		__HEAP_T_H__
#define		__HEAP_T_H__

#include "node_t.h" 

#define		FATHER(i)		(i/2)
#define		MIN_SON(i)		(((2*i+2) < heap->elems) ? ((nCompare(&(heap->nodes[2*i+1]), &(heap->nodes[2*i+2])) < 0) ? (2*i+1) : (2*i+2)) : (2*i+1))	
#define		SWAP(i, k)		{ node_t tmp; nCopy(&(heap->nodes[i]), &tmp); nCopy(&(heap->nodes[k]), &(heap->nodes[i])); nCopy(&tmp, &(heap->nodes[k])); } 

#define		DEFAULT_HEAP_REALLOC_ADDEND		10

typedef struct heap {
	int size;
	int elems;
	node_t *nodes;
	short *flags;
	int total_nodes;
} heap_t; 

heap_t* hAlloc(int, int);
void hFree(heap_t *);
void hInsert(heap_t *, node_t *);
void hPop(heap_t *);
node_t* hGetMin(heap_t *);
void hSendUp(heap_t *, int);
void hSendDown(heap_t *, int);
void hReset(heap_t *);
node_t* hFind(heap_t *, int);

#endif /* __HEAP_T_H__ */
