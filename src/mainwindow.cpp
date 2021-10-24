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

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    // Initialize Text Editor
    m_texteditor = new hyper::TextEditor(this);
    this->setCentralWidget(m_texteditor);
    // Initialize StatusBar
    m_statusbar = new hyper::StatusBar();
    this->setStatusBar(m_statusbar);
    // Connecting signals
    // Verify if exit of the app
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onActionExit()));
    connect(m_texteditor, SIGNAL(textChanged()), this,
            SLOT(onActionDocumentChanged()));
    // MenuBarActions
    // Menu File
    connect(m_ui->actionNew, SIGNAL(triggered(bool)),  this, SLOT(onActionNew()));
    connect(m_ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(onActionOpen()));
    connect(m_ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(onActionSave()));
    connect(m_ui->actionSaveAs,SIGNAL(triggered(bool)), this, SLOT(onActionSaveAs()));
    connect(m_ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(onActionExit()));
    // Menu Edit
    connect(m_ui->actionUndo, SIGNAL(triggered(bool)), this, SLOT(onActionUndo()));
    connect(m_ui->actionRedo, SIGNAL(triggered(bool)), this, SLOT(onActionRedo()));
    connect(m_ui->actionCut, SIGNAL(triggered(bool)), this, SLOT(onActionCut()));
    connect(m_ui->actionCopy, SIGNAL(triggered(bool)), this, SLOT(onActionCopy()));
    connect(m_ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(onActionPaste()));
    connect(m_ui->actionSelect_All, SIGNAL(triggered(bool)), this,
            SLOT(onActionSelectAllText()));
    // Menu View
    connect(m_ui->actionVisible_MenuBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionMenubar()));
    connect(m_ui->actionVisible_ToolBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionToolbar()));
    connect(m_ui->actionMovable_ToolBar, SIGNAL(toggled(bool)),
            this, SLOT(onActionToolbar()));
    //    connect(ui->actionVisible_StatusBar, SIGNAL(toggled(bool)),
    //            this, SLOT(onActionStatusbar()));
    connect(m_ui->actionToolbar_IconsOnly, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleIconsOnly()));
    connect(m_ui->actionToolbar_TextOnly, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleTextOnly()));
    connect(m_ui->actionToolbar_TextBesideIcons, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleTextBesideIcons()));
    connect(m_ui->actionToolbar_TextUnderIcons, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleTextUnderIcons()));
    connect(m_ui->actionToolbar_Follow, SIGNAL(triggered(bool)),
            this, SLOT(onActionToolbarStyleFollow()));
    // Menu Help
    connect(m_ui->actionAbout_Hyper, SIGNAL(triggered(bool)),
            this, SLOT(onActionAboutHyper()));
    connect(m_ui->actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    // Toolbar setup
    setupToolbar();
    // Read the configuration
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete m_texteditor;
    delete m_statusbar;
    delete m_ui;

}

void MainWindow::loadFile(QString name)
{
    m_currentfile = name;
    // Send a message to statusbar
    m_statusbar->sendMessage("File opened");
    // Set new window title
    this->setWindowTitle(m_currentfile.name());
    // Read text and put in Text Editor
    m_texteditor->setText(m_currentfile.read());
}

void MainWindow::storeSettings()
{
    st.setValue("window/geometry", this->geometry());
    st.setValue("window/hidden_menubar", m_ui->menubar->isHidden());
    st.setValue("window/hidden_statusbar", m_ui->statusbar->isHidden());
    st.setValue("toolbar/hidden", m_ui->toolBar->isHidden());
    st.setValue("toolbar/movable", m_ui->toolBar->isMovable());
    st.setValue("toolbar/geometry", m_ui->toolBar->geometry());
    st.setValue("toolbar/orientation", m_ui->toolBar->orientation());
    st.setValue("toolbar/style", m_ui->toolBar->toolButtonStyle());
}

void MainWindow::loadSettings()
{
    this->setGeometry(st.value("window/geometry",
                                QRect(180,150,700,360)).toRect());
    m_ui->menubar->setHidden(st.value("window/hidden_menubar").toBool());
    m_ui->statusbar->setHidden(st.value("window/hidden_statusbar").toBool());
    m_ui->toolBar->setHidden(st.value("toolbar/hidden").toBool());
    m_ui->toolBar->setMovable(st.value("toolbar/movable").toBool());
    m_ui->toolBar->setGeometry(st.value("toolbar/geometry").toRect());
    m_ui->toolBar->setToolButtonStyle(
        st.value("toolbar/style").value<Qt::ToolButtonStyle>());
}

