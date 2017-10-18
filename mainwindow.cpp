#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setFixedSize(100,500);
    Init();
    this->setWindowTitle(QObject::tr("Title"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    qDebug()<<e->key()<<e->text();
}

void MainWindow::Init()
{
    m_translator = new QTranslator(qApp);
    InitUI();
    SetStyleSheet();
}

void MainWindow::InitUI()
{
    ui->pushButton->setText(QObject::tr("Change"));
}

void MainWindow::SetStyleSheet()
{
    QFile file("");
    if(file.open(QFile::ReadOnly))
    {
        QByteArray data = file.readAll();
        this->setStyleSheet(data);
        file.close();
    }
}

QStringList MainWindow::FindFile(QString dir, QStringList fliters)
{
    QStringList list;
    QDir Dir(dir);
    foreach(QString file,Dir.entryList(fliters,QDir::Files))
        list<<dir + "/" + file;
    foreach(QString subdir,Dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot))
        list += FindFile(dir + "/" + subdir,fliters);
    return list;
}

WordCount MainWindow::SingleThread(QStringList list)
{
    WordCount wordcount;
    for(auto p:list)
    {
        QString tmp = p;
        QFile file(tmp);
        if(file.open(QFile::ReadOnly))
        {
            QTextStream ts(&file);
            while(ts.atEnd() == false)
            {
                foreach(const QString& word,ts.readLine().split(' '))
                    wordcount[word] += 1;
            }
            file.close();
        }
    }
    return wordcount;
}

void MainWindow::reduce(WordCount& result,const WordCount& w)
{
    QMapIterator<QString,int> i(w);
    while(i.hasNext())
    {
        i.next();
        result[i.key()] += i.value();
    }
}

WordCount MainWindow::countWords(QString& filename)
{
    WordCount wordcount;
    QFile file(filename);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream ts(&file);
        while(ts.atEnd() == false)
        {
            foreach(const QString& word,ts.readLine().split(' '))
                wordcount[word] += 1;
        }
        file.close();
    }
    return wordcount;
}

void MainWindow::CheckUSB()
{
    QDBusConnection::systemBus().connect("org.freedesktop.Hal",
                                         "/org/freedesktop/Manager",
                                         "org.freedesktop.Hal.Manager",
                                         "DeviceAdded",
                                         this,
                                         SLOT(DeviceAdd(QString)));
}

void MainWindow::Calculate()
{
    QDBusInterface remoteApp("com.example.Calculator","/Calculator/Operations","org.mathematics.RPNCalculator");
    remoteApp.call("PushOperand",2);
    remoteApp.call("PushOperand",2);
    remoteApp.call("ExecuteOperation","+");
    QDBusReply<int> reply = remoteApp.call("PopOperand");
    qDebug()<<reply.value();
    if(reply.isValid())
    {
        qDebug()<<reply.value();
    }
}

void MainWindow::DeviceAdd(QString str)
{
    QDBusInterface device("org.freedesktop.Hal",str,"org.freedesktop.Hal.Device",QDBusConnection::systemBus());
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<QDir::currentPath();
    Calculate();
    int static state = 0;
    if(state == 0)
    {
        state = 1;
        m_translator->load("E:/Qt/Qt5.7.1/Projects/New/test_en.qm");
        qApp->installTranslator(m_translator);
    }
    else
    {
        state = 0;
        m_translator->load("E:/Qt/Qt5.7.1/Projects/New/bin/test_cn.qm");
        qApp->installTranslator(m_translator);
    }
    ui->retranslateUi(this);
    ui->pushButton->setText(tr("Change"));
    this->setWindowTitle(tr("title"));

//    QStringList list = FindFile("../../",QStringList()<<"*.h"<<"*.cpp");
//    qDebug()<<list.size();
//    QTime time;
//    time.start();
//    WordCount word = SingleThread(list);
//    qDebug()<<"SingleThread "<<time.elapsed()<<word.size();
//    QFile file("abc.txt");
//    if(file.open(QFile::WriteOnly))
//    {
//        auto it=word.begin(),itend=word.end();
//        for(;it!=itend;it++)
//        {
//           int value = it.value();
//           QString key = it.key();
//           QString tmp = QString("%1:%2\r\n").arg(key).arg(value);
//           file.write(tmp.toStdString().c_str());
//        }
//        file.close();
//    }
//    QKeyEvent* e = new QKeyEvent(QKeyEvent::KeyPress,Qt::Key_Y,Qt::NoModifier,"this is a txt");
//    QApplication::sendEvent(this,e);
//    time.start();
//    word =  QtConcurrent::mappedReduced(list,countWords,reduce);
//    qDebug()<<"mappedreduce "<<time.elapsed();
//    QDialog dlg;dlg.open();
//    QVERIFY(1 == 1);
//    QFETCH(QString,string);
}
