/**
 ** This file is part of the hyperpad project.
 ** Copyright 2022 Ernest C. Suarez <ernestcsuarez@gmail.com>.
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

#include "ui.hpp"

namespace hyper::ui {

// TextEditor class
TextEditor::TextEditor(QWidget *parent)
    : QTextEdit(parent)
{
    // Disable by default the markdown view
    m_markdown_view = false;
}

void TextEditor::showText(io::CurrentFile &file)
{
    QString text = file.read();

    // Support filetypes
    switch (file.filetype()) {
    case io::fileType::TXT:
         this->setPlainText(text);
        break;
    case io::fileType::MD:
        if (m_markdown_view == true)
            this->setMarkdown(text);
        else
            this->setPlainText(text);
        break;
    default:
        this->setPlainText(text);
        break;
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

// StatusBar class
StatusBar::StatusBar(QWidget *parent)
    : QStatusBar(parent)
{
  // Initialize widgets
}

StatusBar::~StatusBar() { }

void StatusBar::sendMessage(QString message)
{
    this->showMessage(message, 4000);
}


} //namespace hyper::io
