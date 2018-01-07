#include <QWindow>

#include "QTWebServer.h"
#include "RequestsHandler.h"
#include "ApplicationManager.h"
#include "DisplayWindow.h"


ApplicationManager::ApplicationManager()
    : m_pQTWebServer(nullptr )
    , m_pDisplayWindow( nullptr )
    , m_pRequestsHandler( nullptr )

{
    m_pRequestsHandler = new RequestsHandler();
    m_pQTWebServer = new QTWebServer( nullptr, m_pRequestsHandler );         
    m_pDisplayWindow = new DisplayWindow();
   
    m_pRequestsHandler->setConnections( m_pQTWebServer, m_pDisplayWindow );
    m_pDisplayWindow->show();
   // m_pMediaPlayer->showNormal();
    if( qApp->screens().count() > 1)
    {
        m_pDisplayWindow->windowHandle()->setScreen( qApp->screens()[1] );
    }       
}


ApplicationManager::~ApplicationManager()
{
    delete m_pRequestsHandler;
    delete m_pQTWebServer;
    delete m_pDisplayWindow;
}
