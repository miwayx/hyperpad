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

#include "texteditor.hpp"

namespace Hyper
{

TextEditor::TextEditor(QWidget *parent)
    : QTextEdit(parent)
{
    // Disable by default the markdown view
    m_markdown_view = false;
}

void TextEditor::showText(CurrentFile &file)
{
    QString text = file.read();
    // Plain text
    if (file.filetype() == io::fileType::TXT) {
        this->setPlainText(text);
        // Set the markdown view by default
    } else if (file.filetype() == io::fileType::MD) {
        if (m_markdown_view == true) {
            this->setMarkdown(text);
        } else {
            this->setPlainText(text);
        }
    } else {
        this->setPlainText(text);
    }
}

void TextEditor::setMarkdownView(bool b)
{
    m_markdown_view = b;
}

bool TextEditor::markdownView()
{
    return m_markdown_view;
}

} // namespace hyper
