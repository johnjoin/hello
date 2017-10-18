#include "mainwindow.h"
#include <QApplication>
#include <qdebug>
#include "freezetable.h"
#include <QStandardItemModel>
#include <QProgressDialog>
#include <qt_windows.h>
#include <fstream>
#include <qtoolbutton.h>
#include <iostream>
#include <QFutureWatcher>
#include <QTest>
#include <QtUiTools>

bool sort(int**& arrdst,int x,int y,int* arrsrc,int len,int num = -1,int flag = true)
{
    if(arrdst != NULL && arrsrc != NULL && x != 0 && y != 0 && len != 0)
    {
        int index = 0;
        int tmpx = 0;
        int tmpy = 0;
        while(tmpx < x)
        {
            if(flag)
            {
                for(tmpy=0;tmpy<y;tmpy++)
                {
                    if(arrdst[tmpx][tmpy] == -1)
                    {
                        continue;
                    }
                    arrdst[tmpx][tmpy] = arrsrc[index++];
                    if(index >= len)
                    {
                        return true;
                    }
                }
            }
            else
            {
                for(tmpy=y-1;tmpy>=0;tmpy--)
                {
                    if(arrdst[tmpx][tmpy] == num)
                    {
                        continue;
                    }
                    arrdst[tmpx][tmpy] = arrsrc[index++];
                    if(index >= len)
                    {
                        return true;
                    }
                }
            }
            flag = !flag;
            tmpx++;
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool sort2(int**& arrdst,int x,int y,int* arrsrc,int len)
{
    if(arrdst != NULL && arrsrc != NULL && x != 0 && y != 0 && len != 0)
    {
        int tmpx = 0;
        int tmpy = 0;
        int index = 0;

        return true;

    }
    else
    {
        return false;
    }
}

void run()
{
    int* arr = new int[100];
    for(int i=0;i<100;i++)
    {
        arr[i] = i+1;
    }
    int arr2[4][7];
    int** arr3 = new int *[5];
    for(int i=0;i<5;i++)
    {
        arr3[i] = new int[8];
        for(int j=0;j<8;j++)
        {
            arr3[i][j] = 0;
        }
    }
    arr3[0][3] = -1;
    arr3[1][5] = -1;
    arr3[2][0] = -1;
    arr3[3][7] = -1;
    for(int m =0;m<4;m++)
    {
        for(int n = 0;n<7;n++)
        {
            arr2[m][n] = 0;
        }
    }
    arr2[1][6] = -1;
    arr2[2][6] = -1;
    arr2[3][6] = -1;

    sort(arr3,5,8,arr,100);

    for(int m =0;m<5;m++)
    {
        for(int n = 0;n<8;n++)
        {
            qDebug()<<arr3[m][n];
        }
    }
}
void test()
{

    char path[] = "E:/Qt/Qt5.7.1/Projects/New/bin/release/grades.txt";
    std::ifstream fsRead(path);
    fsRead.seekg(0,std::ios::end);
    std::streampos ps = fsRead.tellg();
    std::cout<<"ps"<<ps<<std::endl;
    fsRead.close();

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QUiLoader loader;
//    QString path = QDir::currentPath();
//    qDebug()<<path;
//    path += "/mainwindow.ui";
//    QFile file(path);
//    file.open(QFile::ReadOnly);
//    QWidget* widget = loader.load(&file);
//    widget->show();
//    file.close();
//    MainWindow w;
//    return QTest::qExec(&w,argc,argv);
//    w.show();
//    run();
//    test();

//    int numFiles = 10;
//    QProgressDialog dlg("Copy files...","Abort",0,numFiles);
//    dlg.setWindowModality(Qt::WindowModal);
//    dlg.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
//    for(int i=0;i<numFiles;i++)
//    {
//        dlg.setValue(i);
//        if(dlg.wasCanceled())
//        {
//            break;
//        }
//    }
//    dlg.setValue(numFiles);

    //    QStandardItemModel* model = new QStandardItemModel();
    //    QFile file("E:/Qt/Qt5.7.1/Projects/New/bin/release/grades.txt");
    //    if(file.open(QFile::ReadOnly))
    //    {
    //        QString line = file.readLine(200);
    //        QStringList list = line.simplified().split(',');
    //        model->setHorizontalHeaderLabels(list);
    //        int row = 0;
    //        QStandardItem* newItem = 0;
    //        while(file.canReadLine())
    //        {
    //            line = file.readLine(200);
    //            if(!line.startsWith('#') && line.contains(','))
    //            {
    //                list = line.simplified().split(',');
    //                for(int col = 0;col<list.length();++col)
    //                {
    //                    newItem = new QStandardItem(list.at(col));
    //                    model->setItem(row,col,newItem);
    //                }
    //                ++row;
    //            }
    //        }
    //        file.close();
    //    }
    //    FreezeTable* table = new FreezeTable(model);
    //    table->setWindowTitle("Freeze");
    //    table->resize(560,680);
    //    table->show();
    return a.exec();
}
