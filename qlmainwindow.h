#ifndef QLMAINWINDOW_H
#define QLMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QTextEdit>
#include <QProcess>

#include "qlproject.h"
#include "qlghdloptionsdialog.h"
#include "qlghdlsimoptionsdialog.h"


namespace ql {
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
    explicit QLMainWindow(QWidget *parent = Q_NULLPTR);
    ~QLMainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void newFile();
    void delFile();
    void renFile();
    void openFile();

    void fileRenameDone();

    void clickDirView(QModelIndex);
    void doubleClickFileView(QModelIndex);

    void analyzeFile();
    void buildTestBench();
    void runTestBench();
    void viewWave();

    void setGHDLOptions();
    void setGHDLSimOptions();

    void aboutQuickLogic();

private:
    //ql::QLMainWindow *mainWindow;

    void createActions();
    void createWidgets();
    void createLayout();
    void createConnections();
    void createMenus();

    void openDir(QModelIndex);

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
    QTextEdit *outedit;
    QDockWidget *dock;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *ghdlMenu;
    QMenu *helpMenu;

    QAction *newFileAct;
    QAction *delFileAct;
    QAction *renFileAct;
    QAction *openFileAct;

    QAction *settingsAct;
    QAction *exitAct;

    QAction *aboutAct;

    QAction *ghdlAnalyzeAct;
    QAction *ghdlBuildExecAct;
    QAction *ghdlRunExecAct;
    QAction *ghdlOptionsAct;
    QAction *ghdlSimOptionsAct;

    QAction *gtkwaveAct;

    QLGHDLOptionsDialog *optionsDialog;
    QLGHDLSimOptionsDialog *simoptionsDialog;
    QString optionStr;
    QString simoptionStr;

    QLProject *project;

    //QProcess *subproc;
};

#endif // QLMAINWINDOW_H
