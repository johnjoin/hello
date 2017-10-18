#ifndef SYSTEM_SERVER_H
#define SYSTEM_SERVER_H

#include <QDesktopWidget>
#include <QScreen>
#include <QApplication>
#include <QCursor>
#include "def_struct.h"

class System_Server
{
public:
    System_Server();
    SCREEN GetScreen();
};

#endif // SYSTEM_SERVER_H
