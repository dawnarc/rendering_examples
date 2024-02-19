#pragma once


#define GLM_FORCE_RADIANS


class VBOTorus
{
private:
    unsigned int vaoHandle;
    int faces, rings, sides;

    void generateVerts(float *, float *, float *, unsigned int *,
        float, float);

public:
    VBOTorus(float, float, int, int);

    void render() const;

    int getVertexArrayHandle();
};