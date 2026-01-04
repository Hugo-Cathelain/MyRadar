# My Radar

My Radar is a 2D air traffic simulation program written in C using the CSFML library. It simulates the movement of aircraft across a map, managing their trajectories, speeds, and potential collisions.

The core technical challenge of this project is the efficient handling of collision detection between a large number of entities using a **Quadtree** data structure.

## Features

*   **Aircraft Simulation:** Planes fly from a departure point to a destination at a specific speed and start time.
*   **Control Towers:** Towers define safe zones (circles) where aircraft cannot collide.
*   **Collision Detection:** Aircraft collide and are destroyed if their hitboxes overlap while outside of a control tower's range.
*   **Quadtree Optimization:** Implements a spatial partitioning algorithm (Quadtree) to optimize collision checks, reducing complexity significantly compared to a brute-force approach.
*   **Visual Toggles:** Users can toggle the visibility of sprites, hitboxes, and the quadtree grid in real-time.

## Building the Project

The project includes a [Makefile](Makefile) for easy compilation.

To build the project:
```bash
make
```

To clean up object files:
```bash
make clean
```

To clean up everything including the binary:
```bash
make fclean
```

## Usage

Run the program by providing a path to a script file describing the simulation entities:

```bash
./my_radar [path_to_script]
```

### Options
*   `-h`: Print the usage manual and quit.

### User Controls
During the simulation, you can use the following keyboard shortcuts:

*   **`L`**: Enable/Disable hitboxes and control tower areas.
*   **`S`**: Enable/Disable aircraft and tower sprites.
*   **`Q`**: Enable/Disable the visual representation of the Quadtree grid.

## File Format

The script file passed as an argument defines the entities.
*   **Aircraft (`A`):** `A [start_x] [start_y] [end_x] [end_y] [speed] [delay]`
*   **Tower (`T`):** `T [x] [y] [radius]`

## Technical Implementation

### Quadtree
To handle collisions efficiently, the screen is recursively divided into four quadrants. This logic is implemented in `src/quadtree.c`. This allows the program to only check for collisions between planes that occupy the same or adjacent spatial nodes, rather than checking every plane against every other plane.

### Custom Library
This project utilizes a custom implementation of standard C library functions (located in `src/shared/`), including:
*   `my_atoi`, `my_atof` (String to number conversion)
*   `my_strlen`, `my_strcmp`, `my_strcpy`, `my_strdup` (String manipulation)
*   `my_strtok` (String tokenization)
