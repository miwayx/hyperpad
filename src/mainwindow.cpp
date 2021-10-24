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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize Text Editor
    _texteditor = new hyper::TextEditor(this);
    this->setCentralWidget(_texteditor);
    // Initialize StatusBar
    _statusbar = new hyper::StatusBar();
    this->setStatusBar(_statusbar);
    // Connecting signals
    // Verify if exit of the app
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onActionExit()));
    connect(_texteditor, SIGNAL(textChanged()), this,
            SLOT(onActionDocumentChanged()));
    // MenuBarActions
    // Menu File
    connect(ui->actionNew, SIGNAL(triggered(bool)),  this, SLOT(onActionNew()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(onActionOpen()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(onActionSave()));
    connect(ui->actionSaveAs,SIGNAL(triggered(bool)), this, SLOT(onActionSaveAs()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(onActionExit()));
    // Menu Edit
    connect(ui->actionUndo, SIGNAL(triggered(bool)), this, SLOT(onActionUndo()));
    connect(ui->actionRedo, SIGNAL(triggered(bool)), this, SLOT(onActionRedo()));
    connect(ui->actionCut, SIGNAL(triggered(bool)), this, SLOT(onActionCut()));
    connect(ui->actionCopy, SIGNAL(triggered(bool)), this, SLOT(onActionCopy()));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(onActionPaste()));
    connect(ui->actionSelect_All, SIGNAL(triggered(bool)), this,
            SLOT(onActionSelectAllText()));
    // Menu View
    connect(ui->actionVisible_MenuBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionMenubar()));
    connect(ui->actionVisible_ToolBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionToolbar()));
    connect(ui->actionMovable_ToolBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionToolbar()));
    //    connect(ui->actionVisible_StatusBar, SIGNAL(toggled(bool)),
    //            this, SLOT(onActionStatusbar()));
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
    // Menu Help
    connect(ui->actionAbout_Hyper, SIGNAL(triggered(bool)),
            this, SLOT(onActionAboutHyper()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    // Toolbar setup
    setupToolbar();
    // Read the configuration
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete _texteditor;
    delete _statusbar;
    delete ui;

}

void MainWindow::loadFile(QString name)
{
    _currentfile = name;
    // Send a message to statusbar
    _statusbar->sendMessage("File opened");
    // Set new window title
    this->setWindowTitle(_currentfile.name());
    // Read text and put in Text Editor
    _texteditor->setText(_currentfile.read());
}

void MainWindow::storeSettings()
{
    st.setValue("window/geometry", this->geometry());
    st.setValue("window/hidden_menubar", ui->menubar->isHidden());
    st.setValue("window/hidden_statusbar", ui->statusbar->isHidden());
    st.setValue("toolbar/hidden", ui->toolBar->isHidden());
    st.setValue("toolbar/movable", ui->toolBar->isMovable());
    st.setValue("toolbar/geometry", ui->toolBar->geometry());
    st.setValue("toolbar/orientation", ui->toolBar->orientation());
    st.setValue("toolbar/style", ui->toolBar->toolButtonStyle());
}

void MainWindow::loadSettings()
{
    this->setGeometry(st.value("window/geometry",
                                QRect(180,150,700,360)).toRect());
    ui->menubar->setHidden(st.value("window/hidden_menubar").toBool());
    ui->statusbar->setHidden(st.value("window/hidden_statusbar").toBool());
    ui->toolBar->setHidden(st.value("toolbar/hidden").toBool());
    ui->toolBar->setMovable(st.value("toolbar/movable").toBool());
    ui->toolBar->setGeometry(st.value("toolbar/geometry").toRect());
    ui->toolBar->setToolButtonStyle(
        st.value("toolbar/style").value<Qt::ToolButtonStyle>());
}

bool MainWindow::documentModified()
{
    if(!_currentfile.isSaved()){
        if(_texteditor->document()->isModified()){
            // If the document change launch a message
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("The document has been modified.");
            msgBox->setInformativeText("Do you want to save your changes?");
            msgBox->setStandardButtons(QMessageBox::Save |
                                       QMessageBox::Discard);
            msgBox->setDefaultButton(QMessageBox::Save);
            int return_code = msgBox->exec();
            switch(return_code)
            {
            // Save the file and the preferences
            case QMessageBox::Save:
                onActionSave();
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

void MainWindow::setupToolbar()
{
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

void MainWindow::onActionOpen()
{
    // Check for the document
    documentModified();
    QString file = QFileDialog::getOpenFileName(this, "Open a file");
    loadFile(file);

}

void MainWindow::onActionExit()
{
    if(!documentModified()){
        // Save the preferences
        storeSettings();
        exit(0);
    }
}

void MainWindow::onActionDocumentChanged()
{
    // Set currentFile not saved
    _currentfile.setSaved(false);
    this->setWindowTitle("*" + _currentfile.name());
}

void MainWindow::onActionNew()
{
    if(!_currentfile.isSaved())
        documentModified();
    // Clear the buffer text and the current file
    _currentfile = QString();
    _texteditor->setPlainText(QString());
    // Send a message to statusbar
    _statusbar->sendMessage("New file");
        // Set new window title
    this->setWindowTitle("untitled");
    _currentfile.setSaved(false);
}

void MainWindow::onActionSave()
{
    // Verify for the current file,
    // if empty launch a dialog for save the file buffer
    // check io errors
    bool ok;
    if(_currentfile.isEmpty()) {
        QString file = QFileDialog::getSaveFileName(this, "Save");
        _currentfile = file;
        // Save the new file
        ok = _currentfile.save(_texteditor->toPlainText());
    } else {
        // Save the current file
        ok = _currentfile.save(_texteditor->toPlainText());
    }
    if(ok) {
        _statusbar->sendMessage("File saved successfully");
    } else {
        _statusbar->sendMessage("Cannot save the file");
    }
}

void MainWindow::onActionSaveAs()
{
    // Always launch a dialog and get a new filename
    QString newfile = QFileDialog::getSaveFileName(this, "Save as");
    _currentfile = newfile;
    bool ok = _currentfile.save(_texteditor->toPlainText());
    if(ok) {
        _statusbar->sendMessage("File saved successfully");
    } else {
        _statusbar->sendMessage("Cannot save the file");
    }
}

void MainWindow::onActionMenubar()
{
    // Get the state of menubar
    if(ui->actionVisible_MenuBar->isChecked()==true){
        ui->menubar->setVisible(true);
    }else{
        ui->menubar->setVisible(false);
    }
}

void MainWindow::onActionToolbar()
{
    // Get the state of toolbar
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

// Style of the toolbar icons and text action
void MainWindow::onActionToolbarStyleIconsOnly()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void MainWindow::onActionToolbarStyleTextOnly()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
}

void MainWindow::onActionToolbarStyleTextBesideIcons()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::onActionToolbarStyleTextUnderIcons()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MainWindow::onActionToolbarStyleFollow()
{
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
}

void MainWindow::onActionAboutHyper()
{
    QMessageBox *msg = new QMessageBox(this);
    msg->setWindowTitle("About HyperPad");
    msg->setIconPixmap(QPixmap(QString(":/icons/hyper_ico.png")));
    QString text =
       // Version and libs
      "Version: " + qApp->applicationVersion() +
      "\nLibraries:\n" +
        "Qt 5.15.2 (GCC 10.2.0, 64 bit)\n" +
      // Author
      "Authors:\n" +
        "(C) 2021 Ernest C. Suarez <ernestcsuarez@gmail.com>\n" +
      // Licence
      "\nLicence: GNU General Public Licence Version 3\n" +
        qApp->organizationDomain();
    msg->setText(text);
    msg->exec();
}

void MainWindow::onActionUndo()
{
    if(_texteditor->isUndoRedoEnabled()) {
        _texteditor->undo();
    }
}

void MainWindow::onActionRedo()
{
    if(_texteditor->isUndoRedoEnabled()) {
        _texteditor->redo();
    }
}

void MainWindow::onActionCut()
{
    _texteditor->cut();
}

void MainWindow::onActionCopy()
{
    _texteditor->copy();
}

void MainWindow::onActionPaste()
{
    if(_texteditor->canPaste()) {
        _texteditor->paste();
    } else {
        // Send a error message to statusbar
        _statusbar->sendMessage("You cant paste in this file");
    }
}

void MainWindow::onActionSelectAllText()
{
    _texteditor->selectAll();
}
