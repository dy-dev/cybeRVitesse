#include "QTWebServer.h"
#include "DisplayWindow.h"
#include "ApplicationManager.h"        
#include "FullMediaPlayerWithList.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication app( argc, argv );

    QCoreApplication::setApplicationName( "Test PIDS" );
    QCoreApplication::setOrganizationName( "Light In Chaos" );
    QCoreApplication::setApplicationVersion( QT_VERSION_STR );
    QCommandLineParser parser;
    parser.setApplicationDescription( "Light In Chaos Webserver - Appli Mobile Example" );
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument( "url", "The URL to open." );
    parser.process( app );

    ApplicationManager appMgr;
    return app.exec();

}
