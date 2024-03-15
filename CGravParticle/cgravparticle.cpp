#include "cbase.h"
#include "cgravparticle.hpp"

LINK_ENTITY_TO_CLASS(grav_particle, CGravParticle);

BEGIN_DATADESC(CGravParticle)

DEFINE_THINKFUNC(MoveThink),


DEFINE_FIELD(m_active, FIELD_BOOLEAN),
DEFINE_FIELD(m_model, FIELD_MODELNAME),

DEFINE_FIELD(m_mass, FIELD_INTEGER),


// Seen in hammer
DEFINE_INPUT(m_model, FIELD_MODELNAME, "Model"),
DEFINE_KEYFIELD(m_mass, FIELD_FLOAT, "Mass"),

DEFINE_INPUTFUNC(FIELD_VOID, "Toggle", InputToggle),


END_DATADESC()



//-----------------------------------------------------------------------------
// Purpose: Precache assets used by the entity
//-----------------------------------------------------------------------------
void CGravParticle::Precache(void)
{
	PrecacheModel(m_model);

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: Sets up the entity's initial state
//-----------------------------------------------------------------------------
void CGravParticle::Spawn(void)
{
	Precache();

	SetModel(m_model);
	SetSolid(SOLID_VPHYSICS);
	VPhysicsInitNormal(SOLID_VPHYSICS, 0, false);
	CGravParticleHandler* gParticleHandler;

	CBaseEntity* resultPtr = gEntList.FindEntityByClassname(NULL, "grav_handler");
	while (resultPtr)
	{
		gParticleHandler = dynamic_cast<CGravParticleHandler*>(resultPtr);
		gParticleHandler->AddGravParticle(this);

	}


}


//-----------------------------------------------------------------------------
// Purpose: Think function to oscillate the particle
//-----------------------------------------------------------------------------
void CGravParticle::MoveThink(void)
{
	
	// Think at 20Hz
	SetNextThink(gpGlobals->curtime + 0.05f);
}

float CGravParticle::GetMass(void)
{
	return m_mass;
}


//-----------------------------------------------------------------------------
// Purpose: Toggle the movement of the entity
//-----------------------------------------------------------------------------
void CGravParticle::InputToggle(inputdata_t& inputData)
{
	// Toggle our active state
	if (!m_active)
	{
		// Convert from vphysics to our physics.
		DevMsg("Activated\n");
		VPhysicsDestroyObject();
		SetSolid(SOLID_VPHYSICS);
		VPhysicsInitShadow(SOLID_VPHYSICS, 0, false);

		// Start thinking
		SetThink(&CGravParticle::MoveThink);

		SetNextThink(gpGlobals->curtime + 0.05f);

		// Start moving
		SetMoveType(MOVETYPE_FLY);


		// Update m_bActive to reflect our new state
		m_active = true;
	}
	else
	{
		DevMsg("Deactivated\n");
		// Stop thinking
		SetThink(NULL);

		// Stop moving
		SetAbsVelocity(vec3_origin);
		SetMoveType(MOVETYPE_VPHYSICS);

		// Convert from our physics to vphysics.
		VPhysicsDestroyObject();
		SetSolid(SOLID_VPHYSICS);
		VPhysicsInitNormal(SOLID_VPHYSICS, 0, false);

		m_active = false;
	}
}