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


	void AddGravParticle(CGravParticle* _gParticlePtr);
	void RemoveGravParticle(CGravParticle* _gParticlePtr);

private:
	static int maxNumOfGravParticles;
	CGravParticle* gParticles[maxNumOfGravParticles];

};

#endif CGRAVPARTICLEHANDLER
