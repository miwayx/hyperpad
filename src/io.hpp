/**
 ** This file is part of the hyperpad project.
 ** Copyright 2021 Ernest C. Suarez <ernestcsuarez2@gmail.com>.
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

#ifndef HYPER_IO_HPP
#define HYPER_IO_HPP

#include <QFile>
#include <QTextStream>

namespace hyper {

/// Basic io functions
namespace io {
/// Open a file in the filesystem
bool openFile(QString filename, QIODevice::OpenModeFlag);
/// Save the current file
bool saveText(QString filename, QString text);
/// Read file contents
QString readFile(QString filename);

} //namespace io

} // namespace hyper

#endif // HYPER_IO_HPP
