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

#ifndef HYPER_UI_HPP
#define HYPER_UI_HPP

#include <QTextEdit>
#include <QStatusBar>

#include "io.hpp"

namespace hyper::ui {

class TextEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor() { }
    // Analyze and return the text
    void showText(io::CurrentFile &file);
    // Enable or disable markdown view
    void setMarkdownView(bool b);
    bool markdownView();

private:
    bool m_markdown_view;
};

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();
    /// Send a message to statusbar for 4 seconds
    void sendMessage(QString message);
};

} //namespace hyper::ui

#endif // HYPER_UI_HPP
