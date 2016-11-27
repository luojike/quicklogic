#include "qlghdloptionsdialog.h"

#include <QGridLayout>

QLGHDLOptionsDialog::QLGHDLOptionsDialog(QWidget *parent) :
    QDialog(parent)
{
    workdirlabel = new QLabel(tr("Work Directory:"));
    workdiredit = new QLineEdit;
    workdirlabel->setBuddy(workdiredit);

    vhdlstdlabel = new QLabel(tr("VHDL Standard:"));
    // must be "87", "93", "93c", "00", "02", "08"
    vhdlstdcombo = new QComboBox;
    QStringList stds;
    stds << "" << "87" << "93" << "93c" << "00" << "02" << "08";
    vhdlstdcombo->addItems(stds);
    vhdlstdcombo->setEditable(false);

    ieeeliblabel = new QLabel(tr("IEEE Library:"));
    QStringList libs;
    libs << "" << "none" << "standard" << "synopsys" << "mentor";
    ieeelibcombo = new QComboBox; // must be "none", "standard", "synopsys" or "mentor"
    ieeelibcombo->addItems(libs);
    ieeelibcombo->setEditable(false);

    //QStringList libdirs;
    libdirslabel = new QLabel(tr("Library Directories:"));
    libdirsedit = new QLineEdit;
    libdirslabel->setBuddy(libdirsedit);

    fexplicit = new QCheckBox(tr("-fexplicit"));
    frelaxed_rules = new QCheckBox(tr("-frelaxed-rules"));
    fpsl = new QCheckBox(tr("-fpsl"));
    no_vital_checks = new QCheckBox(tr("--no-vital-checks"));
    vital_checks = new QCheckBox(tr("--vital-checks"));
    syn_binding = new QCheckBox(tr("--syn-binding"));

    prefixdirlabel = new QLabel(tr("Prefix Path:"));
    prefixdiredit = new QLineEdit;
    prefixdirlabel->setBuddy(prefixdiredit);

    ghdl1cmdlabel = new QLabel(tr("GHDL Compiler Command:"));
    ghdl1cmdedit = new QLineEdit;
    ghdl1cmdlabel->setBuddy(ghdl1cmdedit);

    verbose = new QCheckBox(tr("-v (verbose)"));

    optionstrlabel = new QLabel(tr("Option String:"));
    optionstredit = new QLineEdit;
    optionstrlabel->setBuddy(optionstredit);

    okButton = new QPushButton(tr("OK"));
    okButton->setDefault(true);

    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(false);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(optionstrlabel, 0, 0);
    grid->addWidget(optionstredit, 0, 1, 1, 3);

    grid->addWidget(workdirlabel, 1, 0);
    grid->addWidget(workdiredit, 1, 1, 1, 3);

    grid->addWidget(prefixdirlabel, 2, 0);
    grid->addWidget(prefixdiredit, 2, 1, 1, 3);

    grid->addWidget(libdirslabel, 3, 0);
    grid->addWidget(libdirsedit, 3, 1, 1, 3);

    grid->addWidget(ghdl1cmdlabel, 4, 0);
    grid->addWidget(ghdl1cmdedit, 4, 1, 1, 3);

    grid->addWidget(vhdlstdlabel, 5, 0);
    grid->addWidget(vhdlstdcombo, 5, 1);

    grid->addWidget(ieeeliblabel, 5, 2);
    grid->addWidget(ieeelibcombo, 5, 3);

    grid->addWidget(fexplicit, 6, 0);
    grid->addWidget(frelaxed_rules, 6, 1);
    grid->addWidget(fpsl, 6, 2);
    grid->addWidget(syn_binding, 6, 3);

    grid->addWidget(no_vital_checks, 7, 0);
    grid->addWidget(vital_checks, 7, 1);

    grid->addWidget(okButton, 8, 2);
    grid->addWidget(cancelButton, 8, 3);

    setLayout(grid);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Options"));

}

