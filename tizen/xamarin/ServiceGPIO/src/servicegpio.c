#include <tizen.h>
#include <service_app.h>
#include "servicegpio.h"
#include <peripheral_io.h>
#include <Ecore.h>

#define SENSOR_LED_GPIO_NUMBER (20)
#define TIMER_GATHER_INTERVAL (2.0f)

peripheral_gpio_h g_sensor_h = NULL;
Ecore_Timer *getter_timer = NULL;

int flagLight = 0;

static bool service_app_create(void *data)
{
    return true;
}

static Eina_Bool _get_motion_set_led()
{
    peripheral_gpio_open(SENSOR_LED_GPIO_NUMBER, &g_sensor_h);
    peripheral_gpio_set_direction(g_sensor_h, PERIPHERAL_GPIO_DIRECTION_OUT_INITIALLY_LOW);

    if(flagLight == 1)
    {
    	flagLight = 0;
    }
    else{
    	flagLight = 1;
    }
    peripheral_gpio_write(g_sensor_h, flagLight);

	return ECORE_CALLBACK_RENEW;
}

static void service_app_terminate(void *data)
{
	// Delete timer
	if (getter_timer) {
		ecore_timer_del(getter_timer);
		getter_timer = NULL;
	}

	peripheral_gpio_close(g_sensor_h);
}

static void service_app_control(app_control_h app_control, void *data)
{
	// Delete old timer if there is one
	if (getter_timer) {
		ecore_timer_del(getter_timer);
		getter_timer = NULL;
	}

	// Create a timer to call the given function in given period of time
	ecore_timer_add(TIMER_GATHER_INTERVAL, _get_motion_set_led, data);
}


int main(int argc, char* argv[])
{
	service_app_lifecycle_callback_s event_callback;

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	return service_app_main(argc, argv, &event_callback, NULL);
}
