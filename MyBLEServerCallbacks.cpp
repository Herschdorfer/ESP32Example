#include "MyBLEServerCallbacks.h"



inline void MyBLEServerCallbacks::onConnect(BLEServer * pServer) {
	_BLEClientConnected = true;
}

inline void MyBLEServerCallbacks::onDisconnect(BLEServer * pServer) {
	_BLEClientConnected = false;
}

bool MyBLEServerCallbacks::isClientConnected()
{
	return _BLEClientConnected;
}



