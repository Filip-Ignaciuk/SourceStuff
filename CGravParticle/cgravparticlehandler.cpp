#include "cbase.h"
#include "cgravparticlehandler.hpp"

#include "cgravparticle.hpp"
#include <vector>


LINK_ENTITY_TO_CLASS(grav_handler, CGravParticleHandler);

// Start of our data description for the class
BEGIN_DATADESC(CGravParticleHandler)

DEFINE_THINKFUNC(MoveThink),

DEFINE_FIELD(maxNumOfGravParticles, FIELD_INTEGER),



END_DATADESC()


//-----------------------------------------------------------------------------
// Purpose: Think function to do physics calculations
//-----------------------------------------------------------------------------
void CGravParticleHandler::MoveThink(void)
{
	// We start at one as we are just going to do every calculation with the first object
	Vector firstObjectVector;
	Vector vFirstObjectInitialVelocity;
	float firstObjectMass;


	float secondObjectMass;
	bool hasFirstObject = false;

	for (int i = 0; i < 64; i++)
	{
		if(gParticles[i] && !hasFirstObject)
		{
			firstObjectVector = gParticles[0]->GetAbsOrigin();
			vFirstObjectInitialVelocity = gParticles[0]->GetAbsVelocity();
			firstObjectMass = PhysGetEntityMass(gParticles[0]);
			hasFirstObject = true;
		}
		else if (hasFirstObject)
		{
			CGravParticle* gParticle = gParticles[i];
			if (gParticle)
			{
				Vector secondObjectVector = gParticle->GetAbsOrigin();
				if (gParticle->GetMass() == 0.0f)
				{
					secondObjectMass = PhysGetEntityMass(gParticle);
				}
				else
				{
					secondObjectMass = gParticle->GetMass();
				}
				float distance = firstObjectVector.DistTo(secondObjectVector);
				// Final force
				float force = gravConst * firstObjectMass * secondObjectMass / distance;


				// For first object
				float firstObjectAcceleration = force / firstObjectMass;
				float fFirstObjectInitialVelocity = Sqr((vFirstObjectInitialVelocity.x * vFirstObjectInitialVelocity.x) + (vFirstObjectInitialVelocity.y * vFirstObjectInitialVelocity.y) + (vFirstObjectInitialVelocity.z * vFirstObjectInitialVelocity.z));
				float firstObjectVelocity = fFirstObjectInitialVelocity + firstObjectAcceleration * 0.05;
				float equalVector = cbrt(firstObjectVelocity);
				Vector finalForce(equalVector, equalVector, equalVector);


				// Second Object


			}
		}

		

	}

	

	// Think at 20 times per second
	SetNextThink(gpGlobals->curtime + 0.05f);
}

//-----------------------------------------------------------------------------
// Purpose: Adding particle to list.
//-----------------------------------------------------------------------------
void CGravParticleHandler::AddGravParticle(CGravParticle* _gParticlePtr)
{
	// Check if it's not null
	if(_gParticlePtr)
	{
		for (int i = 0; i < 64; i++)
		{
			if (!gParticles[i])
			{
				gParticles[i] = _gParticlePtr;
				break;
			}
		}
	}
}

void CGravParticleHandler::RemoveGravParticle(CGravParticle* _gParticlePtr)
{
	// Check if it's not null
	if (_gParticlePtr)
	{
		for (int i = 0; i < 64; i++)
		{
			if(gParticles[i] == _gParticlePtr)
			{
				gParticles[i] = nullptr;
				break;
			}
		}
	}
}
