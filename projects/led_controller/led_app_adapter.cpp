#include "led_app_adapter.h"
#include "led.h"
#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define ISSUE_BUFFER_LEN        (40)
namespace cppfs = std::filesystem;

LEDHandle::LEDHandle(const std::string& dev_file_name)
{
    this->dev_file_name = dev_prefix + dev_file_name;
    this->led_internal_handle = -1;
}

bool LEDHandle::open(void)
{
    // in linux, we have to do so, cause read write dev file
    // need bytes level control
    this->led_internal_handle = ::open(this->dev_file_name.c_str(), O_RDWR);
    return this->led_internal_handle < 0;
}

LEDHandle::status LEDHandle::get_status(void)
{   
    if(this->led_internal_handle < 0) return status::LED_UNAVAILABLE;
    char issue_buffer[ISSUE_BUFFER_LEN];
    memset(issue_buffer, 0, ISSUE_BUFFER_LEN);
    int result = ::read(this->led_internal_handle, issue_buffer , ISSUE_BUFFER_LEN);
    
    if(result < 0){
        return status::LED_UNAVAILABLE;
    }
    
    std::string st{issue_buffer};
    if(K_LED_STATUS_CLOSED == st){
        return status::LED_OFF;
    }else if(K_LED_STATUS_OPEN == st){
        return status::LED_ON;
    }else{
        return status::LED_UNKNOWN;
    }
}

bool LEDHandle::set_status(const LEDHandle::status st)
{
    const char* cmd = nullptr;
    switch(st)
    {
        case status::LED_ON:
            cmd = K_LED_OPEN_CMD;
        break;
        default:
            cmd = K_LED_CLOSE_CMD;
        break;
    }
    int result = ::write(this->led_internal_handle, cmd, strlen(cmd));
    return result < 0;
}

bool LEDHandle::available(void)
{
    return cppfs::exists({ this->dev_file_name }) && led_internal_handle >= 0;
}
