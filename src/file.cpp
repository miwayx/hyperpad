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

namespace hyper::file {

File::File(std::string filename)
{
    // Set filename now the currentfile open
    _filename = filename;
    // Set is_saved to false
    _is_saved = false;
}

File::File(QString filename)
{
    // Set filename in std format
    _filename = filename.toStdString();
    // Set is_saved to false
    _is_saved = false;
}

File::~File()
{
    // Close if the file is not closed yet
    if(in.is_open()) {
        in.close();
    }
}

bool File::openFile()
{
    try {
        // Try to open in reader mode
        in.open(_filename, std::ios::in);
        return true;
    } catch(std::ios::failure& e) {
        // Retun an error
        return false;
    }
}

bool File::saveText(std::string text)
{
    std::ofstream out;
    try {
        // Try to write current file
        out.open(_filename, std::ios::out);
        out << text;
        // All ok
        // Mark saved the file
        _is_saved = true;
        return true;
    }  catch(std::ios::failure& e) {
        // Return an error
        return false;
    }
}

bool File::saveText(QString text)
{
    bool ok = this->saveText(text.toStdString());
    if(ok) {
        return true;
    } else {
        return false;
    }
}

void File::closeFile()
{
    // Close input buffer
    if(in.is_open()) {
        in.close();
    }
}

void File::setSaved(bool saved)
{
    _is_saved = saved;
}

bool File::isSaved()
{
    return _is_saved;
}

std::string File::currentFilename()
{
    return _filename;
}

QString File::currentqFilename()
{
    return QString::fromStdString(_filename);
}

std::string File::readFile()
{
    std::string file_text;
    if(in.is_open()) {
        // If the file is open, read all an return the text
        in >> file_text;
        return file_text;
    } else {
        return nullptr;
    }
}

QString File::readqFile()
{
    return QString::fromStdString(this->readFile());
}

} // namespace hyper::file
