#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <VistaKernel/EventManager/VistaEventObserver.h>
#include <zeq/subscriber.h>
#include <zeq/event.h>

class VistaTransformNode;

class EventHandler : public VistaEventObserver
{
public:
	EventHandler(VistaTransformNode *pNode);
	virtual ~EventHandler();

	virtual void Notify(const VistaEvent *pEvent);
	void OnVector3DEvent(const zeq::Event& newEvent);
private:
	

	VistaTransformNode *m_pTransNode;
	zeq::Subscriber *m_subscriber;
};

#endif //EVENTHANDLER_H
