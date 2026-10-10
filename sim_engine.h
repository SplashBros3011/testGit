#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include "motion_planner.h"
#include "mech_convert.h"

typedef struct {
    motion_plan_t plan;   // S型规划器(脉冲域)
    mech_cfg_t    mech;  // 机械配置
    double t;            // 仿真时间(s)
    int    steps;        // 已步进周期数
} sim_engine_t;

void sim_init(sim_engine_t *e);
// 工程单位下发相对/绝对指令(内部换算脉冲)
void sim_move_rel(sim_engine_t *e, double delta, double vel, double acc, double dec, double jerk);
void sim_move_abs(sim_engine_t *e, double pos,   double vel, double acc, double dec, double jerk);
void sim_stop(sim_engine_t *e);
// 步进一个周期(dt=1ms)，返回是否在运动中
bool sim_tick(sim_engine_t *e);
// 读当前状态(工程单位)
double sim_pos(sim_engine_t *e);   // deg 或 mm
double sim_vel(sim_engine_t *e);   // deg/s 或 mm/s
double sim_acc(sim_engine_t *e);   // deg/s^2 或 mm/s^2


#endif // SIM_ENGINE_H
