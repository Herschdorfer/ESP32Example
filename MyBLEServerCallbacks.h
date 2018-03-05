#pragma once
#include <BLEServer.h>

class MyBLEServerCallbacks : public BLEServerCallbacks {
private:
	bool _BLEClientConnected = false;

public:
	void onConnect(BLEServer* pServer);;
	void onDisconnect(BLEServer* pServer);

	bool isClientConnected();

};