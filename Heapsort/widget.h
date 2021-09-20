#ifndef WIDGET_H
#define WIDGET_H
#include <sstream>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QtTest/QTest>
#include <QPen>
#include <QQueue>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr); //构造函数
    ~Widget();   //析构函数
    void HeapAdjust(int s, int m) ;   //堆排序的交换调整函数
    void HeapSort();                //堆排序函数
    void paintEvent(QPaintEvent* event);  //GUI界面的绘画事件

private slots:
    void data_in();                 //负责键值读取的槽函数
    void on_start_clicked();       //负责开始绘画演示的槽函数
    void on_restart_clicked();     //负责清空界面重开的槽函数

private:
    Ui::Widget *ui;               //Qt的UI界面指针
    std::vector<int> H;           //利用线性空间vector实现堆的底层构造
    int order;                    //传递堆排序调整的序数
};
#endif // WIDGET_H
