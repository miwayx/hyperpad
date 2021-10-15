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

#include "mainwindow.hpp"
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
    m_saved = false;

    // Connecting signals
    // verify if exit of the app
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(actExit()));
    // document changed
    connect(ui->plainTextEdit,SIGNAL(textChanged()),this,SLOT(actDocChanged()));
    // MenuBar
    // file
    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(actNew()));
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(actOpen()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(actSave()));
    connect(ui->actionSaveAs,SIGNAL(triggered(bool)),this,SLOT(actSaveas()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(actExit()));
    // view
    connect(ui->actionVisible_MenuBar,SIGNAL(toggled(bool)),
            this,SLOT(actMenubar()));
    connect(ui->actionVisible_StatusBar,SIGNAL(toggled(bool)),
            this,SLOT(actStatusbar()));
    connect(ui->actionVisible_ToolBar,SIGNAL(toggled(bool)),
            this,SLOT(actToolbar()));
    connect(ui->actionMovable_ToolBar,SIGNAL(toggled(bool)),
            this,SLOT(actToolbar()));
    // view toolbar style
    connect(ui->actionToolbar_IconsOnly,SIGNAL(triggered(bool)),
            this,SLOT(actToolbarStyleIconsOnly()));
    connect(ui->actionToolbar_TextOnly,SIGNAL(triggered(bool)),
            this,SLOT(actToolbarStyleTextOnly()));
    connect(ui->actionToolbar_TextBesideIcons,SIGNAL(triggered(bool)),
            this,SLOT(actToolbarStyleTextBesideIcons()));
    connect(ui->actionToolbar_TextUnderIcons,SIGNAL(triggered(bool)),
            this,SLOT(actToolbarStyleTextUnderIcons()));
    connect(ui->actionToolbar_Follow,SIGNAL(triggered(bool)),
            this,SLOT(actToolbarStyleFollow()));
    // text
    connect(ui->actionFind,SIGNAL(triggered(bool)),this,SLOT(actFind()));
    connect(ui->actionFont,SIGNAL(triggered(bool)),this,SLOT(actNewfont()));
    // help
    connect(ui->actionAbout_Hyper,SIGNAL(triggered(bool)),
            this,SLOT(actAboutHyper()));
    connect(ui->actionAbout_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));

    // Read the configuration
    readAllSettings();
    // Toolbar setup
    setupToolbarAndStatusbar();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete status;
}

// Settings
void MainWindow::saveAllSettings()
{
    st.setValue("window/geometry",this->geometry());
    st.setValue("window/hidden_menubar", ui->menubar->isHidden());
    st.setValue("window/hidden_statusbar",ui->statusbar->isHidden());
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
    ui->menubar->setHidden(st.value("window/hidden_menubar").toBool());
    ui->statusbar->setHidden(st.value("window/hidden_statusbar").toBool());
    //Toolbar
    // get state of toolbar
    ui->toolBar->setHidden(st.value("toolbar/hidden").toBool());
    ui->toolBar->setMovable(st.value("toolbar/movable").toBool());
    ui->toolBar->setGeometry(st.value("toolbar/geometry").toRect());
    //ui->toolBar->setOrientation(st.value("toolbar/orientation").value<Qt::Orientation>());
    ui->toolBar->setToolButtonStyle(st.value("toolbar/style").value<Qt::ToolButtonStyle>());
    //Editor
    ui->plainTextEdit->setFont(st.value("editor/font").value<QFont>());
}

void MainWindow::setupToolbarAndStatusbar()
{
    //ui->toolBar->addAction(ui->actionFind);
    // Actions
    ui->toolBar->addAction(ui->actionNew);
    ui->toolBar->addAction(ui->actionOpen);
    ui->toolBar->addAction(ui->actionSave);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionRedo);
    ui->toolBar->addAction(ui->actionUndo);
    ui->toolBar->addAction(ui->actionCut);
    ui->toolBar->addAction(ui->actionCopy);
    ui->toolBar->addAction(ui->actionPaste);

    status = new QLabel;
    ui->statusbar->addWidget(status);

    // Checking
    if(ui->menubar->isHidden() == false)
        ui->actionVisible_MenuBar->setChecked(true);
    if(st.value("toolbar/movable").toBool() == true)
        ui->actionMovable_ToolBar->setChecked(true);
    if(st.value("toolbar/hidden").toBool() == true)
        ui->actionVisible_ToolBar->setChecked(true);
    if(ui->statusbar->isHidden() == false)
        ui->actionVisible_StatusBar->setChecked(true);
}

