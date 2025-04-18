#ifndef CHARLIES_LED_H
#define CHARLIES_LED_H

#define     LED_OFF_VALUE       (1)
#define     LED_ON_VALUE        (0)
#define     LED_NAME            "charlies_led"
#define     LED_GPIO_PROPERTY   "charliesled-gpio"

#define     LED_DEF_BEHAVE      1

#define     K_LED_STATUS_OPEN   "opened"
#define     K_LED_STATUS_CLOSED "closed"

#define     K_LED_OPEN_CMD      "open"
#define     K_LED_CLOSE_CMD     "close"

#define     K_TIMER_START       (_IO(0XEF, 0x2))
#define     K_TIMER_STOP        (_IO(0XEF, 0x1))
#define     K_SET_PERIOD        (_IO(0XEF, 0x3))

#define     K_DEF_PERIOD        (1000)

#endif