// DataStore.h

#ifndef _DATASTORE_h
#define _DATASTORE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class DataStore {
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
