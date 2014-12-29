#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include "applicationui.h"

#include <Qt/qdeclarativedebug.h>

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);


    ApplicationUI *pointer = new ApplicationUI(&app);
    pointer->init();
    return Application::exec();
}
