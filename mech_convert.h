#ifndef MECH_CONVERT_H
#define MECH_CONVERT_H

typedef enum {
    MECH_ROTARY = 0,   // 旋转轴：位置=度(deg)、速度=度/s
    MECH_LINEAR = 1,   // 直线轴：位置=毫米(mm)、速度=mm/s
} mech_type_t;

// 机械结构与单位换算配置
typedef struct {
    mech_type_t type;         // 轴类型
    double encoder_cpr;       // 电机编码器分辨率(脉冲/圈)，如 131072
    double gear_ratio;        // 传动比 = 电机转速/负载转速(减速机>1)
    double screw_pitch;       // 丝杠导程(mm/圈)，仅直线轴使用，旋转轴填0
    int    dir_sign;          // 安装方向：+1 机械正向=电机正向，-1 反向
} mech_cfg_t;

// 统一比例系数：每 1 工程单位对应脉冲数(含方向)
double mech_scale(const mech_cfg_t *c);

// 位置换算
double mech_pos_to_pulses(const mech_cfg_t *c, double pos_eng);
double mech_pulses_to_pos(const mech_cfg_t *c, double pulses);

// 速度换算
double mech_vel_to_pulses(const mech_cfg_t *c, double vel_eng);      // 度/s或mm/s -> 脉冲/s
double mech_pulses_to_vel(const mech_cfg_t *c, double pulses_per_s);

// 加速度/加加速度换算(共用一个系数，单位不同)
double mech_acc_to_pulses(const mech_cfg_t *c, double acc_eng);      // -> 脉冲/s^2
double mech_jerk_to_pulses(const mech_cfg_t *c, double jerk_eng);    // -> 脉冲/s^3

#endif // MECH_CONVERT_H
