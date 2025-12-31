#include "../includes/header.h"

// Cube mesh - standard unit cube
t_mesh cube = {
    .VertexCount = 8,
    .IndexCount = 36,
    .Vbuffer = (t_vertex[]){
        {5, 5, 5, "32m█"},      // 0
        {-5, 5, 5, "32m█"},     // 1
        {5, -5, 5, "32m█"},     // 2
        {-5, -5, 5, "32m█"},    // 3
        {5, 5, -5, "32m█"},     // 4
        {-5, 5, -5, "32m█"},    // 5
        {5, -5, -5, "32m█"},    // 6
        {-5, -5, -5, "32m█"}    // 7
    },
    .indexBuffer = (int[]){
        // Front face
        0, 1, 2, 1, 3, 2,
        // Back face
        4, 6, 5, 5, 6, 7,
        // Top face
        0, 4, 1, 1, 4, 5,
        // Bottom face
        2, 3, 6, 3, 7, 6,
        // Right face
        0, 2, 4, 2, 6, 4,
        // Left face
        1, 5, 3, 3, 5, 7,
        0
    }
};

// Cuby mesh - stretched/modified cube (taller)
t_mesh cuby = {
    .VertexCount = 8,
    .IndexCount = 36,
    .Vbuffer = (t_vertex[]){
        {5, 10, 5, "36m█"},     // 0 - taller (y doubled)
        {-5, 10, 5, "36m█"},    // 1
        {5, -10, 5, "36m█"},    // 2
        {-5, -10, 5, "36m█"},   // 3
        {5, 10, -5, "36m█"},    // 4
        {-5, 10, -5, "36m█"},   // 5
        {5, -10, -5, "36m█"},   // 6
        {-5, -10, -5, "36m█"}   // 7
    },
    .indexBuffer = (int[]){
        // Front face
        0, 1, 2, 1, 3, 2,
        // Back face
        4, 6, 5, 5, 6, 7,
        // Top face
        0, 4, 1, 1, 4, 5,
        // Bottom face
        2, 3, 6, 3, 7, 6,
        // Right face
        0, 2, 4, 2, 6, 4,
        // Left face
        1, 5, 3, 3, 5, 7,
        0
    }
};