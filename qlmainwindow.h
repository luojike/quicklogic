#ifndef QLMAINWINDOW_H
#define QLMAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

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
    void showFiles(QModelIndex);

private:
    Ui::QLMainWindow *ui;

    void createWidgets();
    void createLayout();
    void createConnections();
    void createActions();

    QTreeView *dirView;
    QTreeView *fileView;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QSplitter *splitter;

    QAction *newFileAction;
    QAction *delFileAction;
    QAction *renFileAction;
    QAction *openFileAction;
    QAction *ghdlaFileAction;
    QAction *ghdleFileAction;
    QAction *ghdlrFileAction;
    QAction *gtkwaveFileAction;
};

#endif // QLMAINWINDOW_H