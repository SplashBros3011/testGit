#include "motion_planner.h"
#include <math.h>

#define MP_EPS_POS (1.0)   // 到位位置阈值(脉冲)
#define MP_EPS_VEL (1.0)   // 到位速度阈值(脉冲/s)

void motion_plan_init(motion_plan_t *p)
{
    p->tra_pos = p->tra_vel = p->tra_acc = p->tra_dec = p->tra_jerk = 0.0;
    p->cur_pos = p->cur_vel = p->cur_acc = 0.0;
    p->busy = false;
}

void motion_plan_set_target(motion_plan_t *p, double target,
                            double vel, double acc, double dec, double jerk)
{
    p->tra_pos  = target;
    p->tra_vel  = vel;
    p->tra_acc  = acc;
    p->tra_dec  = dec;
    p->tra_jerk = (jerk > 0.0) ? jerk : 1e9;   // jerk<=0 退化为梯形曲线
    p->busy = true;
}

// 估算从当前速度 vel/加速度 acc 减速到停所需距离(工程近似，偏保守，保证不冲过目标)
static double braking_distance(double vel, double acc, double dec, double jerk)
{
    double v = fabs(vel);
    double d = (v * v) / (2.0 * dec);            // 匀减速基础项 v^2/2a
    d += v * dec / (2.0 * jerk);                 // jerk 平滑阶段引入的额外距离
    if (acc * vel > 0.0)                         // 当前正在同向加速，需额外补偿
        d += v * fabs(acc) / (2.0 * jerk);
    return d;
}

void motion_plan_tick(motion_plan_t *p, double dt)
{
    if (!p->busy || dt <= 0.0) return;

    double dist = p->tra_pos - p->cur_pos;                       // 剩余距离(带符号)
    double dir  = (dist > 0.0) ? 1.0 : (dist < 0.0 ? -1.0 : 0.0);

    // 到位判定
    if (dir == 0.0 && fabs(p->cur_vel) < MP_EPS_VEL) {
        p->cur_pos = p->tra_pos;
        p->cur_vel = p->cur_acc = 0.0;
        p->busy = false;
        return;
    }

    // 1) 决定本周期目标加速度(加速/匀速/减速三区)
    double a_cmd = 0.0;
    if (fabs(dist) <= braking_distance(p->cur_vel, p->cur_acc, p->tra_dec, p->tra_jerk)) {
        a_cmd = -dir * p->tra_dec;                    // 减速区
    } else {
        double v_target = dir * p->tra_vel;
        double dv = v_target - p->cur_vel;
        if (fabs(dv) < MP_EPS_VEL)
            a_cmd = 0.0;                              // 匀速区
        else
            a_cmd = (dv > 0.0 ? 1.0 : -1.0) * p->tra_acc;   // 加速区
    }

    // 2) 用 Jerk 平滑逼近目标加速度 -> 形成 S 型
    double da = a_cmd - p->cur_acc;
    double da_max = p->tra_jerk * dt;
    if (da > da_max)       da = da_max;
    else if (da < -da_max) da = -da_max;
    p->cur_acc += da;

    // 加速度范围钳制
    if (p->cur_acc > p->tra_acc) p->cur_acc = p->tra_acc;
    if (p->cur_acc < -p->tra_dec) p->cur_acc = -p->tra_dec;

    // 3) 积分速度 + 限速(且速度不允许反向越过 0)
    p->cur_vel += p->cur_acc * dt;
    if (dir > 0.0 && p->cur_vel < 0.0) p->cur_vel = 0.0;
    if (dir < 0.0 && p->cur_vel > 0.0) p->cur_vel = 0.0;
    if (p->cur_vel > p->tra_vel)  p->cur_vel = p->tra_vel;
    if (p->cur_vel < -p->tra_vel) p->cur_vel = -p->tra_vel;

    // 4) 积分位置
    p->cur_pos += p->cur_vel * dt;

    // 5) 越位保护(不得冲过目标)
    if (dir > 0.0 && p->cur_pos > p->tra_pos) { p->cur_pos = p->tra_pos; p->cur_vel = p->cur_acc = 0.0; }
    if (dir < 0.0 && p->cur_pos < p->tra_pos) { p->cur_pos = p->tra_pos; p->cur_vel = p->cur_acc = 0.0; }
}
