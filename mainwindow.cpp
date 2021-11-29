#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <Qdebug>
#include <QPoint>
#include<QString>
#include<QMovie>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    //Paint(10,10,810,810),
    Alloffset(0,0)
{
    ui->setupUi(this);
    setWindowTitle(tr("地图导航"));// 设置窗体标题
    /*ratio= 0.3;             //初始化图片缩放比例
    action = MainWindow::None;
    pixW = 3071;            //设置图片尺寸为985*740
    pixH = 3071;


    QPixmap *pixmap = new QPixmap(":/new/prefix1/shangdamap.jpg");//从这里开始
    pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);   //图片显示，适配label框大小
    QPainter painter(this);*/

}
int qsd;
int zzd;
int qy;
int b[120];

void MainWindow:: paintEvent(QPaintEvent*)
    {


    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/shangdamap.jpg");

    painter.drawPixmap(30, 60, 900, 900, pix);
    painter.setBrush(QColor(255, 255, 255, 100));
    painter.drawRect(30,60, 900, 900);

   //画线程序+Floy主程序
    int pathpointx[126];
    int pathpointy[126];
    int v, w, k,sum;
    MGraph MG;
    Path P;
    ShortDis D;
    CreateMGraph(&MG);
    ShortestPath_Floyd(MG, P, D);

    //ui->shuzi->setText("索引号："+QString::number(index));//输出
   // qDebug ()<< "各顶点间最短路径如下: " << endl;
    if(qsd==0)
    {
        if(zzd==0)
        {
            if(qy==0)
            {
                qy=qy+1;
            }
            zzd=zzd+1;
        }
        qsd=qsd+1;
    }
    v=qsd;
    w=zzd;
    cnt=0;
   //qDebug() << v << "--" << w << " weight: " << D[v][w]<< "m"<< " Path: " << v << ' ';
    D[v][w]=D[v][w]*1.33;
    if(qy==2)
    {
        D[v][w]=D[v][w]*1.2;
    }
    ui->label_7->setText(QString::number(D[v][w]/1)+"s");
    ui->label_6->setText(QString::number(D[v][w])+"m");
            //path
    sum=1;
    setStartStation(v);
    pathpoint[cnt]=v;
    pathpointx[cnt]=startX;
    pathpointy[cnt]=startY;
   // qDebug() << startX << ", " << startY;
    cnt++;
       k = P[v][w];
            while (k != w)
              {
                 // qDebug() << "-> " << k << " ";
                 k = P[k][w];

                 printf("%d",k);
                 setNextPos(k);
                 pathpoint[cnt]=k;
                 pathpointx[cnt]=endX;
                 pathpointy[cnt]=endY;
               //  qDebug() << endX << ", " << endY;
                 sum++;
                 cnt++;
      //  qDebug()<< "-> " << w << endl;

    }
     setEndStation(w);
     pathpoint[cnt]=v;
     pathpointx[cnt]=endX;
     pathpointy[cnt]=endY;
   //   qDebug() << endX << ", " << endY;


    QPen pen;
    QBrush brush;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    painter.setPen(pen);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    //if (cnt==1)
      //  painter.drawLine(pathpointx[0],pathpointy[0],pathpointx[1],pathpointy[1]);
    //else
    //{
        QPoint points[126];
        for(cnt=0;cnt<=sum;cnt++)
        {
            points[cnt].setX(pathpointx[cnt]);
            points[cnt].setY(pathpointy[cnt]);
         }
        painter.drawPolyline(points,sum);
    //}

}





void MainWindow:: ShortestPath_Floyd(MGraph MG, Path P, ShortDis D)
{
    int v, w, k;
    for (v = 1; v < MG.numPlots; v++)/* 初始化D与P */
    {
        for (w = 1; w < MG.numPlots; w++)
        {
            D[v][w] = MG.b[v][w];/* D[v][w]值即为对应点间的权值 */
            P[v][w] = w;/* 初始化P */
        }
    }

    for (k = 1; k < MG.numPlots; k++)
    {
        for (v = 1; v < MG.numPlots; v++)
        {
            for (w = 1; w < MG.numPlots; w++)
            {

                if (D[v][w] > D[v][k] + D[k][w])
                {
                    D[v][w] = D[v][k] + D[k][w];
                    P[v][w] = P[v][k];/* 路径设置为经过下标为k的顶点 */
                }
            }
        }
    }


}

void MainWindow::setStart(int X, int Y)
{
    startX = X; startY = Y;
  // qDebug() << X << ", " << Y;
}

void MainWindow::setEnd(int X, int Y)
{
    endX = X; endY = Y;
}


