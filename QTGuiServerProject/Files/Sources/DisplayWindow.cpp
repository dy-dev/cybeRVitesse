#include <QVideoWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QMediaService>
#include <QMediaPlaylist>

#include <QAudioFormat>
#include <QAudioBuffer>
#include <QIODevice>
#include <QAudioOutput>
#include <QAudioDecoder>
#include <QFile>

#include <numeric>
#include <chrono>

#include <qvideowidget.h>
#include <qvideosurfaceformat.h>

#include "RequestsHandler.h"
#include "DisplayWindow.h"



DisplayWindow::DisplayWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_pRequestsHandler( nullptr )
    , startInHtml( 0 )
{
    ui.setupUi( this );

    //    connect( m_pQMediaPlayer, SIGNAL( mediaStatusChanged( QMediaPlayer::MediaStatus ) ), this, SLOT( statusChanged( QMediaPlayer::MediaStatus ) ) );
}


DisplayWindow::~DisplayWindow()
{
}
/*
void DisplayWindow::statusChanged( QMediaPlayer::MediaStatus status )
{
    int a = -1;
    int b = -1;
    // handle status message
    switch ( status ) {
        //  case QMediaPlayer::PlayingState:
    case QMediaPlayer::BufferedMedia:
        _sleep( 200 );
        ui.DisplayLayout->removeWidget( ui.waitingWidget );
        ui.DisplayLayout->addWidget( m_pQVideoWidget );
        startMedia();
        muteLeft();
        if ( startInHtml > 0 )
        {
            long long time_ms = std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
            unsigned long long offsetToApply = time_ms - startInHtml;
            m_pQMediaPlayer->setPosition( m_pQMediaPlayer->position() + offsetToApply );
            startInHtml = 0;
        }
        break;
    case QMediaPlayer::LoadingMedia:
        //setStatusInfo( tr( "Loading..." ) );

        break;
    case QMediaPlayer::StalledMedia:
        //setStatusInfo( tr( "Media Stalled" ) );
        break;
    case QMediaPlayer::EndOfMedia:
        a = m_pQMediaPlayer->playlist()->currentIndex();
        b = m_pQMediaPlayer->playlist()->mediaCount();
        if ( m_pQMediaPlayer->playlist()->currentIndex() == m_pQMediaPlayer->playlist()->mediaCount() - 1 )
        {
            ui.DisplayLayout->removeWidget( m_pQVideoWidget );
            ui.DisplayLayout->addWidget( ui.waitingWidget );
            endPlayList();
        }
        else
        {
            endMedia();
        }
        break;
    case QMediaPlayer::InvalidMedia:
        //  displayErrorMessage();
        break;
    }
}        */


void DisplayWindow::actOnRequest( QString p_QStringRequest, QString p_QStringColor )
{
    if ( m_pRequestsHandler == nullptr )
    {
        m_pRequestsHandler = dynamic_cast< RequestsHandler* > ( sender() );
        connect( this, SIGNAL( startMedia() ), m_pRequestsHandler, SLOT( sendRedInfo() ) );
        connect( this, SIGNAL( endMedia() ), m_pRequestsHandler, SLOT( sendGreenInfo() ) );
    }

    if ( p_QStringColor == "Green" )
    {
        this->setStyleSheet( QStringLiteral( "background-color: rgb(0, 255, 0);" ) );
    }

   
    else if ( p_QStringColor == "Red" )
    {
        this->setStyleSheet( QStringLiteral( "background-color: rgb(255, 0, 0);" ) );

    }
   /* else if ( p_QStringRequest == "StartSoon" )
    {
        ui.centralWidget->setStyleSheet( QStringLiteral( "background-image: url(:/QTWebServer/Medias/GaumontWelcome.png) 0 20 0 0 stretch stretch;  background-repeat : no-repeat;" ) );
        play = false;
    }*/
}
