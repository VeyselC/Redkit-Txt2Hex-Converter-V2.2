#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowTitle("ReDkIt Rus2Txt Converter V2.2");
    this->setWindowIcon(QIcon("://images/favicon.ico"));
    ui->setupUi(this);
    ui->comboBox->addItem("Cryllic");
    ui->comboBox->addItem("Polish");
    ui->comboBox_ayrac->addItem("\"");
//    ui->comboBox_ayrac->addItem("{");
    ui->comboBox_ayrac->addItem("txt");
    ui->HusamettinEdit_1->setLineWrapMode(QTextEdit::NoWrap);
    ui->HusamettinEdit_2->setLineWrapMode(QTextEdit::NoWrap);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
//    connect(this, SIGNAL(on_), this, SLOT(on_actionAbout_clicked()));

    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerSlot()
{
//    int count = ui->lineEdit->text().size();
    QString osman4 = ui->lineEdit->text();
    QString osman5;
    int k=0;
    for(int j=0;j<osman4.size();j++)
    {//CR,LF ayıklanıyor.
        if(osman4[j] != 0x0A && osman4[j] != 0x0D)        //CR veya Lf varsa
            osman5[k++] = osman4[j];
    }
    int count = osman5.size();

    if(count > 21)
        ui->label->setStyleSheet("QLabel { background-color : red; color : white; }");
    else
        ui->label->setStyleSheet("QLabel { background-color : green;color : yellow;}");

    ui->label->setText(QString::number(count));
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_2->clear();
    HexString.clear();
    RusString.clear();
    ui->HusamettinEdit_2->clear();

    Husamettin_HexString.clear();
    Husamettin_RusString.clear();

    QString osman4 = ui->lineEdit->text();
    int k=0;
    for(int j=0;j<osman4.size();j++)
    {
        if(osman4[j] != 0x0A && osman4[j] != 0x0D)        //CR veya Lf varsa
            RusString[k++] = osman4[j];
    }
    QTextCodec *codec;
    if(ui->comboBox->currentIndex() == 0)
        codec = QTextCodec::codecForName("Windows-1251");
    else //if(ui->comboBox->currentIndex() == 1)
        codec = QTextCodec::codecForName("Windows-1250");

    QByteArray encodedString = codec->fromUnicode(RusString);
    QString osman,osman2,osman3;
    for(int i=0; i<encodedString.size();i++)
        osman[i] = encodedString[i] ;
    osman2 = osman.toLatin1().toHex().toUpper();
    HexString = "0x";
    for(int i=0; i<osman2.size();i+=2)
    {
        osman3[0]=osman2[i];osman3[1]=osman2[i+1];
        if(i != osman2.size()-2)
        HexString  = QString(HexString + osman3 +",0x");
        else
            HexString  = QString(HexString + osman3);
    }
    ui->lineEdit_2->setText(HexString);

    QString husamettinline = ui->HusamettinEdit_1->toPlainText();
    QStringList strList = husamettinline.split(QRegExp("[\n]"),QString::SkipEmptyParts);

    int husam=0,ayrac_saydir,ayrac_saydir2,husamettinin_kucukoglan,husamettinin_buyukoglan;

    for(husam = 0; husam<strList.size();husam++)
    {
        ayrac_saydir = 0;
        ayrac_saydir2 = 0;
        husamettinin_kucukoglan = 0;
        husamettinin_buyukoglan = 0;
        QString Husamettin_1 = strList[husam];

        QByteArray encodedString_husamettin = codec->fromUnicode(Husamettin_1);         //codec'li hali
        QString husamettin,husamettin_bas,husamettin_orta,husamettinin_gotu,husamettin2,husamettin3;

        for(int ruknettin=0; ruknettin<encodedString_husamettin.size();ruknettin++)
        {
            if(ui->comboBox_ayrac->currentIndex() == 0)
            {
                if(encodedString_husamettin[ruknettin] == '"')
                    ayrac_saydir++;
                if(ayrac_saydir == 1 && encodedString_husamettin[ruknettin] != '"')
                {
                    husamettinin_buyukoglan++;
                    husamettin[ruknettin-husamettinin_kucukoglan] = encodedString_husamettin[ruknettin] ;
                }
                else if(ayrac_saydir == 0 || (ayrac_saydir == 1 && encodedString_husamettin[ruknettin] == '"'))
                {
                    husamettinin_kucukoglan++;
                    husamettinin_buyukoglan++;
                    husamettin_bas[ruknettin] = encodedString_husamettin[ruknettin] ;
                }
                else if(ayrac_saydir >= 2)
                {
                    husamettinin_gotu[ruknettin-husamettinin_buyukoglan] = encodedString_husamettin[ruknettin] ;
                }
            }
//            else if(ui->comboBox_ayrac->currentIndex() == 1)
//            {
//                if(encodedString_husamettin[ruknettin] == '{')
//                    ayrac_saydir++;
//                if(encodedString_husamettin[ruknettin] == '}')
//                    ayrac_saydir++;
//                if(ayrac_saydir == 1 && encodedString_husamettin[ruknettin] != '{')
//                {
//                    husamettinin_buyukoglan++;
//                    husamettin[ruknettin-husamettinin_kucukoglan] = encodedString_husamettin[ruknettin] ;
//                }
//                else if(ayrac_saydir == 0 || (ayrac_saydir == 1 && encodedString_husamettin[ruknettin] == '{'))
//                {
//                    husamettinin_kucukoglan++;
//                    husamettinin_buyukoglan++;
//                    husamettin_bas[ruknettin] = encodedString_husamettin[ruknettin] ;
//                }
//                else if(ayrac_saydir == 2)
//                {
//                    husamettinin_gotu[ruknettin-husamettinin_buyukoglan] = encodedString_husamettin[ruknettin] ;
//                }
//            }
            else// if(ui->comboBox_ayrac->currentIndex() == 2)
            {
                husamettin[ruknettin] = encodedString_husamettin[ruknettin] ;
            }

        }
//husamettinin de g.tü başı ayrı oynuo
//        qDebug() << "bas1:" <<husamettin_bas << "\n";
//        qDebug() << "orta1:" <<husamettin << "\n";
//        qDebug() << "got1:" <<husamettinin_gotu << "\n";
        if(ayrac_saydir != 0)
        {
            husamettin_bas[husamettinin_kucukoglan-1] = '{';
            husamettinin_gotu[0] = '}';
        }

//        qDebug() << "bas1:" <<husamettin_bas << "\n";
//        qDebug() << "orta1:" <<husamettin << "\n";
//        qDebug() << "got1:" <<husamettinin_gotu << "\n";
//husamettinin de g.tü başı ayrı oynuo

        husamettin2 = husamettin.toLatin1().toHex().toUpper();
        husamettin_orta = "0x";
        for(int sukufe=0; sukufe<husamettin2.size();sukufe+=2)
        {
            husamettin3[0]=husamettin2[sukufe];husamettin3[1]=husamettin2[sukufe+1];
            if(sukufe != husamettin2.size()-2)
            husamettin_orta  = QString(husamettin_orta + husamettin3 +",0x");
            else
                husamettin_orta  = QString(husamettin_orta + husamettin3);
        }
        if(ui->comboBox_ayrac->currentIndex() == 0)
        {
            if(ayrac_saydir != 0)
            Husamettin_HexString = husamettin_bas + husamettin_orta + husamettinin_gotu;
            else Husamettin_HexString = husamettin_bas;
        }
        else
        {
            Husamettin_HexString = husamettin_orta;
        }

        ui->HusamettinEdit_2->append(Husamettin_HexString);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    HexString.clear();
    RusString.clear();
    ui->HusamettinEdit_1->clear();

    QString osman10 = ui->lineEdit_2->text();

    osman10.replace(QString("0X"), QString(""),Qt::CaseInsensitive);
    osman10.replace(QString(","), QString(""),Qt::CaseInsensitive);
    unsigned int sayac=0;

    while(sayac < osman10.size())
    {
        if((osman10[sayac] >= 0x30 && osman10[sayac] <= 0x39) || (osman10[sayac] >= 0x41 && osman10[sayac] <= 0x46) || (osman10[sayac] >= 0x61 && osman10[sayac] <= 0x66))
                sayac++;
        else
        {
            QMessageBox::information(
                this,
                tr("ReDkIt Rus2Txt V2.2"),
                tr("HEX code FAIL FAIL "));
              //qDebug() << "Debug Message" << sayac;
            break;
        }
    }
    QByteArray array (osman10.toStdString().c_str());

    QByteArray text =  QByteArray::fromHex(array);
    text.data();            // returns "Qt is great!"
    QTextCodec *codec;
    if(ui->comboBox->currentIndex() == 0)
        codec = QTextCodec::codecForName("Windows-1251");
    else //if(ui->comboBox->currentIndex() == 1)
        codec = QTextCodec::codecForName("Windows-1250");

    QString encodedString = codec->toUnicode(text);
//qDebug() << "-2";
    ui->lineEdit->setText(encodedString);

//qDebug() << "-1";
    QString husamettinline = ui->HusamettinEdit_2->toPlainText();
    QStringList strList2 = husamettinline.split(QRegExp("[\n]"),QString::SkipEmptyParts);
//qDebug() << "0";
//    int husam=0;
    for(int husam = 0; husam<strList2.size();husam++)
    {
        QString husamettin10 = strList2[husam];

        husamettin10.replace(QString("0X"), QString(""),Qt::CaseInsensitive);
        husamettin10.replace(QString(","), QString(""),Qt::CaseInsensitive);
        unsigned int husamsayac=0;

        while(husamsayac < husamettin10.size())
        {
            if((husamettin10[husamsayac] >= 0x30 && husamettin10[husamsayac] <= 0x39) || (husamettin10[husamsayac] >= 0x41 && husamettin10[husamsayac] <= 0x46) || (husamettin10[husamsayac] >= 0x61 && husamettin10[husamsayac] <= 0x66))
                    husamsayac++;
            else
            {
                QMessageBox::information(
                    this,
                    tr("ReDkIt Rus2Txt V2.2"),
                    tr("HEX code FAIL FAIL "));
                break;
            }
        }
        QByteArray husamarray (husamettin10.toStdString().c_str());
//        qDebug(husamarray.);
//        qDebug() << "1" << husamarray;
        QByteArray husamtext =  QByteArray::fromHex(husamarray);
        husamtext.data();            // returns "Qt is great!"
        QString husamencodedString = codec->toUnicode(husamtext);
//        qDebug() << "2" << husamencodedString;
        ui->HusamettinEdit_1->append(husamencodedString);
    }

}




void MainWindow::on_actionAbout_triggered()
{
//    aboutDialog = new AboutDialog(); // Be sure to destroy your window somewhere
       aboutDialog.show();

}
