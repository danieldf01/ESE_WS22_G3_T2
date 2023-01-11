/* Start
 * @author: Franz Korf
 * @author: Thomas Lehmann
 * @author: Bardia Filizadeh
 * @author: Tobias Thoelen
 * @author: Marek Peer Irmert
 * @author: Daniel Drefs Fernandes
 * @date: 2022-10-01
 */

//#include "hal/sensorik/SensorikSteuerung.h"
#include "hal/sensorik/SensorikSim.h"
#include"dispatcher/InputDispatcher.h"
#include "Kommunikation/Kommunikation.h"
#include "Logik/Hauptzustaende/Ruhezustand.h"
#include "Logik/LogikMain.h"

using namespace std;

int main() {
//	system("gns");
	// request IO privileges
	//ThreadCtl( _NTO_TCTL_IO, 0);

	HALAktorik *aktorik = new HALAktorik();

	OutputDispatcher *outputDispatcher = new OutputDispatcher();
	SensorikSim *sensorik = new SensorikSim(*outputDispatcher, *aktorik);
	//SensorikSteuerung *sensorik = new SensorikSteuerung(*outputDispatcher, *aktorik);
	InputDispatcher *inputDispatcher = new InputDispatcher(*aktorik);

	thread t3(&InputDispatcher::receiveSignal, ref(inputDispatcher));

	LogikMain *logik = new LogikMain();
	Kommunikation *kommunikation = new Kommunikation(*outputDispatcher);
	thread komm(&Kommunikation::receiveSignal, ref(kommunikation));
	thread t5 (&LogikMain::receiveSignal, ref(logik));
	thread t6 (&LogikMain::init, ref(logik));
	thread t7 (&OutputDispatcher::init, ref(outputDispatcher));
	thread kommInit(&Kommunikation::init, ref(kommunikation));
	sensorik->runHALSteuerung();

	t7.join();
	t6.join();
	t5.join();
	komm.join();
	//t4.join();
	t3.join();

	return 0;
}
