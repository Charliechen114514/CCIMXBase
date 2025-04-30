#include "icm20608_adapter.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    ICM20608            icm20608;
    ICM20608AppData    pack;
    while (1) {
        icm20608.get_package_sync(pack);
        printf("act gx = %.2f°/S, act gy = %.2f°/S, act gz = %.2f°/S\r\n", pack.rol.x, pack.rol.y, pack.rol.z);
        printf("act ax = %.2fg, act ay = %.2fg, act az = %.2fg\r\n", pack.g_acc.x, pack.g_acc.y, pack.g_acc.z);
        printf("act temp = %.2f°C\r\n", pack.temperature);
        sleep(1);
    }
}

