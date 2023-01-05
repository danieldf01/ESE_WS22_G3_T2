#include <iostream>
#include "demo/HALSensorikDemo.h"

using namespace std;

int main() {
	// request IO privileges
		ThreadCtl( _NTO_TCTL_IO, 0);
		HALSensorikDemo *sensorikDemo = new HALSensorikDemo();

		while (true) {
			sensorikDemo->runDemo();
		}
	return 0;
}
