#ifndef QLMAINWINDOW_H
#define QLMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QTextEdit>
#include <QProcess>

#include "qlproject.h"


namespace Ui {
class QLMainWindow;
}

class QTreeView;
class QFileSystemModel;
class QContextMenuEvent;
class QAction;
class QSplitter;


class QLMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QLMainWindow(QWidget *parent = 0);
    ~QLMainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void newFile();
    void delFile();
    void renFile();
    void openFile();
    void onDirviewClick(QModelIndex);
    void onFileviewDoubleClick(QModelIndex);

    void analyzeFile();
    void buildTestBench();
    void runTestBench();
    void viewWave();

private:
    Ui::QLMainWindow *ui;

    void createWidgets();
    void createLayout();
    void createConnections();
    void createActions();

    void callGHDLaOnFile(QString fname);
    void callGHDLaOnAllFiles();
    void callGHDLeOnTestBench();
    void callGHDLrOnTestBench();
    void callGtkWave();

    void readSubprocessStdOut();

    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;

    QTreeView *dirView;
    QTreeView *fileView;
    QSplitter *splitter;
    QTextEdit *logger;
    QDockWidget *dock;

    QAction *newFileAction;
    QAction *delFileAction;
    QAction *renFileAction;
    QAction *openFileAction;
    QAction *analyzeFileAction;
    QAction *buildTestBenchAction;
    QAction *runTestBenchAction;
    QAction *viewWaveAction;

    QLProject *project;

    //QProcess *subproc;
};

#endif // QLMAINWINDOW_H
