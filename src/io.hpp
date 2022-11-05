/**
 ** This file is part of the hyperpad project.
 ** Copyright 2021-2022 Ernest C. Suarez <ernestcsuarez@gmail.com>.
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
#include <QFileInfo>
#include <QTextStream>

/// Basic io functions
namespace hyper::io {

/// Open file in the filesystem
// bool openFile(QString filename, QIODevice::OpenModeFlag);
/// Save the current file
bool saveText(QString filename, QString text);
/// Read file contents
QString readFile(QString filename);

// QString analyzeFile(QString filename);

/// Supported file Types
enum fileType {
    TXT, // .txt
    MD // .md
};

/// Controller for current file in the editor
class CurrentFile
{
public:
    CurrentFile();
    CurrentFile(QString filename);
    ~CurrentFile() { }
    /// Set a filename
    void setFilename(QString filename);
    /// Set saved the fileabsolute
    void setSaved(bool op);
    /// Return if the current file is saved
    bool isSaved();
    /// Read file context
    QString read();
    /// Save text in the file
    bool save(QString text);
    /// Return the filename
    QString name();
    /// Return the path to the filename
    QString path();
    /// Return the filetypeabsolute
    fileType filetype();
    /// Return the file size
    int size();
    /// Return true if empty
    bool isEmpty();
    // implemented operator "=" for assign a new name
    /// Assign a new name
    void operator=(QString name);

private:
    // Current name of the file open
    QString   m_cfilename;
    QFileInfo m_cfinfo;
    // if its saved
    bool m_is_saved;
};

} // namespace Hyper::io


#endif // HYPER_IO_HPP
