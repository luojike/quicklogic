#include "qlproject.h"

#include <QProcess>
#include <QFile>


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

void QLProject::callGHDLaOnFile(QString fname)
{
    if(mFileList.contains(fname)) {
        QProcess p = new QProcess(this);

        QString cmd = "ghdl -a " + fname;

        p.setProcessChannelMode(QProcess::MergedChannels);

        p.start(cmd);
    }
    else {
        qWarning("%s is not in HDL file list.\n", qUtf8Printable(fname));
    }
}

void QLProject::callGHDLaOnAllFiles()
{
    for(int i=0; i<mFileList.size(); ++i) {
        QProcess p = new QProcess(this);

        QString cmd = "ghdl -a " + fname;

        p.setProcessChannelMode(QProcess::MergedChannels);

        p.start(cmd);
    }
}

void QLProject::callGHDLeOnTestBench()
{
    if(mBench.isEmpty()) {
        qWarning("No testbench file. Please create a testbench.");
    }
    else {
        callGHDLaOnAllFiles();

        QProcess p = new QProcess(this);

        QString cmd = "ghdl -e " + mBench;

        p.setProcessChannelMode(QProcess::MergedChannels);

        p.start(cmd);

    }
}

void QLProject::callGHDLrOnTestBench()
{
    if(mBench.isEmpty()) {
        qWarning("No testbench file. Please create a testbench.");
    }
    else {

        QProcess p = new QProcess(this);

        QString cmd = "ghdl -r " + mBench + "--vcd=" + mBench + ".vcd";

        p.setProcessChannelMode(QProcess::MergedChannels);

        p.start(cmd);

    }

}

void QLProject::callGtkWave()
{
    if(mBench.isEmpty()) {
        qWarning("No testbench file. Please create a testbench.");
    }
    else {

        QProcess p = new QProcess(this);

        QString cmd = "gtkwave " + mBench + ".vcd";

        p.setProcessChannelMode(QProcess::MergedChannels);

        p.start(cmd);

    }

}

