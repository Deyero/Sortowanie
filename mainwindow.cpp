#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sortwidget.h"

CodeDialog::CodeDialog(QWidget *parent):
    QDialog(parent)
{
    layout.addWidget(&code);
    setLayout(&layout);
    setWindowFlags(Qt::Window);
    code.setLineWrapMode(QTextEdit::NoWrap);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    codeDialog(this)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(pauseClicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(stopClicked()));
    connect(ui->buttonKod, SIGNAL(clicked()), this, SLOT(kodClicked()));
    connect(ui->widget, SIGNAL(labelInfoStarted(QString)), this, SLOT(labelInfoStarted(QString)));
    connect(ui->widget, SIGNAL(labelInfoTick(QString, QString)), this, SLOT(labelInfoTick(QString, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startClicked()
{
    bool ok;
    //sprawdzenie poprawnosci wejscia
    int n = ui->lineEdit->text().toInt(&ok);
    if (ok)
    {
        int delay = ui->lineEdit_2->text().toInt(&ok);
        if (ok)
        {
            SortWidget::Algorithm a = static_cast<SortWidget::Algorithm>(static_cast<int>(ui->comboBox->currentIndex()));
            if (n >= 0 && delay >= 0)
                ui->widget->start(a, n, delay);
            else
                QMessageBox::critical(this, "BUONT!", "Liczby większe od zera podać należy");
        }
    }
    if(!ok)
        QMessageBox::critical(this, "BUONT!", "Wartości liczbowe podać należy");
}

void MainWindow::pauseClicked()
{
    ui->widget->pause();
}

void MainWindow::stopClicked()
{
    ui->widget->stop();
}

void MainWindow::kodClicked()
{
    codeDialog.file = new QFile(":/kody/" + SortWidget::strAlgorithm[ui->widget->getAlgorithm()]+ ".txt");
    codeDialog.file->open(QIODevice::ReadOnly);
    codeDialog.stream = new QTextStream(codeDialog.file);
    codeDialog.code.setText(codeDialog.stream->readAll());
    codeDialog.file->close();
    delete codeDialog.stream;
    delete codeDialog.file;
    codeDialog.show();
}

void MainWindow::labelInfoStarted(QString alg)
{
    ui->labelAlgorithm->setText(alg);
}

void MainWindow::labelInfoTick(QString c, QString a)
{
    ui->labelComparisions->setText(c);
    ui->labelAccesses->setText(a);
}
