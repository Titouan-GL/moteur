#include "proceduralterrain.h"

void ProceduralTerrain::InitMesh(int resX, int resY , float sizeX , float sizeY, float sizeZ){
    direction = glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f));
    center = glm::vec3(sizeX/2.0, 0.0f, sizeY/2.0);
    this->resX = resX;
    this->resY = resY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->sizeZ = sizeZ;

    vertices = std::vector<Vertex>() ;
    triangles = std::vector<Triangle>();
    for(int i = 0; i < resX+1; i ++){
        for(int j = 0; j < resY+1; j++){
            float height = static_cast <float> (rand()) / (static_cast <float> ((float)RAND_MAX/sizeZ));
            Vertex v(glm::vec3(i*(sizeX/resX), height, j*(sizeY/resY)));
            v.texCoord = glm::vec2(i*(sizeX/resX), j*(sizeY/resY));
            vertices.push_back(v);
            if(i > 0 && j > 0){
                int i0 = (i-1)*(resY+1)+j-1;
                int i1 = (i-1)*(resY+1)+j;
                int i2 = (i)*(resY+1)+j;
                int i3 = (i)*(resY+1)+j-1;
                triangles.push_back(Triangle(i0, i1, i2));
                triangles.push_back(Triangle(i2, i3, i0));
            }
        }
    }
    recomputeSmoothVertexNormals(1);
    _synchronized = false;
}

void ProceduralTerrain::ApplyHeightMap(std::string hmapName, float scale){
    this->hmapName = hmapName;
    Texture hmap = Texture(hmapName);
    for(int i = 0; i < vertices.size(); i ++){
        Color c = hmap.getPixelSafe(vertices[i].position[0]/sizeX, vertices[i].position[2]/sizeY);
        vertices[i].position[1] = ((float)c.g/255.0) * scale;
    }
    recomputeSmoothVertexNormals(1);
}
