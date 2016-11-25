#include "qlmainwindow.h"
//#include "ui_qlmainwindow.h"

#include "qlmisc.h"
#include "qlproject.h"
#include "qlprocess.h"
#include "qlghdloptionsdialog.h"

#include <QApplication>
#include <QStatusBar>
#include <QDockWidget>
#include <QTextEdit>
#include <QTreeView>
#include <QHeaderView>
#include <QMenuBar>
#include <QFileSystemModel>
#include <QDir>
#include <QItemSelectionModel>
#include <QAbstractItemView>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>
#include <QModelIndexList>
#include <QList>
#include <QFile>
#include <exception>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <QFileDialog>
#include <QSplitter>
#include <QMessageBox>
#include <QtGlobal>

QLMainWindow::QLMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //mainWindow = new QLMainWindow();
    //mainWindow->setupUi(this);

    createWidgets();
    createLayout();
    createActions();
    createConnections();

    createMenus();

    QApplication::setApplicationName(tr("QuickLogic"));

    setWindowTitle(QApplication::applicationName());

    QString message = tr("Choose an action to start");
    statusBar()->showMessage(message);

    project = new QLProject();

    //subproc = new QProcess(this);

    //subproc->setProcessChannelMode(QProcess::MergedChannels);

}

QLMainWindow::~QLMainWindow()
{
    delete project;

    delete dirView;
    delete fileView;
    delete dirModel;
    delete fileModel;
    delete splitter;

    delete newFileAct;
    delete delFileAct;
    delete renFileAct;
    delete openFileAct;

    delete settingsAct;

    delete aboutAct;

    delete ghdlAnalyzeAct;
    delete ghdlBuildExecAct;
    delete ghdlRunExecAct;
    delete gtkwaveAct;

    //delete mainWindow;

}

void QLMainWindow::createWidgets()
{
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::currentPath());
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setReadOnly(true);

    fileModel = new QFileSystemModel(this);
    fileModel->setReadOnly(true);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

    splitter = new QSplitter;

    dirView = new QTreeView(splitter);

    fileView = new QTreeView(splitter);

    dirView->setModel(dirModel);
    dirView->header()->setStretchLastSection(true);
    dirView->header()->setSortIndicator(0, Qt::AscendingOrder);
    dirView->header()->setSortIndicatorShown(true);
    dirView->header()->setSectionsClickable(true);

    QModelIndex index = dirModel->index(QDir::currentPath());

    dirView->expand(index);
    dirView->scrollTo(index);
    dirView->resizeColumnToContents(0);
    dirView->setAnimated(false);
    dirView->setIndentation(20);
    dirView->setSortingEnabled(true);
    dirView->setExpandsOnDoubleClick(true);

    fileView->setModel(fileModel);
    fileView->setRootIndex(
        fileModel->setRootPath(dirModel->fileInfo(index).absoluteFilePath()));

    fileView->header()->setStretchLastSection(true);
    fileView->header()->setSortIndicator(0, Qt::AscendingOrder);
    fileView->header()->setSortIndicatorShown(true);
    fileView->header()->setSectionsClickable(true);

    fileView->resizeColumnToContents(0);
    fileView->setAnimated(false);
    fileView->setSortingEnabled(true);
    fileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    fileView->setItemsExpandable(false);

    dock = new QDockWidget(tr("Output Window"), this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);


    outedit = new QTextEdit(dock);

    dock->setWidget(outedit);

}

void QLMainWindow::createLayout()
{
    setCentralWidget(splitter);

    addDockWidget(Qt::BottomDockWidgetArea, dock);

    resize(800, 600);
}

void QLMainWindow::createActions()
{

    newFileAct = new QAction(tr("&New File"), this);
    newFileAct->setShortcuts(QKeySequence::New);
    newFileAct->setStatusTip(tr("Create a new file"));

    delFileAct = new QAction(tr("&Delete File(s)"), this);
    delFileAct->setShortcut(QKeySequence::Delete);
    delFileAct->setStatusTip(tr("Delete selected file(s)"));

    renFileAct = new QAction(tr("&Change File Name"), this);
    renFileAct->setStatusTip(tr("Change file name"));


    openFileAct = new QAction(tr("&Open File"), this);
    openFileAct->setShortcut(QKeySequence::Open);
    openFileAct->setStatusTip(tr("Open a file"));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit QuickLogic"));

    settingsAct = new QAction(tr("&Settings"), this);
    settingsAct->setStatusTip(tr("Set options"));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("About QuickLogic"));


    ghdlAnalyzeAct = new QAction(tr("Ana&lyze File"), this);
    ghdlAnalyzeAct->setStatusTip(tr("Run GHDL -a on file"));


    ghdlBuildExecAct = new QAction(tr("&Build Testbench"), this);
    ghdlBuildExecAct->setStatusTip(tr("Run GHDL -e on file"));

    ghdlRunExecAct = new QAction(tr("&Run Testbench"), this);
    ghdlRunExecAct->setStatusTip(tr("Run GHDL -r on file"));


    gtkwaveAct = new QAction(tr("&View Waveform"), this);
    gtkwaveAct->setStatusTip(tr("Run Gtkwave on file"));

    ghdlOptionsAct = new QAction(tr("O&ptions"), this);
    ghdlOptionsAct->setStatusTip(tr("Set GHDL Options"));


}

void QLMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(renFileAct);
    fileMenu->addAction(delFileAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(settingsAct);
    //editMenu->addSeparator();

    ghdlMenu = menuBar()->addMenu(tr("&GHDL"));
    ghdlMenu->addAction(ghdlAnalyzeAct);
    ghdlMenu->addAction(ghdlBuildExecAct);
    ghdlMenu->addAction(ghdlRunExecAct);
    ghdlMenu->addAction(gtkwaveAct);
    ghdlMenu->addSeparator();
    ghdlMenu->addAction(ghdlOptionsAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);

}

void QLMainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // context menu for the file tree.
    QMenu menu(this);

    menu.addAction(openFileAct);
    menu.addAction(delFileAct);
    menu.addAction(renFileAct);
    menu.addAction(newFileAct);

    menu.addSeparator();

    menu.addAction(ghdlAnalyzeAct);
    menu.addAction(ghdlBuildExecAct);
    menu.addAction(ghdlRunExecAct);
    menu.addAction(gtkwaveAct);

    menu.exec(event->globalPos());
}

void QLMainWindow::createConnections()
{
    connect(dirView, SIGNAL(clicked(QModelIndex)), this,
            SLOT(clickDirView(QModelIndex)));

    connect(fileView, SIGNAL(doubleClicked(QModelIndex)), this,
            SLOT(doubleClickFileView(QModelIndex)));

    connect(fileModel, SIGNAL(fileRenamed(QString, QString, QString)), this,
            SLOT(fileRenameDone()));

    //auto stopEditingSlot = [&]() { fileModel->setReadOnly(true); };
    //connect(fileView, &QTreeView::doubleClicked, stopEditingSlot);


    connect(newFileAct, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openFileAct, SIGNAL(triggered()), this, SLOT(openFile()));

    connect(renFileAct, SIGNAL(triggered()), this, SLOT(renFile()));
    connect(delFileAct, SIGNAL(triggered()), this, SLOT(delFile()));

    connect(ghdlAnalyzeAct, SIGNAL(triggered()), this, SLOT(analyzeFile()));
    connect(ghdlBuildExecAct, SIGNAL(triggered()), this, SLOT(buildTestBench()));
    connect(ghdlRunExecAct, SIGNAL(triggered()), this, SLOT(runTestBench()));
    connect(gtkwaveAct, SIGNAL(triggered()), this, SLOT(viewWave()));
    connect(ghdlOptionsAct, SIGNAL(triggered()), this, SLOT(setGHDLOptions()));

    connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutQuickLogic()));

}


void QLMainWindow::clickDirView(QModelIndex index)
{
    QString dir = dirModel->fileInfo(index).absoluteFilePath();

    fileView->setRootIndex( fileModel->setRootPath(dir) );

    QDir::setCurrent(dir);
}

void QLMainWindow::doubleClickFileView(QModelIndex index)
{
    if( fileModel->isDir(index) ) {

        openDir(index);
    }
    else {
        QString fileName = fileModel->filePath(index);
        try
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
        }
        catch (const std::exception &e)
        {
            outedit->append("Unable to open file " + fileName + "\n" +
                     qUtf8Printable(e.what()));
        }

    }

}

void QLMainWindow::openDir(QModelIndex index)
{
    fileView->setRootIndex( index );

    QString dir = fileModel->fileInfo(index).absolutePath();

    QDir::setCurrent(dir);

    QModelIndex idx = dirModel->index(dir);

    dirView->expand(idx);
    dirView->scrollTo(idx);

}

void QLMainWindow::openFile()
{
    QString fileName = fileModel->filePath(fileView->currentIndex());
    try
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
    catch (const std::exception &e)
    {
        outedit->append("Unable to open file " + fileName + "\n" +
                 qUtf8Printable(e.what()));
    }
}


void QLMainWindow::renFile()
{
    fileModel->setReadOnly(false);
    fileView->edit(fileView->currentIndex());
}


