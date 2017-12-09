/* 2DPathfinder -- library for pathfinding in 2D maps
 * list_t.h
 * Copyright (c) 2005 Alessandro Presta <alessandro.presta@gmail.com>
 * Released under the GNU Lesser General Public License */

#ifndef		__LIST_T_H__
#define		__LIST_T_H__

typedef struct lelem lelem_t;
struct lelem {
	int val;
	struct lelem *next;
};

typedef struct list {
	lelem_t *front;
	lelem_t *back;
} list_t;

typedef lelem_t* list_iterator_t;

list_t* lAlloc();
void lFree(list_t *);
void lPushFront(list_t *, int);
void lPushBack(list_t *, int);
void lPopFront(list_t *);
void lPopBack(list_t *);
int lGetFront(list_t *);
int lGetBack(list_t *);
void lClear(list_t *);

#endif /* __LIST_T_H__ */	
