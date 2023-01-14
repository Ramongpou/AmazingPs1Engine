#include "projectile.h"

void UpdateProjectile(SDC_Projectile* Projectile)
{
     Projectile->Location.vx +=Projectile->Vox ;
     Projectile->Location.vy += Projectile->Voy - 10;
}