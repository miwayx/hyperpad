/**
 ** This file is part of the hyperpad project.
 ** Copyright 2021 Ern <ern8642@gmail.com>.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // st is the settings of the app
    QSettings st;
    void openfile(QString filename);
    void savefile(QString filename);

private slots:
    void act_exit();
    void act_doc_changed();
    void act_new();
    void act_open();
    void act_save();
    void act_saveas();
    void act_find();
    void act_newfont();
    void act_menubar();
    void act_statusbar();
    void act_toolbar();
    void act_toolbar_style_icons_only();
    void act_toolbar_style_text_only();
    void act_toolbar_style_text_beside_icons();
    void act_toolbar_style_text_under_icons();
    void act_toolbar_style_follow();
    void act_about_hyper();

private:
    Ui::MainWindow *ui;
    QLabel *status;
    QString currentfile;
    bool m_saved;
    bool documentModified();
    void setupToolbarAndStatusbar();
    void saveAllSettings();
    void readAllSettings();

};
#endif // MAINWINDOW_H
