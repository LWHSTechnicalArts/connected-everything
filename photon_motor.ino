Servo serv;
int pos = 0;

void setup() {
    serv.attach(D3);
    Particle.function("setpos", setPos);
    Particle.variable("getpos", &pos, INT);
}

void loop() {
}

int setPos(String pstn) {
    pos = pstn.toInt();
    serv.write(pos);
    return pos;
}
