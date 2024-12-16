#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

#define MAX_COLOR_VALUE 255
#define CEIL_DIV(x, y) (((x) + (y) - 1) / (y))

void readPointCloudData(FILE *stream, int *rasterWidth, List *pc) {
    if (listInit(pc, sizeof(pcd_t)) == -1) {
        fprintf(stderr, "Error: Memory allocation failed for point cloud list\n");
        return;
    }

    double x, y, z;
    int pointCount = 0;
    while (fscanf(stream, "%lf %lf %lf", &x, &y, &z) == 3) {
        pcd_t point;
        point.x = x;
        point.y = y;
        point.z = z;
        point.water = 0.0; // Initialize water to 0
        point.north = NULL;
        point.south = NULL;
        point.east = NULL;
        point.west = NULL;

        listAdd(pc, &point);
        pointCount++;
    }

    // Calculate raster width as the square root of the total number of points
    *rasterWidth = (int)sqrt(pointCount);
}

void imagePointCloud(List *l, int width, char *filename) {
    if (l->size == 0) {
        fprintf(stderr, "Error: No points available to generate the image.\n");
        return;
    }

    double min_z = DBL_MAX;
    double max_z = -DBL_MAX;

    // Determine the minimum and maximum z values
    for (int i = 0; i < l->size; i++) {
        pcd_t *point = (pcd_t *)listGet(l, i);
        if (point->z < min_z) {
            min_z = point->z;
        }
        if (point->z > max_z) {
            max_z = point->z;
        }
    }

    double range = max_z - min_z;
    if (range == 0) {
        range = 1; // Avoid division by zero
    }

    // Calculate height based on the number of points and the provided width
    int height = CEIL_DIV(l->size, width);
    Bitmap *image = bm_create(width, height);
    if (image == NULL) {
        fprintf(stderr, "Error: Failed to create bitmap image.\n");
        return;
    }

    // Assign pixel values based on height ranges
    for (int i = 0; i < l->size; i++) {
        pcd_t *point = (pcd_t *)listGet(l, i);
        int color_value = (int)((point->z - min_z) / range * MAX_COLOR_VALUE);
        int x = i % width;
        int y = i / width;
        unsigned int color = 0xFF000000 | (color_value << 16) | (color_value << 8) | color_value; // RGBA
        bm_set(image, x, y, color);
    }

    // Save the Bitmap image
    bm_save(image, filename);

    // Free the Bitmap image
    bm_free(image);
    listFree(l); // Free the point cloud data to prevent memory leaks
}

void stat1() {
    Point *points = NULL; // Pointer to dynamically allocate memory for points
    int count = 0; // Initialize amount of data points to 0
    int capacity = 10; // Initial capacity

    points = malloc(capacity * sizeof(Point)); // Allocate initial memory
    if (points == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return;
    }

    // Read input values until end of file
    while (fscanf(stdin, "%lf %lf %lf", &points[count].x, &points[count].y, &points[count].height) == 3) {
        printf("Read values: x = %lf, y = %lf, height = %lf\n", points[count].x, points[count].y, points[count].height);
        count++;

        if (count >= capacity) {
            capacity *= 2;
            points = realloc(points, capacity * sizeof(Point));
            if (points == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                return;
            }
        }
    }

    if (feof(stdin)) {
        printf("End of input reached.\n");
    } else if (ferror(stdin)) {
        perror("Error reading input");
    }

    if (count == 0) {
        printf("No data points read.\n");
        free(points);
        return;
    }

    double minHeight = points[0].height, maxHeight = points[0].height;
    double minX = points[0].x, minY = points[0].y, maxX = points[0].x, maxY = points[0].y;
    double sumHeight = 0;

    // Process all points to find min and max heights and their coordinates
    for (int i = 0; i < count; i++) {
        if (points[i].height < minHeight) {
            minHeight = points[i].height;
            minX = points[i].x;
            minY = points[i].y;
        }
        if (points[i].height > maxHeight) {
            maxHeight = points[i].height;
            maxX = points[i].x;
            maxY = points[i].y;
        }
        sumHeight += points[i].height;
    }

    double avgHeight = sumHeight / count; // Calculate the average height

    // Print the results
    printf("Minimum Height: %lf at (%lf, %lf)\n", minHeight, minX, minY);
    printf("Maximum Height: %lf at (%lf, %lf)\n", maxHeight, maxX, maxY);
    printf("Average Height: %lf\n", avgHeight);

    free(points); // Free the allocated memory
}
