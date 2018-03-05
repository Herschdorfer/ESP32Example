#pragma once
#include <Arduino.h>


class Data {
private:
	double  _Pressure;
	double  _Temperature;

	uint32_t _Pressure_int;
	int16_t _Temperature_int;

public:
	void FillData(double pTemp, double pPress);

	String getTemperatureAsString();

	String getPressureAsString();

	uint8_t* Temperature();

	uint8_t* Pressure();

private:
	String toString(double value);

};

