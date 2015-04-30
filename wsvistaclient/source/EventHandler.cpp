#include "EventHandler.h"

#include <VistaKernel/GraphicsManager/VistaTransformNode.h>

#include <zeq/zeq.h>
#include <zeq/receiver.h>
#include <lunchbox/uri.h>
#include <wsvoc/vocabulary.h>
#include<boost/bind.hpp>

#include <functional>

EventHandler::EventHandler(VistaTransformNode *pNode)
	:m_pTransNode(pNode)
	, m_subscriber(new zeq::Subscriber(lunchbox::URI("ws://137.226.49.137:8888")))
{
	m_subscriber->registerHandler(wsvoc::EVENT_VECTOR3D, std::bind(&EventHandler::OnVector3DEvent, this, std::placeholders::_1));
}

EventHandler::~EventHandler()
{}

void EventHandler::Notify(const VistaEvent *pEvent)
{
	if (m_subscriber->receive(0))
	{
		;
	}
}

void EventHandler::OnVector3DEvent(const zeq::Event& newEvent)
{
	wsvoc::data::Vector3d v3 = wsvoc::deserializeVector3d(newEvent);
	VistaVector3D v3Trans;
	v3Trans[0] = v3.x;
	v3Trans[1] = v3.y;
	v3Trans[2] = v3.z;
	std::cout << "receive: " << v3Trans << std::endl;
	v3Trans[2] = 0 - v3Trans[2];
	m_pTransNode->SetTranslation(v3Trans);
}
