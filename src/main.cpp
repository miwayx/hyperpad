/**
 ** This file is part of the hyperpad project.
 ** Copyright 2021 Ernest C. Suarez <ernestcsuarez@gmail.com>.
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

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "mainwindow.hpp"
#include "version.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Application Config
    QApplication::setApplicationName("HyperPad");
    QApplication::setApplicationVersion(HYPER_VERSION);
    QApplication::setOrganizationName("HyperPad");
    QApplication::setOrganizationDomain("https://github.con/ecsuarez/hyperpad");
    QApplication::setWindowIcon(QIcon(":/icons/hyper_ico.png"));

    HyperWindow mainwindow;

    // Parse arguments
    QCommandLineParser parser;
    parser.setApplicationDescription("HyperPad -Fast text editor");
    parser.addHelpOption();
    parser.addVersionOption();
    // File argument
    parser.addPositionalArgument("file", "Document to open");
    // Process parser
    parser.process(a);
    // Get file argument
    QStringList positionals_arguments = parser.positionalArguments();
    if (parser.positionalArguments().count() > 0)
        mainwindow.loadFile(positionals_arguments[0]);

    mainwindow.show(); // Init Window
    return a.exec();
}
