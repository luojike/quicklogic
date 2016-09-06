#include <QString>

QString stripSurfix(QString filename)
{
    return filename.section('.', -2);
}
