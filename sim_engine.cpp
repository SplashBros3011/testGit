#include "sim_engine.h"

#define SIM_DT (0.001)   // 1ms，与控制器周期一致

void sim_init(sim_engine_t *e)
{
    motion_plan_init(&e->plan);
    e->mech.type         = MECH_ROTARY;
    e->mech.encoder_cpr  = 131072.0;
    e->mech.gear_ratio   = 1.0;
    e->mech.screw_pitch  = 0.0;
    e->mech.dir_sign     = 1;
    e->t = 0.0;
    e->steps = 0;
}

void sim_move_rel(sim_engine_t *e, double delta, double vel, double acc, double dec, double jerk)
{
    double k = mech_scale(&e->mech);
    motion_plan_set_target(&e->plan, e->plan.cur_pos + delta * k,
                           vel * k, acc * k, dec * k, jerk * k);
}

void sim_move_abs(sim_engine_t *e, double pos, double vel, double acc, double dec, double jerk)
{
    double k = mech_scale(&e->mech);
    motion_plan_set_target(&e->plan, pos * k,
                           vel * k, acc * k, dec * k, jerk * k);
}

void sim_stop(sim_engine_t *e)
{
    motion_plan_set_target(&e->plan, e->plan.cur_pos, 0, 0, 0, 0);
}

bool sim_tick(sim_engine_t *e)
{
    motion_plan_tick(&e->plan, SIM_DT);
    e->t += SIM_DT;
    e->steps++;
    return !motion_plan_done(&e->plan);
}

double sim_pos(sim_engine_t *e) { return mech_pulses_to_pos(&e->mech, e->plan.cur_pos); }
double sim_vel(sim_engine_t *e) { return mech_pulses_to_vel(&e->mech, e->plan.cur_vel); }
double sim_acc(sim_engine_t *e) { return e->plan.cur_acc / mech_scale(&e->mech); }
