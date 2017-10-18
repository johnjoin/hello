#ifndef FREEZETABLE_H
#define FREEZETABLE_H

#include <QWidget>
#include <QTableView>
#include <QResizeEvent>
#include <QHeaderView>
#include <QAbstractSlider>
#include <QScrollBar>

//namespace Ui {
//class FreezeTable;
//}

class FreezeTable : public QTableView
{
    Q_OBJECT

public:
    explicit FreezeTable(QAbstractItemModel *model);
    ~FreezeTable();
protected:
    virtual void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;
private:
    QTableView* frozenview;
    void Init();
    void updateFrozenTableGeometry();
private slots:
    void updateSectionWidth(int logicalIndex,int oldSize,int newSize);
    void updateSeectionHeight(int logicalIndex,int oldSize,int newSize);

private:
 //   Ui::FreezeTable *ui;
};

#endif // FREEZETABLE_H
