#include "cbase.h"
#include "cgravparticlehandler.hpp"

#include "cgravparticle.hpp"
#include <vector>


LINK_ENTITY_TO_CLASS(grav_handler, CGravParticleHandler);

// Start of our data description for the class
BEGIN_DATADESC(CGravParticleHandler)

DEFINE_THINKFUNC(MoveThink),

DEFINE_FIELD(maxNumOfGravParticles, FIELD_INTEGER),
DEFINE_AUTO_ARRAY(gParticles, FIELD_CLASSPTR),




END_DATADESC()


//-----------------------------------------------------------------------------
// Purpose: Think function to do physics calculations
//-----------------------------------------------------------------------------
void CGravParticleHandler::MoveThink(void)
{
	// We start at one as we are just going to do every calculation with the first object
	for (int i = 1; i < 64; i++)
	{
		Vector firstObjectVector = gParticles[0]->GetAbsOrigin();
		if(gParticles[i])
		{
			Vector secondObjectVector = gParticles[i]->GetAbsOrigin();

		}

	}

	// Think at 20Hz
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
