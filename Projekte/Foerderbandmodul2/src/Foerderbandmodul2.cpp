#include <iostream>

//#include "hal/sensorik/SensorikSteuerung.h"
#include "hal/sensorik/SensorikSim.h"
#include"dispatcher/InputDispatcher.h"
#include "Kommunikation/Kommunikation.h"
using namespace std;

int main() {
	HALAktorik *aktorik = new HALAktorik();

	OutputDispatcher *outputDispatcher = new OutputDispatcher();
	SensorikSim *sensorik = new SensorikSim(*outputDispatcher, *aktorik);
	//SensorikSteuerung *sensorik = new SensorikSteuerung(*outputDispatcher, *aktorik);
	InputDispatcher *inputDispatcher = new InputDispatcher(*aktorik);
	thread t3(&InputDispatcher::receiveSignal, ref(inputDispatcher));
	Kommunikation *kommunikation = new Kommunikation(*outputDispatcher);
	thread komm(&Kommunikation::receiveSignal, ref(kommunikation));
	outputDispatcher->init();

	sensorik->runHALSteuerung();

	komm.join();
	t3.join();

	return 0;
}
