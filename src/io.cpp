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

#include "io.hpp"

namespace hyper::io {

bool saveText(QString filename, QString text)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
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

// class currentFile
CurrentFile::CurrentFile()
{
    // set default false
    m_is_saved = false;
}

CurrentFile::CurrentFile(QString filename)
{
    m_cfilename = filename;
    m_cfinfo = QFileInfo(filename);
    m_is_saved = false;
}

void CurrentFile::setFilename(QString filename)
{
    m_cfilename = filename;
    m_cfinfo = QFileInfo(filename);
    // set is_saved false
    m_is_saved = false;
}

void CurrentFile::setSaved(bool op)
{
    m_is_saved = op;
}

bool CurrentFile::isSaved()
{
    return m_is_saved;
}

QString CurrentFile::read()
{
    return io::readFile(m_cfilename);
}

bool CurrentFile::save(QString text)
{
    bool ok = io::saveText(m_cfilename, text);
    if (ok) {
        // set is_saved true
        m_is_saved = true;
        return true;
    } else {
        return false;
    }
}

QString CurrentFile::name()
{
    return m_cfinfo.baseName();
}

QString CurrentFile::path()
{
    return m_cfinfo.path();
}

int CurrentFile::size()
{
    return m_cfinfo.size();
}

io::fileType CurrentFile::filetype()
{
    QString ext = m_cfinfo.suffix();

    if (ext == "txt") {
        return io::fileType::TXT;
    } else if (ext == "md") {
        return io::fileType::MD;
    } else {
        return io::fileType::TXT;
    }
}

bool CurrentFile::isEmpty()
{
    // check if empty the string
    if (m_cfilename.isEmpty())
        return true;
    else
        return false;
}

void CurrentFile::operator=(QString name)
{
    this->setFilename(name);
}

} // namespace hyper::io
