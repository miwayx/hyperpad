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

#ifndef HYPER_FILE_HPP
#define HYPER_FILE_HPP

#include <iostream>
#include <fstream>
#include <QString>

namespace hyper::file {

/// Basic file
class File
{
public:
    /// Rute to the file
    File(std::string filename);
    File(QString filename);
    ~File();
    /// Set a new filename
    void setFilename(std::string name);
    /// Open a file in the filesystem
    bool openFile();
    /// Save the current file
    bool saveText(std::string text);
    /// Save the current file, with text in QString
    bool saveText(QString text);
    /// Close the current file
    void closeFile();
    /// Mark saved the file
    void setSaved(bool saved);
    /// Get if the current file  saved in the disk
    bool isSaved();
    /// Get the current filename in std::string
    std::string currentFilename();
    /// Get the current filename in QString
    QString currentqFilename();
    /// Read file contents
    std::string readFile();
    /// Read file contents and return in QString
    QString readqFile();

private:
    std::ifstream in;
    // current filename
    std::string _filename;
    bool _is_saved;
};

} // namespace hyper::file

#endif // HYPER_FILE_HPP
