#include "qlproject.h"

#include <QProcess>
#include <QFile>
#include <QTextStream>

#include "qlmainwindow.h"


QLProject::QLProject()
{
    mName = QString("");
    mBench = QString("");
    mPath = QString("");
    mHDL = QString("VHDL");
    mFileList = QStringList();

}

QLProject::~QLProject()
{

}

void QLProject::Load()
{
    // Read project settings from a file.
}

void QLProject::Save()
{
    if(mName.isEmpty()) {
        qWarning("Project name not set while trying to save the project.");
        return;
    }

    QString fname = mName + ".qlp";

    QFile f(fname);

    if(!f.open(QFile::Truncate | QFile::WriteOnly | QFile::Text)) {

        qWarning("%s can't be opened.", qUtf8Printable(fname));
        return;
    }

    QTextStream out(&f);

    out << "PRJNAME=" << mName << "\n";
    out << "PRJDIR=" << mPath << "\n";
    out << "HDL=" << mHDL << "\n";
    out << "BENCHNAME=" << mBench << "\n";

    out << "HDLFILES=" << mFileList.join(" ");

}

void QLProject::addFile(QString fname)
{
    if(!mFileList.contains(fname)) {
        mFileList += fname;
    }
}

void QLProject::delFile(QString fname)
{
    int i = mFileList.indexOf(fname);

    if(i >= 0) mFileList.removeAt(i);
}

bool QLProject::hasFile(QString fname)
{
    return mFileList.contains(fname);
}

