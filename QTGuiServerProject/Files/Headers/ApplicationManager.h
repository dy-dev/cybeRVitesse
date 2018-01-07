class QTWebServer;
class RequestsHandler;
class DisplayWindow;


#pragma once
class ApplicationManager
{
public:
    ApplicationManager();
    ~ApplicationManager();

private:
    QTWebServer * m_pQTWebServer;
    DisplayWindow * m_pDisplayWindow;
    RequestsHandler * m_pRequestsHandler;
};

