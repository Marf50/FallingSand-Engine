#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

// Utility functions for Perlin Noise
float Fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float Lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float Grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// Permutation array (256 values + a repeated set for overflow protection)
int p[512];  // Need 512 values, as we'll mirror the first 256 for overflow protection

void InitNoise(int seed) {
    std::vector<int> permutation(256);
    for (int i = 0; i < 256; ++i)
        permutation[i] = i;

    // Shuffle permutation array based on the seed
    std::mt19937 rng(seed);  // Mersenne Twister RNG seeded
    std::shuffle(permutation.begin(), permutation.end(), rng);

    // Fill p[] with shuffled values
    for (int i = 0; i < 256; ++i) {
        p[i] = permutation[i];
        p[256 + i] = p[i];  // Repeat for overflow protection
    }
}

float PerlinNoise2D(float x, float y, int seed) {
    InitNoise(seed);  // Initialize the permutation array using the seed

    int X = (int)floor(x) & 255;  // Get integer value and wrap within [0, 255]
    int Y = (int)floor(y) & 255;

    x -= floor(x);  // Get fractional part
    y -= floor(y);

    float u = Fade(x);  // Apply fade function to smooth out transitions
    float v = Fade(y);

    // Hash coordinates of the 4 corners of the grid
    int a = p[X] + Y;
    int b = p[X + 1] + Y;

    // Blend results using the fade and gradient functions
    return Lerp(v, Lerp(u, Grad(p[a], x, y), Grad(p[b], x - 1, y)),
        Lerp(u, Grad(p[a + 1], x, y - 1), Grad(p[b + 1], x - 1, y - 1)));
}