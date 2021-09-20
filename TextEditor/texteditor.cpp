#include "texteditor.h"
#include "ui_texteditor.h"
int TextEditor::next[Edit_Len];
TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    edit=false;
    ui->setupUi(this);

    stack.base=new QString[stack_size];
    QString*tmp=stack.base;
    stack.top=stack.base;
    tmp--;
    stack.stack_ptr=tmp;
    QObject::connect(ui->action_save, SIGNAL(triggered()),
                         this, SLOT(save_change()));
    QObject::connect(ui->action_undo, SIGNAL(triggered()),
                         this, SLOT(undo_change()));
    QObject::connect(ui->action_redo, SIGNAL(triggered()),
                         this, SLOT(redo_change()));
}

TextEditor::~TextEditor()
{
    delete ui;
    delete []stack.base;
}
void TextEditor::on_plainTextEdit_textChanged()
{
    str=ui->plainTextEdit->toPlainText();
    edit=true;
}
void TextEditor::on_statistic_clicked()
{
    int space_num=0,char_num=0,no_num=0;
    for(int i=0;i<str.size();i++)
    {
        if(str[i]==' ')
            space_num++;
        else if((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z'))
            char_num++;
        else if((str[i]>='0'&&str[i]<='9'))
            no_num++;
    }
    QString str_space=QString::number(space_num,10);
    ui->lineEdit_space->setText(str_space);
    QString str_char=QString::number(char_num,10);
    ui->lineEdit_char->setText(str_char);
    QString str_num=QString::number(no_num,10);
    ui->lineEdit_num->setText(str_num);
}
void TextEditor::get_next(QString T, int* next)
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < T.size()) {
        if (j == -1 || T[i] == T[j]) {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}
int TextEditor::Index_KMP(QString S, QString T, int pos)
{
    int i = pos, j = 0;
    while (i != S.size() && j !=T.size()) {
        if (j == -1 || S[i] == T[j]) {
            ++i;
            ++j;
        }
        else
            j = next[j];
    }
    if (j == T.size())
        return i - T.size();
    else
        return -1;
}
void TextEditor::on_substringnum_clicked()
{
    QString sub_string=ui->lineEdit->text();
    if(sub_string.size()==0||str.size()==0)
        ui->lineEdit_2->setText("0");
    else
    {
        get_next(sub_string, next);
        int total=0;
        for(int i=0;;){
            if(Index_KMP(str,sub_string, i)==-1)
                break;
            else{
                total++;
                i=sub_string.size()+Index_KMP(str,sub_string, i);
            }
        }
        QString num=QString::number(total,10);
        ui->lineEdit_2->setText(num);
    }
}
void TextEditor::on_delete_substring_clicked()
{
    QString sub_string=ui->lineEdit->text();
    QString temp=str.replace(sub_string,"");
    ui->plainTextEdit->setPlainText(temp);
}
void TextEditor::save_change()
{
    edit=false;
    QString*tmp=stack.stack_ptr;
    tmp++;
    if(tmp==stack.top){
        QString s=str;
        *stack.top=s;
        stack.stack_ptr=stack.top;
        stack.top++;
    }
    else{
        stack.stack_ptr++;
        tmp=stack.stack_ptr;
        tmp++;
        while(stack.top!=tmp){
            --stack.top;
        }
        QString s=str;
        *stack.top=s;
        stack.top++;
    }
}
void TextEditor::undo_change()
{
    if(stack.stack_ptr>=stack.base)
    {
       if(edit){
           ui->plainTextEdit->setPlainText(*stack.stack_ptr);
           stack.stack_ptr--;
       }
       else{
           stack.stack_ptr--;
           if(stack.stack_ptr>=stack.base){
               ui->plainTextEdit->setPlainText(*stack.stack_ptr);
               stack.stack_ptr--;
           }
           else
               ui->plainTextEdit->setPlainText("");

       }
    }
    else
        ui->plainTextEdit->setPlainText("");
}
void TextEditor::redo_change()
{
    QString*tmp=stack.stack_ptr;
    tmp++;
    if(tmp!=stack.top){
        stack.stack_ptr++;
        ui->plainTextEdit->setPlainText(*stack.stack_ptr);
    }
}

