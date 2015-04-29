#include <VistaAspects/VistaExplicitCallbackInterface.h>

#include <VistaTools/VistaRandomNumberGenerator.h>
#include <VistaKernel/VistaSystem.h>

#include <zeq/zeq.h>
#include <zeq/event.h>
#include <zeq/publisher.h>
#include <lunchbox/uri.h>
#include <wsvoc/vocabulary.h>

class ActivationCallback : public IVistaExplicitCallbackInterface
{
public:
	ActivationCallback(VistaSystem *pSystem)
		: m_pSystem(pSystem)
		, m_publisher(lunchbox::URI("ws://137.226.49.140:1337"))
	{	};

	bool Do()
	{
		VistaVector3D v3NewPos;
		VistaRandomNumberGenerator *pGen = new VistaRandomNumberGenerator();
		pGen->SetSeed(static_cast<unsigned int> (m_pSystem->GetFrameClock()));
		v3NewPos[0] = pGen->GenerateFloat3();
		v3NewPos[1] = pGen->GenerateFloat3();
		v3NewPos[2] = pGen->GenerateFloat3();

		std::cout << "sending:: " <<  v3NewPos << std::endl;
		//send this values to be sorted;
		wsvoc::data::Vector3d vec;
		vec.x = v3NewPos[0];
		vec.y = v3NewPos[1];
		vec.z = v3NewPos[2];
		zeq::Event newEvent = wsvoc::serializeVector3d(vec);

		m_publisher.publish(newEvent);

		return true;
	};

private:
	VistaSystem *m_pSystem;
	zeq::Publisher m_publisher;
};
