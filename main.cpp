#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	FakeServer test;
	test.start();
	return a.exec();
}
