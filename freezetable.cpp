#include "freezetable.h"
#include <qdebug>
//#include "ui_freezetable.h"

FreezeTable::FreezeTable(QAbstractItemModel *model)
//    ui(new Ui::FreezeTable)
{
//    ui->setupUi(this);
    setModel(model);
    frozenview = new QTableView(this);
    Init();
    connect(this->horizontalHeader(),&QHeaderView::sectionResized,this,&FreezeTable::updateSectionWidth);
    connect(horizontalHeader(),&QHeaderView::sectionResized,this,&FreezeTable::updateSeectionHeight);
    connect(frozenview->verticalScrollBar(),&QAbstractSlider::valueChanged,verticalScrollBar(),&QAbstractSlider::setValue);
    connect(verticalScrollBar(),&QAbstractSlider::valueChanged,frozenview->verticalScrollBar(),&QAbstractSlider::setValue);
}

FreezeTable::~FreezeTable()
{
//    delete ui;
}

void FreezeTable::resizeEvent(QResizeEvent *e)
{
    QTableView::resizeEvent(e);
    updateFrozenTableGeometry();
}

QModelIndex FreezeTable::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex index = QTableView::moveCursor(cursorAction,modifiers);
    if(cursorAction == MoveLeft && index.column() > 0 && visualRect(index).topLeft().x() < frozenview->columnWidth(0))
    {
        const int newValue = this->horizontalScrollBar()->value() + visualRect(index).topLeft().x() - frozenview->columnWidth(0);
        horizontalScrollBar()->setValue(newValue);
    }
    return index;
}

void FreezeTable::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
//    if(index.column() > 0)
//    {
//        QTableView::scrollTo(index,hint);
//    }
}

void FreezeTable::Init()
{
    frozenview->setModel(this->model());
    frozenview->setFocusPolicy(Qt::NoFocus);
    frozenview->verticalHeader()->hide();
    frozenview->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->viewport()->stackUnder(frozenview);
    frozenview->setStyleSheet("QTableView{border:node;"
                              "background-color:#8EDE21;"
                              "selection-background-color:#ccc}");
    frozenview->setSelectionModel(this->selectionModel());
    int size = this->model()->columnCount();
    for(int col = 1;col<size;++col)
    {
        frozenview->setColumnHidden(col,true);
    }
    frozenview->setColumnWidth(0,this->columnWidth(0));
    frozenview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenview->show();
    updateFrozenTableGeometry();
    setHorizontalScrollMode(this->ScrollPerPixel);
    setVerticalScrollMode(this->ScrollPerPixel);
    frozenview->setVerticalScrollMode(this->ScrollPerPixel);
}

void FreezeTable::updateFrozenTableGeometry()
{
    qDebug()<<"updateFrozenTableGeometry"<<verticalHeader()->width()<<frameWidth()<<columnWidth(0)<<viewport()->height()<<horizontalHeader()->height();
    frozenview->setGeometry(verticalHeader()->width()+frameWidth(),frameWidth(),columnWidth(0),viewport()->height()+horizontalHeader()->height());
}

void FreezeTable::updateSectionWidth(int logicalIndex, int oldSize, int newSize)
{
    if(logicalIndex == 0)
    {
        frozenview->setColumnWidth(0,newSize);
        updateFrozenTableGeometry();
    }
}

void FreezeTable::updateSeectionHeight(int logicalIndex, int oldSize, int newSize)
{
    frozenview->setRowHeight(logicalIndex,newSize);
}
