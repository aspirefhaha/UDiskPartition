#include "UDiskPartitionDlg.h"
#include "ui_UDiskPartitionDlg.h"
#include "CAuthDlg.h"
#include "CFormatDlg.h"

UDiskPartitionDlg::UDiskPartitionDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UDiskPartitionDlg)
{
    ui->setupUi(this);
}

UDiskPartitionDlg::~UDiskPartitionDlg()
{
    delete ui;
}

void UDiskPartitionDlg::sltPartition()
{
    CFormatDlg formatDlg;
    formatDlg.setModal(true);
    formatDlg.exec();
}

void UDiskPartitionDlg::sltAuth()
{
    CAuthDlg authDlg;
    authDlg.setModal(true);
    authDlg.exec();
}