//
// openfile is used for open a file from the terminal and for the actions
void MainWindow::openfile(QString filename)
{
    // filename is now the currentfile open
    currentfile = filename;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
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
    status->setText("File "+filename+" open");
    m_saved = false;
}

void MainWindow::savefile(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        // Launch a message error
        status->setText("Cannot save the file "+file.errorString());
        return;
    }
    QTextStream out(&file);
    // get the text in the editor and save it
    QString txt = ui->plainTextEdit->toPlainText();
    out << txt;
    file.close();
    // send a message to the statusbar
    this->setWindowTitle(filename);
    status->setText("File "+filename+" saved");
    m_saved = true;
}

// Check for the document
bool MainWindow::documentModified()
{
    if(!m_saved){
        if(ui->plainTextEdit->document()->isModified()){
            // if the document change launch a message
            QMessageBox *msgBox = new QMessageBox(this);
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
                actSave();
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

//Actions
void MainWindow::actExit()
{
    if(!documentModified()){
        // save the preferences
        saveAllSettings();
        qApp->quit();
    }
}

// document changed
void MainWindow::actDocChanged()
{
    m_saved = false;
    status->setText("File "+currentfile);
    this->setWindowTitle("*"+currentfile);
}

// create a new file
void MainWindow::actNew()
{
    if(!m_saved){
        documentModified();
        // just clear the text and the current file
        currentfile.clear();
        ui->plainTextEdit->setPlainText(QString());

        this->setWindowTitle("untitled");
        status->setText("New file");
        m_saved = false;
    }else{
       // just clear the text and the current file
       currentfile.clear();
       ui->plainTextEdit->setPlainText(QString());

       this->setWindowTitle("untitled");
       status->setText("New file");
       m_saved = false;
    }

}

// open a file with dialog
void MainWindow::actOpen()
{
    // Get the filename to open
    QString filename = QFileDialog::getOpenFileName(this,"Open a file");
    openfile(filename);
}

// save a file
void MainWindow::actSave()
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

// save as
void MainWindow::actSaveas()
{
    QString filename;
    // Get the file
    filename = QFileDialog::getSaveFileName(this,"Save As",QDir::currentPath());
    // currentfile now is the new file selected
    currentfile = filename;
    savefile(filename);
}

// find a text
void MainWindow::actFind()
{
    // Get the thext to find
    // **WARNING** This method is incomplete
    QString f = QInputDialog::getText(this,"Find","Text:");
    ui->plainTextEdit->find(f);
}

// felect a new Font
void MainWindow::actNewfont()
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

// get the state of the menubar action
void MainWindow::actMenubar()
{
   if(ui->actionVisible_MenuBar->isChecked()==true){
       ui->menubar->setVisible(true);
   }else{
       ui->menubar->setVisible(false);
   }
}

// get the state of the statusbar actions
void MainWindow::actStatusbar()
{
    // If the signal toggle emit true the action is marcked
    if(ui->actionVisible_StatusBar->isChecked()==true){
        ui->statusbar->setVisible(true);
    }else{
        ui->statusbar->setVisible(false);
    }
}

// get the state of the toolbar actions
void MainWindow::actToolbar()
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
void MainWindow::actToolbarStyleIconsOnly()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void MainWindow::actToolbarStyleTextOnly()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
}

void MainWindow::actToolbarStyleTextBesideIcons()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::actToolbarStyleTextUnderIcons()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MainWindow::actToolbarStyleFollow()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
}

// this is the application about dialog
void MainWindow::actAboutHyper()
{
    QMessageBox *msg = new QMessageBox(this);
    msg->setWindowTitle("About HyperPad");
    msg->setIconPixmap(QPixmap(QString(":/ico/res/hyper_ico.png")));
    QString text = "Version: "+qApp->applicationVersion()+"\n"+
        "Libraries: \nQt 5.15.2 (GCC 10.2.0, 64 bit)\n"+"\n"+"(C) 2021 Ern \n"+
        qApp->organizationDomain()+"\n\nGNU General Public Licence Version 3\n";
    msg->setText(text);
    msg->exec();
}

//__END__
