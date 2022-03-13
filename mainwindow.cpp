#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include "stringdata.h"
#include "reader.h"
#include "writer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_writeData_clicked()
{
    // prepare data that you want to save to csv-file
    QList<QString> strList;
    strList << "one" << "two" << "three";

    QtCSV::StringData strData;
    strData.addRow(strList);
    strData.addEmptyRow();
    strData << strList << "this is the last row";

    // write to file
    const auto filePath = QDir::currentPath() + "/test.csv";
    QtCSV::Writer::write(filePath, strData);
}

void MainWindow::on_btn_readData_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Excel file"), qApp->applicationDirPath (),tr("Files (*.csv)"));

    // read data from file
    QList<QStringList> readData = QtCSV::Reader::readToList(fileName);
    for (int i = 0; i < readData.size(); ++i)
    {
        //qDebug() << readData.at(i).join(",");
        QStringList stringList = readData.at(i);
        for (int j = 0; j < stringList.size(); ++j) {
            qDebug() << stringList.at(j);
        }
    }

}
