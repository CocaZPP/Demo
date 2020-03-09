#ifndef _FLASH_MAP_H_
#define _FLASH_MAP_H_

#define ENCODE_FACTOR_START_ADD            (0)
#define ENCODE_FACTOR_END_ADD            (30)

#define NUMBER_ADDR			(ENCODE_FACTOR_END_ADD+3)
#define DESTINATIONIP_ADDR	NUMBER_ADDR+sizeof(number)
#define DESTINATIONPORT_ADDR	DESTINATIONIP_ADDR+sizeof(destinationIP)
#define UPLOAD_INTERVAL_ADDR	DESTINATIONPORT_ADDR+sizeof(destinationPort)
#define UPLOAD_START_ADDR	UPLOAD_INTERVAL_ADDR+sizeof(upload_interval)
#define SAMPLE_INTERVAL_ADDR	UPLOAD_START_ADDR+sizeof(upload_start)
#define FIBRE_OPTICAL_INTERVAL_ADDR	SAMPLE_INTERVAL_ADDR+sizeof(sample_interval)
#define FIBRE_OPTICAL_ENABLE_ADDR	FIBRE_OPTICAL_INTERVAL_ADDR+sizeof(fibre_optical_interval)
#define WATER_LEVEL_ENABLE_ADDR		FIBRE_OPTICAL_ENABLE_ADDR+sizeof(fibre_optical_enable)
#define TEMP_NUMBER_ADDR		WATER_LEVEL_ENABLE_ADDR+sizeof(water_level_enable)
#define MOVE_NUMBER_ADDR		TEMP_NUMBER_ADDR+sizeof(temp_number)
#define TEMPERATURE_ALARM_VALUE_ADDR		MOVE_NUMBER_ADDR+sizeof(move_number)
#define TEMPERATURE_ALARM_BOUND_ADDR		TEMPERATURE_ALARM_VALUE_ADDR+sizeof(temperature_alarm_value)
#define TEMP_SAMPLE_TIME_ADDR		TEMPERATURE_ALARM_BOUND_ADDR+sizeof(temperature_alarm_bound)
#define TEMP_UPLOAD_TIME_ADDR		TEMP_SAMPLE_TIME_ADDR+sizeof(temp_sample_time)
#define TEMP_TEMPERATURE_ALARM_ADDR		TEMP_UPLOAD_TIME_ADDR+sizeof(temp_upload_time)
#define TEMP_TEMPERATURE_BOUND_ADDR		TEMP_TEMPERATURE_ALARM_ADDR+sizeof(temp_temperature_alarm)
#define MOVE_DETECTION_TIME_ADDR		TEMP_TEMPERATURE_BOUND_ADDR+sizeof(temp_temperature_bound)
#define MOVE_SENSITIVITY_ADDR		MOVE_DETECTION_TIME_ADDR+sizeof(move_detection_time)
#define NOW_TEMP_NUMBER_LENTH_ADDR		MOVE_SENSITIVITY_ADDR+sizeof(move_sensitivity)
#define NOW_MOVE_NUMBER_LENTH_ADDR		NOW_TEMP_NUMBER_LENTH_ADDR+sizeof(now_temp_number_lenth)

#define WATER_NUMBER_ADDR               	NOW_MOVE_NUMBER_LENTH_ADDR+sizeof(now_move_number_lenth)
#define NOW_WATER_NUMBER_LENTH_ADDR				WATER_NUMBER_ADDR+sizeof(water_number)
#define SMOKE_NUMBER_ADDR               	NOW_WATER_NUMBER_LENTH_ADDR+sizeof(now_water_number_lenth)
#define NOW_SMOKE_NUMBER_LENTH_ADDR				SMOKE_NUMBER_ADDR+sizeof(smoke_number)

#define RF_CHANNEL_NUM_ADDR		NOW_SMOKE_NUMBER_LENTH_ADDR+sizeof(now_smoke_number_lenth)





 















#endif

