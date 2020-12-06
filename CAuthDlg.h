#ifndef CAUTHDLG_H
#define CAUTHDLG_H

#include <QDialog>

namespace Ui {
class CAuthDlg;
}

class CAuthDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAuthDlg(QWidget *parent = nullptr);
    ~CAuthDlg();

protected slots:
    void sltConfirm();
	void sltNoEnc(bool);
	void sltSM4(bool);

private:
    Ui::CAuthDlg *ui;
};

#endif // CAUTHDLG_H
