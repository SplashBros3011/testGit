#ifndef MOTION_PLANNER_H
#define MOTION_PLANNER_H

#include <stdbool.h>

/*
工作在脉冲域的 S 型速度规划器
*/
typedef struct {
    // 用户设定参数
    double tra_pos;   // 目标位置(脉冲)
    double tra_vel;   // 最大速度(脉冲/s)
    double tra_acc;   // 最大加速度(脉冲/s^2)
    double tra_dec;   // 最大减速度(脉冲/s^2)
    double tra_jerk;  // 最大加加速度(脉冲/s^3)，决定S型平滑度

    // 运行状态(每周期更新)
    double cur_pos;   // 当前规划位置(输出给伺服)
    double cur_vel;   // 当前规划速度
    double cur_acc;   // 当前规划加速度
    bool   busy;      // 是否运行中
} motion_plan_t;

/**
 * @brief 初始化S型速度规划器
 * @param p 规划器指针
 */
void motion_plan_init(motion_plan_t *p);

/**
 * @brief 下发新指令：正转/反转由 (target - 当前位置) 的符号自动决定
 * @param p 规划器指针
 * @param target 目标位置(脉冲)
 * @param vel 最大速度(脉冲/s)
 * @param acc 最大加速度(脉冲/s^2)
 * @param dec 最大减速度(脉冲/s^2)
 * @param jerk 最大加加速度(脉冲/s^3)，决定S型平滑度
 */
void motion_plan_set_target(motion_plan_t *p, double target,
                            double vel, double acc, double dec, double jerk);

/**
 * @brief 每周期调用，更新规划器状态
 * @param p 规划器指针
 * @param dt 时间间隔(秒)
 */
void motion_plan_tick(motion_plan_t *p, double dt);   // 每周期调用

/**
 * @brief 检查规划器是否完成
 * @param p 规划器指针
 * @return true 规划完成
 * @return false 规划未完成
 */
static inline bool motion_plan_done(const motion_plan_t *p) { return !p->busy; }


#endif // MOTION_PLANNER_H
