#include "mech_convert.h"

// 负载转 1 圈所需的电机脉冲数 = 编码器分辨率 × 传动比
static double pulses_per_load_rev(const mech_cfg_t *c)
{
    return c->encoder_cpr * c->gear_ratio;
}

double mech_scale(const mech_cfg_t *c)
{
    double k = pulses_per_load_rev(c);
    if (c->type == MECH_ROTARY)
        k /= 360.0;              // 旋转轴：每 1 度
    else
        k /= c->screw_pitch;     // 直线轴：每 1 mm
    return k * c->dir_sign;
}

double mech_pos_to_pulses(const mech_cfg_t *c, double pos_eng) { return pos_eng * mech_scale(c); }
double mech_pulses_to_pos(const mech_cfg_t *c, double pulses)   { return pulses / mech_scale(c); }

double mech_vel_to_pulses(const mech_cfg_t *c, double vel_eng) { return vel_eng * mech_scale(c); }
double mech_pulses_to_vel(const mech_cfg_t *c, double pps)     { return pps / mech_scale(c); }

double mech_acc_to_pulses(const mech_cfg_t *c, double acc_eng) { return acc_eng * mech_scale(c); }
double mech_jerk_to_pulses(const mech_cfg_t *c, double jerk_eng) { return jerk_eng * mech_scale(c); }
