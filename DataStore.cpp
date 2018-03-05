// 
// 
// 

#include "DataStore.h"

void DataStore::FillData(double pTemp, double pPress) {
	this->_Pressure = pPress;
	this->_Temperature = pTemp;

	String temp = String(_Pressure * 10.0);
	_Pressure_int = temp.toInt();

	temp = String(_Temperature * 100.0);
	_Temperature_int = temp.toInt();
}

String DataStore::getTemperatureAsString() {
	return toString(_Temperature);
}

String DataStore::getPressureAsString() {
	return toString(_Pressure);
}

uint8_t * DataStore::Temperature() {
	return ((uint8_t*)&_Temperature_int);
}

uint8_t * DataStore::Pressure() {
	return ((uint8_t*)&_Pressure_int);
}

String DataStore::toString(double value)
{
	return String(value);
}