#ifndef UDISKPARTITIONDLG_H
#define UDISKPARTITIONDLG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class UDiskPartitionDlg; }
QT_END_NAMESPACE

class UDiskPartitionDlg : public QDialog
{
    Q_OBJECT

public:
    UDiskPartitionDlg(QWidget *parent = nullptr);
    ~UDiskPartitionDlg();

protected slots:
    void sltPartition();
    void sltAuth();

private:
    Ui::UDiskPartitionDlg *ui;
};
#endif // UDISKPARTITIONDLG_H
