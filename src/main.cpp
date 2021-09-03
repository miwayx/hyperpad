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
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Application Config
    QApplication::setApplicationName("HyperPad");
    QApplication::setApplicationVersion("0.50");
    QApplication::setOrganizationName("HyperPad");
    QApplication::setOrganizationDomain("https://github.con/ern126/hyperpad");
    QApplication::setWindowIcon(QIcon(":/ico/res/hyperpad_ico.png"));

    // Init
    MainWindow mw;

    // Parse Arguments
	 if(argc != 1){
		QString file(argv[1]);
		mw.openfile(file);
	}

    QCommandLineParser parse;
    parse.setApplicationDescription("HyperPad -Fast text editor");
    parse.addHelpOption();
    parse.addVersionOption();
    // file argument
    QCommandLineOption opt_file(QStringList() << "f" << "file", "Open a file", "file");
    parse.addOption(opt_file);
    // Process parse
    parse.process(a);
    // Get file argument
    if(parse.isSet(opt_file)){
        QString filename = parse.value(opt_file);
        mw.openfile(filename);
    }

    mw.show(); //Init Window
    return a.exec();
}
