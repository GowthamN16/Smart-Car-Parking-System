#include <Wire.h>
#include <Servo.h>

Servo myservo1;
int IR1 = 2;
int IR2 = 4;
int Slot = 4; // Number of parking slots
int flag1 = 0;
int flag2 = 0;

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo1.attach(7);
  myservo1.write(100); // Close gate
  delay(2000);
}

void loop() {
  // Entry logic
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0); // Open gate
        Slot = Slot - 1;
      }
    } else {
      delay(3000); // Wait if no slots
    }
  }

  // Exit logic
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo1.write(0); // Open gate
      Slot = Slot + 1;
    }
  }

  // Reset gate after both flags
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo1.write(100); // Close gate
    flag1 = 0;
    flag2 = 0;
  }
}
