#define _CRT_SECURE_NO_WARNINGS
#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include <QMainWindow>
#define Edit_Len 201
#define stack_size 1024
QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

struct STACK{
    QString*base;//栈底指针
    QString*stack_ptr;//记录修改的指针
    QString*top;//栈顶指针
};
class TextEditor : public QMainWindow
{
    Q_OBJECT
    static int next[Edit_Len];    //用于实现KMP算法的静态数组
    static void get_next(QString T, int* next);//构造next数组的静态函数
    static int Index_KMP(QString S, QString T, int pos);//KMP子串匹配算法
public:
    TextEditor(QWidget *parent = nullptr);//构造函数
    ~TextEditor();//析构函数

private slots:
    void on_plainTextEdit_textChanged();//跟踪文本编辑变化的槽函数
    void on_statistic_clicked();//对字符进行分类统计的槽函数
    void on_delete_substring_clicked();//删除子串的槽函数
    void on_substringnum_clicked();//统计子串的槽函数
    void save_change();//保存修改的槽函数
    void undo_change();//撤销修改的槽函数
    void redo_change();//恢复修改的槽函数

private:
    Ui::TextEditor *ui;//Qt的UI界面指针
    QString str;//用于保存当前文本的串
    STACK stack;//用于记录修改的指针
    bool edit;//检测用户是否对文本进行了编辑
};
#endif // TEXTEDITOR_H
