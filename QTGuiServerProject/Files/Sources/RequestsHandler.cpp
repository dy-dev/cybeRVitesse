#include <QtWidgets>
#include <QtNetwork>      
#include <QtWebSockets/qwebsocketserver.h>
#include <QtWebSockets/qwebsocket.h>

#include <stdlib.h>

#include "QTWebServer.h"
#include "DisplayWindow.h"
#include "RequestsHandler.h"

RequestsHandler::RequestsHandler()
    :m_pQTWebServer(nullptr)
{
}

RequestsHandler::~RequestsHandler()
{
}

void RequestsHandler::setConnections( QTWebServer* p_pQTWebServer, DisplayWindow * p_pMediaPlayer )
{
    connect( this, &RequestsHandler::ManageTextClientResponse, p_pQTWebServer, &QTWebServer::processTextResponse );
    connect( this, &RequestsHandler::ManageBinaryClientResponse, p_pQTWebServer, &QTWebServer::processBinaryResponse );

    connect( this, &RequestsHandler::sendRequest, p_pMediaPlayer, &DisplayWindow::actOnRequest );

}

//! [processTextMessage]
void RequestsHandler::processTextMessage( QString message )
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson( message.toUtf8() );
    if ( !doc.isNull() )
    {
        if ( doc.isObject() )
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << "Invalid JSON...\n" << message << endl;
    }
    


    sendRequest( obj["Action"].toString(), obj["color"].toString());
   
   
    m_pClient = qobject_cast< QWebSocket * >( sender() );
    ManageTextClientResponse( m_pClient, message);
    
}
//! [processTextMessage]                               
void RequestsHandler::sendRedInfo()
{
    ManageTextClientResponse( m_pClient, "Frame is Red" );
}

void RequestsHandler::sendGreenInfo()
{
    ManageTextClientResponse( m_pClient, "Frame is Green" );
}

//! [processBinaryMessage]
void RequestsHandler::processBinaryMessage( QByteArray message )
{
    QWebSocket *pClient = qobject_cast< QWebSocket * >( sender() );
    ManageTextClientResponse( pClient, message);
}
//! [processBinaryMessage]

