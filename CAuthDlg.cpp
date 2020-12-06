#include "CAuthDlg.h"
#include "ui_CAuthDlg.h"
#include <QMessageBox>
#include <QDebug>
#include <QCryptographicHash>
#include "sdcryptostor.h"

CAuthDlg::CAuthDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAuthDlg)
{
    ui->setupUi(this);
}

CAuthDlg::~CAuthDlg()
{
    delete ui;
}

void CAuthDlg::sltNoEnc(bool)
{
	ui->lePassword->setText("");
	ui->lePassword->setEnabled(false);
}
void CAuthDlg::sltSM4(bool)
{
	ui->lePassword->setEnabled(true);
}

void CAuthDlg::sltConfirm()
{
	if (ui->rbSM4->isChecked()) {
		if (ui->lePassword->text().isEmpty()) {
			QMessageBox::warning(this, tr("Encrypt Key Empty"), tr("Please Input Encrypt/Decrypt Key"));
			return;
		}
	}
    QString md5;
    QString key=ui->lePassword->text();
    QByteArray bb;
    bb = QCryptographicHash::hash ( key.toUtf8(), QCryptographicHash::Md5 );
    //bb.at(0)==0x3f;
    md5.append(bb.toHex());
    char * pdata = bb.data();
    char datalen = 16;
    qDebug() << md5 << " result: " << (bb.at(0)=='\x41') << "data:" << QString::number(pdata[0],16)
            << " " << QString::number(pdata[1],16);

	char sName[256] = { 0 };
	char * psName = sName;
    DWORD len = 0;
    int enuret = sd_EnumDevice((char **)&sName,&len);
    if(enuret == SDR_OK){
        HDEV hDevice = 0;
        int openret = sd_OpenDevice(sName, &hDevice);
        if(openret != SDR_OK){
            QMessageBox::warning(this,tr("Open Failed"),tr("Open TF Card!"));
            return;
        }

        ULONG cap = 0;
        if(SDR_OK == sd_GetCapcity(hDevice,&cap)){
            char tmpdata[1024] = {0};
            memset(tmpdata,0xff,1024);
            tmpdata[0] = 0x5a;
            tmpdata[1] = 0xa5;
			if (ui->rbNoEnc->isChecked()) {
				tmpdata[2] = 0;
			}
            if(ui->rbSM4->isChecked()){
                tmpdata[2] = 0x1;
				memcpy(&(tmpdata[3]), pdata, 16);
				memcpy(&(tmpdata[512]), pdata, 16);
            }
            
            if(sd_WriteData(hDevice,cap - 2,sizeof(tmpdata),(UCHAR *)tmpdata)!=SDR_OK){
                QMessageBox::warning(this,tr("Write Failed"),tr("Set Authority Data Failed!"));
				sd_CloseDevice(hDevice);
            }
            else{
                QMessageBox::information(this,tr("Auth"),tr("Authority Succeed!"));
				sd_CloseDevice(hDevice);
				QDialog::accept();
            }
        }
        else{
            QMessageBox::warning(this,tr("GetCap Failed"),tr("Get TF Capacity Failed!"));
            sd_CloseDevice(hDevice);
			QDialog::accept();
            return;
        }
    } else {

        QMessageBox::warning(this,tr("Enum Failed"),tr("Not Found TF Card!"));
        return;
    }

}
