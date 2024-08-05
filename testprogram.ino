#include <Servo.h>;


Servo servo[2];

const byte servoPins[] = {0, 1, 2, 3};




void setup() {

  for (int n = 0; n < 2; n++) {
    servo[n].attach(servoPins[n]);
  }

}

void loop() {

  // Myservo[1].write(150);
  // delay(500);
  // Myservo[1].write(10);
  // delay(500);
  servo[0].write(10);
}




// void movementEyeLid() {

//   for (int positionServo = 10; positionServo <= 50; positionServo++) {
//     Myservo.write(positionServo);
//   }


// }




// fungsi yang berguna untuk menggerakan mata bot
//SpeedEyeMovement -> sebagai delay/kecepatan bergerak mata
// void movementEye(short SpeedEyeMovement) {

//     for (int pos = 0; pos <= 50; pos++) {
//         Myservo.write(pos);
//         delay(25);

//         if (pos == 50) {
//           for (pos; pos >= 0; pos--) {
          
//             Myservo.write(pos);
//             delay(25);
//           }
//         }
//       }

// }
