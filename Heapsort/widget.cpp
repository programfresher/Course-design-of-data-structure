#include "widget.h"
#include "ui_widget.h"
/**************************************
 构造函数
**************************************/
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    /*相关变量初始状态的设置*/
    H.push_back(INT32_MIN);
    ui->setupUi(this);
    order=0;

    /*实现相关信号与槽函数的关联*/
    QObject::connect(ui->comboBox, SIGNAL(currentTextChanged(QString)),
                         this, SLOT(data_in()));
    QObject::connect(ui->lineEdit, SIGNAL(textChanged(QString)),
                         this, SLOT(data_in()));
}
/**************************************
析构函数
**************************************/
Widget::~Widget()
{
    delete ui;
}
/**************************************
堆的重新筛选调整函数
**************************************/
void Widget::HeapAdjust(int s, int m)
{
    int rc = H[s];
    for (int j = 2 * s; j <= m; j *= 2) {
        if (j < m && H[j] < H[j + 1])
            ++j;
        if (rc >= H[j])
            break;
        H[s] = H[j];
        s = j;
    }
    H[s] = rc;
}
/**************************************
界面的绘图函数
**************************************/
void Widget::paintEvent(QPaintEvent* event)
{
    /*绘图所需的pen、brush的预设*/
    QPainter p(this);
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
    p.setBrush(QBrush(qRgb(215,232,245)));

    /*相关绘图点的设置*/
    QVector<QPointF> vec;
    QPointF q0(400,160);
    QPointF q1(200,240);
    QPointF q2(600,240);
    QPointF q3(100,310);
    QPointF q4(300,310);
    QPointF q5(500,310);
    QPointF q6(700,310);
    QPointF q7(50,370);
    QPointF q8(150,370);
    QPointF q9(250,370);
    QPointF q10(350,370);
    QPointF q11(450,370);
    QPointF q12(550,370);
    QPointF q13(650,370);
    QPointF q14(750,370);
    if(1){
        vec.append(QPointF(0,0));
        vec.append(q0);
        vec.append(q1);
        vec.append(q2);
        vec.append(q3);
        vec.append(q4);
        vec.append(q5);
        vec.append(q6);
        vec.append(q7);
        vec.append(q8);
        vec.append(q9);
        vec.append(q10);
        vec.append(q11);
        vec.append(q12);
        vec.append(q13);
        vec.append(q14);

        /*根据排序条件实时绘画连线*/
        if(order>=2)
            p.drawLine(q0,q1);
        if(order>=3)
            p.drawLine(q0,q2);
        if(order>=4)
            p.drawLine(q1,q3);
        if(order>=5)
            p.drawLine(q1,q4);
        if(order>=6)
            p.drawLine(q2,q5);
        if(order>=7)
            p.drawLine(q2,q6);
        if(order>=8)
            p.drawLine(q3,q7);
        if(order>=9)
            p.drawLine(q3,q8);
        if(order>=10)
            p.drawLine(q4,q9);
        if(order>=11)
            p.drawLine(q4,q10);
        if(order>=12)
            p.drawLine(q5,q11);
        if(order>=13)
            p.drawLine(q5,q12);
        if(order>=14)
            p.drawLine(q6,q13);
        if(order>=15)
            p.drawLine(q6,q14);
    }

    /*绘制存放各键值的图形圆*/
    if(1){
        int n=H.size()-1;
        if(n>=2){
            p.drawEllipse(q0,20,20);
            p.drawEllipse(q1,20,20);
        }
        if(n>=3)
            p.drawEllipse(q2,20,20);
        if(n>=4)
            p.drawEllipse(q3,20,20);
        if(n>=5)
            p.drawEllipse(q4,20,20);
        if(n>=6)
            p.drawEllipse(q5,20,20);
        if(n>=7)
            p.drawEllipse(q6,20,20);
        if(n>=8)
            p.drawEllipse(q7,20,20);
        if(n>=9)
            p.drawEllipse(q8,20,20);
        if(n>=10)
            p.drawEllipse(q9,20,20);
        if(n>=11)
            p.drawEllipse(q10,20,20);
        if(n>=12)
            p.drawEllipse(q11,20,20);
        if(n>=13)
            p.drawEllipse(q12,20,20);
        if(n>=14)
            p.drawEllipse(q13,20,20);
        if(n>=15)
            p.drawEllipse(q14,20,20);
    }

    /*绘制显示各键值*/
    for(int i=1;i<H.size();i++)
        p.drawText(vec[i],QString::number(H[i],10));

}
/**************************************
开始演示按钮的槽函数
**************************************/
void Widget::on_start_clicked()
{
    /*设置按钮状态并调用堆排序算法*/
    ui->start->setEnabled(false);
    ui->restart->setEnabled(false);
    HeapSort();
    ui->restart->setEnabled(true);
}
/**************************************
堆排序算法
**************************************/
void Widget::HeapSort()
{
     /*初始建堆*/
    for (int i = (H.size() - 1) / 2; i > 0; i--)
        HeapAdjust(i, H.size() - 1);

    /*初始建堆界面的相关设置*/
    int time=ui->speed->value();
    order=H.size()-1;
    ui->label_3->setText("堆顶元素--->");
    ui->label_4->setText("初始建堆");
    repaint();

    /*加入延时动画*/
    QTime delayTime = QTime::currentTime().addMSecs(time);
    while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    /*后续筛选及相应界面变化设置*/
    ui->label_4->setText("后续筛选");
    for (int i = H.size() - 1; i > 1; i--) {
        int tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        HeapAdjust(1, i - 1);

        order--;
        repaint();
        if(i!=2)
        {
            QTime delayTime = QTime::currentTime().addMSecs(time);
            while( QTime::currentTime() < delayTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
    ui->label_4->setText("演示完毕");
}
/**************************************
负责检查输入键值输入是否合法的槽函数
**************************************/
void Widget::data_in()
{
    /*读取界面输入*/
    ui->start->setEnabled(false);
    int total=ui->comboBox->currentText().toInt();
    std::istringstream iss(ui->lineEdit->text().toStdString());

    /*判断键值个数及类型是否合法*/
    int i=0,tmp;
    std::vector<int> TMP;
    for(;iss>>tmp;i++){
        if(total==i)
            break;
        TMP.push_back(tmp);
    }
    if(total==i){
        H.clear();
        H.push_back(INT32_MIN);
        for(auto s:TMP)
            H.push_back(s);
        ui->start->setEnabled(true);
    }
}

/**************************************
重置按钮的槽函数
**************************************/
void Widget::on_restart_clicked()
{
    /*相关变量的处理*/
    H.clear();
    H.push_back(INT32_MIN);
    order=0;

    /*界面内容的重置*/
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->lineEdit->setText("");
    ui->start->setEnabled(false);
    update();
}

