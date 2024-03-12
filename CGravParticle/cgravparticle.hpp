#ifndef CGRAVPARTICLE
#define CGRAVPARTICLE
#include "cgravparticle.hpp"
#include "cgravparticlehandler.hpp"

class CGravParticle : public CBaseAnimating
{
public:
	DECLARE_CLASS(CGravParticle, CBaseAnimating);
	DECLARE_DATADESC();

	CGravParticle()
	{
		m_active = false;
	}

	void Spawn(void);
	void Precache(void);

	void MoveThink(void);

	void InputToggle(inputdata_t& inputData);

private:

	bool m_active;
	static char* m_model;
	CGravParticleHandler* gParticleHandler;

	int m_mass;
};

#endif CGRAVPARTICLE