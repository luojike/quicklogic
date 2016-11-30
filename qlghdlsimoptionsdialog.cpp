#include "qlghdlsimoptionsdialog.h"

#include <QGridLayout>

QLGHDLSimOptionsDialog::QLGHDLSimOptionsDialog(QWidget *parent) :
    QDialog(parent)
{
    assertlevelLabel = new QLabel(tr("Assert Level:"));
    assertlevelCombo = new QComboBox;
    QStringList levels;
    levels << "" << "none" << "note" << "warning" << "error" << "failure";
    assertlevelCombo->addItems(levels);
    assertlevelCombo->setEditable(false);

    ieeeassertsLabel = new QLabel(tr("Asserts Policy:"));
    QStringList policies;
    policies << "" << "enable" << "disable" << "diable-at-0";
    ieeeassertsCombo = new QComboBox;
    ieeeassertsCombo->addItems(policies);
    ieeeassertsCombo->setEditable(false);

    stoptimeLabel = new QLabel(tr("Stop Time:"));
    stoptimeEdit = new QLineEdit;
    stoptimeLabel->setBuddy(stoptimeEdit);

    stopdeltaLabel = new QLabel(tr("Stop Delta:"));
    stopdeltaEdit = new QLineEdit;
    stopdeltaLabel->setBuddy(stopdeltaEdit);

    disptime = new QCheckBox(tr("--disp-time"));

    norun = new QCheckBox(tr("--no-run"));

    unbuffered = new QCheckBox(tr("--unbuffered"));

    disptreeLabel = new QLabel(tr("Display Tree:"));
    QStringList details;
    details << "" << "none" << "inst" << "proc" << "port";
    disptreeCombo = new QComboBox;
    disptreeCombo->addItems(policies);
    disptreeCombo->setEditable(false);

    readoptfileLabel = new QLabel(tr("Read Opt File:"));
    readoptfileEdit = new QLineEdit;
    readoptfileLabel->setBuddy(readoptfileEdit);

    writeoptfileLabel = new QLabel(tr("Write Opt File:"));
    writeoptfileEdit = new QLineEdit;
    writeoptfileLabel->setBuddy(writeoptfileEdit);

    vcdLabel = new QLabel(tr("VCD File:"));
    vcdEdit = new QLineEdit;
    vcdLabel->setBuddy(vcdEdit);

    vcdgzLabel = new QLabel(tr("VCD GZ File:"));
    vcdgzEdit = new QLineEdit;
    vcdgzLabel->setBuddy(vcdgzEdit);

    fstLabel = new QLabel(tr("FST File:"));
    fstEdit = new QLineEdit;
    fstLabel->setBuddy(fstEdit);

    waveLabel = new QLabel(tr("WAVE File:"));
    waveEdit = new QLineEdit;
    waveLabel->setBuddy(waveEdit);

    pslreportLabel = new QLabel(tr("PSL Report:"));
    pslreportEdit = new QLineEdit;
    pslreportLabel->setBuddy(pslreportEdit);

    sdfLabel = new QLabel(tr("SDF File:"));
    sdfEdit = new QLineEdit;
    sdfLabel->setBuddy(sdfEdit);

    simoptionstrLabel = new QLabel(tr("Simulation Options:"));
    simoptionstrEdit = new QLineEdit;
    simoptionstrLabel->setBuddy(simoptionstrEdit);

    okButton = new QPushButton(tr("OK"));
    okButton->setDefault(true);

    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(false);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(simoptionstrLabel, 0, 0);
    grid->addWidget(simoptionstrEdit, 0, 1, 1, 4);

    grid->addWidget(disptime, 1, 0);
    grid->addWidget(norun, 1, 1);
    grid->addWidget(unbuffered, 1, 2);

    grid->addWidget(disptreeLabel, 1, 3);
    grid->addWidget(disptreeCombo, 1, 4);

    grid->addWidget(ieeeassertsLabel, 2, 0);
    grid->addWidget(ieeeassertsCombo, 2, 1);

    grid->addWidget(assertlevelLabel, 2, 2);
    grid->addWidget(assertlevelCombo, 2, 3);

    grid->addWidget(stoptimeLabel, 3, 0);
    grid->addWidget(stoptimeEdit, 3, 1);
    grid->addWidget(stopdeltaLabel, 3, 2);
    grid->addWidget(stopdeltaEdit, 3, 3);

    grid->addWidget(readoptfileLabel, 4, 0);
    grid->addWidget(readoptfileEdit, 4, 1, 1, 3);

    grid->addWidget(writeoptfileLabel, 5, 0);
    grid->addWidget(writeoptfileEdit, 5, 1, 1, 3);

    grid->addWidget(vcdLabel, 6, 0);
    grid->addWidget(vcdEdit, 6, 1, 1, 3);

    grid->addWidget(vcdgzLabel, 7, 0);
    grid->addWidget(vcdgzEdit, 7, 1, 1, 3);

    grid->addWidget(fstLabel, 8, 0);
    grid->addWidget(fstEdit, 8, 1, 1, 3);

    grid->addWidget(waveLabel, 9, 0);
    grid->addWidget(waveEdit, 9, 1, 1, 3);

    grid->addWidget(pslreportLabel, 10, 0);
    grid->addWidget(pslreportEdit, 10, 1, 1, 3);

    grid->addWidget(sdfLabel, 11, 0);
    grid->addWidget(sdfEdit, 11, 1, 1, 3);

    grid->addWidget(okButton, 12, 3);
    grid->addWidget(cancelButton, 12, 4);

    setLayout(grid);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("SimOptions"));

}

QLGHDLSimOptionsDialog::~QLGHDLSimOptionsDialog()
{

    delete  assertlevelLabel;
    delete  assertlevelCombo; // must be "none", "note", "warning", "error", "failure"
    
    delete  ieeeassertsLabel;
    delete  ieeeassertsCombo; // must be "enable", "disable", "disable-at-0"
    
    delete stoptimeLabel;
    delete stoptimeEdit;
    
    delete stopdeltaLabel;
    delete stopdeltaEdit;
    
    delete disptime;
    
    delete disptreeLabel;
    delete disptreeCombo; // must be "none", "inst", "proc", "port"
    
    delete norun;
    
    delete unbuffered;
    
    delete readoptfileLabel;
    delete readoptfileEdit;
    
    delete writeoptfileLabel;
    delete writeoptfileEdit;
    
    delete vcdLabel;
    delete vcdEdit;
    
    delete vcdgzLabel;
    delete vcdgzEdit;
    
    delete fstLabel;
    delete fstEdit;
    
    delete waveLabel;
    delete waveEdit;
    
    delete pslreportLabel;
    delete pslreportEdit;
    
    delete sdfLabel;
    delete sdfEdit;


    delete simoptionstrLabel;
    delete simoptionstrEdit;

    delete okButton;
    delete cancelButton;
}
