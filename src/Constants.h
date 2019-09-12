#pragma once

#define BEST_SPEED_MOD 2.f

// tile dimensions in pixels
#define TILE_SIZE 32
#define TILE_MAP_SIZE 32

// dimensions of the window in pixels
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

// dimensions of the renderable area in tiles
#define CHUNK_HEIGHT (WINDOW_HEIGHT / TILE_SIZE)
#define CHUNK_WIDTH (WINDOW_WIDTH / TILE_SIZE)
#define CHUNK_EXTRA_HEIGHT 1
#define CHUNK_EXTRA_WIDTH 1

// dimensions of the entire world in tiles
#define WORLD_HEIGHT_RADIUS (CHUNK_HEIGHT * 10)
#define WORLD_WIDTH_RADIUS (CHUNK_WIDTH * 10)
