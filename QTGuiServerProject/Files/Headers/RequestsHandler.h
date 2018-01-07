#pragma once
#include <QObject>

class QTWebServer;
class DisplayWindow;

QT_BEGIN_NAMESPACE
class QWebSocket;
QT_END_NAMESPACE

class RequestsHandler : public QObject
{
    Q_OBJECT

public:
    RequestsHandler();
    ~RequestsHandler();

    void setConnections( QTWebServer* p_pQTWebServer, DisplayWindow* p_pMediaPlayer );

    public slots:
    void processTextMessage( QString message );
    void processBinaryMessage( QByteArray message );
    void sendRedInfo();
    void sendGreenInfo();

signals:
    void ManageTextClientResponse( QWebSocket *pClient, QString message);
    void ManageBinaryClientResponse( QWebSocket *pClient, QByteArray message );
    void sendRequest( QString , QString);
    void StartVideo();


private:
    QTWebServer* m_pQTWebServer;
    QWebSocket *m_pClient;
};

