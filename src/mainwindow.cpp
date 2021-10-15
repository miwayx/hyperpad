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

#include "mainwindow.hpp"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget();

    // Connecting signals
    // verify if exit of the app
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onActionExit()));
    // document changed
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this,
            SLOT(onActionDocumentChanged()));
    // MenuBar
    connect(ui->actionNew, SIGNAL(triggered(bool)),  this, SLOT(onActionNew()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(onActionOpen()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(onActionSave()));
    connect(ui->actionSaveAs,SIGNAL(triggered(bool)), this, SLOT(onActionSaveas()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(onActionExit()));
    connect(ui->actionVisible_MenuBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionMenubar()));
    connect(ui->actionVisible_StatusBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionStatusbar()));
    connect(ui->actionVisible_ToolBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionToolbar()));
    connect(ui->actionMovable_ToolBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionToolbar()));
    connect(ui->actionToolbar_IconsOnly, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleIconsOnly()));
    connect(ui->actionToolbar_TextOnly, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleTextOnly()));
    connect(ui->actionToolbar_TextBesideIcons, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleTextBesideIcons()));
    connect(ui->actionToolbar_TextUnderIcons, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleTextUnderIcons()));
    connect(ui->actionToolbar_Follow, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleFollow()));
    connect(ui->actionFont, SIGNAL(triggered(bool)),this, SLOT(onActionNewfont()));
    connect(ui->actionAbout_Hyper, SIGNAL(triggered(bool)),
            this, SLOT(onactionAboutHyper()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    // Read the configuration
    loadSettings();
    // Toolbar setup
    setupToolbar();
}

MainWindow::~MainWindow()
{
    delete st;
    delete ui;
    delete _currentfile;
}

void MainWindow::storeSettings()
{
    st->setValue("window/geometry",this->geometry());
    st->setValue("window/hidden_menubar", ui->menubar->isHidden());
    st->setValue("window/hidden_statusbar",ui->statusbar->isHidden());
    st->setValue("toolbar/hidden",ui->toolBar->isHidden());
    st->setValue("toolbar/movable",ui->toolBar->isMovable());
    st->setValue("toolbar/geometry",ui->toolBar->geometry());
    st->setValue("toolbar/orientation",ui->toolBar->orientation());
    st->setValue("toolbar/style",ui->toolBar->toolButtonStyle());
    st->setValue("editor/font",ui->plainTextEdit->font());
}
