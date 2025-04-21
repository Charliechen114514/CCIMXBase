#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "icm20608.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("usage with dev file!\n");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("failed to open the dev file: %d", errno);
        return -1;
    }
    ICM20608Data icm_data;
    while (1)
    {
        int result = read(fd, &icm_data, sizeof(ICM20608Data));
        if (result)
        {
            printf("error occurs!\n");
        }
        else
        {
            float gyro_x_act = (float)(icm_data.rol.x) / 16.4f;
            float gyro_y_act = (float)(icm_data.rol.y) / 16.4f;
            float gyro_z_act = (float)(icm_data.rol.z) / 16.4f;

            float accel_x_act = (float)(icm_data.g_acc.x) / 2048.0f;
            float accel_y_act = (float)(icm_data.g_acc.y) / 2048.0f;
            float accel_z_act = (float)(icm_data.g_acc.z) / 2048.0f;

            float temp_act = ((float)(icm_data.temperature) - 25.0f) / 326.8f + 25.0f;
            printf("act gx = %.2f°/S, act gy = %.2f°/S, act gz = %.2f°/S\r\n", gyro_x_act, gyro_y_act, gyro_z_act);
            printf("act ax = %.2fg, act ay = %.2fg, act az = %.2fg\r\n", accel_x_act, accel_y_act, accel_z_act);
            printf("act temp = %.2f°C\r\n", temp_act);
        }
        sleep(1);
    }

    close(fd);
    return 0;
}
