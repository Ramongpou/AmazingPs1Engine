#ifndef _DC_LEVEL_
#define _DC_LEVEL_
#include "dcRender.h"
#include <stdlib.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

typedef struct SDC_Object SDC_Object;

typedef struct SDC_Object
{
    VECTOR Location;
    SVECTOR Rotation;
    SDC_Mesh3D* Mesh;
    SDC_DrawParams* DrawParams;
    SDC_Object* Parent;
}SDC_Object;


typedef struct 
{
    int bShot;
    int bIsAiming;
    int bShooting;
    int PlayerIndex;
    VECTOR Location;
    SVECTOR Rotation;
    SDC_Mesh3D* Mesh;
    SVECTOR Direction;
    SDC_DrawParams* DrawParams;
    //TEXTURE
    //Life
    //Speed
    //.
    //.
    //.
}SDC_Character;

typedef struct SDC_Projectile
{
    int Vox;
    int Voy;
    VECTOR Location;
    SVECTOR Rotation;
    SDC_Mesh3D* Mesh;
    SVECTOR Direction;
    SDC_DrawParams* DrawParams;
}SDC_Projectile;

typedef struct SDC_Level
{
    SDC_Object** Objects;
    SDC_Projectile** Projectiles;
    SDC_Character** Characters;
    int NumCharacters;
    int NumObjects;
    int NumProjectiles;
    int MaxObjects;

// Back color  
CVECTOR  AmbientColor;
// Light rotation angle - used to calculate the world direction of the light in each object
SVECTOR LightAngle; 
// These will be used to store the light rotation matrix, cube rotation matrix, and composite light matrix.
MATRIX  RotLight, RotObject, WorldLightMatrix;
  
 // Local Light Matrix : Direction and reach of each light source. 
// Each light points in the direction aligned with the axis, hence direction is in the same coordinate system as the PSX (see l.23-30 of this file)
// Negative/positive value denotes light direction on corresponding axis
// -4096 > Value < 4096 denotes reach/intensity of light source
MATRIX LocalLightMatrix;
// Local Color Matrix
// Set color of each light source (L)
// Value range : 0 > x < 4096
MATRIX ColorMatrix;    
}SDC_Level;


void dcLevel_InitLight(SDC_Level* Level, CVECTOR* AmbientColor);
void dcLevel_SetLight(SDC_Level* Level, int LightIndex, SVECTOR* LightDirection, SVECTOR* LightColor);
SDC_Object* dcLevel_AddObject(SDC_Level* Level, SDC_Mesh3D* Mesh, VECTOR* Location, SDC_DrawParams* DrawParams, SDC_Object* Parent);

void dcLevel_InitProjectile(SDC_Level *Level, SDC_Mesh3D *Mesh, VECTOR *Location, SDC_DrawParams *DrawParams);

void dcLevel_InitCharacter(SDC_Level* Level, SDC_Mesh3D* Mesh, VECTOR* Location, SDC_DrawParams* DrawParams);
void GetParentTransform(SDC_Object* Object, MATRIX* Transform, MATRIX* OutTransform);

#endif /* _DC_LEVEL_H */