bool MainWindow::documentModified()
{
    if(!m_currentfile.isSaved()){
        if(m_texteditor->document()->isModified()){
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
    m_ui->toolBar->addAction(m_ui->actionNew);
    m_ui->toolBar->addAction(m_ui->actionOpen);
    m_ui->toolBar->addAction(m_ui->actionSave);
    m_ui->toolBar->addSeparator();
    m_ui->toolBar->addAction(m_ui->actionRedo);
    m_ui->toolBar->addAction(m_ui->actionUndo);
    m_ui->toolBar->addAction(m_ui->actionCut);
    m_ui->toolBar->addAction(m_ui->actionCopy);
    m_ui->toolBar->addAction(m_ui->actionPaste);

    // Checking
    if(m_ui->menubar->isHidden() == false)
        m_ui->actionVisible_MenuBar->setChecked(true);
    if(st.value("toolbar/movable").toBool() == true)
        m_ui->actionMovable_ToolBar->setChecked(true);
    if(st.value("toolbar/hidden").toBool() == true)
        m_ui->actionVisible_ToolBar->setChecked(true);
    if(m_ui->statusbar->isHidden() == false)
        m_ui->actionVisible_StatusBar->setChecked(true);
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
    m_currentfile.setSaved(false);
    this->setWindowTitle("*" + m_currentfile.name());
}

void MainWindow::onActionNew()
{
    if(!m_currentfile.isSaved())
        documentModified();
    // Clear the buffer text and the current file
    m_currentfile = QString();
    m_texteditor->setPlainText(QString());
    // Send a message to statusbar
    m_statusbar->sendMessage("New file");
        // Set new window title
    this->setWindowTitle("untitled");
    m_currentfile.setSaved(false);
}

void MainWindow::onActionSave()
{
    // Verify for the current file,
    // if empty launch a dialog for save the file buffer
    // check io errors
    bool ok;
    if(m_currentfile.isEmpty()) {
        QString file = QFileDialog::getSaveFileName(this, "Save");
        m_currentfile = file;
        // Save the new file
        ok = m_currentfile.save(m_texteditor->toPlainText());
    } else {
        // Save the current file
        ok = m_currentfile.save(m_texteditor->toPlainText());
    }
    if(ok) {
        m_statusbar->sendMessage("File saved successfully");
    } else {
        m_statusbar->sendMessage("Cannot save the file");
    }
}

void MainWindow::onActionSaveAs()
{
    // Always launch a dialog and get a new filename
    QString newfile = QFileDialog::getSaveFileName(this, "Save as");
    m_currentfile = newfile;
    bool ok = m_currentfile.save(m_texteditor->toPlainText());
    if(ok) {
        m_statusbar->sendMessage("File saved successfully");
    } else {
        m_statusbar->sendMessage("Cannot save the file");
    }
}

void MainWindow::onActionMenubar()
{
    // Get the state of menubar
    if(m_ui->actionVisible_MenuBar->isChecked()==true){
        m_ui->menubar->setVisible(true);
    }else{
        m_ui->menubar->setVisible(false);
    }
}

void MainWindow::onActionToolbar()
{
    // Get the state of toolbar
    // is visible
    if(m_ui->actionVisible_ToolBar->isChecked()==true){
        m_ui->toolBar->setVisible(false);
    }else{
        m_ui->toolBar->setVisible(true);
    }
    // is movable
    if(m_ui->actionMovable_ToolBar->isChecked()==true){
        m_ui->toolBar->setMovable(true);
    }else{
        m_ui->toolBar->setMovable(false);
    }
}

// Style of the toolbar icons and text action
void MainWindow::onActionToolbarStyleIconsOnly()
{
    m_ui->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void MainWindow::onActionToolbarStyleTextOnly()
{
    m_ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
}

void MainWindow::onActionToolbarStyleTextBesideIcons()
{
    m_ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void MainWindow::onActionToolbarStyleTextUnderIcons()
{
    m_ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void MainWindow::onActionToolbarStyleFollow()
{
    m_ui->toolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
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
    if(m_texteditor->isUndoRedoEnabled()) {
        m_texteditor->undo();
    }
}

void MainWindow::onActionRedo()
{
    if(m_texteditor->isUndoRedoEnabled()) {
        m_texteditor->redo();
    }
}

void MainWindow::onActionCut()
{
    m_texteditor->cut();
}

void MainWindow::onActionCopy()
{
    m_texteditor->copy();
}

void MainWindow::onActionPaste()
{
    if(m_texteditor->canPaste()) {
        m_texteditor->paste();
    } else {
        // Send a error message to statusbar
        m_statusbar->sendMessage("You cant paste in this file");
    }
}

void MainWindow::onActionSelectAllText()
{
    m_texteditor->selectAll();
}
