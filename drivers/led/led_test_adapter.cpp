#include "led_app_adapter.h"
#include <iostream>
#include <thread>
#include <chrono>
int main(int argc, char* argv[])
{
    LEDHandle handle("charlies_led");

    handle.open();

    LEDHandle::status status = handle.get_status();
    switch(status)
    {
        case LEDHandle::status::LED_ON:
            std::cout << "LED is on!" << std::endl;
        break;
        case LEDHandle::status::LED_OFF:
            std::cout << "LED is off!" << std::endl;
        break;
        case LEDHandle::status::LED_UNKNOWN:
        std::cout << "LED is unknown!" << std::endl;
        break;
        case LEDHandle::status::LED_UNAVAILABLE:
            std::cout << "LED is unavailable!" << std::endl;
        break;        
    }

    handle.set_status(LEDHandle::status::LED_ON);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    handle.set_status(LEDHandle::status::LED_OFF);
}

