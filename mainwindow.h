#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QPropertyAnimation>
#include <QMap>
#include <qdebug>
#include <qdir>
#include <QFileInfoList>
#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include <QKeyEvent>
#include <QDialog>
#include <qtest.h>
#include <QApplication>
#include <QTranslator>
#include <QtDBus>
#include <QtDBus/qdbusconnection.h>

typedef QMap<QString,int> WordCount;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* e);
    void Init();
    void InitUI();
    void SetStyleSheet();
    QStringList FindFile(QString dir,QStringList fliters);
    WordCount SingleThread(QStringList list);
    void reduce(WordCount &result, const WordCount &w);
    WordCount countWords(QString &filename);
    void CheckUSB();
    void Calculate();
private slots:
    void DeviceAdd(QString str);


private slots:
    void on_pushButton_clicked();
private:
    QTranslator* m_translator;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
