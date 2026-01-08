# Cub3D

A raycasting-based 3D graphical representation engine inspired by Wolfenstein 3D, implementing the Digital Differential Analysis (DDA) algorithm for real-time rendering.

## Overview

Cub3D is a 42 School project that creates a realistic 3D perspective inside a 2D maze using raycasting techniques. The engine renders a first-person view environment with textured walls, floor/ceiling colors, and smooth player movement.

## Architecture

### Core Components

```
Cub3D Engine
├── Parsing System
│   ├── Configuration Parser (.cub files)
│   ├── Map Validator (flood fill algorithm)
│   └── Texture Loader (.xpm files)
├── Raycasting Engine
│   ├── DDA Algorithm
│   ├── Wall Detection
│   └── Perspective Calculation
├── Rendering System
│   ├── Texture Mapping
│   ├── Color Processing
│   └── Frame Buffer
└── Input System
    ├── Movement Handler (WASD)
    └── Camera Rotation (Arrow Keys)
```

### Raycasting Pipeline

```
For each vertical stripe (x):
  1. Calculate ray direction
     └── camera_x = 2 * x / screen_width - 1

  2. Initialize DDA parameters
     ├── delta_dist_x = |1 / ray_dir_x|
     ├── delta_dist_y = |1 / ray_dir_y|
     └── step direction (+1 or -1)

  3. DDA Wall Detection
     └── Step through grid until wall hit

  4. Calculate perpendicular wall distance
     └── Avoid fisheye effect

  5. Compute wall slice height
     └── wall_height = screen_height / perp_wall_dist

  6. Texture mapping
     ├── Calculate wall_x (hit point)
     ├── Map to texture coordinates
     └── Render vertical stripe
```

### Data Structures

```c
t_game
├── t_map (map_game)
│   ├── char **map              // 2D grid representation
│   ├── int height              // Map height in tiles
│   ├── t_player                // Player state
│   ├── t_sprite[4]             // Wall textures (NO/SO/WE/EA)
│   └── unsigned int colors     // Floor/ceiling RGB
├── t_raycast (ray)
│   ├── ray_dir_x, ray_dir_y    // Ray direction vector
│   ├── side_dist_x, side_dist_y // Distance to next grid line
│   ├── delta_dist_x, delta_dist_y // Ray step size
│   ├── perp_wall_dist          // Perpendicular distance to wall
│   └── wall_height             // Projected wall height
└── t_keys                      // Input state flags
```

### Directory Structure

```
src/
├── main.c                    // Entry point and initialization
├── engine.c                  // Main game loop
├── parsing/
│   ├── parsing.c            // Argument validation
│   ├── read_file.c          // .cub file parser
│   ├── data_verification.c  // Configuration validator
│   ├── flood_fill.c         // Map boundary checker
│   └── rgb.c                // Color parser (TRGB format)
├── window/
│   ├── ft_raycasting.c      // DDA implementation
│   ├── ft_draw.c            // Texture rendering
│   ├── mlx_utils.c          // Sprite initialization
│   └── ft_window.c          // Window manager
├── movement/
│   ├── hooks.c              // Input event handlers
│   ├── movement.c           // Position updates
│   └── movement_utils.c     // Collision detection
└── error/
    ├── ft_error.c           // Error handling
    └── ft_error2.c          // Memory cleanup
```

## Map Format

Configuration files (.cub) must specify:

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm

F 220,100,0    # Floor color (R,G,B)
C 225,30,0     # Ceiling color (R,G,B)

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

Map constraints:
- Walls represented by '1'
- Empty spaces as '0'
- Player spawn: N, S, E, W (direction)
- Must be surrounded by walls (closed map)

## Mathematical Foundation

### Perpendicular Wall Distance

To avoid fisheye distortion, distance is calculated perpendicular to the camera plane:

```
If side == 0:  perp_wall_dist = side_dist_x - delta_dist_x
If side == 1:  perp_wall_dist = side_dist_y - delta_dist_y
```

### Texture Mapping

Wall hit point calculation:
```c
if (side == 0)
    wall_x = pos_y + perp_wall_dist * ray_dir_y;
else
    wall_x = pos_x + perp_wall_dist * ray_dir_x;
wall_x -= floor(wall_x);  // Normalize to [0,1]
```

Texture coordinate mapping:
```c
tex_x = (int)(wall_x * texture_width);
step = (double)texture_height / wall_height;
tex_pos = (draw_start - screen_height/2 + wall_height/2) * step;
```

## Build and Usage

### Compilation

```bash
make        # Build cub3d executable
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Rebuild from scratch
```

### Running

```bash
./cub3d path/to/map.cub
```

Example:
```bash
./cub3d assets/maps/test1.cub
```

### Controls

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Strafe left |
| D | Strafe right |
| Left Arrow | Rotate camera left |
| Right Arrow | Rotate camera right |
| ESC | Exit program |

### Testing

```bash
make test         # Run local tests
make val ARGS='assets/maps/test1.cub'  # Valgrind memory check
```

## Dependencies

- **MiniLibX**: Graphics library for X11/Cocoa
- **libft**: Custom C standard library implementation
- **Math library** (-lm): Trigonometric functions
- **X11 libraries**: -lX11, -lXext (Linux)

### System Requirements

- GCC or Clang (C99 standard)
- Make
- X11 development libraries (Linux)
- XQuartz (macOS)

## Implementation Details

### Player View Representation

The camera system uses vectors instead of Euclidean angles:

```
Camera Plane (perpendicular to direction)
        |
        |
   <----+----> FOV
        |
        |
   Direction Vector
```

Field of View (FOV) is determined by the ratio:
```
FOV = 2 * atan(plane_length / dir_length)
```

Default configuration (66° FOV):
```c
dir_x = -1.0, dir_y = 0.0    // Direction vector
plane_x = 0.0, plane_y = 0.66 // Camera plane
```

### DDA Algorithm

The Digital Differential Analysis efficiently traverses the grid:

1. Calculate initial `side_dist` to first grid intersection
2. Compare `side_dist_x` vs `side_dist_y`
3. Step in direction with smaller distance
4. Increment by `delta_dist`
5. Repeat until wall hit

This avoids floating-point precision issues and ensures every grid cell is checked.

### Collision Detection

Movement validation checks next position:
```c
new_pos_x = pos_x + dir_x * MOVE_SPEED
new_pos_y = pos_y + dir_y * MOVE_SPEED

if (map[(int)new_pos_y][(int)new_pos_x] != '1')
    update_position();
```

### Rotation Matrix

Camera rotation applies 2D rotation matrix:
```
| cos(θ)  -sin(θ) |
| sin(θ)   cos(θ) |
```

Applied to both direction and plane vectors to maintain perpendicularity.

## Technical References

Based on the raycasting tutorial by Lode Vandevenne:
- https://lodev.org/cgtutor/raycasting.html

Implements techniques pioneered by Wolfenstein 3D (id Software, 1992).

## Project Structure Highlights

- **Parsing**: Robust error handling for invalid maps and configurations
- **Flood Fill**: Ensures map closure (no open boundaries)
- **Texture Loading**: XPM file format support via MiniLibX
- **Frame Rendering**: Direct pixel buffer manipulation for performance
- **Memory Management**: Comprehensive cleanup on error and exit

## Performance Considerations

- Raycasting is O(w) per frame where w = screen width
- Vertical stripe rendering optimizes cache locality
- Texture lookups use pre-loaded image buffers
	- No floating-point divisions in inner loops where possible

## Authors

- guclemen (Guilherme Clemente)
- yfaustin (Yuri Faustin)
