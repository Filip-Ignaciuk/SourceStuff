#include "cbase.h"
#include "cgravparticlehandler.hpp"

#include "cgravparticle.hpp"
#include <vector>


LINK_ENTITY_TO_CLASS(grav_handler, CGravParticleHandler);

// Start of our data description for the class
BEGIN_DATADESC(CGravParticleHandler)

DEFINE_THINKFUNC(MoveThink),



END_DATADESC()


//-----------------------------------------------------------------------------
// Purpose: Think function to do physics calculations
//-----------------------------------------------------------------------------
void CGravParticleHandler::MoveThink(void)
{
	// We start at one as we are just going to do every calculation with the first object
	Vector firstObjectPosition;
	float firstObjectMass;

	Vector secondObjectPosition;
	float secondObjectMass;

	for (int i = 0; i < 64; i++)
	{
		CBaseEntity* base1 = gParticles[i];
		if (base1)
		{
			CGravParticle* gParticle1 = dynamic_cast<CGravParticle*>(base1);
			firstObjectPosition = gParticle1->GetAbsOrigin();
			if (gParticle1->GetMass() == 0.0f)
			{
				firstObjectMass = PhysGetEntityMass(gParticle1);
			}
			else
			{
				firstObjectMass = gParticle1->GetMass();
			}


			for (int j = 0; j < 64; j++)
			{
				CBaseEntity* base2= gParticles[j];

				if (base2)
				{
					CGravParticle* gParticle2 = dynamic_cast<CGravParticle*>(base1);

					secondObjectPosition = gParticle2->GetAbsOrigin();
					if (gParticle2->GetMass() == 0.0f)
					{
						secondObjectMass = PhysGetEntityMass(gParticle2);
					}
					else
					{
						secondObjectMass = gParticle2->GetMass();
					}


					float distance = firstObjectPosition.DistTo(secondObjectPosition);
					// Final force
					float force = gravConst * firstObjectMass * secondObjectMass / distance;
					Vector direction = firstObjectPosition - secondObjectPosition;
					direction = direction.Normalized() * force;
					gParticle1->ApplyAbsVelocityImpulse(direction);


				}


			}


		}

		

		

	}

	

	// Think at 20 times per second
	SetNextThink(gpGlobals->curtime + 0.05f);
}

//-----------------------------------------------------------------------------
// Purpose: Adding particle to list.
//-----------------------------------------------------------------------------
void CGravParticleHandler::AddGravParticle(CBaseEntity* _basePtr)
{
	// Check if it's not null
	if(_basePtr)
	{
		CGravParticle* gParticlePtr = dynamic_cast<CGravParticle*>(_basePtr);
		for (int i = 0; i < 64; i++)
		{
			if (!gParticles[i])
			{
				gParticles[i] = gParticlePtr;
				break;
			}
		}
	}
}

void CGravParticleHandler::RemoveGravParticle(CBaseEntity* _basePtr)
{
	// Check if it's not null
	if (_basePtr)
	{
		CGravParticle* gParticlePtr = dynamic_cast<CGravParticle*>(_basePtr);

		for (int i = 0; i < 64; i++)
		{
			if(gParticles[i] == gParticlePtr)
			{
				gParticles[i] = nullptr;
				break;
			}
		}
	}
}
