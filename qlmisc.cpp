#include <QString>

QString stripPath(QString pathname)
{
	int i = pathname.lastIndexOf('/');
	
	return pathname.right(pathname.size()-1-i);
}

QString stripSurfix(QString filename)
{
    int i = filename.lastIndexOf('.');

    return filename.left(i);
}
