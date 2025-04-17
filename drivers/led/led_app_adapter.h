#ifndef LED_ADAPTER_H
#define LED_ADAPTER_H
#include <string>

class LEDHandle{
public:
    LEDHandle() = delete;
    /* you must pass a concrete dev file */
    LEDHandle(const std::string& dev_file_name);

    /* show the status of the led */
    enum class status{
        LED_ON,
        LED_OFF,
        LED_UNAVAILABLE,
        LED_UNKNOWN
    };

    status  get_status(void);

    bool    set_status(const status st);

    bool    available(void);

    bool    open(void);

private:
    static constexpr    const char* dev_prefix = "/dev/";
    std::string         dev_file_name;
    int                 led_internal_handle;
};
#endif
