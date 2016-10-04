#include "Widget.h"
#include <QMessageBox>
#include <QFileDialog>

#include "TxtFilesRW.h"
#include <armadillo>
#include <QFileInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent){
    setupUi(this);
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::on_inputFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                       tr("Select dat-file"), ".",
                                       tr("Dat-files (*.dat *.txt);;All files(*.*)"));
    fileNameEdit->setText(fileName);
}

void Widget::on_convertButton_clicked()
{
    QString fileName = fileNameEdit->text();
    QString indexString = freqIndexEdit->text();

    // index
    bool ok;
    int freqIndex = indexString.toInt(&ok);
    if(ok==false)
    {
        QMessageBox::information(this,"Error", "Cannot read frequency index!");
        return;
    }
    if(freqIndex<=0)
    {
        QMessageBox::information(this,"Error", "Frequency index must be positive!");
        return;
    }
    int colsCount = 3 + freqIndex*2;



    // reading file
    arma::mat fileData = ReadTxtFile_comma(0,colsCount,fileName.toLocal8Bit().constData(),&ok);
    if (ok==false)
    {
        QMessageBox::information(this,"Error", "Bad input file or\n"
                                 "too large frequency index!");
        return;
    }

    // constructing output array
    int length = fileData.n_rows;
    arma::mat ampData(length, 2);
    arma::mat phaseData(length, 2);
    if (azRadio->isChecked()==true)
    {
        ampData.col(0) = fileData.col(0);
        phaseData.col(0) = fileData.col(0);
    }
    else
    {
        ampData.col(0) = fileData.col(1);
        phaseData.col(0) = fileData.col(1);
    }

    int ampIndex = 3+(freqIndex-1)*2;
    int phaseIndex = ampIndex+1;
    ampData.col(1) = fileData.col(ampIndex);
    phaseData.col(1) = -fileData.col(phaseIndex)*0.1; // -18...+18 phase
                                                      // "-" from 13.04.2011
    // writing files
    QString inputFileName = QFileInfo(fileName).fileName();
    QString path = QFileInfo(fileName).path();

    QString ampFileName = "a_" + inputFileName;
    QString phaseFileName = "p_" + inputFileName;

    QString ampFileFull = path + "/" + ampFileName;
    QString phaseFileFull = path + "/" + phaseFileName;

    WriteTxtFile(ampFileFull.toLocal8Bit().constData(), ampData, 5);
    WriteTxtFile(phaseFileFull.toLocal8Bit().constData(), phaseData, 5);

    QMessageBox::information(this,"Program", "Conversion complete.");
}

