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

#ifndef HYPER_MAINWINDOW_HPP
#define HYPER_MAINWINDOW_HPP

#include <QMainWindow>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "io.hpp"
#include "texteditor.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Application settings
    QSettings st;

private slots:
    // Actions
    void onActionDocumentChanged();
    // Actions in menubar
    // Menu File
    void onActionNew();
    void onActionOpen();
    void onActionSave();
    void onActionSaveAs();
    void onActionExit();
    // Menu Edit
    void onActionUndo();
    void onActionRedo();
    void onActionCut();
    void onActionCopy();
    void onActionPaste();
    void onActionSelectAllText();
    // Menu View
    void onActionToolbar();
    //void onActionStatusbar();
    void onActionMenubar();
    void onActionToolbarStyleIconsOnly();
    void onActionToolbarStyleTextOnly();
    void onActionToolbarStyleTextBesideIcons();
    void onActionToolbarStyleTextUnderIcons();
    void onActionToolbarStyleFollow();
    // Menu Help
    void onActionAboutHyper();

private:
    Ui::MainWindow *ui;
    // Current file
    hyper::currentFile _currentfile;
    // Main text editor
    hyper::TextEditor *_texteditor;
    bool documentModified();
    void setupToolbar();
    // Store and Load default settings
    void storeSettings();
    void loadSettings();
};

#endif // HYPER_MAINWINDOW_HPP

