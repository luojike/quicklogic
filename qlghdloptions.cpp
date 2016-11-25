#include "qlghdloptions.h"

#include <QString>
#include <QStringList>
#include <QRegExp>


QString QLGHDLOptions::buildOptionString()
{
    QString s = "";

    if(!workdir.isEmpty()) {
        s += " --workdir=" + workdir;
    }

    if(!vhdlstd.isEmpty()) {
        s += " --std=" + vhdlstd;
    }

    if(!ieeelib.isEmpty()) {
        s += " --ieee=" + ieeelib;
    }

    if(!libdirs.isEmpty()) {
        s += "-P" + libdirs.join(" -P");
    }

    if(fexplicit) {
        s += " -fexplicit";
    }

    if(frelaxed_rules) {
        s += " -frelaxed-rules";
    }

    if(fpsl) {
        s += " -fpsl";
    }

    if(no_vital_checks) {
        s += " --no-vital-checks";
    }

    if(vital_checks) {
        s += " --vital-checks";
    }

    if(syn_binding) {
        s += " --syn-binding";
    }

    if(!prefixdir.isEmpty()) {
        s += " --PREFIX=" + prefixdir;
    }

    if(!ghdl1cmd.isEmpty()) {
        s += " --GHDL1=" + ghdl1cmd;
    }

    if(verbose) {
        s += " -v";
    }

    return s;
}

void QLGHDLOptions::parseOptionString()
{
    QStringList options = optionString.split(QRegExp("\\s+"));

    //clear();

    bool newlibdirs = false;

    //optionString = options.join(" ");

    for (int i = 0; i < options.size(); ++i) {
        QString s = options.at(i);

        if(s.startsWith("--workdir=")) {
            workdir = s.mid(10);
        }

        if(s.startsWith("--std=")) {
            vhdlstd = s.mid(6);
        }

        if(s.startsWith("--ieee=")) {
            ieeelib = s.mid(7);
        }

        if(s.startsWith("-P")) {
            if(!newlibdirs) { libdirs.clear(); newlibdirs = true; }

            libdirs.append(s.mid(2));
        }

        if(s.startsWith("-fexplicit")) {
            fexplicit = true;
        }

        if(s.startsWith("-frelaxed-rules")) {
            frelaxed_rules = true;
        }

        if(s.startsWith("-fpsl")) {
            fpsl = true;
        }

        if(s.startsWith("--no-vital-checks")) {
            no_vital_checks = true;
        }

        if(s.startsWith("--vital-checks")) {
            vital_checks = true;
        }

        if(s.startsWith("--syn-binding")) {
            syn_binding= true;
        }

        if(s.startsWith("--PREFIX=")) {
            prefixdir = s.mid(9);
        }

        if(s.startsWith("--GHDL1=")) {
            ghdl1cmd = s.mid(8);
        }

        if(s.startsWith(" -v")) {
            verbose = true;
        }

    }
}
