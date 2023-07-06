// 今回は正規化する必要がないためNormalize関数は仕様していない
const int IN_POWER = 8;
const int IN_SWITCH = 9;
const int OUT_POW = 10;
const int OUT_AVE = 11;
const int OUT_MAX = 12;
const int OUT_SIGNAL = 13;
const float RATIO = 3.937;    // 3.937 * 4064 = 16000Hz = 500 * 32
const unsigned int MIN = 92;
//#define float RATIO = 1.047;     1.047 * 4064 = 4256 Hz = 133 * 32

int dimave[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int dimmax[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int freave = MIN;
unsigned int tmpave = MIN;
unsigned int fremax = MIN;
unsigned int tmpmax = MIN;

int normalize(int value) {
    float tempf;
    int tempi;
    tempf = value * RATIO;
    tempi = int(tempf);

    return tempi;
}

unsigned int minlimit(unsigned int value) {
    int temp = value;
    if(value < MIN) {
        temp = MIN;
    }
    return temp;
}

void input() {
    unsigned int data = (byte)Serial.read();
    if(data < 128) {
        for(int i = 0; i <= 14; i++) {
            dimave[i] = dimave[i + 1];
        }
        dimave[15] = data;

        // 最近の入力にバイアスのかかった過去32回を考慮した値，値は0から4064
        unsigned int rowave = 0;
        rowave += data;
        for(int i = 0; i <= 15; i++) {
          rowave += 2 * dimave[i];
        }
        // freave  = normalize(rowave);     // 正規化
        freave = minlimit(rowave);          // tone関数は32Hzより低い音は出せないため
        }else if(data > 127) {
        for(int i = 0; i <= 14; i++) {
            dimmax[i] = dimmax[i + 1];
        }
        dimmax[15] = data - 128;

        unsigned int rowmax = 0;
        rowmax += data - 128;
        for(int i = 0; i <= 15; i++) {
          rowmax += 2 * dimmax[i];
        }
        // fremax  = normalize(rowmax);
        fremax = minlimit(rowmax);
    }
}

void setup() {
    // put your setup code here, to run once:
    pinMode(IN_POWER, INPUT);
    pinMode(IN_SWITCH, INPUT);
    pinMode(OUT_POW, OUTPUT);
    pinMode(OUT_AVE, OUTPUT);
    pinMode(OUT_MAX, OUTPUT);
    pinMode(OUT_SIGNAL, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    if(Serial.available() > 0){
        input();
    }

    if(digitalRead(IN_POWER) == 0) {
        tone(OUT_SIGNAL, MIN);
        digitalWrite(OUT_POW, LOW);
        digitalWrite(OUT_AVE, LOW);
        digitalWrite(OUT_MAX, LOW);
    } else {
        if(digitalRead(IN_SWITCH) == 0) {
            tone(OUT_SIGNAL, freave);
            digitalWrite(OUT_POW, HIGH);
            digitalWrite(OUT_AVE, HIGH);
            digitalWrite(OUT_MAX, LOW);
        } else {
            tone(OUT_SIGNAL, fremax);
            digitalWrite(OUT_POW, HIGH);
            digitalWrite(OUT_AVE, LOW);
            digitalWrite(OUT_MAX, HIGH);
        }
    }
}
