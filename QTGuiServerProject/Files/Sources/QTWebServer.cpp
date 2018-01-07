
#include <QtWidgets>
#include <QtNetwork>      
#include <QtWebSockets/qwebsocketserver.h>
#include <QtWebSockets/qwebsocket.h>
#include "RequestsHandler.h"

#include <stdlib.h>

#include "QTWebServer.h"

QTWebServer::QTWebServer( QWidget *parent, RequestsHandler * handler )
    : m_pWebSocketServer( new QWebSocketServer( QStringLiteral( "Gaumont Web Server" ), QWebSocketServer::NonSecureMode, this ) )
    , m_pRequestsHandler( handler )
{
    if ( m_pWebSocketServer->listen(/*QHostAddress::Any*/QHostAddress( "10.0.0.10" ), 1234 ) ||
        m_pWebSocketServer->listen(/*QHostAddress::Any*/QHostAddress( "192.168.0.50" ), 1234 ) ||
        m_pWebSocketServer->listen(/*QHostAddress::Any*/QHostAddress( "127.0.0.1" ), 1234 ) ||
        m_pWebSocketServer->listen( QHostAddress::Any, 1234 ) )
    {
        auto address = m_pWebSocketServer->serverAddress();
        auto id = address.toString();
        qDebug() << "Echoserver listening on port 1234";
        connect( m_pWebSocketServer, &QWebSocketServer::newConnection, this, &QTWebServer::onNewConnection );
        connect( m_pWebSocketServer, &QWebSocketServer::closed, this, &QTWebServer::closed );
    }
    else
    {
        qDebug() << "Failed listening on port 1234" << m_pWebSocketServer->errorString();
    }
}

//! [onNewConnection]
void QTWebServer::onNewConnection()
{
    if ( m_pRequestsHandler != nullptr )
    {

        QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

        connect( pSocket, &QWebSocket::textMessageReceived, m_pRequestsHandler, &RequestsHandler::processTextMessage );
        connect( pSocket, &QWebSocket::binaryMessageReceived, m_pRequestsHandler, &RequestsHandler::processBinaryMessage );
        connect( pSocket, &QWebSocket::disconnected, this, &QTWebServer::socketDisconnected );

        m_clients << pSocket;
    }
    else
    {
        qDebug() << "Request Handler not set";
    }
}
//! [onNewConnection]

//! [processTextMessage]
void QTWebServer::processTextResponse( QWebSocket *pClient, QString message )
{
    //QWebSocket *pClient = qobject_cast< QWebSocket * >( sender() );
    qDebug() << "Message received:" << message;
    if ( pClient )
    {
        pClient->sendTextMessage( message );
    }
}
//! [processTextMessage]

//! [processBinaryMessage]
void QTWebServer::processBinaryResponse( QWebSocket *pClient, QByteArray message )
{
    //QWebSocket *pClient = qobject_cast< QWebSocket * >( sender() );
    qDebug() << "Binary Message received:" << message;
    if ( pClient ) {
        pClient->sendBinaryMessage( message );
    }
}
//! [processBinaryMessage]

//! [socketDisconnected]
void QTWebServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast< QWebSocket * >( sender() );
    qDebug() << "socketDisconnected:" << pClient;
    if ( pClient ) {
        m_clients.removeAll( pClient );
        pClient->deleteLater();
    }
}
//! [socketDisconnected]