void QLMainWindow::fileRenameDone()
{
    fileModel->setReadOnly(true);
}


void QLMainWindow::delFile()
{
    // del one or multiple files at once
    // function will ask confirmation for the action
    QItemSelectionModel *selectionModel = fileView->selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();
    int numberOfFiles = 0;
    for (const auto &index : indexList) {
        QFileInfo file(fileModel->filePath(index));
        if (!file.isDir())
            numberOfFiles += 1;
    }
    int ret = QMessageBox::warning(
        this, tr("File Browser"),
        tr("You are about to del %1 selected file(s)\n"
           "Are you sure you want to continue?")
            .arg(qRound(static_cast<qreal>(numberOfFiles / 4))),
        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    switch (ret) {
    case QMessageBox::Ok:
        for (const auto &index : indexList) {
            QFileInfo file(fileModel->filePath(index));
            if (!file.isDir() && !fileModel->remove(index))
                qWarning("Could not del file %s from the file system",
                         qPrintable(file.fileName()));
        }
        break;
    case QMessageBox::Cancel:
        return;
    default:
        break;
    }
}

void QLMainWindow::newFile()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("New file"), QDir::currentPath(), tr("VHDL files (*.vhdl)"));
    if (!fileName.isEmpty()) {
        QFile f(fileName);
        f.open(QFile::Text | QFile::Append);
        f.close();

        QProcess *p = new QProcess(this);
        p->start("gedit", QStringList() << fileName);
    }
}

void QLMainWindow::analyzeFile()
{
    QString fileName = fileModel->filePath(fileView->currentIndex());

    if (!fileName.isEmpty()) {

        callGHDLaOnFile(fileName);

    }
}

void QLMainWindow::buildTestBench()
{
    callGHDLeOnTestBench();
}

void QLMainWindow::runTestBench()
{
    callGHDLrOnTestBench();
}

void QLMainWindow::viewWave()
{
    callGtkWave();
}

void QLMainWindow::setGHDLOptions()
{
    QLGHDLOptionsDialog optionsDialog(this);

    optionsDialog.exec();
}

void QLMainWindow::callGHDLaOnFile(QString fname)
{
    QStringList filelist = project->getFiles();

    if(!filelist.contains(fname)) {
        outedit->append( qUtf8Printable(fname + " is not in current project HDL file list.\n") );
    }

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(outedit);

    QString cmd = "ghdl -a " + fname;

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);
}

void QLMainWindow::callGHDLaOnAllFiles()
{
    QStringList filelist = project->getFiles();

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(outedit);

    p->setProcessChannelMode(QProcess::MergedChannels);

    for(int i=0; i<filelist.size(); ++i) {
        QString cmd = "ghdl -a " + filelist.at(i);

        p->start(cmd);
    }
}

void QLMainWindow::callGHDLeOnTestBench()
{
    QString bench = project->getTestBenchName();

    if(bench.isEmpty()) {
        outedit->append("No testbench file. Please create a testbench.");

        QString fname = stripPath( fileModel->filePath(fileView->currentIndex()) );

        outedit->append("File to use as TestBench: " + fname);

        bench = stripSurfix(fname);

        outedit->append("TestBench name: " + bench);
    }

    callGHDLaOnAllFiles();

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(outedit);

    QString cmd = "ghdl -e " + bench;

    outedit->append(cmd);

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);

}

void QLMainWindow::callGHDLrOnTestBench()
{
    QString bench = project->getTestBenchName();

    if(bench.isEmpty()) {
        outedit->append("No testbench file. Please create or select a testbench.");

        QString fname = stripPath( fileModel->filePath(fileView->currentIndex()) );

        outedit->append("File to use as TestBench: " + fname);

        bench = stripSurfix(fname);

        outedit->append("TestBench name: " + bench);
    }

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(outedit);

    QString cmd = "ghdl -r " + bench + " --vcd=" + bench + ".vcd";

    outedit->append(cmd);

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);

}

void QLMainWindow::callGtkWave()
{
    QString bench = project->getTestBenchName();

    if(bench.isEmpty()) {
        outedit->append("No testbench file. Please create or select a testbench.");

        QString fname = stripPath( fileModel->filePath(fileView->currentIndex()) );

        outedit->append("File to use as TestBench: " + fname);

        bench = stripSurfix(fname);

        outedit->append("TestBench name: " + bench);
    }


    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(outedit);

    QString cmd = "gtkwave " + bench + ".vcd";

    outedit->append(cmd);

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);

}

void QLMainWindow::aboutQuickLogic()
{
    QMessageBox::about(this, tr("About QuickLogic"),
            tr("<b>QuickLogic</b> is a program to use GHDL graphically."));

}



