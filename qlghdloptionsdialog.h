#ifndef QLGHDLOPTIONSDIALOG_H
#define QLGHDLOPTIONSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>


class QLGHDLOptionsDialog : public QDialog
{
    Q_OBJECT


public:
    QLGHDLOptionsDialog(QWidget *parent = 0);

private:
    QLabel* workdirlabel;
    QLineEdit* workdiredit;

    QLabel* vhdlstdlabel; // must be "87", "93", "93c", "00", "02", "08"
    QComboBox* vhdlstdcombo;

    QLabel* ieeeliblabel;
    QComboBox* ieeelibcombo; // must be "none", "standard", "synopsys" or "mentor"

    //QStringList libdirs;
    QLabel *libdirslabel;
    QLineEdit *libdirsedit;

    QCheckBox* fexplicit;
    QCheckBox* frelaxed_rules;
    QCheckBox* fpsl;
    QCheckBox* no_vital_checks;
    QCheckBox* vital_checks;
    QCheckBox* syn_binding;

    QLabel* prefixdirlabel;
    QLineEdit* prefixdiredit;

    QLabel* ghdl1cmdlabel;
    QLineEdit* ghdl1cmdedit;

    QCheckBox* verbose;

    QLabel* optionstrlabel;
    QLineEdit* optionstredit;

    QPushButton *okButton;
    QPushButton *cancelButton;

};

#endif // QLGHDLOPTIONSDIALOG_H
