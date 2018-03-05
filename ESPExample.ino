#include "DataStore.h"
#include "SimpleBLE.h"

#include <Arduino.h>
#include <Adafruit_BMP085.h>

#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLE2902.h>

#include <U8g2lib.h>

#include "Data.h"
#include "MyBLEServerCallbacks.h"

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define bluetooth_width 6
#define bluetooth_height 10
static unsigned char bluetooth_bits[] = { 0x04, 0x0c, 0x14, 0x25, 0x16, 0x0c, 0x16, 0x25, 0x14, 0x0c, 0x04 };

#define TEMP_UUID     0x2A6E
#define PRESSURE_UUID 0x2A6D

U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 5, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

BLEDescriptor tempDescriptor(BLEUUID((uint16_t)0x2901));
BLEDescriptor pressureDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic *pressureCharacteristic;
BLECharacteristic *tempCharacteristic;


Adafruit_BMP085 bmp;

SimpleBLE ble;
String beaconMsg = "ESP00";
int rec = 0;


MyBLEServerCallbacks *callback;

void InitBLE() {

	callback = new MyBLEServerCallbacks();


	BLEDevice::init("ESP32-EE060");

	// Create the BLE Server
	BLEServer *pServer = BLEDevice::createServer();
	pServer->setCallbacks(callback);

	// Create the BLE Service
	BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x181A));

	tempCharacteristic = pService->createCharacteristic(
		BLEUUID((uint16_t)TEMP_UUID),
		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
	);

	pressureCharacteristic = pService->createCharacteristic(
		BLEUUID((uint16_t)PRESSURE_UUID),
		BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
	);

	pressureDescriptor.setValue("Pressure Pa");
	pressureCharacteristic->addDescriptor(&pressureDescriptor);
	pressureCharacteristic->addDescriptor(new BLE2902());

	tempDescriptor.setValue("Temperature -40-60°C");
	tempCharacteristic->addDescriptor(&tempDescriptor);
	tempCharacteristic->addDescriptor(new BLE2902());

	pService->start();

	// Start advertising
	pServer->getAdvertising()->start();
}

Data *aD;

void setup() {


	aD = new Data();
	InitBLE();

	Serial.begin(115200);
	Serial.println();
	Serial.println();


	u8g2.begin();

	if (!bmp.begin())
	{
		Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
		while (1) {}
	}

}

void TransferBLE() {
	tempCharacteristic->setValue(aD->Temperature(), 2);
	tempCharacteristic->notify();

	pressureCharacteristic->setValue(aD->Pressure(), 4);
	pressureCharacteristic->notify();
}


void loop()
{

	aD->FillData(bmp.readTemperature(), bmp.readPressure());

	u8g2.firstPage();
	do {
		u8g2.drawFrame(0, 0, 128, 32);
		u8g2.setFont(u8g2_font_ncenB08_tr);
		u8g2.setCursor(2, 10);
		u8g2.print(aD->getTemperatureAsString());
		u8g2.setCursor(2, 20);
		u8g2.print(aD->getPressureAsString());
		u8g2.drawStr(2, 30, "Hello World!");
		if (callback->isClientConnected())
		{
			u8g2.drawXBMP(100, 10, bluetooth_width, bluetooth_height, bluetooth_bits);
		}

	} while (u8g2.nextPage());

	TransferBLE();
	delay(4000);
}


