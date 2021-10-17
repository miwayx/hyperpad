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

#include "io.hpp"

namespace hyper {

namespace io {

bool saveText(QString filename, QString text)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        // Write text in the file buffer
        out << text;
        // all ok
        file.close();
        return true;
    } else {
        return false;
    }
}

QString readFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    // Return all text
    return in.readAll();
}

} // namespace io

// class currentFile
currentFile::currentFile()
{
    // set default false
    _is_saved = false;
}

currentFile::currentFile(QString filename)
{
    _cfilename = filename;
    _is_saved = false;
}

void currentFile::setFilename(QString filename) {
    _cfilename = filename;
    // set is_saved false
    _is_saved = false;
}

void currentFile::setSaved(bool op) {
    _is_saved = op;
}

bool currentFile::isSaved() {
    return _is_saved;
}

QString currentFile::read()
{
    return io::readFile(_cfilename);
}

bool currentFile::save(QString text)
{
    bool ok = io::saveText(_cfilename, text);
    if(ok) {
        // set is_saved true
        _is_saved = true;
        return true;
    } else {
        return false;
    }
}

QString currentFile::name()
{
    return _cfilename;
}

bool currentFile::isEmpty()
{
    // check if empty the string
    if(_cfilename.isEmpty())
        return true;
    else
        return false;
}

void currentFile::operator=(QString name){
    this->setFilename(name);
}


} // namespace hyper
