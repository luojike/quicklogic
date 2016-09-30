#ifndef QLPROCESS_H
#define QLPROCESS_H

#include <QProcess>
#include <QPlainTextEdit>


class QLProcess: public QProcess
{
  Q_OBJECT
  public:
  QLProcess(QTextEdit *pedit): QProcess()
  {
    logger = pedit;
    //logger->resize(500,500);
    //logger->setWindowTitle("Standard Output Redirection");
    //logger->show();
    connect(this,SIGNAL(readyReadStandardOutput()),this,SLOT(readStdOutput()));
    connect(this,SIGNAL(error(QProcess::ProcessError)),this,SLOT(readError()));
  };

  ~QLProcess()  {};

private slots:
  void readStdOutput()
  {
    logger->append(readAllStandardOutput());
  }

  void readError()
  {
    logger->append("An Error Occured! Error Code is: "+QString::number(error()));
  }

private:
  QTextEdit* logger;
};

#endif // QLPROCESS_H

