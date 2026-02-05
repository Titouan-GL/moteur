#ifndef PROCEDURALTERRAIN_H
#define PROCEDURALTERRAIN_H

#include "../Mesh.hpp"

class ProceduralTerrain : public Mesh
{
public:
    void InitMesh(int resX = 16, int resY = 16, float sizeX = 16, float sizeY = 16, float sizeZ = 1);
    void ApplyHeightMap(std::string hmapName, float scale = 1);
private:
    int resX;
    int resY;
    float sizeX;
    float sizeY;
    float sizeZ;
    std::string hmapName;
};

#endif // PROCEDURALTERRAIN_H
