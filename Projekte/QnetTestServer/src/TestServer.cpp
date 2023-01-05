#include <gtest/gtest.h>
#include <iostream>

#include "Server.cpp"

using namespace std;

class TestServer: public ::testing::Test {
protected:
	qnetServer* server;

	virtual void SetUp() {
		this->server = new qnetServer();
	}

	virtual void TearDown() {
		delete this->server;
	}

};

TEST_F(TestServer, testsServer) {
	int chid = this->server->serverAttach();
	EXPECT_NE(this->server->attach, nullptr);
	EXPECT_NE(chid, 0);
	int result = this->server->rcvMsgAndDetach();
	EXPECT_EQ(result, 0);
}
;
