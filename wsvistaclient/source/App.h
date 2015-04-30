#ifndef APP_H
#define APP_H


class VistaSystem;
class VistaTransformNode;
class EventHandler;

class App 
{
public:
	App();
	virtual ~App();

	bool Init(int argc, char** argv);

	void Run();

private:
	void InitText();
	void InitKeyAction();
	void InitEventHandler();

	VistaSystem *m_pSystem;
	VistaTransformNode *m_pTransNode;

	EventHandler *m_pEventHandler;

};



#endif //APP_H
