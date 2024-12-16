#include <stdio.h>
#include <stdlib.h>
#include "pointcloud.h"
#include "util.h"
#include "bmp.h"

#ifdef MAIN_STAT1
int main() {
    stat1(); // Call the stat1 function
    return 0; // Return 0 to indicate successful execution
}
#endif

#ifdef MAIN_DISPLAY
int main() {
    // Hardcoded output filename
    char output_filename[] = "out.gif";

    // Create a list to store point-cloud data
    List pointCloud;
    if (listInit(&pointCloud, sizeof(pcd_t)) == -1) {
        fprintf(stderr, "Error: Failed to initialize point cloud list.\n");
        return 1;
    }

    // Read point-cloud data from stdin
    int rasterWidth;
    readPointCloudData(stdin, &rasterWidth, &pointCloud);

    // Check if rasterWidth is valid
    if (rasterWidth <= 0) {
        fprintf(stderr, "Invalid raster width: %d\n", rasterWidth);
        listFree(&pointCloud); // Free the list before returning
        return 1;
    }

    // Generate the output image file (e.g., BMP or GIF)
    imagePointCloud(&pointCloud, rasterWidth, output_filename);

    // Free the list
    listFree(&pointCloud);

    return 0;
}
#endif