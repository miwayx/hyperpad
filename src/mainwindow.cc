/*
 * mainwindow.cc
 *
 * Copyright 2021 Ern <ern8642@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QFontDialog>
#include <QFont>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    this->setWindowIcon(QIcon(QIcon::fromTheme("text-editor",QIcon(":/ico/res/qtext_ico-svg"))));
    // Connecting signals
    // verify if exit of the app
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(act_exit()));
    // MEnuBar
    //File
    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(act_new()));
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(act_open()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(act_save()));
    connect(ui->actionSaveAs,SIGNAL(triggered(bool)),this,SLOT(act_saveas()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(act_exit()));
    //View
    connect(ui->actionVisible_StatusBar,SIGNAL(toggled(bool)),this,SLOT(act_statusbar()));
    connect(ui->actionVisible_ToolBar,SIGNAL(toggled(bool)),this,SLOT(act_toolbar()));
    connect(ui->actionMovable_ToolBar,SIGNAL(toggled(bool)),this,SLOT(act_toolbar()));
    // View toolbar style
    connect(ui->actionToolbar_IconsOnly,SIGNAL(triggered(bool)),this,SLOT(act_toolbar_style_icons_only()));
    connect(ui->actionToolbar_TextOnly,SIGNAL(triggered(bool)),this,SLOT(act_toolbar_style_text_only()));
    connect(ui->actionToolbar_TextBesideIcons,SIGNAL(triggered(bool)),this,SLOT(act_toolbar_style_text_beside_icons()));
    connect(ui->actionToolbar_TextUnderIcons,SIGNAL(triggered(bool)),this,SLOT(act_toolbar_style_text_under_icons()));
    connect(ui->actionToolbar_Follow,SIGNAL(triggered(bool)),this,SLOT(act_toolbar_style_follow()));
    //Text
    connect(ui->actionFind,SIGNAL(triggered(bool)),this,SLOT(act_find()));
    connect(ui->actionFont,SIGNAL(triggered(bool)),this,SLOT(act_newfont()));
    // Help
    connect(ui->actionAbout_qText,SIGNAL(triggered(bool)),this,SLOT(act_about_qtext()));
    connect(ui->actionAbout_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));

    //toolbar setup
    setupToolbarAndStatusbar();
    // Read the configuration
    readAllSettings();
    saved = false;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete status;
}

// Settings
void MainWindow::saveAllSettings()
{
    //Window
    st.setValue("window/geometry",this->geometry());
    st.setValue("window/hidden_statusbar",ui->statusbar->isHidden());
    //st.setValue("window/fullscreen",this->isFullScreen());
    st.setValue("toolbar/hidden",ui->toolBar->isHidden());
    st.setValue("toolbar/movable",ui->toolBar->isMovable());
    st.setValue("toolbar/geometry",ui->toolBar->geometry());
    st.setValue("toolbar/orientation",ui->toolBar->orientation());
    st.setValue("toolbar/style",ui->toolBar->toolButtonStyle());
    st.setValue("editor/font",ui->plainTextEdit->font());


}
void MainWindow::readAllSettings()
{
    //Window
    // get the window geomery
    this->setGeometry(st.value("window/geometry",QRect(180,150,700,360)).toRect());
    ui->statusbar->setHidden(st.value("window/hidden_statusbar").toBool());
    //toolbar
    // get state of toolbar
    ui->toolBar->setHidden(st.value("toolbar/hidden").toBool());
    ui->toolBar->setMovable(st.value("toolbar/movable").toBool());
    ui->toolBar->setGeometry(st.value("toolbar/geometry").toRect());
    //ui->toolBar->setOrientation(st.value("toolbar/orientation").value<Qt::Orientation>());
    ui->toolBar->setToolButtonStyle(st.value("toolbar/style").value<Qt::ToolButtonStyle>());
    //editor
    ui->plainTextEdit->setFont(st.value("editor/font").value<QFont>());
}
void MainWindow::setupToolbarAndStatusbar()
{

    ui->toolBar->addAction(ui->actionNew);
    ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addAction(ui->actionSave);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionRedo);
    ui->toolBar->addAction(ui->actionUndo);
    ui->toolBar->addAction(ui->actionCut);
    ui->toolBar->addAction(ui->actionCopy);
    ui->toolBar->addAction(ui->actionPaste);
    ui->toolBar->addAction(ui->actionDelete);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionFont);
    ui->toolBar->addAction(ui->actionFind);

    status = new QLabel;
    ui->statusbar->addWidget(status);

    // Chekeando
    if(st.value("toolbar/movable").toBool()==true){
        ui->actionMovable_ToolBar->setChecked(true);
    }
    if(st.value("toolbar/hidden").toBool()==true){
        ui->actionVisible_ToolBar->setChecked(true);
    }
    if(st.value("window/hidden_statusbar").toBool()==true){
        ui->actionVisible_StatusBar->setChecked(true);
    }
}

//
// openfile is used for open a file from the terminal and for the actions
void MainWindow::openfile(QString filename)
{
    // filename is now the currentfile open
    currentfile = filename;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){

        //QMessageBox::warning(this,"Cannot open the file",file.errorString());
        status->setText("Cannot open the file "+file.errorString());
        return;
    }
    // set the window title
    this->setWindowTitle(filename);
    QTextStream in(&file);
    QString txt = in.readAll();
    // set the file content in the editor
    ui->plainTextEdit->setPlainText(txt);
    file.close();
    // send a message to the statusbar
    QString fstatus = "File "+filename+" open";
    status->setText(fstatus);
    saved = false;
}

void MainWindow::savefile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        // Launch a message error
        //QMessageBox::warning(this,"Cannot save the file",file.errorString());
        status->setText("Cannot save the file "+file.errorString());
        return;
    }
    QTextStream out(&file);
    // get the text in the editor and save it
    QString txt = ui->plainTextEdit->toPlainText();
    out << txt;
    file.close();
    // send a message to the statusbar
    QString fstatus = "File "+filename+" saved";
    status->setText(fstatus);
    saved = true;
}

// Verify for the document
bool MainWindow::documentModified()
{
    if(!saved){
        if(ui->plainTextEdit->document()->isModified()){
            // if the document have a change launch a message
            QMessageBox *msgBox = new QMessageBox(this);
            //msgBox->setModal(true);
            msgBox->setText("The document has been modified.");
            msgBox->setInformativeText("Do you want to save your changes?");
            msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
            msgBox->setDefaultButton(QMessageBox::Save);
            // take the selection
            int ret = msgBox->exec();
            switch(ret)
            {
            // This case save the file and the preferences
            case QMessageBox::Save:
                // Save the file and all settings
                act_save();
                saveAllSettings();
                return true;
            case QMessageBox::Discard:
                return false;
            default:
                return false;
           }
        }else{
            return false;
        }
        return false;
    }
    return true;
}

//actions
void MainWindow::act_exit()
{
    if(!documentModified()){
        // save the preferences
        saveAllSettings();
        qApp->quit();
    }
}

// create a new file
void MainWindow::act_new()
{
    if(!documentModified()){
       // just clear the text and the current file
       currentfile.clear();
       ui->plainTextEdit->setPlainText(QString());

       this->setWindowTitle("untitled");
       status->setText("New file");
       saved = false;
    }

}

// open a file with dialog
void MainWindow::act_open()
{
    // Get the filename to open
    QString filename = QFileDialog::getOpenFileName(this,"Open a file");
    openfile(filename);
}
// Save a file
void MainWindow::act_save()
{
    // Verify for the current file, if empty launch a dialog for save the file
    QString filename;
    if(currentfile.isEmpty()){
        filename = QFileDialog::getSaveFileName(this,"Save",QDir::currentPath());
        // the current file now is the file selected
        currentfile = filename;
    }else{
        // if the current file not empty, filename take the reference
        filename = currentfile;
    }
    savefile(filename);
}

// Save As
void MainWindow::act_saveas()
{
    QString filename;
    // Get the file
    filename = QFileDialog::getSaveFileName(this,"Save",QDir::currentPath());
    // currentfile now is the new file selected
    currentfile = filename;
    savefile(filename);
}

// Find a text
void MainWindow::act_find()
{
    // Get the thext to find
    // **WARNING** This method is incomplete
    QString f = QInputDialog::getText(this,"Find","Text:");
    ui->plainTextEdit->find(f);
}

// Select a new Font
void MainWindow::act_newfont()
{
    // This launch te font dialog and verify this, if all is ok, set the font
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->plainTextEdit->setFont(font);
        // Send a message to the statusbar
        status->setText("Font changed susefully");
    }else{
        status->setText("Cannot change the font");
    }
}

// get the state of the statusbar actions
void MainWindow::act_statusbar()
{
    // If the signal toggle emit true the action is marcked
    if(ui->actionVisible_StatusBar->isChecked()==true){
        ui->statusbar->setVisible(false);
    }else{
        ui->statusbar->setVisible(true);
    }
}
// get the state of the toolbar actions
void MainWindow::act_toolbar()
{
    // is visible
    if(ui->actionVisible_ToolBar->isChecked()==true){
        ui->toolBar->setVisible(false);
    }else{
        ui->toolBar->setVisible(true);
    }
    // is movable
    if(ui->actionMovable_ToolBar->isChecked()==true){
        ui->toolBar->setMovable(true);
    }else{
        ui->toolBar->setMovable(false);
    }
}
// style of the toolbar icons and text action
void MainWindow::act_toolbar_style_icons_only()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void MainWindow::act_toolbar_style_text_only()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
}

void MainWindow::act_toolbar_style_text_beside_icons()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::act_toolbar_style_text_under_icons()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}
void MainWindow::act_toolbar_style_follow()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
}

// This is the application about dialog
void MainWindow::act_about_qtext()
{
    QMessageBox *msg = new QMessageBox(this);
    msg->setWindowTitle("About qText");
    msg->setIconPixmap(QPixmap(QString(":/ico/res/qtext_ico.svg")));
    QString text = "Version: "+qApp->applicationVersion()+"\n"+
        "Libraries: \nQt 5.15.2 (GCC 10.2.0, 64 bit)\n"+"\n"+"(C) 2021 Ern \n"+
        qApp->organizationDomain()+"\n\nGNU General Public Licence Version 3\n";
    msg->setText(text);
    msg->exec();
}

//__END__
