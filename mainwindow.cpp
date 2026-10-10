#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // mainwindow.cpp 构造函数
    sim_init(&m_sim);

    // ===== 创建S型曲线图: 位置/速度/加速度 三条线 =====
    auto chart = new QChart();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("S型速度规划曲线");

    m_sPos = new QLineSeries(); m_sPos->setName("位置");
    m_sVel = new QLineSeries(); m_sVel->setName("速度");
    m_sAcc = new QLineSeries(); m_sAcc->setName("加速度");
    m_sPos->setColor(Qt::blue); m_sVel->setColor(Qt::red); m_sAcc->setColor(Qt::green);
    chart->addSeries(m_sPos);
    chart->addSeries(m_sVel);
    chart->addSeries(m_sAcc);

    auto axisX = new QValueAxis;
    axisX->setTitleText("时间 (s)");
    axisX->setRange(0, 1);
    axisX->setTickCount(6);        // X轴: 6个刻度左右
    axisX->setLabelFormat("%.1f"); // 小数1位，如 0.5

    auto axisY = new QValueAxis;
    axisY->setTitleText("工程单位值");
    axisY->setTickCount(5);        // Y轴: 5个刻度左右
    axisY->setLabelFormat("%.0f"); // 整数显示，不显示小数
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // ★ 关键: 三条曲线必须绑定 axisX/axisY, 否则曲线会用到隐藏的默认轴
    m_sPos->attachAxis(axisX); m_sVel->attachAxis(axisX); m_sAcc->attachAxis(axisX);
    m_sPos->attachAxis(axisY); m_sVel->attachAxis(axisY); m_sAcc->attachAxis(axisY);

    // 放进界面: chartView 填满 plot 容器
    auto chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    auto lay = new QVBoxLayout(ui->plot);          // 给 plot 容器建布局
    lay->setContentsMargins(0, 0, 0, 0);
    lay->addWidget(chartView);

    m_timer = new QTimer(this);
    m_timer->setInterval(1);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onSimTick);
    m_clock.start();                       // 新增
    m_timer->start();
}

void MainWindow::onSimTick()
{
    // 按真实流逝时间步进仿真(补偿Windows定时器精度不足)
    double dtReal = m_clock.restart() / 1000.0;        // 距上拍的真实秒数
    if (dtReal > 0.1) dtReal = 0.1;                    // 防卡顿造成大跳步
    int steps = qRound(dtReal / 0.001);                // 应补的1ms步数
    for (int i = 0; i < steps; i++)
        sim_tick(&m_sim);

    m_t  .append(m_sim.t);
    m_pos.append(sim_pos(&m_sim));
    m_vel.append(sim_vel(&m_sim));
    m_acc.append(sim_acc(&m_sim));

    // 界面数值刷新(工程单位)
    ui->labelPos->setText(QString::number(sim_pos(&m_sim), 'f', 3));
    ui->labelVel_2->setText(QString::number(sim_vel(&m_sim), 'f', 3));

    // ===== 每20ms把数据喂给曲线并刷新 =====
    if (m_t.size() % 20 == 0) {
        m_sPos->clear(); m_sVel->clear(); m_sAcc->clear();

        double ymin = 0.0, ymax = 1.0;
        for (int i = 0; i < m_t.size(); i++) {
            m_sPos->append(m_t[i], m_pos[i]);
            m_sVel->append(m_t[i], m_vel[i]);
            m_sAcc->append(m_t[i], m_acc[i]);
            // 统计三条曲线的总范围
            ymin = qMin(ymin, qMin(m_pos[i], qMin(m_vel[i], m_acc[i])));
            ymax = qMax(ymax, qMax(m_pos[i], qMax(m_vel[i], m_acc[i])));
        }

        // X轴跟随时间
        auto axisX = qobject_cast<QValueAxis*>(
            m_sPos->chart()->axes(Qt::Horizontal).first());
        if (axisX)
            axisX->setRange(0, qMax(1.0, m_sim.t + 0.5));

        // ★ Y轴自适应数据范围(上下留10%边距)
        auto axisY = qobject_cast<QValueAxis*>(
            m_sPos->chart()->axes(Qt::Vertical).first());
        if (axisY) {
            double pad = (ymax - ymin) * 0.1;
            if (pad < 0.1) pad = 0.1;
            axisY->setRange(ymin - pad, ymax + pad);
        }
    }

    // 运动结束后自动停在原地，可继续下发新指令
}

// "+"按钮: 相对正转/前进
void MainWindow::on_btnPlus_clicked()
{
    double vel = ui->spinVel->value();      // 如 30
    double acc = ui->spinAcc->value();      // 如 60
    double dec = ui->spinDec->value();      // 如 60
    double jk  = ui->spinJerk->value();     // 如 300
    double step = ui->spinStep->value();   // 如 1
    sim_move_rel(&m_sim, +step, vel, acc, dec, jk);
}

// "-"按钮
void MainWindow::on_btnMinus_clicked()
{
    double vel = ui->spinVel->value(), acc = ui->spinAcc->value();
    double dec = ui->spinDec->value(), jk = ui->spinJerk->value();
    sim_move_rel(&m_sim, -ui->spinStep->value(), vel, acc, dec, jk);
}

// 绝对定位按钮
void MainWindow::on_btnAbs_clicked()
{
    sim_move_abs(&m_sim, ui->spinTarget->value(),
                 ui->spinVel->value(), ui->spinAcc->value(),
                 ui->spinDec->value(), ui->spinJerk->value());
}

// 停止
void MainWindow::on_btnStop_clicked() { sim_stop(&m_sim); }

// 清空曲线，便于下一轮测试
void MainWindow::on_btnClear_clicked()
{
    m_t.clear(); m_pos.clear(); m_vel.clear(); m_acc.clear();
    m_sim.t = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
