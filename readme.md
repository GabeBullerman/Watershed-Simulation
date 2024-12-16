# Point Cloud Statistics

## Author
- Gabriel Bullerman

## Project Description
This project reads a set of 3D points from standard input and calculates information about the points. The program reads points in the format `x y height` and outputs the following statistics:
- Minimum height and its coordinates
- Maximum height and its coordinates
- Average height

Additionally, the project can make a GIF image representing the point-cloud data.

## Files
- `parta.c`: Contains the `main` function for both `stat1` and `display` executables.
- `pointcloud.c`: Contains functions for reading point-cloud data, calculating statistics, and generating the out.gif image from the points.
- `pointcloud.h`: Header file containing function prototypes for point-cloud operations.
- `util.c`: Utility functions used in the project.
- `util.h`: Header file for utility functions.
- `bmp.c`: Functions for creating BMP images.
- `bmp.h`: Header file for BMP image functions.
- `makefile`: The Makefile used to build the project.
- `test_gradient.txt`: Gradient style test with points made using a simple Python script.
- `test.xyz`: Another sample data file.

### Steps to Compile and Run
1. **Navigate to the Project Directory**:
    ```sh
    cd path/to/project/directory
    ```

2. **Compile the Project**:
    - Run the `make` command to compile the project:
      ```sh
      make
      ```

3. **Run the Executables**:
    - To run the `stat1` executable and provide input from a file:
      ```sh
      stat1 < test.xyz
      ```
    - To run the `display` executable and generate the `out.gif` file:
      ```sh
      display < test.xyz
      ```

### Cleaning Up
- To clean up the compiled files and the generated `out.gif`, run:
  ```sh
  make clean