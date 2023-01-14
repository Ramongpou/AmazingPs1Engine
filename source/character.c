#include "character.h"

void UpdateCharacter(SDC_Character* Character)
{
    int PlayerIndex = Character->PlayerIndex;
    u_long PadState = PadRead(0);

    if ( Character->bIsAiming ==  1)
    {
        Character->bShooting = 1;
    }

    SVECTOR IncrementalPosition = {0,0,0};
    if( _PAD(PlayerIndex,PADLup ) & PadState )
    {
        IncrementalPosition.vz -=10;
    }
    if( _PAD(PlayerIndex,PADLdown ) & PadState )
    {
        IncrementalPosition.vz +=10;
    }
    if( _PAD(PlayerIndex,PADLright ) & PadState )
    {
        IncrementalPosition.vx +=10;
    }
    if( _PAD(PlayerIndex,PADLleft ) & PadState )
    {
        IncrementalPosition.vx -=10;
    }
    if( _PAD(PlayerIndex,PADL1 ) & PadState )
    {
        if(Character->bIsAiming == 0)
        {
            printf("Aiming! %d \n",  PlayerIndex );
            Character->bIsAiming = 1;
        }
        else{
            Character->bShooting = 0;
        }

    }
    if( _PAD(0,PADRup ) & PadState )
    {
    }
    if( _PAD(0,PADRdown ) & PadState )
    {
    }
    if( _PAD(0,PADRright ) & PadState )
    {
    }
    if( _PAD(0,PADRleft ) & PadState )
    {
    }
    if(  Character->bShooting == 1)
    {
        Character->bShooting = 0;
        Character->bIsAiming = 0;
        Character->bShot = 1;
        printf(" Stop Shooting!\n");

    
    }
    if(IncrementalPosition.vx != 0 || IncrementalPosition.vz != 0)
    {
        
    SVECTOR Dir;    
    VectorNormalSS(&IncrementalPosition, &Dir);
    SVECTOR Diff = {Dir.vx -  Character->Direction.vx,Dir.vy -  Character->Direction.vy,Dir.vz -  Character->Direction.vz};
    int LerpSpeed = 8;
    SVECTOR DIffDivided = {Diff.vx / LerpSpeed, Diff.vy / LerpSpeed, Diff.vz / LerpSpeed};
    SVECTOR Summ = {Character->Direction.vx + DIffDivided.vx, Character->Direction.vy + DIffDivided.vy, Character->Direction.vz + DIffDivided.vz};
    Character->Direction =  Summ;

    long atan2 = ratan2(Character->Direction.vx, Character->Direction.vz);

    Character->Rotation.vy = atan2;
    Character->Location.vx += IncrementalPosition.vx;    
    Character->Location.vz += IncrementalPosition.vz;

    }
}
