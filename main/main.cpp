#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/component.hpp"
#include "common/slave.hpp"
#include "master/master.hpp"

#define BUILD_MASTER 1

extern "C" void app_main(void)
{
#if BUILD_MASTER
    Master master;
    master.init();
    printf("Built Master component\n");
#else
    // Slave code here
#endif
}