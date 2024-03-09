#include "cbase.h"
#define	ENTITY_MODEL	"models/particle/particle.mdl"

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

	void InputToggle(inputdata_t& inputData);

private:

	bool m_active;

	bool m_xDirection;
	bool m_yDirection;
	bool m_zDirection;

	int m_currentXVelocity;
	int m_currentYVelocity;
	int m_currentZVelocity;

	int m_changeInXVelocity;
	int m_changeInYVelocity;
	int m_changeInZVelocity;

	int m_maxXVelocity;
	int m_maxYVelocity;
	int m_maxZVelocity;
};

LINK_ENTITY_TO_CLASS(wave_particle, CWaveParticle);

BEGIN_DATADESC(CWaveParticle)

DEFINE_FIELD(m_active, FIELD_BOOLEAN),


DEFINE_FIELD(m_xDirection, FIELD_BOOLEAN),
DEFINE_FIELD(m_yDirection, FIELD_BOOLEAN),
DEFINE_FIELD(m_zDirection, FIELD_BOOLEAN),


DEFINE_FIELD(m_currentXVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_currentYVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_changeInZVelocity, FIELD_INTEGER),

DEFINE_FIELD(m_changeInXVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_changeInYVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_changeInZVelocity, FIELD_INTEGER),

DEFINE_FIELD(m_maxXVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_maxYVelocity, FIELD_INTEGER),
DEFINE_FIELD(m_maxZVelocity, FIELD_INTEGER),

// Seen in hammer

DEFINE_KEYFIELD(m_maxXVelocity, FIELD_INTEGER, "MaxXVelocity"),
DEFINE_KEYFIELD(m_maxYVelocity, FIELD_INTEGER, "MaxYVelocity"),
DEFINE_KEYFIELD(m_maxZVelocity, FIELD_INTEGER, "MaxZVelocity"),

DEFINE_KEYFIELD(m_changeInXVelocity, FIELD_INTEGER, "ChangeInXVelocity"),
DEFINE_KEYFIELD(m_changeInYVelocity, FIELD_INTEGER, "ChangeInYVelocity"),
DEFINE_KEYFIELD(m_changeInZVelocity, FIELD_INTEGER, "ChangeInZVelocity"),

DEFINE_INPUTFUNC(FIELD_VOID, "Toggle", InputToggle),

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
	DevLog("Spawned!\n");
	Precache();

	SetModel(ENTITY_MODEL);
	SetSolid(SOLID_BBOX);
	UTIL_SetSize(this, -Vector(20, 20, 20), Vector(20, 20, 20));
}


//-----------------------------------------------------------------------------
// Purpose: Think function to oscillate the particle
//-----------------------------------------------------------------------------
void CWaveParticle::MoveThink(void)
{
	
	// Checking if any particles are at their limit.
	// If so reverse direction.
	

	// This occurs if the max velocity and change in velocity are multiple of one another.
	if (m_currentXVelocity == m_maxXVelocity || m_currentXVelocity == -m_maxXVelocity)
	{
		if (m_xDirection)
		{
			m_xDirection = 0;
		}
		else
		{
			m_xDirection = 1;
		}
	}


	// This occurs if the max velocity and change in velocity are not multiples of one another.
	
	if (m_currentXVelocity > m_maxXVelocity || m_currentXVelocity < -m_maxXVelocity)
	{
		if (m_xDirection)
		{
			m_xDirection = 0;
			m_currentXVelocity = -m_maxXVelocity;
		}
		else
		{
			m_xDirection = 1;
			m_currentXVelocity = m_maxXVelocity;
		}
	}

	if (m_currentYVelocity == m_maxYVelocity || m_currentYVelocity == -m_maxYVelocity)
	{
		if (m_yDirection)
		{
			m_yDirection = 0;
		}
		else
		{
			m_yDirection = 1;
		}
	}

	if (m_currentYVelocity > m_maxYVelocity || m_currentYVelocity < -m_maxYVelocity)
	{
		if (m_xDirection)
		{
			m_xDirection = 0;
			m_currentYVelocity = -m_maxYVelocity;
		}
		else
		{
			m_xDirection = 1;
			m_currentYVelocity = m_maxYVelocity;
		}
	}


	if (m_currentZVelocity == m_maxZVelocity || m_currentZVelocity == -m_maxZVelocity)
	{
		if (m_zDirection)
		{
			m_zDirection = 0;
		}
		else
		{
			m_zDirection = 1;
		}
	}

	if (m_currentZVelocity > m_maxZVelocity || m_currentZVelocity < -m_maxZVelocity)
	{
		if (m_xDirection)
		{
			m_xDirection = 0;
			m_currentZVelocity = -m_maxZVelocity;
		}
		else
		{
			m_xDirection = 1;
			m_currentZVelocity = m_maxZVelocity;
		}
	}

	

	
	// Apply motion

	if(m_xDirection)
	{
		m_currentXVelocity -= m_changeInXVelocity;
	}
	else
	{
		m_currentXVelocity += m_changeInXVelocity;
	}

	if (m_yDirection)
	{
		m_currentYVelocity -= m_changeInYVelocity;
	}
	else
	{
		m_currentYVelocity += m_changeInYVelocity;
	}

	if (m_zDirection)
	{
		m_currentZVelocity -= m_changeInZVelocity;
	}
	else
	{
		m_currentZVelocity += m_changeInZVelocity;
	}

	Vector move(m_currentXVelocity, m_currentYVelocity, m_currentZVelocity);
	
	SetAbsVelocity(move);

	// Think at 20Hz
	SetNextThink(gpGlobals->curtime + 0.05f);
}

//-----------------------------------------------------------------------------
// Purpose: Toggle the movement of the entity
//-----------------------------------------------------------------------------
void CWaveParticle::InputToggle(inputdata_t& inputData)
{
	// Toggle our active state
	if (!m_active)
	{
		DevMsg("Activated\n");
		m_currentXVelocity = m_maxXVelocity;
		m_currentYVelocity = m_maxYVelocity;
		m_currentZVelocity = m_maxZVelocity;

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
		DevMsg("Deactivated\n");
		// Stop thinking
		SetThink(NULL);

		// Stop moving
		SetAbsVelocity(vec3_origin);
		SetMoveType(MOVETYPE_NONE);

		m_active = false;
	}
}