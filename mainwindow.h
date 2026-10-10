#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QElapsedTimer>
#include "sim_engine.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSimTick();
    void on_btnPlus_clicked();
    void on_btnMinus_clicked();
    void on_btnAbs_clicked();
    void on_btnStop_clicked();
    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    sim_engine_t m_sim;
    QTimer *m_timer = nullptr;
    QElapsedTimer m_clock;   // 真实时间基准
    QVector<double> m_t, m_pos, m_vel, m_acc;
    QLineSeries *m_sPos = nullptr;   // 新增: 三条曲线
    QLineSeries *m_sVel = nullptr;
    QLineSeries *m_sAcc = nullptr;
};
#endif // MAINWINDOW_H
