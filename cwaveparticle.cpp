#include "cbase.h"

#include <string>

#define	ENTITY_MODEL	"models/gibs/airboat_broken_engine.mdl"

class CWaveParticle : public CBaseAnimating
{
public:
	DECLARE_CLASS(CWaveParticle, CBaseAnimating);
	DECLARE_DATADESC();

	CWaveParticle()
	{
		m_active = false;
	}

	void Spawn(void);
	void Precache(void);

	void MoveThink(void);

	// Input function
	void InputToggle(inputdata_t& inputData);

private:

	bool m_active;
	bool m_direction;
	int m_currentVelocity;
	int m_maxVelocity;
};

LINK_ENTITY_TO_CLASS(wave_particle, CWaveParticle);

// Start of our data description for the class
BEGIN_DATADESC(CWaveParticle)

// Save/restore our active state
DEFINE_FIELD(m_active, FIELD_BOOLEAN),
DEFINE_FIELD(m_direction, FIELD_BOOLEAN),
DEFINE_FIELD(m_currentVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_maxVelocity, FIELD_INTEGER),

DEFINE_KEYFIELD(m_maxVelocity, FIELD_INTEGER, "MaxVelocity"),


// Links our input name from Hammer to our input member function
DEFINE_INPUTFUNC(FIELD_VOID, "Toggle", InputToggle),

// Declare our think function
DEFINE_THINKFUNC(MoveThink),

END_DATADESC()


//-----------------------------------------------------------------------------
// Purpose: Precache assets used by the entity
//-----------------------------------------------------------------------------
void CWaveParticle::Precache(void)
{
	PrecacheModel(ENTITY_MODEL);

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: Sets up the entity's initial state
//-----------------------------------------------------------------------------
void CWaveParticle::Spawn(void)
{
	DevLog("Spawned!");
	Precache();

	SetModel(ENTITY_MODEL);
	SetSolid(SOLID_BBOX);
	UTIL_SetSize(this, -Vector(20, 20, 20), Vector(20, 20, 20));
}


//-----------------------------------------------------------------------------
// Purpose: Think function to randomly move the entity
//-----------------------------------------------------------------------------
void CWaveParticle::MoveThink(void)
{
	std::string currentVelocityMessage = std::to_string(m_currentVelocity);
	DevLog(currentVelocityMessage.c_str());
	if(m_currentVelocity == m_maxVelocity || m_currentVelocity == -m_maxVelocity)
	{
		if(m_direction)
		{
			m_direction = 0;
		}
		else
		{
			m_direction = 1;
		}
	}

	if(m_direction)
	{
		m_currentVelocity -= 10;
	}
	else
	{
		m_currentVelocity += 10;
	}

	Vector move(0, 0, m_currentVelocity);
	
	SetAbsVelocity(move);

	// Think at 20Hz
	SetNextThink(gpGlobals->curtime + 0.05f);
}

//-----------------------------------------------------------------------------
// Purpose: Toggle the movement of the entity
//-----------------------------------------------------------------------------
void CWaveParticle::InputToggle(inputdata_t& inputData)
{
	DevMsg("Hello");
	// Toggle our active state
	if (!m_active)
	{
		DevMsg("Activated");
		m_currentVelocity = m_maxVelocity;
		// Start thinking
		SetThink(&CWaveParticle::MoveThink);

		SetNextThink(gpGlobals->curtime + 0.05f);

		// Start moving
		SetMoveType(MOVETYPE_FLY);


		// Update m_bActive to reflect our new state
		m_active = true;
	}
	else
	{
		// Stop thinking
		SetThink(NULL);

		// Stop moving
		SetAbsVelocity(vec3_origin);
		SetMoveType(MOVETYPE_NONE);

		m_active = false;
	}
}