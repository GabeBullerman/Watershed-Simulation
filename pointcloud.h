#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <stdio.h>
#include "util.h" // Include util.h to define List

typedef struct pcd {
    double x;
    double y;
    double z; // height
    double water;
    struct pcd *north;
    struct pcd *south;
    struct pcd *east;
    struct pcd *west;
} pcd_t;

typedef struct {
    double x, y, height;
} Point;

void readPointCloudData(FILE *stream, int *rasterWidth, List *pc);
void imagePointCloud(List *l, int width, char *filename);
void stat1(); // Declare the stat1 function

#endif // POINTCLOUD_H