#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QGridLayout>

class CodeDialog : public QDialog
{
public:
    CodeDialog(QWidget *parent = 0);
    QTextEdit code;
    QFile *file;
    QTextStream *stream;
    QGridLayout layout;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void startClicked();
    void stopClicked();
    void pauseClicked();
    void kodClicked();
    void labelInfoStarted(QString alg);
    void labelInfoTick(QString c, QString a);

private:
    Ui::MainWindow *ui;
    CodeDialog codeDialog;
};

#endif // MAINWINDOW_H
