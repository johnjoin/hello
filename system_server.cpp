#include "system_server.h"

System_Server::System_Server()
{

}

SCREEN System_Server::GetScreen()
{
    QDesktopWidget* desktop = QApplication::desktop();

    QPoint pt = QCursor::pos();
    int index = desktop->screenNumber(pt);
    QRect rect = desktop->availableGeometry(index);
    SCREEN screen;
    screen.index = index;
    screen.width = rect.width();
    screen.height = rect.height();
    return screen;
}
