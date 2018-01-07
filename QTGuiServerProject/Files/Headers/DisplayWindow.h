#pragma once

#include <QtWidgets/QMainWindow>
#include <windows.h>

#include <mmsystem.h>
#include <stdlib.h>

#include "ui_GaumontMediaDisplay.h"

class RequestsHandler;

class DisplayWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::QTMediaPlayerClass ui;
    RequestsHandler* m_pRequestsHandler;

public:
    DisplayWindow( QWidget *parent = Q_NULLPTR );
    ~DisplayWindow();

    public slots:
    //void statusChanged( QMediaPlayer::MediaStatus status );
    void actOnRequest( QString p_QStringRequest, QString p_QStringColor );
  

signals:
    void startMedia();
    void endMedia();
    void endPlayList();

private :
    unsigned long long  startInHtml;
};

