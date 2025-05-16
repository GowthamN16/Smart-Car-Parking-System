#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "car-parking-system-5e041-default-rtdb.firebaseio.com"
#define WIFI_SSID "Rohit"
#define WIFI_PASSWORD "bunny6436"
#define FIREBASE_Authorization_key "HdXbBC9S8ciVjiN9mEjJf1EFNFUXSav4rHXFe3ig"

FirebaseData firebaseData;
FirebaseJson json;

unsigned long presentTime1 = 0, presentTime2 = 0, presentTime3 = 0, presentTime4 = 0;
unsigned long previousTime1 = 0, previousTime2 = 0, previousTime3 = 0, previousTime4 = 0;
int resultTime1, resultTime2, resultTime3, resultTime4;
int f1 = 0, f2 = 0, f3 = 0, f4 = 0;
int rate = 10; // per 1 second
int amount1, amount2, amount3, amount4;

String filled = "Filled";
String empty = "Empty";

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);

  pinMode(4, INPUT);  // P1 D2
  pinMode(5, INPUT);  // P2 D1
  pinMode(12, INPUT); // P3 D6
  pinMode(13, INPUT); // P4 D7
}

void loop() {
  // Parking Slot 1
  if (digitalRead(4) == LOW) {
    Firebase.setString(firebaseData, "PS1", filled);
    presentTime1 = millis();
    f1 = 1;
    resultTime1 = (presentTime1 - previousTime1) / 1000;
  } else {
    if (f1 == 1) {
      amount1 = resultTime1 * rate;
      previousTime1 = presentTime1;
    }
    f1 = 0;
    Firebase.setString(firebaseData, "PS1", empty);
  }

  // Parking Slot 2
  if (digitalRead(5) == LOW) {
    Firebase.setString(firebaseData, "PS2", filled);
    presentTime2 = millis();
    f2 = 1;
    resultTime2 = (presentTime2 - previousTime2) / 1000;
  } else {
    if (f2 == 1) {
      amount2 = resultTime2 * rate;
      previousTime2 = presentTime2;
    }
    f2 = 0;
    Firebase.setString(firebaseData, "PS2", empty);
  }

  // Parking Slot 3
  if (digitalRead(12) == LOW) {
    Firebase.setString(firebaseData, "PS3", filled);
    presentTime3 = millis();
    f3 = 1;
    resultTime3 = (presentTime3 - previousTime3) / 1000;
  } else {
    if (f3 == 1) {
      amount3 = resultTime3 * rate;
      previousTime3 = presentTime3;
    }
    f3 = 0;
    Firebase.setString(firebaseData, "PS3", empty);
  }

  // Parking Slot 4
  if (digitalRead(13) == LOW) {
    Firebase.setString(firebaseData, "PS4", filled);
    presentTime4 = millis();
    f4 = 1;
    resultTime4 = (presentTime4 - previousTime4) / 1000;
  } else {
    if (f4 == 1) {
      amount4 = resultTime4 * rate;
      previousTime4 = presentTime4;
    }
    f4 = 0;
    Firebase.setString(firebaseData, "PS4", empty);
  }

  // Update bills
  Firebase.setFloat(firebaseData, "PS1Bill", amount1);
  Firebase.setFloat(firebaseData, "PS2Bill", amount2);
  Firebase.setFloat(firebaseData, "PS3Bill", amount3);
  Firebase.setFloat(firebaseData, "PS4Bill", amount4);
}
