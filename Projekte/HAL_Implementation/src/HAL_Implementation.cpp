/* Start
 * @author: Franz Korf
 * @author: Thomas Lehmann
 * @author: Bardia Filizadeh
 * @author: Tobias Thoelen
 * @author: Marek Peer Irmert
 * @author: Daniel Drefs Fernandes
 * @date: 2022-10-01
 */

#include <sys/neutrino.h>
#include <thread>
#include <iostream>

#include "hal/demo/HALAktorikDemo.h"
#include "hal/demo/HALSensorikDemo.h"

using std::thread;

int main() {

	// request IO privileges
	ThreadCtl( _NTO_TCTL_IO, 0);
	HALAktorikDemo *aktorikDemo = new HALAktorikDemo();
	HALSensorikDemo *sensorikDemo = new HALSensorikDemo();

	while (true) {
		aktorikDemo->runDemo();
		sensorikDemo->runDemo();
	}

	return 0;
}
