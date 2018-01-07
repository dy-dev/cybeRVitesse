#pragma once

#include <QObject>
//#include "ui_QTWebServer.h"


QT_BEGIN_NAMESPACE
class QWebSocketServer;
class QWebSocket;
QT_END_NAMESPACE

class RequestsHandler;

class QTWebServer : public QObject
{
    Q_OBJECT

public:
    //explicit  QTWebServer( QWidget *parent = Q_NULLPTR );
    QTWebServer( QWidget *parent = Q_NULLPTR, RequestsHandler * handler = Q_NULLPTR );

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    RequestsHandler* m_pRequestsHandler;

signals:
    void closed();

    public slots:
    void processTextResponse( QWebSocket *pClient, QString message);
    void processBinaryResponse( QWebSocket *pClient, QByteArray message );
    void socketDisconnected();

    private slots:
    void onNewConnection();
 

};
