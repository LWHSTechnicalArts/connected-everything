const unsigned long PUBLISH_PERIOD_MS = 15000;
const unsigned long FIRST_PUBLISH_MS = 5000;
const char *PUBLISH_EVENT_NAME = "test1data";

unsigned long lastPublish = FIRST_PUBLISH_MS - PUBLISH_PERIOD_MS;
int nextValue = 1;

void setup() {
	Serial.begin(9600);
}

void loop() {
	if (millis() - lastPublish >= PUBLISH_PERIOD_MS) {
		lastPublish = millis();
		publishData();
	}
}

void publishData() {
	// This just publishes some somewhat random data for testing

	// a is a monotonically increasing integer
	int a = nextValue++;
	// b is a decimal derived from a 
	double b = a*2.2;
	// c is a random integer
	int c = rand();
	
	char buf[256];
	snprintf(buf, sizeof(buf), "{\"a\":%d,\"b\":%.3f,\"c\":%d}", a, b, c);
	Serial.printlnf("publishing %s", buf);
	Particle.publish(PUBLISH_EVENT_NAME, buf, PRIVATE);
}
