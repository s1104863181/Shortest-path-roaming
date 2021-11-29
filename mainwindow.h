#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include<Qstring>
#include <iostream>
#include<string>
using namespace std;

namespace Ui {
class MainWindow;
}

extern int qsd;
extern int zzd;
extern int b[120];

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int k;
    int w;
    int v;
    void  setStartStation (int v);
    void  setEndStation (int k);
    void  setNextPos (int w);
    void  paintEvent(QPaintEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void FindPath ();
    int startX, startY, endX, endY;
    int i,cnt,cntx,cnty;

    #define MAXVEX 127
    #define INFINITY 1000000
    typedef int Path[MAXVEX][MAXVEX];
    typedef int ShortDis[MAXVEX][MAXVEX];
    int pathpoint[126];
    int pathpointx[126];
    int pathpointy[126];
    typedef int sum;
    typedef struct
    {
    string a[MAXVEX];   //顶点集合
    int b[MAXVEX][MAXVEX];    //边距/权重
    int numPlots;
    } MGraph;
    void CreateMGraph(MGraph *G);
    void ShortestPath_Floyd(MGraph MG, Path P, ShortDis D);
    void mainFloyd();
    void setStart(int X, int Y);
    void setEnd(int X, int Y);

    static int qd;
    static int zd;
    enum  Type {
        None          = 0,
        Amplification ,
        Shrink,
        Lift,
        Right,
        Up,
        Down,
        Move
    };

private:
    Ui::MainWindow *ui;
    QPixmap  *pix;
        int action;          //动作(放大,缩小,移动...)
        int pixW;            //图片宽
        int pixH;            //图片高

        QRect Paint;         //绘画区域
        QLabel label;

        float ratio;                //比例
        QPoint offset;              //一次的图片偏移值
        QPoint Alloffset;           //总偏移





        void on_pushButton_clicked();
};

#endif // MAINWINDOW_H

