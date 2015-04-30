#include <VistaKernel/VistaSystem.h>

#include <VistaKernel/InteractionManager/VistaKeyboardSystemControl.h>

#include <VistaKernel/GraphicsManager/VistaGraphicsManager.h>
#include <VistaKernel/GraphicsManager/VistaSceneGraph.h>
#include <VistaKernel/GraphicsManager/VistaTextNode.h>
#include <VistaKernel/GraphicsManager/VistaTransformNode.h>
#include <VistaKernel/GraphicsManager/Vista3DText.h>

#include <VistaKernel/EventManager/VistaCentralEventHandler.h>
#include <VistaKernel/EventManager/VistaEventObserver.h>
#include <VistaKernel/EventManager/VistaEventManager.h>


#include "App.h"
#include "EventHandler.h"
#include "ActivationCallback.h"

App::App()
	:m_pSystem( new VistaSystem)
{

}

 App::~App()
{
	 delete m_pSystem;
}

bool App::Init(int argc, char** argv)
{

	// Mind to init the search path for configuration files particularly mind to
	// include the "global" ini-files.
	std::list<std::string> liSearchPaths;
	liSearchPaths.push_back("configfiles/");
	liSearchPaths.push_back("../configfiles/");
	liSearchPaths.push_back("../../configfiles/");
	m_pSystem->SetIniSearchPaths(liSearchPaths);

	if (!m_pSystem->Init(argc, argv))
	{
		printf("*** ERROR *** VistaSystem initialization failed\n");
		printf("\tBAILING OUT!\n");

		delete m_pSystem;

		m_pSystem = NULL;

		return false;
	}

	InitText();
	InitKeyAction();
	InitEventHandler();
	
	return true;
}

void App::InitText()
{
	VistaGraphicsManager *pGrMgr = m_pSystem->GetGraphicsManager();

	// get a pointer to the scene graph and root
	VistaSceneGraph *pSceneGraph = pGrMgr->GetSceneGraph();
	VistaGroupNode *pRoot = pSceneGraph->GetRoot();

	// setup a node first for the callbacks later on
	m_pTransNode = pSceneGraph->NewTransformNode(pRoot);

	// move it a bit away
	m_pTransNode->SetTranslation(VistaVector3D(-.5f, 0.f, 0.f));

	const std::string sFontName("SANS"); // if you have problems, you may try "sans"
	VistaTextNode *pTextNode = pSceneGraph->NewTextNode(m_pTransNode, sFontName);
	pTextNode->GetTextImp()->SetFontSize(0.08f); // make it a bit smaller, so we can read it (hopefully)
	pTextNode->SetText("you can move this text by pressing 'm'"); // set a default text.
	pTextNode->SetName("Text Node");
	
}

void App::InitKeyAction()
{
	VistaKeyboardSystemControl *pCtrl = m_pSystem->GetKeyboardSystemControl();
	// register a few callbacks to switch the text up key stroke

	pCtrl->BindAction('m', new ActivationCallback(m_pSystem), "move text");
}


void App::InitEventHandler()
{
	m_pEventHandler = new EventHandler(m_pTransNode);
	m_pSystem->GetEventManager()->RegisterObserver(m_pEventHandler, VistaEventManager::NVET_ALL);
}

void App::Run()
{
	// Enter the app loop of the underlying ViSTA system.
	m_pSystem->Run();
}
