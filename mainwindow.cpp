#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chart.h"
#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < 500; i++) {
        QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
        p.ry() += qrand() % 20;
        *series << p;
    }
    //Third part chart
    Chart *chart = new Chart();
    chart->addSeries(series);
    chart->setTitle("Zoom in/out example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();
    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView,0);
    series->append(501,3);

    //Org Chart
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 960, 560);
    QChart *lineChart = new QChart();
    lineChart->setTitle("Simple Line Chart");
    lineChart->legend()->setVisible(false);
    QLineSeries *lines = new QLineSeries();
    lines->append(5, 5);
    lines->append(10, 38);
    lines->append(35, 60);
    lines->append(50, 20);
    lines->append(80, 90);
    lines->append(100, 70);
    lineChart->addSeries(lines);
    lineChart->setGeometry(10, 4, 300, 260); // the method of QGraphicsWidget, move && resize
    lineChart->createDefaultAxes();
    lineChart->setBackgroundVisible(true);
    lineChart->setBackgroundPen(QPen(Qt::lightGray)); // the frame
    lineChart->setBackgroundBrush(QBrush(QColor(240, 240, 240)));
    scene->addItem(lineChart);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}


