#ifndef QLGHDLSIMOPTIONSDIALOG_H
#define QLGHDLSIMOPTIONSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QString>


class QLGHDLSimOptionsDialog : public QDialog
{
    Q_OBJECT


public:
    QLGHDLSimOptionsDialog(QWidget *parent = 0);
    ~QLGHDLSimOptionsDialog();

    QString getSimOptionstring() { return simoptionstrEdit->text(); }

private:

    QLabel* assertlevelLabel;
    QComboBox* assertlevelCombo; // must be "none", "note", "warning", "error", "failure"

    QLabel* ieeeassertsLabel;
    QComboBox* ieeeassertsCombo; // must be "enable", "disable", "disable-at-0"

    //QStringList libdirs;
    QLabel *stoptimeLabel;
    QLineEdit *stoptimeEdit;

    QLabel *stopdeltaLabel;
    QLineEdit *stopdeltaEdit;

    QCheckBox* disptime;

    QLabel* disptreeLabel;
    QComboBox* disptreeCombo; // must be "none", "inst", "proc", "port"

    QCheckBox* norun;

    QCheckBox* unbuffered;

    QLabel *readoptfileLabel;
    QLineEdit *readoptfileEdit;

    QLabel *writeoptfileLabel;
    QLineEdit *writeoptfileEdit;

    QLabel *vcdLabel;
    QLineEdit *vcdEdit;

    QLabel *vcdgzLabel;
    QLineEdit *vcdgzEdit;

    QLabel *fstLabel;
    QLineEdit *fstEdit;

    QLabel *waveLabel;
    QLineEdit *waveEdit;

    QLabel *pslreportLabel;
    QLineEdit *pslreportEdit;

    QLabel *sdfLabel;
    QLineEdit *sdfEdit;

    QLabel *simoptionstrLabel;
    QLineEdit *simoptionstrEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

};

#endif // QLGHDLSIMOPTIONSDIALOG_H
