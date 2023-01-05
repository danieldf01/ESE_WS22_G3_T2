//#include "MsgHandler.h"
#include "Main.h"

using namespace std;

int main(int argc, char **argv) {
	int ret;
	if (argc < 2) {
		printf("Usage %s -s | -c & -sync | -pulse \n", argv[0]);
		ret = EXIT_FAILURE;
	} else if (strcmp(argv[1], "-c") == 0) {
		if (strcmp(argv[2], "-sync") == 0) {
			SyncMessages *sync = new SyncMessages();
			printf("Running Client sync ... \n");
//			ret = sync->clientSync(); /* see name_open() for this code */
			thread t(&SyncMessages::clientSync, sync);
		} else {
			PulseMessages *pulse = new PulseMessages();
			printf("Running Client pulse... \n");
//			ret = pulse->clientPulse();
			thread t(&PulseMessages::clientPulse, pulse, 0);
			thread t2(&PulseMessages::clientPulse, pulse, 0);
			thread t3(&PulseMessages::clientPulse, pulse, 1);
			thread t4(&PulseMessages::clientPulse, pulse, 1);
			t.join();
			t2.join();
			t3.join();
			t4.join();
		}
	} else if (strcmp(argv[1], "-s") == 0) {
		if (strcmp(argv[2], "-sync") == 0) {
			SyncMessages *sync = new SyncMessages();
			printf("Running Server sync ... \n");
//			ret = sync->serverSync(); /* see name_open() for this code */
			thread t(&SyncMessages::serverSync, sync);
		} else {
			PulseMessages *pulse = new PulseMessages();
			printf("Running Server pulse ... \n");
//			ret = pulse->serverPulse();
			thread t(&PulseMessages::serverPulse, pulse, 0);
			thread t2(&PulseMessages::serverPulse, pulse, 1);
			t.join();
			t2.join();
		}
	} else {
		printf("Usage %s -s | -c & -sync | -pulse \n", argv[0]);
		ret = EXIT_FAILURE;
	}
	return ret;
}
