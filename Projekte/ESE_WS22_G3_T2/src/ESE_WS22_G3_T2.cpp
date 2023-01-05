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
#include "hal/demo/DemoHAL.h"

int main() {
	
	// request IO privileges
	ThreadCtl( _NTO_TCTL_IO, 0);
	HALAktorikDemo *demo = new HALAktorikDemo();

	while (true) {
		demo->runDemo();
	}

	return 0;
}

