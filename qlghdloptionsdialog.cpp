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
    libs << "none" << "standard" << "synopsys" << "mentor";
    ieeelibcombo = new QComboBox; // must be "none", "standard", "synopsys" or "mentor"
    ieeelibcombo->addItems(libs);
    ieeelibcombo->setEditable(false);

    //QStringList libdirs;

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

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(optionstrlabel, 0, 0);
    grid->addWidget(optionstredit, 0, 1, 1, 3);

    grid->addWidget(fexplicit, 1, 0);
    grid->addWidget(frelaxed_rules, 1, 1);
    grid->addWidget(fpsl, 1, 2);
    grid->addWidget(syn_binding, 1, 3);

    grid->addWidget(no_vital_checks, 2, 0);
    grid->addWidget(vital_checks, 2, 1);

    grid->addWidget(workdirlabel, 1, 0);
    grid->addWidget(workdiredit, 1, 1);

    grid->addWidget(prefixdirlabel, 1, 2);
    grid->addWidget(prefixdiredit, 1, 3);

    grid->addWidget(vhdlstdlabel, 2, 0);
    grid->addWidget(vhdlstdcombo, 2, 1);

    grid->addWidget(ieeeliblabel, 2, 2);
    grid->addWidget(ieeelibcombo, 2, 3);

    grid->addWidget(ghdl1cmdlabel, 3, 0);
    grid->addWidget(ghdl1cmdedit, 3, 1, 1, 3);

    setLayout(grid);

    setWindowTitle(tr("Options"));

}