void MainWindow::setStartStation (int v)
{
    switch (v) {

        case 1:
            setStart ( 233 ,	150 ); break;
        case 2:
            setStart ( 227 ,	163 ); break;
        case 3:
            setStart ( 233 , 178 ); break;
        case 4:
            setStart ( 204 , 185 ); break;
        case 5:
            setStart ( 156 , 203 ); break;
        case 6:
            setStart ( 255 , 207 );break;
        case 7:
            setStart ( 207 , 267 ); break;
        case 8:
            setStart ( 198 , 254 ); break;
        case 9:
            setStart ( 231 , 277 ); break;
        case 10:
            setStart ( 220 , 292 ); break;

        case 11:
            setStart ( 175 , 306 ); break;
        case 12:
            setStart ( 235 , 301 ); break;
        case 13:
            setStart ( 221 , 326 ); break;
        case 14:
            setStart ( 249 , 317 ); break;
        case 15:
            setStart ( 179 , 353 ); break;
        case 16:
            setStart ( 226 , 351 ); break;
        case 17:
            setStart ( 250 , 352 ); break;
        case 18:
            setStart ( 281 , 339 ); break;
        case 19:
            setStart ( 287 , 360 ); break;
        case 20:
            setStart ( 300 , 349 ); break;


        case 21:
            setStart ( 316 , 369 ); break;
        case 22:
            setStart ( 181 , 377 ); break;
        case 23:
            setStart ( 227 , 372 ); break;
        case 24:
            setStart ( 242 , 373 ); break;
        case 25:
            setStart ( 288 , 380 ); break;
        case 26:
            setStart ( 310 , 378 ); break;
        case 27:
            setStart ( 252 , 404 ); break;
        case 28:
            setStart ( 282 , 396 ); break;
        case 29:
            setStart ( 306 , 398 ); break;
        case 30:
            setStart ( 156 , 427 ); break;


        case 31:
            setStart ( 184 , 428 ); break;
        case 32:
            setStart ( 235 , 434 ); break;
        case 33:
            setStart ( 252 , 420 ); break;
        case 34:
            setStart ( 274 , 420 ); break;
        case 35:
            setStart ( 305 , 419 ); break;
        case 36:
            setStart ( 147 , 458 ); break;
        case 37:
            setStart ( 187 , 454 ); break;
        case 38:
            setStart ( 307 , 447 ); break;
        case 39:
            setStart ( 150 , 480 ); break;
        case 40:
            setStart ( 93 , 502 ); break;


        case 41:
            setStart ( 200 , 482 ); break;
        case 42:
            setStart ( 215 , 505 ); break;
        case 43:
            setStart ( 311 , 494 ); break;
        case 44:
            setStart ( 213 , 535 ); break;
        case 45:
            setStart ( 230 , 530 ); break;
        case 46:
            setStart ( 319 , 514 ); break;
        case 47:
            setStart ( 336 , 527 ); break;
        case 48:
            setStart ( 374 , 563 ); break;
        case 49:
            setStart ( 430 , 586 ); break;
        case 50:
            setStart ( 479 , 585 ); break;
        case 51:
            setStart ( 220 , 617 ); break;
        case 52:
            setStart ( 222 , 649 ); break;
        case 53:
            setStart ( 239 , 652 ); break;
        case 54:
            setStart ( 241 , 722 ); break;
        case 55:
            setStart ( 228 , 746 ); break;
        case 56:
            setStart ( 293 , 642 );break;
        case 57:
            setStart ( 380 , 643 ); break;
        case 58:
            setStart ( 457 , 682 ); break;
        case 59:
            setStart ( 482 , 655 ); break;
        case 60:
            setStart ( 584 , 675 ); break;

        case 61:
            setStart ( 596 , 690 ); break;
        case 62:
            setStart ( 636 , 645 ); break;
        case 63:
            setStart ( 666 , 621 ); break;
        case 64:
            setStart ( 631 , 610 ); break;
        case 65:
            setStart ( 540 , 602 ); break;
        case 66:
            setStart ( 599 , 601 ); break;
        case 67:
            setStart ( 623 , 588 ); break;
        case 68:
            setStart ( 653 , 560 ); break;
        case 69:
            setStart ( 712 , 547 ); break;
        case 70:
            setStart ( 523 , 576 ); break;


        case 71:
            setStart ( 602 , 559 ); break;
        case 72:
            setStart ( 636 , 531 ); break;
        case 73:
            setStart ( 506 , 549 ); break;
        case 74:
            setStart ( 585 , 530 ); break;
        case 75:
            setStart ( 617 , 504 ); break;
        case 76:
            setStart ( 666 , 486 ); break;
        case 77:
            setStart ( 488 , 523 ); break;
        case 78:
            setStart ( 570 , 503 ); break;
        case 79:
            setStart ( 596 , 475 ); break;
        case 80:
            setStart ( 598 , 455 ); break;


        case 81:
            setStart ( 434 , 465 ); break;
        case 82:
            setStart ( 480 , 464 ); break;
        case 83:
            setStart ( 434 , 440 ); break;
        case 84:
            setStart ( 476 , 435 ); break;
        case 85:
            setStart ( 555 , 416 ); break;
        case 86:
            setStart ( 575 , 421 ); break;
        case 87:
            setStart ( 398 , 405 ); break;
        case 88:
            setStart ( 454 , 409 ); break;
        case 89:
            setStart ( 536 , 387 ); break;
        case 90:
            setStart ( 431 , 385 ); break;


        case 91:
            setStart ( 520 , 362 ); break;
        case 92:
            setStart ( 570 , 345 ); break;
        case 93:
            setStart ( 531 , 334 ); break;
        case 94:
            setStart ( 495 , 298 ); break;
        case 95:
            setStart ( 550 , 300 ); break;
        case 96:
            setStart ( 587 , 300 ); break;
        case 97:
            setStart ( 657 , 293 ); break;
        case 98:
            setStart ( 689 , 284 ); break;
        case 99:
            setStart ( 483 , 258 ); break;
        case 100:
            setStart ( 514 , 261 ); break;
         case 101:
            setStart ( 565 , 248 ); break;
        case 102:
            setStart ( 476 , 221 ); break;
        case 103:
            setStart ( 417 , 197 ); break;
        case 104:
            setStart ( 437 , 186 ); break;
        case 105:
            setStart ( 477 , 187 ); break;
        case 106:
            setStart ( 509 , 190 );break;
        case 107:
            setStart ( 509 , 157 ); break;
        case 108:
            setStart ( 357 , 168 ); break;
        case 109:
            setStart ( 322 , 198 ); break;
        case 110:
            setStart ( 368 , 213 ); break;

        case 111:
            setStart ( 332 , 233 ); break;
        case 112:
            setStart ( 315 , 251 ); break;
        case 113:
            setStart ( 382 , 244 ); break;
        case 114:
            setStart ( 342 , 273 ); break;
        case 115:
            setStart ( 371 , 263 ); break;
        case 116:
            setStart ( 396 , 263 ); break;
        case 117:
            setStart ( 398 , 286 ); break;
        case 118:
            setStart ( 410 , 283 ); break;
        case 119:
            setStart ( 364 , 303 ); break;
        case 120:
            setStart ( 337 , 345 ); break;


        case 121:
            setStart ( 375 , 320 ); break;
        case 122:
            setStart ( 426 , 306 ); break;
        case 123:
            setStart ( 501 , 388 ); break;
        case 124:
            setStart ( 517 , 416 ); break;
        case 125:
            setStart ( 537 , 445 ); break;
        case 126:
            setStart ( 260 , 508 ); break;

    default:
        break;
    }
}
void MainWindow::setNextPos (int k)
{
    switch (k) {
        case 1:
            setEnd ( 233 ,	150 ); break;
        case 2:
            setEnd ( 227 ,	163 ); break;
        case 3:
            setEnd ( 233 , 178 ); break;
        case 4:
            setEnd ( 204 , 185 ); break;
        case 5:
            setEnd ( 156 , 203 ); break;
        case 6:
            setEnd ( 255 , 207 );break;
        case 7:
            setEnd ( 207 , 267 ); break;
        case 8:
            setEnd ( 198 , 254 ); break;
        case 9:
            setEnd ( 231 , 277 ); break;
        case 10:
            setEnd ( 220 , 292 ); break;

        case 11:
            setEnd ( 175 , 306 ); break;
        case 12:
            setEnd ( 235 , 301 ); break;
        case 13:
            setEnd ( 221 , 326 ); break;
        case 14:
            setEnd ( 249 , 317 ); break;
        case 15:
            setEnd ( 179 , 353 ); break;
        case 16:
            setEnd ( 226 , 351 ); break;
        case 17:
            setEnd ( 250 , 352 ); break;
        case 18:
            setEnd ( 281 , 339 ); break;
        case 19:
            setEnd ( 287 , 360 ); break;
        case 20:
            setEnd ( 300 , 349 ); break;


        case 21:
            setEnd ( 316 , 369 ); break;
        case 22:
            setEnd ( 181 , 377 ); break;
        case 23:
            setEnd ( 227 , 372 ); break;
        case 24:
            setEnd ( 242 , 373 ); break;
        case 25:
            setEnd ( 288 , 380 ); break;
        case 26:
            setEnd ( 310 , 378 ); break;
        case 27:
            setEnd ( 252 , 404 ); break;
        case 28:
            setEnd ( 282 , 396 ); break;
        case 29:
            setEnd ( 306 , 398 ); break;
        case 30:
            setEnd ( 156 , 427 ); break;


        case 31:
            setEnd ( 184 , 428 ); break;
        case 32:
            setEnd ( 235 , 434 ); break;
        case 33:
            setEnd ( 252 , 420 ); break;
        case 34:
            setEnd ( 274 , 420 ); break;
        case 35:
            setEnd ( 305 , 419 ); break;
        case 36:
            setEnd ( 147 , 458 ); break;
        case 37:
            setEnd ( 187 , 454 ); break;
        case 38:
            setEnd ( 307 , 447 ); break;
        case 39:
            setEnd ( 150 , 480 ); break;
        case 40:
            setEnd ( 93 , 502 ); break;


        case 41:
            setEnd ( 200 , 482 ); break;
        case 42:
            setEnd ( 215 , 505 ); break;
        case 43:
            setEnd ( 311 , 494 ); break;
        case 44:
            setEnd ( 213 , 535 ); break;
        case 45:
            setEnd ( 230 , 530 ); break;
        case 46:
            setEnd ( 319 , 514 ); break;
        case 47:
            setEnd ( 336 , 527 ); break;
        case 48:
            setEnd ( 374 , 563 ); break;
        case 49:
            setEnd ( 430 , 586 ); break;
        case 50:
            setEnd ( 479 , 585 ); break;
        case 51:
            setEnd ( 220 , 617 ); break;
        case 52:
            setEnd ( 222 , 649 ); break;
        case 53:
            setEnd ( 239 , 652 ); break;
        case 54:
            setEnd ( 241 , 722 ); break;
        case 55:
            setEnd ( 228 , 746 ); break;
        case 56:
            setEnd ( 293 , 642 );break;
        case 57:
            setEnd ( 380 , 643 ); break;
        case 58:
            setEnd ( 457 , 682 ); break;
        case 59:
            setEnd ( 482 , 655 ); break;
        case 60:
            setEnd ( 584 , 675 ); break;

        case 61:
            setEnd ( 596 , 690 ); break;
        case 62:
            setEnd ( 636 , 645 ); break;
        case 63:
            setEnd ( 666 , 621 ); break;
        case 64:
            setEnd ( 631 , 610 ); break;
        case 65:
            setEnd ( 540 , 602 ); break;
        case 66:
            setEnd ( 599 , 601 ); break;
        case 67:
            setEnd ( 623 , 588 ); break;
        case 68:
            setEnd ( 653 , 560 ); break;
        case 69:
            setEnd ( 712 , 547 ); break;
        case 70:
            setEnd ( 523 , 576 ); break;


        case 71:
            setEnd ( 602 , 559 ); break;
        case 72:
            setEnd ( 636 , 531 ); break;
        case 73:
            setEnd ( 506 , 549 ); break;
        case 74:
            setEnd ( 585 , 530 ); break;
        case 75:
            setEnd ( 617 , 504 ); break;
        case 76:
            setEnd ( 666 , 486 ); break;
        case 77:
            setEnd ( 488 , 523 ); break;
        case 78:
            setEnd ( 570 , 503 ); break;
        case 79:
            setEnd ( 596 , 475 ); break;
        case 80:
            setEnd ( 598 , 455 ); break;


        case 81:
            setEnd ( 434 , 465 ); break;
        case 82:
            setEnd ( 480 , 464 ); break;
        case 83:
            setEnd ( 434 , 440 ); break;
        case 84:
            setEnd ( 476 , 435 ); break;
        case 85:
            setEnd ( 555 , 416 ); break;
        case 86:
            setEnd ( 575 , 421 ); break;
        case 87:
            setEnd ( 398 , 405 ); break;
        case 88:
            setEnd ( 454 , 409 ); break;
        case 89:
            setEnd ( 536 , 387 ); break;
        case 90:
            setEnd ( 431 , 385 ); break;


        case 91:
            setEnd ( 520 , 362 ); break;
        case 92:
            setEnd ( 570 , 345 ); break;
        case 93:
            setEnd ( 531 , 334 ); break;
        case 94:
            setEnd ( 495 , 298 ); break;
        case 95:
            setEnd ( 550 , 300 ); break;
        case 96:
            setEnd ( 587 , 300 ); break;
        case 97:
            setEnd ( 657 , 293 ); break;
        case 98:
            setEnd ( 689 , 284 ); break;
        case 99:
            setEnd ( 483 , 258 ); break;
        case 100:
            setEnd ( 514 , 261 ); break;
     case 101:
            setEnd ( 565 , 248 ); break;
        case 102:
            setEnd ( 476 , 221 ); break;
        case 103:
            setEnd ( 417 , 197 ); break;
        case 104:
            setEnd ( 437 , 186 ); break;
        case 105:
            setEnd ( 477 , 187 ); break;
        case 106:
            setEnd ( 509 , 190 );break;
        case 107:
            setEnd ( 509 , 157 ); break;
        case 108:
            setEnd ( 357 , 168 ); break;
        case 109:
            setEnd ( 322 , 198 ); break;
        case 110:
            setEnd ( 368 , 213 ); break;

        case 111:
            setEnd ( 332 , 233 ); break;
        case 112:
            setEnd ( 315 , 251 ); break;
        case 113:
            setEnd ( 382 , 244 ); break;
        case 114:
            setEnd ( 342 , 273 ); break;
        case 115:
            setEnd ( 371 , 263 ); break;
        case 116:
            setEnd ( 396 , 263 ); break;
        case 117:
            setEnd ( 398 , 286 ); break;
        case 118:
            setEnd ( 410 , 283 ); break;
        case 119:
            setEnd ( 364 , 303 ); break;
        case 120:
            setEnd ( 337 , 345 ); break;


        case 121:
            setEnd ( 375 , 320 ); break;
        case 122:
            setEnd ( 426 , 306 ); break;
        case 123:
            setEnd ( 501 , 388 ); break;
        case 124:
            setEnd ( 517 , 416 ); break;
        case 125:
            setEnd ( 537 , 445 ); break;
        case 126:
            setEnd ( 260 , 508 ); break;

    default:
        break;
    }
}
void MainWindow::setEndStation (int w)
{
    switch (w) {
        case 1:
            setEnd ( 233 ,	150 ); break;
        case 2:
            setEnd ( 227 ,	163 ); break;
        case 3:
            setEnd ( 233 , 178 ); break;
        case 4:
            setEnd ( 204 , 185 ); break;
        case 5:
            setEnd ( 156 , 203 ); break;
        case 6:
            setEnd ( 255 , 207 );break;
        case 7:
            setEnd ( 207 , 267 ); break;
        case 8:
            setEnd ( 198 , 254 ); break;
        case 9:
            setEnd ( 231 , 277 ); break;
        case 10:
            setEnd ( 220 , 292 ); break;

        case 11:
            setEnd ( 175 , 306 ); break;
        case 12:
            setEnd ( 235 , 301 ); break;
        case 13:
            setEnd ( 221 , 326 ); break;
        case 14:
            setEnd ( 249 , 317 ); break;
        case 15:
            setEnd ( 179 , 353 ); break;
        case 16:
            setEnd ( 226 , 351 ); break;
        case 17:
            setEnd ( 250 , 352 ); break;
        case 18:
            setEnd ( 281 , 339 ); break;
        case 19:
            setEnd ( 287 , 360 ); break;
        case 20:
            setEnd ( 300 , 349 ); break;


        case 21:
            setEnd ( 316 , 369 ); break;
        case 22:
            setEnd ( 181 , 377 ); break;
        case 23:
            setEnd ( 227 , 372 ); break;
        case 24:
            setEnd ( 242 , 373 ); break;
        case 25:
            setEnd ( 288 , 380 ); break;
        case 26:
            setEnd ( 310 , 378 ); break;
        case 27:
            setEnd ( 252 , 404 ); break;
        case 28:
            setEnd ( 282 , 396 ); break;
        case 29:
            setEnd ( 306 , 398 ); break;
        case 30:
            setEnd ( 156 , 427 ); break;


        case 31:
            setEnd ( 184 , 428 ); break;
        case 32:
            setEnd ( 235 , 434 ); break;
        case 33:
            setEnd ( 252 , 420 ); break;
        case 34:
            setEnd ( 274 , 420 ); break;
        case 35:
            setEnd ( 305 , 419 ); break;
        case 36:
            setEnd ( 147 , 458 ); break;
        case 37:
            setEnd ( 187 , 454 ); break;
        case 38:
            setEnd ( 307 , 447 ); break;
        case 39:
            setEnd ( 150 , 480 ); break;
        case 40:
            setEnd ( 93 , 502 ); break;


        case 41:
            setEnd ( 200 , 482 ); break;
        case 42:
            setEnd ( 215 , 505 ); break;
        case 43:
            setEnd ( 311 , 494 ); break;
        case 44:
            setEnd ( 213 , 535 ); break;
        case 45:
            setEnd ( 230 , 530 ); break;
        case 46:
            setEnd ( 319 , 514 ); break;
        case 47:
            setEnd ( 336 , 527 ); break;
        case 48:
            setEnd ( 374 , 563 ); break;
        case 49:
            setEnd ( 430 , 586 ); break;
        case 50:
            setEnd ( 479 , 585 ); break;
        case 51:
            setEnd ( 220 , 617 ); break;
        case 52:
            setEnd ( 222 , 649 ); break;
        case 53:
            setEnd ( 239 , 652 ); break;
        case 54:
            setEnd ( 241 , 722 ); break;
        case 55:
            setEnd ( 228 , 746 ); break;
        case 56:
            setEnd ( 293 , 642 );break;
        case 57:
            setEnd ( 380 , 643 ); break;
        case 58:
            setEnd ( 457 , 682 ); break;
        case 59:
            setEnd ( 482 , 655 ); break;
        case 60:
            setEnd ( 584 , 675 ); break;

        case 61:
            setEnd ( 596 , 690 ); break;
        case 62:
            setEnd ( 636 , 645 ); break;
        case 63:
            setEnd ( 666 , 621 ); break;
        case 64:
            setEnd ( 631 , 610 ); break;
        case 65:
            setEnd ( 540 , 602 ); break;
        case 66:
            setEnd ( 599 , 601 ); break;
        case 67:
            setEnd ( 623 , 588 ); break;
        case 68:
            setEnd ( 653 , 560 ); break;
        case 69:
            setEnd ( 712 , 547 ); break;
        case 70:
            setEnd ( 523 , 576 ); break;


        case 71:
            setEnd ( 602 , 559 ); break;
        case 72:
            setEnd ( 636 , 531 ); break;
        case 73:
            setEnd ( 506 , 549 ); break;
        case 74:
            setEnd ( 585 , 530 ); break;
        case 75:
            setEnd ( 617 , 504 ); break;
        case 76:
            setEnd ( 666 , 486 ); break;
        case 77:
            setEnd ( 488 , 523 ); break;
        case 78:
            setEnd ( 570 , 503 ); break;
        case 79:
            setEnd ( 596 , 475 ); break;
        case 80:
            setEnd ( 598 , 455 ); break;


        case 81:
            setEnd ( 434 , 465 ); break;
        case 82:
            setEnd ( 480 , 464 ); break;
        case 83:
            setEnd ( 434 , 440 ); break;
        case 84:
            setEnd ( 476 , 435 ); break;
        case 85:
            setEnd ( 555 , 416 ); break;
        case 86:
            setEnd ( 575 , 421 ); break;
        case 87:
            setEnd ( 398 , 405 ); break;
        case 88:
            setEnd ( 454 , 409 ); break;
        case 89:
            setEnd ( 536 , 387 ); break;
        case 90:
            setEnd ( 431 , 385 ); break;


        case 91:
            setEnd ( 520 , 362 ); break;
        case 92:
            setEnd ( 570 , 345 ); break;
        case 93:
            setEnd ( 531 , 334 ); break;
        case 94:
            setEnd ( 495 , 298 ); break;
        case 95:
            setEnd ( 550 , 300 ); break;
        case 96:
            setEnd ( 587 , 300 ); break;
        case 97:
            setEnd ( 657 , 293 ); break;
        case 98:
            setEnd ( 689 , 284 ); break;
        case 99:
            setEnd ( 483 , 258 ); break;
        case 100:
            setEnd ( 514 , 261 ); break;
     case 101:
            setEnd ( 565 , 248 ); break;
        case 102:
            setEnd ( 476 , 221 ); break;
        case 103:
            setEnd ( 417 , 197 ); break;
        case 104:
            setEnd ( 437 , 186 ); break;
        case 105:
            setEnd ( 477 , 187 ); break;
        case 106:
            setEnd ( 509 , 190 );break;
        case 107:
            setEnd ( 509 , 157 ); break;
        case 108:
            setEnd ( 357 , 168 ); break;
        case 109:
            setEnd ( 322 , 198 ); break;
        case 110:
            setEnd ( 368 , 213 ); break;

        case 111:
            setEnd ( 332 , 233 ); break;
        case 112:
            setEnd ( 315 , 251 ); break;
        case 113:
            setEnd ( 382 , 244 ); break;
        case 114:
            setEnd ( 342 , 273 ); break;
        case 115:
            setEnd ( 371 , 263 ); break;
        case 116:
            setEnd ( 396 , 263 ); break;
        case 117:
            setEnd ( 398 , 286 ); break;
        case 118:
            setEnd ( 410 , 283 ); break;
        case 119:
            setEnd ( 364 , 303 ); break;
        case 120:
            setEnd ( 337 , 345 ); break;


        case 121:
            setEnd ( 375 , 320 ); break;
        case 122:
            setEnd ( 426 , 306 ); break;
        case 123:
            setEnd ( 501 , 388 ); break;
        case 124:
            setEnd ( 517 , 416 ); break;
        case 125:
            setEnd ( 537 , 445 ); break;
        case 126:
            setEnd ( 260 , 508 ); break;

    default:
        break;

    }
}


