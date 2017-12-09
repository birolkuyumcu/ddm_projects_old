/* 2DPathfinder -- library for pathfinding in 2D maps
 * node_t.h
 * Copyright (c) 2005 Alessandro Presta <alessandro.presta@gmail.com>
 * Released under the GNU Lesser General Public License */

#ifndef	__NODE_T_H__
#define	__NODE_T_H__

typedef struct node {
	int pos;
	int f, g;
} node_t;  

void nCopy(node_t *, node_t *);
int nCompare(node_t *, node_t *);

#endif /* __NODE_T_H__ */
