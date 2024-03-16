#include "cbase.h"
#include "cgravparticlehandler.hpp"

#include <string>

#include "cgravparticle.hpp"


LINK_ENTITY_TO_CLASS(grav_handler, CGravParticleHandler);

// Start of our data description for the class
BEGIN_DATADESC(CGravParticleHandler)

DEFINE_THINKFUNC(Think),
DEFINE_FIELD(gravConst, FIELD_FLOAT),
DEFINE_FIELD(inUse, FIELD_BOOLEAN),
DEFINE_FIELD(multiplier, FIELD_FLOAT),

DEFINE_AUTO_ARRAY(gParticles, FIELD_CLASSPTR),


DEFINE_KEYFIELD(multiplier, FIELD_FLOAT, "multiplier"),

END_DATADESC()


//-----------------------------------------------------------------------------
// Purpose: Think function to do physics calculations
//-----------------------------------------------------------------------------
void CGravParticleHandler::Think(void)
{
	// We start at one as we are just going to do every calculation with the first object
	Vector firstObjectPosition;
	float firstObjectMass;
	
	Vector secondObjectPosition;
	float secondObjectMass;
	
	// Make sure we aren't writing simultaneously

	while (inUse)
	{
		
	}
	inUse = true;

	for (int i = 0; i < 64; i++)
	{
		CBaseEntity* base1 = gParticles[i];
		if (base1)
		{
			CGravParticle* gParticle1 = dynamic_cast<CGravParticle*>(base1);
			if(!gParticle1->IsActivated())
			{
				continue;
			}

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
				if(i == j)
				{
					continue;
				}
				CBaseEntity* base2= gParticles[j];
				

				if (base2)
				{
					CGravParticle* gParticle2 = dynamic_cast<CGravParticle*>(base2);
					if (!gParticle2->IsActivated())
					{
						continue;
					}

	
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


					Vector direction = secondObjectPosition - firstObjectPosition;
					Vector forceMultiplier(force, force, force);
					
					direction = direction.Normalized();
					
					if (multiplier != 0.0f)
					{
						std::string mulki = std::to_string(multiplier);

						DevMsg(mulki.c_str());
						Vector final = direction * forceMultiplier * -1 * multiplier;

						DevMsg("\nX: ");
						std::string x = std::to_string(final.x);
						DevMsg(x.c_str());
						DevMsg("\nY: ");
						std::string y = std::to_string(final.y);
						DevMsg(y.c_str());
						DevMsg("\nZ: ");
						std::string z = std::to_string(final.z);
						DevMsg(z.c_str());
						gParticle1->SetAbsOrigin(final);

					}
					else
					{
						Vector final = direction * forceMultiplier * -1;
						DevMsg("X: ");
						std::string x = std::to_string(final.x);
						DevMsg(x.c_str());
						DevMsg("\nY: ");
						std::string y = std::to_string(final.y);
						DevMsg(y.c_str());
						DevMsg("\nZ: ");
						std::string z = std::to_string(final.z);
						DevMsg(z.c_str());
						gParticle1->SetAbsOrigin(final);

					}


	
				}
	
	
			}
	
	
		}
	
		
	
		
	
	}
	inUse = false;
	

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
		while (inUse)
		{
	
		}
		inUse = true;
		CGravParticle* gParticlePtr = dynamic_cast<CGravParticle*>(_basePtr);
		for (int i = 0; i < 64; i++)
		{
			if (!gParticles[i])
			{
				gParticles[i] = gParticlePtr;
				break;
			}
		}
		inUse = false;
	}
}

void CGravParticleHandler::RemoveGravParticle(CBaseEntity* _basePtr)
{
	// Check if it's not null
	if (_basePtr)
	{
		while (inUse)
		{
	
		}
		inUse = true;
		CGravParticle* gParticlePtr = dynamic_cast<CGravParticle*>(_basePtr);
	
		for (int i = 0; i < 64; i++)
		{
			if(gParticles[i] == gParticlePtr)
			{
				gParticles[i] = nullptr;
				break;
			}
		}
		inUse = false;
	}
	
}
