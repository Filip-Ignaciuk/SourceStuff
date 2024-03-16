#ifndef CGRAVPARTICLEHANDLER
#define CGRAVPARTICLEHANDLER
#include "cgravparticlehandler.hpp"
#include "cgravparticle.hpp"
#include "cmath"

class CGravParticleHandler : public CLogicalEntity
{
public:
	DECLARE_CLASS(CGravParticleHandler, CLogicalEntity);
	DECLARE_DATADESC();

	// Constructor
	CGravParticleHandler()
	{
		SetThink(&CGravParticleHandler::Think);
		SetNextThink(gpGlobals->curtime);
		inUse = false;
	}

	void Think(void);


	void AddGravParticle(CBaseEntity* _gParticlePtr);
	void RemoveGravParticle(CBaseEntity* _gParticlePtr);

private:
	float gravConst = 6.6743 * pow(10, -11) * 61020.0f; // convert from metres cubed to inches cubed
	bool inUse;
	float multiplier;
	CBaseEntity* gParticles[64];

};

#endif CGRAVPARTICLEHANDLER
