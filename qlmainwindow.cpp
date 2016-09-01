#include "qlmainwindow.h"
#include "ui_qlmainwindow.h"

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
}

QLMainWindow::~QLMainWindow()
{
    delete ui;
}

void QLMainWindow::createWidgets()
{
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::homePath());
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

    QModelIndex index = dirModel->index(QDir::homePath());
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
}

void QLMainWindow::createLayout()
{
    setCentralWidget(splitter);
    resize(800, 600);
}

void QLMainWindow::createActions()
{

    delFileAction = new QAction(tr("&Delete File(s)"), this);
    delFileAction->setShortcut(QKeySequence::Delete);

    newFileAction = new QAction(tr("&New File"), this);

    renFileAction = new QAction(tr("&Rename File..."), this);

    openFileAction = new QAction(tr("&Open File"), this);
    openFileAction->setShortcut(QKeySequence::Open);
}

void QLMainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // declate contect menu for the file tree.
    QMenu menu(this);
    menu.addAction(openFileAction);
    menu.addAction(delFileAction);
    menu.addAction(renFileAction);
    menu.addAction(newFileAction);
    menu.exec(event->globalPos());
}

void QLMainWindow::createConnections()
{
    connect(renFileAction, SIGNAL(triggered()), this, SLOT(renFile()));
    connect(delFileAction, SIGNAL(triggered()), this, SLOT(delFile()));
    //connect(fileModel, SIGNAL(fileRenamed(QString, QString, QString)), this,
    //        SLOT(fileRenameDone()));
    //auto stopEditingSlot = [&]() { fileModel->setReadOnly(true); };
    //connect(fileView, &QTreeView::doubleClicked, stopEditingSlot);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(dirView, SIGNAL(clicked(QModelIndex)), this,
            SLOT(showFiles(QModelIndex)));
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
        qWarning("Unable to open file %s\n%s", qPrintable(fileName),
                 qPrintable(e.what()));
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
    }
}

/*
void QLMainWindow::tarFiles()
{
    // new selected files using qprocess and new command
    QItemSelectionModel *selectionModel = fileView->selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();
    QProcess *myProcess = new QProcess(this);
    QStringList files;
    for (const auto &index : indexList) {
        QFileInfo file(fileModel->filePath(index));
        if (file.exists() && !files.contains(file.absoluteFilePath()))
            files.append(file.absoluteFilePath());
    }
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save tar file"), QDir::currentPath(), tr("tar files (*.tz)"));
    if (!fileName.isEmpty()) {
        myProcess->start("tar -czvf", QStringList() << fileName << files);
    }
}
*/

void QLMainWindow::showFiles(QModelIndex index)
{
    fileView->setRootIndex(
        fileModel->setRootPath(dirModel->fileInfo(index).absoluteFilePath()));
}
