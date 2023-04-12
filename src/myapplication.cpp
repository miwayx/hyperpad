/**
 ** This file is part of the hyperpad project.
 ** Copyright 2023 Stanislav Mikhailov (xavetar).
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "myapplication.hpp"
#include "version.hpp"

#ifdef Q_OS_MAC
#include <QFileOpenEvent>

bool MyApplication::event(QEvent *event)
{
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
        mainwindow->loadFile(openEvent->file());
    }

    return QApplication::event(event);
}
#endif

MyApplication::MyApplication(int &argc, char **argv) : QApplication(argc, argv)
{
    setApplicationName("HyperPad");
    setApplicationVersion(HYPER_VERSION);
    setOrganizationName("HyperPad");
    setOrganizationDomain("https://github.con/ecsuarez/hyperpad");
    setWindowIcon(QIcon(":/icons/hyper_ico.png"));

    mainwindow = new HyperWindow();
}

MyApplication::~MyApplication() {
    delete mainwindow;
}

int MyApplication::run()
{
    if (arguments().length() > 1){
        mainwindow->loadFile(arguments().at(1));
    }
    mainwindow->show();

    return exec();
}
