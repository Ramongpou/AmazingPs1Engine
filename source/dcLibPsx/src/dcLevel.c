#include "dcLevel.h"
#include "dcRender.h"
#include <malloc.h>
#include <libetc.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

void dcLevel_InitLight(SDC_Level *Level, CVECTOR *AmbientColor)
{
    Level->AmbientColor = *AmbientColor;
}

//Maybe we should use the Render SetLightFunction, but this way maybe we can store more easy the light info of every level (?)
void dcLevel_SetLight(SDC_Level* Level, int LightIndex, SVECTOR* LightDirection, SVECTOR* LightColor)
{
    if(LightIndex >= 3)
    {
        //BRO :(
        return;
    }

    Level->LocalLightMatrix.m[LightIndex][0]= LightDirection->vx;
    Level->LocalLightMatrix.m[LightIndex][1]= LightDirection->vy;
    Level->LocalLightMatrix.m[LightIndex][2]= LightDirection->vz;

    Level->ColorMatrix.m[0][LightIndex] = LightColor->vx;
    Level->ColorMatrix.m[1][LightIndex] = LightColor->vy;
    Level->ColorMatrix.m[2][LightIndex] = LightColor->vz;

}

SDC_Object* dcLevel_AddObject(SDC_Level *Level, SDC_Mesh3D* Mesh, VECTOR* Location, SDC_DrawParams* DrawParams, SDC_Object* Parent)
{
    SDC_Object* Obj = malloc3(sizeof(SDC_Object));
    Obj->Location = *Location; //<----- to Transform
    SVECTOR Rot = {0,0,0};
    Obj->Rotation =Rot;
    Obj->Mesh = Mesh;
    Obj->DrawParams = DrawParams;
    Obj->Parent = Parent;
    
    //Malloc for every object? or with MaxArray size?
    Level->Objects = realloc3(Level->Objects, (Level->NumObjects + 1) * sizeof(SDC_Object*));

    Level->Objects[Level->NumObjects] = Obj;    
    Level->NumObjects++;
    Level->MaxObjects++;   
    return Obj;
}
void dcLevel_InitProjectile(SDC_Level *Level, SDC_Mesh3D *Mesh, VECTOR *Location, SDC_DrawParams *DrawParams)
{   
    SDC_Projectile* NewProjectile = malloc3(sizeof(SDC_Projectile));
    NewProjectile->Location = *Location; //<----- to Transform
    SVECTOR Rot = {0,0,0};
    NewProjectile->Rotation =Rot;
    NewProjectile->Mesh = Mesh;
    NewProjectile->DrawParams = DrawParams;
    NewProjectile->Vox = 10;
    NewProjectile->Voy = 10;
   // NewProjectile->Init;
    //NewProjectile->PlayerIndex = Level->NumCharacters;
    //Malloc for every object? or with MaxArray size?
    Level->Projectiles[Level->NumProjectiles] = NewProjectile;    
    Level->NumProjectiles++;
}

void dcLevel_InitCharacter(SDC_Level *Level, SDC_Mesh3D *Mesh, VECTOR *Location, SDC_DrawParams *DrawParams)
{   
    SDC_Character* NewCharacter = malloc3(sizeof(SDC_Character));
    NewCharacter->Location = *Location; //<----- to Transform
    SVECTOR Rot = {0,0,0};
    NewCharacter->Rotation =Rot;
    NewCharacter->Mesh = Mesh;
    NewCharacter->DrawParams = DrawParams;
    NewCharacter->PlayerIndex = Level->NumCharacters;
    //Malloc for every object? or with MaxArray size?
    Level->Characters = realloc3(Level->Characters, (Level->NumCharacters + 1) * sizeof(SDC_Object*));

    Level->Characters[Level->NumCharacters] = NewCharacter;    
    Level->NumCharacters++;
}


void GetParentTransform(SDC_Object* Object, MATRIX *Transform, MATRIX *OutTransform)
{ 
    if(Object->Parent != NULL)
    {
        GetParentTransform(Object->Parent, Transform, OutTransform);        
        CompMatrix(OutTransform, Transform, OutTransform);        
    }
    else
    {
        RotMatrix(&Object->Rotation, OutTransform);
        TransMatrix(OutTransform, &Object->Location);
    }
}
