#ifndef CGRAVPARTICLEHANDLER
#define CGRAVPARTICLEHANDLER
#include "cgravparticlehandler.hpp"
#include "cgravparticle.hpp"

class CGravParticleHandler : public CLogicalEntity
{
public:
	DECLARE_CLASS(CGravParticleHandler, CLogicalEntity);
	DECLARE_DATADESC();

	// Constructor
	CGravParticleHandler()
	{
		SetThink(&CGravParticleHandler::MoveThink);

	}

	void MoveThink(void);


	void AddGravParticle(CBaseEntity* _gParticlePtr);
	void RemoveGravParticle(CBaseEntity* _gParticlePtr);

private:
	float gravConst = -9.81f;
	CBaseEntity* gParticles[64];

};

#endif CGRAVPARTICLEHANDLER
