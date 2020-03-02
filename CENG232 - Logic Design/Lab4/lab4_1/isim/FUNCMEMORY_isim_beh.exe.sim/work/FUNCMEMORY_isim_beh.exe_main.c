/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_07110452860414546257_3236520523_init();
    work_m_12539941213871135817_1584025541_init();
    work_m_00374325843224342414_1591742012_init();
    work_m_11491833963429943931_2073120511_init();


    xsi_register_tops("work_m_00374325843224342414_1591742012");
    xsi_register_tops("work_m_11491833963429943931_2073120511");


    return xsi_run_simulation(argc, argv);

}
