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

#include "file.hpp"

namespace hyper {

File::File()
{
    // Set is_saved to false
    _is_saved = false;
}

File::~File()
{
    // Close if the file is not closed yet
    if(_file.isOpen())
        _file.close();
}

void File::setFilename(QString name)
{
    _filename = name;
    _is_saved = false;
}

bool File::openFile()
{
    _file.setFileName(_filename);
    _file.open(QFileDevice::ReadWrite);

    if(_file.isOpen()) {
        return true;
    } else {
        return false;
    }
}

bool File::saveText(QString text)
{
    QTextStream out(&_file);
    // write text in file
    out << text;
    // get status
    if(out.status() == out.Ok)
        return true;
    else
        return false;
}

void File::closeFile()
{
    // Close input buffer
    if(_file.isOpen())
        _file.close();
}

void File::setSaved(bool saved)
{
    _is_saved = saved;
}

bool File::isSaved()
{
    return _is_saved;
}

QString File::currentFilename()
{
    return _filename;
}

QString File::readFile()
{

}

} // namespace hyper
