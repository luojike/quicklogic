#ifndef QLGHDLOPTIONS_H
#define QLGHDLOPTIONS_H

#include <QString>
#include <QStringList>

class QLGHDLOptions {

public:
    QLGHDLOptions() {
		clear();
	}

    ~QLGHDLOptions() {}

	void clear() {
		workdir = "";
		vhdlstd = "";
		ieeelib = ""; // must be "none", "standard", "synopsys" or "mentor"
		libdirs.clear();
		fexplicit = false;
		frelaxed_rules = false;
		fpsl = false;
		no_vital_checks = false;
		vital_checks = false;
		syn_binding = false;
		prefixdir = "";
		ghdl1cmd = "";
		verbose = false;

        optionString = "";
	}

    QString getOptionString() { return  optionString; }
    void setOptionString(QString s) { optionString = s; }

    QString buildOptionString();
    void parseOptionString();

private:
	QString workdir;
	QString vhdlstd;
	QString ieeelib; // must be "none", "standard", "synopsys" or "mentor"
	QStringList libdirs;
	bool fexplicit;
	bool frelaxed_rules;
	bool fpsl;
	bool no_vital_checks;
	bool vital_checks;
	bool syn_binding;
	QString prefixdir;
	QString ghdl1cmd;
	bool verbose;

    QString optionString;
	
	

};

#endif  // QLGHDLOPTIONS_H
