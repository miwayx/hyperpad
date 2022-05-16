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

#ifndef HYPER_TEXTEDITOR_HPP
#define HYPER_TEXTEDITOR_HPP

#include "io.hpp"
#include <QTextEdit>

namespace Hyper
{

class TextEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor() { }
    // Analyze and return the text
    void showText(CurrentFile &file);
    // Enable or disable markdown view
    void setMarkdownView(bool b);
    bool markdownView();

private:
    bool m_markdown_view;
};

} // namespace hyper

#endif // HYPER_TEXTEDITOR_HPP
