#include "qlmainwindow.h"
#include "ui_qlmainwindow.h"

#include "qlmisc.h"
#include "qlproject.h"
#include "qlprocess.h"

#include <QDockWidget>
#include <QTextEdit>
#include <QTreeView>
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
    QMainWindow(parent),
    ui(new Ui::QLMainWindow)
{
    ui->setupUi(this);

    createWidgets();
    createLayout();
    createActions();
    createConnections();

    QApplication::setApplicationName(tr("QuickLogic"));

    setWindowTitle(QApplication::applicationName());

    project = new QLProject();

    //subproc = new QProcess(this);

    //subproc->setProcessChannelMode(QProcess::MergedChannels);

}

QLMainWindow::~QLMainWindow()
{
    delete ui;

    delete project;

    delete dirView;
    delete fileView;
    delete dirModel;
    delete fileModel;
    delete splitter;

    delete newFileAction;
    delete delFileAction;
    delete renFileAction;
    delete openFileAction;
    delete analyzeFileAction;
    delete buildTestBenchAction;
    delete runTestBenchAction;
    delete viewWaveAction;
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

    dock = new QDockWidget(tr("Log Window"), this);
    dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);


    logger = new QTextEdit(dock);

    dock->setWidget(logger);

}

void QLMainWindow::createLayout()
{
    setCentralWidget(splitter);

    addDockWidget(Qt::BottomDockWidgetArea, dock);

    resize(800, 600);
}

void QLMainWindow::createActions()
{

    delFileAction = new QAction(tr("&Delete File(s)"), this);
    delFileAction->setShortcut(QKeySequence::Delete);

    newFileAction = new QAction(tr("&New File"), this);

    renFileAction = new QAction(tr("&Change File Name"), this);

    openFileAction = new QAction(tr("&Open File"), this);
    openFileAction->setShortcut(QKeySequence::Open);

    analyzeFileAction = new QAction(tr("&Analyze File..."), this);

    buildTestBenchAction = new QAction(tr("&Build executable File..."), this);

    runTestBenchAction = new QAction(tr("&Run File..."), this);

    viewWaveAction = new QAction(tr("&View File..."), this);

}

void QLMainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // declate contect menu for the file tree.
    QMenu menu(this);

    menu.addAction(openFileAction);
    menu.addAction(delFileAction);
    menu.addAction(renFileAction);
    menu.addAction(newFileAction);

    menu.addAction(analyzeFileAction);
    menu.addAction(buildTestBenchAction);
    menu.addAction(runTestBenchAction);
    menu.addAction(viewWaveAction);

    menu.exec(event->globalPos());
}

void QLMainWindow::createConnections()
{
    connect(dirView, SIGNAL(clicked(QModelIndex)), this,
            SLOT(onDirviewClick(QModelIndex)));

    connect(fileView, SIGNAL(doubleClicked(QModelIndex)), this,
            SLOT(onFileviewDoubleClick(QModelIndex)));


    connect(renFileAction, SIGNAL(triggered()), this, SLOT(renFile()));
    connect(delFileAction, SIGNAL(triggered()), this, SLOT(delFile()));

    //connect(fileModel, SIGNAL(fileRenamed(QString, QString, QString)), this,
    //        SLOT(fileRenameDone()));
    //auto stopEditingSlot = [&]() { fileModel->setReadOnly(true); };
    //connect(fileView, &QTreeView::doubleClicked, stopEditingSlot);

    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    connect(analyzeFileAction, SIGNAL(triggered()), this, SLOT(analyzeFile()));
    connect(buildTestBenchAction, SIGNAL(triggered()), this, SLOT(buildTestBench()));
    connect(runTestBenchAction, SIGNAL(triggered()), this, SLOT(runTestBench()));
    connect(viewWaveAction, SIGNAL(triggered()), this, SLOT(viewWave()));

}


void QLMainWindow::onDirviewClick(QModelIndex index)
{
    QString dir = dirModel->fileInfo(index).absoluteFilePath();

    fileView->setRootIndex( fileModel->setRootPath(dir) );

    QDir::setCurrent(dir);
}

void QLMainWindow::onFileviewDoubleClick(QModelIndex index)
{
    if( fileModel->isDir(index) ) {
        fileView->setRootIndex( index );

        QString dir = fileModel->fileInfo(index).absolutePath();

        QDir::setCurrent(dir);

        QModelIndex idx = dirModel->index(dir);

        dirView->expand(idx);
        dirView->scrollTo(idx);
    }
    else {
        QString fileName = fileModel->filePath(index);
        try
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
        }
        catch (const std::exception &e)
        {
            logger->append("Unable to open file " + fileName + "\n" +
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


void QLMainWindow::renFile()
{
    fileModel->setReadOnly(false);
    fileView->edit(fileView->currentIndex());
}

/*
void QLMainWindow::fileRenameDone()
{
    fileModel->setReadOnly(true);
}
*/

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

void QLMainWindow::openFile()
{
    QString fileName = fileModel->filePath(fileView->currentIndex());
    try
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
    catch (const std::exception &e)
    {
        qWarning("Unable to open file %s\n%s", qUtf8Printable(fileName),
                 qUtf8Printable(e.what()));
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

void QLMainWindow::callGHDLaOnFile(QString fname)
{
    QStringList filelist = project->getFiles();

    if(!filelist.contains(fname)) {
        logger->append( qUtf8Printable(fname + " is not in current project HDL file list.\n") );
    }

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(logger);

    QString cmd = "ghdl -a " + fname;

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);
}

void QLMainWindow::callGHDLaOnAllFiles()
{
    QStringList filelist = project->getFiles();

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(logger);

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
        logger->append("No testbench file. Please create a testbench.");

        QString fname = stripPath( fileModel->filePath(fileView->currentIndex()) );

        logger->append("File to use as TestBench: " + fname);

        bench = stripSurfix(fname);

        logger->append("TestBench name: " + bench);
    }

    callGHDLaOnAllFiles();

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(logger);

    QString cmd = "ghdl -e " + bench;

    logger->append(cmd);

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);

}

void QLMainWindow::callGHDLrOnTestBench()
{
    QString bench = project->getTestBenchName();

    if(bench.isEmpty()) {
        logger->append("No testbench file. Please create or select a testbench.");

        QString fname = stripPath( fileModel->filePath(fileView->currentIndex()) );

        logger->append("File to use as TestBench: " + fname);

        bench = stripSurfix(fname);

        logger->append("TestBench name: " + bench);
    }

    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(logger);

    QString cmd = "ghdl -r " + bench + " --vcd=" + bench + ".vcd";

    logger->append(cmd);

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);

}

void QLMainWindow::callGtkWave()
{
    QString bench = project->getTestBenchName();

    if(bench.isEmpty()) {
        logger->append("No testbench file. Please create or select a testbench.");

        QString fname = stripPath( fileModel->filePath(fileView->currentIndex()) );

        logger->append("File to use as TestBench: " + fname);

        bench = stripSurfix(fname);

        logger->append("TestBench name: " + bench);
    }


    QLProcess *p = new QLProcess(this);

    p->setOutTextEdit(logger);

    QString cmd = "gtkwave " + bench + ".vcd";

    logger->append(cmd);

    p->setProcessChannelMode(QProcess::MergedChannels);

    p->start(cmd);

}



