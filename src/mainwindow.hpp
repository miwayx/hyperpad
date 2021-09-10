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
    void actExit();
    void actDocChanged();
    void actNew();
    void actOpen();
    void actSave();
    void actSaveas();
    void actFind();
    void actNewfont();
    void actMenubar();
    void actStatusbar();
    void actToolbar();
    void actToolbarStyleIconsOnly();
    void actToolbarStyleTextOnly();
    void actToolbarStyleTextBesideIcons();
    void actToolbarStyleTextUnderIcons();
    void actToolbarStyleFollow();
    void actAboutHyper();

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
