#include "UDiskPartitionDlg.h"
#include "CFormatDlg.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator * pTranslator = new QTranslator();
    if(pTranslator->load("./UDiskPartition.qm")){
        a.installTranslator(pTranslator);
    }
    //UDiskPartitionDlg w;
    CFormatDlg w;
    w.show();
    return a.exec();
}
