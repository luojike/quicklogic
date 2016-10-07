#ifndef QLPROCESS_H
#define QLPROCESS_H

#include <QProcess>
#include <QTextEdit>
//#include <QTextStream>
//#include <QIODevice>
//#include <iostream>



class QLProcess: public QProcess
{
Q_OBJECT
public:
	QLProcess(QObject *parent = Q_NULLPTR): QProcess(parent)
	{
        outTextEdit = Q_NULLPTR;

        connect(this,SIGNAL(readyReadStandardOutput()),this,SLOT(readStdOutput()));
		connect(this,SIGNAL(error(QProcess::ProcessError)),this,SLOT(readError()));
    }

    ~QLProcess()  {}

    QTextEdit* getOutTextEdit() { return outTextEdit; }

    void setOutTextEdit(QTextEdit *pedit) { outTextEdit = pedit; }


private slots:
	void readStdOutput()
	{
        if(outTextEdit != Q_NULLPTR) {
            outTextEdit->append( readAllStandardOutput() );
        }
        //else {
        //	cout << readAllStandardOutput() << endl;
        //}
	}

	void readError()
	{
		if(outTextEdit != Q_NULLPTR) {
			outTextEdit->append("An Error Occured! Error Code is: "+QString::number(error()));
		}
        //else {
        //	cerr << readAllStandardError() << endl;
        //}
	}

private:
	QTextEdit* outTextEdit;

    //QTextStream cout(stdout, QIODevice::WriteOnly);
    //QTextStream cerr(stderr, QIODevice::WriteOnly);
    //QTextStream cin(stdin, QIODevice::ReadOnly);

};

#endif // QLPROCESS_H

