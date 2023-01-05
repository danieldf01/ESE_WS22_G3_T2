#include <gtest/gtest.h>
#include <iostream>

#include "Client.cpp"

using namespace std;

class TestClient: public ::testing::Test {
protected:
	qnetClient* client;

	virtual void SetUp() {
		this->client = new qnetClient();
	}

	virtual void TearDown() {
		delete this->client;
	}

};

TEST_F(TestClient, nameOpen) {
	int result = this->client->clientOpen();
	EXPECT_EQ(result, 0);
	result = this->client->sendMsg();
	EXPECT_EQ(result, 0);
	result = this->client->closeName();
	EXPECT_EQ(result, 0);
}
;
