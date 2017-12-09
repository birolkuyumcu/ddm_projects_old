/* 2DPathfinder -- library for pathfinding in 2D maps
 * pathfinder_t.h
 * Copyright (c) 2005 Alessandro Presta <alessandro.presta@gmail.com>
 * Released under the GNU Lesser General Public License */

#ifndef		__PATHFINDER_T_H__
#define		__PATHFINDER_T_H__

#include "node_t.h"
#include "map_t.h"
#include "heap_t.h"
#include "list_t.h"

#define		OPEN_COUNT			(pathfinder->open_list->elems)
#define		IS_OPEN(pos)		(pathfinder->open_list->flags[pos])					
#define 	IS_CLOSED(pos) 		(pathfinder->closed_list[pos])		
#define		PUSH_OPEN(node)		(hInsert(pathfinder->open_list, &node))				
#define		PUSH_CLOSED(pos)	(pathfinder->closed_list[pos] = 1)		
#define		GET_MIN_OPEN()		(hGetMin(pathfinder->open_list))					
#define		POP_OPEN()			(hPop(pathfinder->open_list))
#define		POP_CLOSED(pos)		(pathfinder->closed_list[pos] = 0)
#define		IS_FREE(pos)		(!(pathfinder->map->cells[pos]))
#define		IS_VALID(x,y)		((x >= 0) && (x < pathfinder->map->x_limit) && (y >= 0) && (y < pathfinder->map->y_limit))		
#define		OPEN_NODE(pos)		(hFind(pathfinder->open_list, pos))					
#define		SET_PARENT(s, p)	(pathfinder->parent[s] = p)
#define		GET_PARENT(s)		(pathfinder->parent[s])								
#define		POSITION_LIMIT		((pathfinder->map->x_limit)*(pathfinder->map->y_limit))
#define		NO_PARENT			-1

enum {
	SOLVED,
	NO_SOLUTION
};

typedef struct pathfinder {
	map_t *map;
	heap_t *open_list;
	short *closed_list;
	int *parent;
	int total_nodes;
} pathfinder_t;

pathfinder_t* pfAlloc(int, int);
void pfFree(pathfinder_t *);
void pfSetMap(pathfinder_t *, map_t *);
int pfFindPath(pathfinder_t *, int, int, list_t *, int *);
void pfReset(pathfinder_t *);

#endif /* __PATHFINDER_T_H__ */
