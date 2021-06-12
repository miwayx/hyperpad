/*
 * main.cc
 *
 * Copyright 2021 Ern <ern8642@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include "mainwindow.hh"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Application Config
    QApplication::setApplicationName("qText");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("qText");
    QApplication::setOrganizationDomain("https://github.con/ern126/qText");
    QApplication::setWindowIcon(QIcon::fromTheme("text-editor",QIcon(":/ico/res/qtext_ico.svg")));

    // Init
    MainWindow mw;

    // Parsing args
    if(argc != 1){
        QString text_arg = argv[1];
        if(text_arg == "-h")
        {
            qDebug("Usage: qText [OPTIONS] [file]\n"
                   "Option     Meaning\n"
                   "file       Open a file\n"
                   "-h         Show this help text and exit\n"
                   "-v         Print version information and exit\n");
            exit(1);
        }else if(text_arg == "-v"){
            qDebug("qText: %s",qPrintable(QApplication::applicationVersion()));
            exit(1);
        }else{
            QFile filename(text_arg);
            if(filename.exists()){
                mw.openfile(text_arg);
            }else{
                qDebug("[Error] File not found");
                exit(1);
            }
        }
    }


    mw.show(); //Init Window
    return a.exec();
}
