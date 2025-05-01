/*
    Adapter file of the icm20608
*/
#include "icm20608_adapter.h"
#include "icm20608.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
void ICM20608::bind_dev_file()
{
    /* bind the file */
    private_fd = ::open(_dev_file_path, O_RDONLY);
}

bool ICM20608::get_package_sync(ICM20608AppData& empty)
{
    if(private_fd == -1){
        bind_dev_file();
        if(private_fd == -1){
            return false;   // try again failed
        }
    }

    ICM20608Data icm_data;
    ssize_t ret = ::read(private_fd, &icm_data, sizeof(ICM20608Data));
    // std::cout  << ret << " " << sizeof(ICM20608Data);
    // if (ret != sizeof(ICM20608Data)) {
    //     /* error reading, but almostly couldn't be! */
    //     return false;
    // }
    (void)ret;
    /* raw data */
    empty.rol.x = (float)(icm_data.rol.x) / 16.4f;
    empty.rol.y = (float)(icm_data.rol.y) / 16.4f;
    empty.rol.z = (float)(icm_data.rol.z) / 16.4f;
    empty.g_acc.x = (float)(icm_data.g_acc.x) / 2048.0f;
    empty.g_acc.y = (float)(icm_data.g_acc.y) / 2048.0f;
    empty.g_acc.z = (float)(icm_data.g_acc.z) / 2048.0f;

    empty.temperature = ((float)(icm_data.temperature) - 25.0f) / 326.8f + 25.0f;
    return true;
}