/* 构建图 */
void MainWindow:: CreateMGraph(MGraph *G)
{
    int i,j;
    G->numPlots = 127;
    //定义每个点的名称
    G->a[1]="上大北门";
    G->a[2]="road";
    G->a[3]="road";
    G->a[4]="校医院";
    G->a[5]="road";
    G->a[6]="road";
    G->a[7]="road";
    G->a[8]="玄陵网球场";
    G->a[9]="road";
    G->a[10]="road";
    G->a[11]="road";
    G->a[12]="road";
    G->a[13]="山明食堂";
    G->a[14]="road";
    G->a[15]="road";
    G->a[16]="road";
    G->a[17]="road";
    G->a[18]="road";
    G->a[19]="road";
    G->a[20]="road";
    G->a[21]="road";
    G->a[22]="road";
    G->a[23]="road";
    G->a[24]="road";
    G->a[25]="road";
    G->a[26]="road";
    G->a[27]="road";
    G->a[28]="road";
    G->a[29]="road";
    G->a[30]="road";
    G->a[31]="上大浴室";
    G->a[32]="益新食堂";
    G->a[33]="road";
    G->a[34]="road";
    G->a[35]="road";
    G->a[36]="road";
    G->a[37]="西门教超";
    G->a[38]="road";
    G->a[39]="上大西门";
    G->a[40]="新世纪北门";
    G->a[41]="road";
    G->a[42]="road";
    G->a[43]="road";
    G->a[44]="足球场";
    G->a[45]="road";
    G->a[46]="road";
    G->a[47]="road";
    G->a[48]="泮池";
    G->a[49]="road";
    G->a[50]="road";
    G->a[51]="篮球场（南）";
    G->a[52]="高尔夫球场";
    G->a[53]="后勤基建大楼";
    G->a[54]="上大西南门";
    G->a[55]="南区北门";
    G->a[56]="road";
    G->a[57]="road";
    G->a[58]="road";
    G->a[59]="美术学院";
    G->a[60]="road";
    G->a[61]="上大南门";
    G->a[62]="溯园";
    G->a[63]="road";
    G->a[64]="行政楼";
    G->a[65]="教学楼A";
    G->a[66]="road";
    G->a[67]="road";
    G->a[68]="教学楼AJ";
    G->a[69]="东区西门（南）";
    G->a[70]="教学楼B";
    G->a[71]="road";
    G->a[72]="教学楼BJ";
    G->a[73]="教学楼C";
    G->a[74]="road";
    G->a[75]="教学楼CJ";
    G->a[76]="road";
    G->a[77]="教学楼D";
    G->a[78]="road";
    G->a[79]="教学楼DJ";
    G->a[80]="教学楼H";
    G->a[81]="音乐广场";
    G->a[82]="教学楼J";
    G->a[83]="文化广场";
    G->a[84]="教学楼E";
    G->a[85]="教学楼EJ";
    G->a[86]="水秀食堂";
    G->a[87]="图书馆";
    G->a[88]="教学楼F";
    G->a[89]="教学楼FJ";
    G->a[90]="教学楼G";
    G->a[91]="教学楼GJ";
    G->a[92]="road";
    G->a[93]="伟长楼";
    G->a[94]="音乐学院";
    G->a[95]="road";
    G->a[96]="road";
    G->a[97]="上大东门";
    G->a[98]="东区西门（北）";
    G->a[99]="road";
    G->a[100]="road";
    G->a[101]="体育馆";
    G->a[102]="游泳馆";
    G->a[103]="体育办公楼";
    G->a[104]="road";
    G->a[105]="road";
    G->a[106]="road";
    G->a[107]="road";
    G->a[108]="乐乎楼";
    G->a[109]="road";
    G->a[110]="风雨操场";
    G->a[111]="尔美食堂";
    G->a[112]="road";
    G->a[113]="road";
    G->a[114]="road";
    G->a[115]="road";
    G->a[116]="road";
    G->a[117]="road";
    G->a[118]="road";
    G->a[119]="road";
    G->a[120]="road";
    G->a[121]="road";
    G->a[122]="road";
    G->a[123]="road";
    G->a[124]="road";
    G->a[125]="road";
    G->a[126]="road";


    for (i = 1; i < G->numPlots; i++)/* 初始化图 */
    {
        for ( j = 1; j < G->numPlots; j++)
        {
            if (i == j)
                G->b[i][j] = 0;
            else
                G->b[i][j] = G->b[j][i] = INFINITY;
        }
    }
    //定义权重的值
    G->b[1][2]=14;		G->b[2][3]=16;	       G->b[3][4]=30;		         G->b[3][6]=36;         G->b[3][108]=124;	G->b[4][5]=51;		G->b[6][7]=99;		G->b[6][109]=356;	G->b[7][8]=16;	G->b[7][9]=26;	G->b[7][10]=28;	G->b[7][11]=50;	G->b[9][10]=19;		G->b[9][12]=24;		G->b[10][12]=17;	G->b[11][15]=47;	G->b[12][13]=29;	G->b[12][14]=21;	G->b[13][17]=39;	G->b[14][17]=35;	G->b[15][16]=47;	G->b[15][22]=24;	G->b[16][17]=24;	G->b[17][18]=34;	G->b[17][19]=38;	G->b[17][20]=22;	G->b[18][20]=21;	G->b[19][20]=17;	G->b[20][21]=26;	G->b[21][26]=11;		G->b[21][120]=32;	G->b[22][23]=46;	G->b[22][31]=51;	G->b[23][24]=15;	G->b[24][25]=47;	G->b[24][27]=33;
        G->b[25][26]=22;
        G->b[26][29]=20;	G->b[27][28]=31;	G->b[27][33]=16;	G->b[28][29]=24;		G->b[29][35]=21;		G->b[30][31]=28;
        G->b[31][37]=26;	G->b[32][33]=22;	G->b[32][37]=52;	G->b[33][34]=22;		G->b[34][35]=31;	G->b[35][38]=28;		G->b[36][37]=40;	G->b[36][39]=22;		G->b[37][41]=31;		G->b[38][43]=47;	G->b[38][83]=127;	G->b[38][87]=100;		G->b[39][40]=61;		G->b[41][42]=27;		G->b[42][44]=30;	G->b[42][45]=29;			G->b[42][126]=45;
        G->b[43][46]=22;		G->b[43][126]=53;
            G->b[44][45]=18;	G->b[44][51]=82;	G->b[45][56]=129;	G->b[45][126]=37;	G->b[46][47]=21;	G->b[46][126]=59;		G->b[47][48]=52;
            G->b[48][49]=61;			G->b[48][81]=115;
        G->b[49][50]=49;	G->b[49][58]=100;
        G->b[50][59]=70;	G->b[50][70]=45;		G->b[51][52]=32;		G->b[52][53]=17;	G->b[53][54]=70;	G->b[53][56]=55;
        G->b[54][55]=27;
            G->b[56][57]=87;		G->b[57][58]=86;	G->b[58][59]=37;	G->b[58][60]=127;	G->b[60][61]=19;	G->b[62][63]=38;	G->b[62][64]=35;	G->b[63][68]=62;	G->b[64][66]=33;		G->b[65][66]=59;	G->b[65][70]=31;		G->b[66][67]=27;		G->b[67][68]=41;		G->b[68][69]=60;	G->b[68][72]=33;
            G->b[69][97]=260;		G->b[70][71]=81;		G->b[70][73]=32;	G->b[71][72]=44;		G->b[71][74]=34;
        G->b[72][75]=33;
            G->b[73][74]=81;		G->b[73][77]=31;
        G->b[74][75]=41;	G->b[74][78]=31;
            G->b[75][76]=52;		G->b[75][79]=36;		G->b[76][97]=202;		G->b[77][78]=84;	G->b[77][81]=89;		G->b[78][79]=38;		G->b[79][80]=20;		G->b[80][82]=118;	G->b[80][86]=41;		G->b[81][82]=46;	G->b[81][83]=25;		G->b[82][84]=29;		G->b[83][84]=42;		G->b[83][87]=50;	G->b[83][88]=37;		G->b[83][90]=55;

            G->b[84][88]=34;	G->b[84][125]=61;		G->b[85][86]=21;		G->b[85][89]=35;		G->b[88][90]=33;		G->b[88][124]=63;	G->b[89][91]=30;	G->b[89][92]=54;
            G->b[90][121]=86;	G->b[90][123]=70;	G->b[91][93]=30;	G->b[91][94]=69;	G->b[92][96]=48;		G->b[93][95]=39;		G->b[94][95]=55;	G->b[94][99]=42;		G->b[94][122]=69;	G->b[95][96]=37;	G->b[95][101]=54;	G->b[96][97]=70;	G->b[96][101]=56;		G->b[97][98]=33;		G->b[99][100]=31;		G->b[99][102]=38;	G->b[100][101]=53;		G->b[100][106]=71;	G->b[102][105]=52;		G->b[103][104]=23;		G->b[103][110]=52;	G->b[104][105]=40;		G->b[105][106]=32;		G->b[106][107]=33;	G->b[107][108]=152;		G->b[108][110]=463;	G->b[109][110]=48;	G->b[109][111]=36;		G->b[110][113]=34;	G->b[111][112]=25;	G->b[112][113]=67;	G->b[112][114]=35;			G->b[113][116]=24;	G->b[114][115]=31;		G->b[114][117]=57;		G->b[114][119]=37;	G->b[115][116]=25;		G->b[116][118]=24;		G->b[117][118]=12;		G->b[118][122]=28;		G->b[119][121]=20;	G->b[120][121]=45;	G->b[121][122]=53;
    for(i = 1; i < G->numPlots; i++)    //只保存右上矩阵
    {
        for(j = i; j < G->numPlots; j++)
        {
            G->b[j][i] = G->b[i][j];
        }
    }

}



MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{   b[1]=1;
    b[2]=4;
    b[3]=8;
    b[4]=13;
    b[5]=31;
    b[6]=32;
    b[7]=37;
    b[8]=39;
    b[9]=40;
    b[10]=44;
    b[11]=48;
    b[12]=51;
    b[13]=52;
    b[14]=53;
    b[15]=54;
    b[16]=55;
    b[17]=59;
    b[18]=61;
    b[19]=62;
    b[20]=64;
    b[21]=65;
    b[22]=68;
    b[24]=69;
    b[25]=70;
    b[26]=72;
    b[27]=73;
    b[28]=75;
    b[29]=77;
    b[30]=79;
    b[31]=80;
    b[32]=81;
    b[33]=82;
    b[34]=83;
    b[35]=84;
    b[36]=85;
    b[37]=86;
    b[38]=87;
    b[39]=88;
    b[40]=89;
    b[41]=90;
    b[42]=91;
    b[43]=93;
    b[44]=94;
    b[45]=97;
    b[46]=98;
    b[47]=101;
    b[48]=102;
    b[49]=103;
    b[50]=108;
    b[51]=110;
    b[52]=111;

if(ui->comboBox->currentIndex()==0||ui->comboBox_2->currentIndex()==0)
{


    //创建 QMessageBox 类对象
    QMessageBox MyBox(QMessageBox::Question,"warring！","请正确选择起始点和目的地！",QMessageBox::Yes);
    //使 MyBox 对话框显示
    MyBox.exec();



}
else{
    qsd=b[ui->comboBox->currentIndex()];
    zzd=b[ui->comboBox_2->currentIndex()];

     qy=2;
    update();
}
}
