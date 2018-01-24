#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defines.h"
#include <string>
#include <numeric>
#include <math.h>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QVector>
#include <algorithm>

//const QString MainWindow::filePath = "./STATISTIKY.txt";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	lines(0),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	/* TODO:
	 * Move watcher to DataMonitoringWorker
	 */
    watcher = new QFileSystemWatcher(this);
    watcher->addPath(Defines::FilePath);

	connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(handleFileChange(const QString &)));

    handleFileChange(Defines::FilePath);
}

MainWindow::~MainWindow()
{
    delete ui;
	delete watcher;
}

/* TODO:
 * Implement DataMonitoringController, DataMonitoringWorker
 * based on first QThread documentation example
 * Move File handling to DataMonitoringWorker slot
 */
void MainWindow::handleFileChange(const QString &path)
{
    struct unique {
        int code;
        int sold;
    };
    QVector<struct unique> uniqueVect;

    struct outpt {
        unsigned int customers;
        float avarage;
        float revenue;
        float expanses;
        float result;
    };

    outpt output;
    output.customers = 0;
    output.revenue = 0;
    output.expanses = 0;
    output.result = 0;

    QString token;

        int idAside = 0;


	/* TODO:
	 * Replace output struct with DataStatistics
	 * Implement DataTransaction class
	 * Replace weird toFloat()s with DataTransaction
	 */

    QFile inputFile(path);

	if (inputFile.open(QIODevice::ReadOnly)) {
	   QTextStream in(&inputFile);
       bool firstP = true;
       int linesCheck = 0;
       try {
           lines = in.readLine().toInt();
           //for (int i=0; i<lines; i++){
           while(!in.atEnd()){
               QString line = in.readLine();
               QStringList strSplitted = line.split(Defines::Separator);
               bool found = false;

               if (strSplitted.at(0) == 'P'){
                   if (idAside != strSplitted.at(1).toInt()){
                       idAside = strSplitted.at(1).toInt();
                       output.customers++;
                   }
                   output.revenue = output.revenue + (strSplitted.at(3).toFloat() * strSplitted.at(4).toFloat());
                   if (firstP == true){
                       uniqueVect.push_back({strSplitted.at(2).toInt(), 0});
                       firstP = false;
                   }
                   for (int y=0; y<uniqueVect.size(); y++){
                       if(uniqueVect[y].code == strSplitted.at(2).toInt()){
                           uniqueVect[y].sold++;
                           found = true;
                           break;
                       }
                    }
                    if (found == false)
                       uniqueVect.push_back({strSplitted.at(2).toInt(), 1});
               }
               else {
                   output.expanses = output.expanses + (strSplitted.at(3).toFloat() * strSplitted.at(4).toFloat());
               }
               linesCheck++;
           }

           inputFile.close();
           //throw;
           if (linesCheck != lines){
               QMessageBox::information(0, "An error occurred", "Source file probably corrupted.");
           }
       }
       catch (...){
           QMessageBox::information(0, "Exception: An error occurred", "Source file probably corrupted.");
       }


       for (int i=0; i<lines; i++){
           for (int y=i+1; y<uniqueVect.size(); y++){
               if(uniqueVect[i].sold < uniqueVect[y].sold){
                   std::swap(uniqueVect[i], uniqueVect[y]);
               }
           }
       }

       if (output.customers != 0)
            output.avarage = output.revenue / output.customers;
       else
            output.avarage = 0;

       output.result = output.revenue - output.expanses;

	   /* TODO:
		* Implement MainWindow::updateStatistics(DataStatistics) slot
		* Move ui related stuff to updateStatistics method
		*/

       if (output.result<0){
           ui->label_result->setStyleSheet("color:red");
       }
       else {
           ui->label_result->setStyleSheet("color:black");
       }

       output.result = roundf(output.result * 100) / 100;

       ui->label_customers->setText(QString::number(output.customers));
       ui->label_avarageBasket->setText(QString::number(output.avarage));
       ui->label_revenue->setText(QString::number(output.revenue)+QString("%1").arg(Defines::Euro));
       ui->label_expanses->setText(QString::number(output.expanses)+QString("%1").arg(Defines::Euro));
       ui->label_result->setText(QString::number(output.result)+QString("%1").arg(Defines::Euro));

       QString text;
       for (int i=0; i<uniqueVect.size(); i++)
            text = text + QString::number(i+1) + ". " + QString::number(uniqueVect[i].code) + ": " + QString::number(uniqueVect[i].sold) + "\n";
       ui->top_browser->setText(text);
       text = "";
       int y=0;
       for (int i=uniqueVect.size()-1; i>=0; i--){
            y++;
            text = text + QString::number(y) + ". " + QString::number(uniqueVect[i].code) + ": " + QString::number(uniqueVect[i].sold) + "\n";
       }
       ui->bottom_browser->setText(text);
	}
	else
        QMessageBox::information(0, "Error: ", inputFile.errorString());
}
