#ifndef QLPROJECT_H
#define QLPROJECT_H


#include <QString>
#include <QStringList>


class QLProject
{
public:
    QLProject();
    ~QLProject();

    void Load();
    void Save();

    void setName(QString s) { mName = s; }
    QString getName() { return mName; }

    void setTestBenchName(QString s) { mBench = s; }
    QString getTestBenchName() { return mBench; }

    void setHDL(QString s) { mHDL = s; }
    QString getHDL() { return mHDL; }

    void setPath(QString s) { mPath = s; }
    QString getPath() { return mPath; }

    void setFiles(QStringList files) { mFileList = files; }
    QStringList getFiles() { return mFileList; }

    void addFile(QString fname);
    void delFile(QString fname);
    bool hasFile(QString fname);


private:

    QString mName;
    QString mBench;
    QString mHDL;
    QString mPath;

    QStringList mFileList;

};

#endif // QLPROJECT_H
