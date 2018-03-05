#include "Data.h"

void Data::FillData(double pTemp, double pPress) {
	this->_Pressure = pPress;
	this->_Temperature = pTemp;

	String temp = String(_Pressure * 10.0);
	_Pressure_int = temp.toInt();

	temp = String(_Temperature * 100.0);
	_Temperature_int = temp.toInt();
}

String Data::getTemperatureAsString() {
	return toString(_Temperature);
}

String Data::getPressureAsString() {
	return toString(_Pressure);
}

uint8_t * Data::Temperature() {
	return ((uint8_t*)&_Temperature_int);
}

uint8_t * Data::Pressure() {
	return ((uint8_t*)&_Pressure_int);
}

String Data::toString(double value)
{
	return String(value);
}
