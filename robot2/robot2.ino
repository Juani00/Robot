#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

#define SERVO_FREQ 60 // Frekuensi PWM, sesuaikan dengan spesifikasi servo Anda
#define SERVO_KANAN_PIN 1 // Pin servo untuk mata kanan (pada pca8695)
#define SERVO_KIRI_PIN 2 // Pin servo untuk mata kiri (pada pca8695)
#define SERVO_KELAPAK_PIN 0 // Pin servo untuk kelopak mata (pada pca8695)
#define SERVOMIN 150   // Lebar pulsa minimum untuk servo
#define SERVOMAX 600   // Lebar pulsa maksimum untuk servo
#define DELAY_BETWEEN_STEPS 10 // Waktu delay antara setiap langkah (ms)



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Inisialisasi objek PCA9685

// const int switchPin = 2; // pin 2 (Digital Pin) pada Arduino Board, yang digunakan untuk membaca status saklar.
const int ledPinWhite = 7;
const int ledPinRed = 8;


// bool robotOn = false; // variabel untuk menandai status robot (hidup/mati)

// Deklarasi prototipe fungsi
void moveEyetoCenter();
void moveEyetoLeftNormalSpeed();
void moveEyeToCenterSlowySpeed();
void moveEyetoLeftSlowySpeed();
void moveEyetoRightNormalSpeed();
void moveEyetoRightSlowySpeed();
void openAndCloseEyelid();
void moveEyeServos(uint16_t angle);
void moveEyelidServo(uint16_t angle);
void shuffleEyeMovements();
void controlEyes();
void moveAndWait(uint16_t delayTime);

void setup() {
  // pinMode(switchPin, INPUT); // Set pin saklar sebagai input
  // pinMode(ledPinWhite, OUTPUT);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set frekuensi PWM

  Serial.begin(9600);

 
}

void loop() {

    // menghidupkan lampu led putih, setelah seluruh proses pada fungsi Void setup selesai dijalankan.

    
    // digitalWrite(ledPinWhite, HIGH);
    openAndCloseEyelid();
    moveEyeServos(25);
    delay(11000);
    moveEyeServos(0); // mata ke kanan
    delay(3000);
    moveEyeServos(50); // mata ke kiri
    delay(3000);
    moveEyeServos(25);
    
    openAndCloseEyelid();
    delay(300);
    openAndCloseEyelid();
    delay(5000);

    
    moveEyeServos(50); // mata ke kiri
    openAndCloseEyelid();
    delay(900);
    openAndCloseEyelid();
    delay(1900);
    moveEyeServos(25); // mata ke tengah
    delay(4000);
    moveEyeServos(50); // mata ke kiri
    delay(4000);
    moveEyeServos(0); // mata ke kanan
    delay(3000);
    moveEyeServos(25); // mata ke tengah
    delay(3900);
    openAndCloseEyelid();
    delay(1000);
    moveEyeServos(0); // mata ke kanan
    delay(3800);
    moveEyeServos(25); // mata ditengah.
    openAndCloseEyelid();
    delay(5000);
    openAndCloseEyelid();
    delay(15000);
    delay(55000);

    



    // *jika, langsung memakai saklar pada arduino
    // int switchStatus = digitalRead(switchPin); // baca status saklar
    // Serial.print("Switch status: ");
    // Serial.println(switchStatus);

    // Jika saklar dimatikan, hentikan semua proses dan pergerakan mata
    // if (switchStatus == LOW) {
    //     // Tidak perlu melakukan apa pun saat saklar dimatikan
    //     delay(100); // Tunggu sebentar 
    //     moveEyetoCenter;
    //     moveEyelidServo(10); // menutup kelopak mata
    //     return; // Keluar dari loop
    // }

    // Jika saklar dinyalakan dan robot masih dalam status mati
    // if (switchStatus == HIGH && !robotOn) {
    //     Serial.println("Menyalakan Robot....");
    //     moveEyelidServo(150); // Kelopak mata terbuka
    //     digitalWrite(ledPinWhite, HIGH);
    //     robotOn = true; // Atur status robot menjadi hidup
    // }

    // Jika robot sedang hidup, pastikan LED putih tetap menyala
    // if (robotOn) {
    //     moveEyelidServo(150); // Kelopak mata terbuka
    //     digitalWrite(ledPinWhite, HIGH);
    //     controlEyes(); // Memanggil controlEyes secara terus-menerus saat robot hidup
    //     moveAndWait(1500); // Tunggu setelah semua gerakan mata dieksekusi
    // }

  
  // digitalWrite(ledPinWhite, HIGH); // menghidupkan lampu led putih.
  // // controlEyes(); // Memanggil controlEyes secara terus-menerus saat robot hidup.
  // openAndCloseEyelid();
  // delay(10);


// -------------------------------------
   
  


    // // mata perlahan mengarah kekiri, dan robot bergerak juga ke arah kiri
    // // manusia pergi ke arah kiri (minum)
    // moveEyetoLeftSlowySpeed();
    // delay(3000);
    // openAndCloseEyelid();
    // delay(2000);

    // controlEyes();
    // delay(2000);
    // controlEyes();
    // delay(1500);

    // moveEyetoCenter();
    // delay(10000);
    // moveEyetoLeftSlowySpeed();
    // delay(1500);
    // moveEyetoRightSlowySpeed();
    // delay(1500);
    // openAndCloseEyelid();
    // moveEyeToCenterSlowySpeed();
    // delay(2000);
    // openAndCloseEyelid();
    

}

// fungsi untuk menuggu dan menggerakan mata robot (delay), jika memakai saklar pada arduino. 
// void moveAndWait(uint16_t delayTime) {
//     delay(delayTime);
//     if (digitalRead(switchPin) == LOW) return; // Periksa saklar, jika mati keluar dari loop
// }

// Definisikan jumlah langkah gerakan mata
const int NUM_EYE_MOVEMENTS = 10;

// Deklarasikan array yang berisi pointer ke fungsi gerakan mata
void (*eyeMovements[NUM_EYE_MOVEMENTS])() = {
    moveEyetoCenter,
    moveEyeToCenterSlowySpeed,
    moveEyetoLeftNormalSpeed,
    moveEyetoLeftSlowySpeed,
    moveEyetoRightNormalSpeed,
    moveEyetoRightNormalSpeed,
    moveEyetoRightSlowySpeed,
    openAndCloseEyelid,
    moveEyeToCenterSlowySpeed,
    moveEyetoLeftSlowySpeed
    
};

// Array untuk menyimpan status setiap gerakan mata
bool eyeMovementsDone[NUM_EYE_MOVEMENTS] = {false};

// Fungsi untuk mengacak urutan gerakan mata dan memeriksa duplikat
void shuffleEyeMovements() {
    for (int i = 0; i < NUM_EYE_MOVEMENTS; i++) {
        eyeMovementsDone[i] = false; // Reset status setiap gerakan
    }

    for (int i = NUM_EYE_MOVEMENTS - 1; i > 0; i--) {
        int j = random(0, i + 1);
        // Tukar posisi elemen array
        void (*temp)() = eyeMovements[i];
        eyeMovements[i] = eyeMovements[j];
        eyeMovements[j] = temp;
    }
}

// Fungsi untuk menggerakkan mata sesuai urutan yang telah diacak
void controlEyes() {
    // Acak urutan gerakan mata setiap kali fungsi dipanggil
    shuffleEyeMovements();

    // Lakukan setiap gerakan mata secara berurutan
    for (int i = 0; i < NUM_EYE_MOVEMENTS; i++) {
        int eyeMovementIndex = -1; // Index gerakan mata yang belum dilakukan
        // Cari gerakan mata yang belum dilakukan
        for (int j = 0; j < NUM_EYE_MOVEMENTS; j++) {
            if (!eyeMovementsDone[j]) {
                eyeMovementIndex = j;
                break;
            }
        }

        // Jika tidak ada gerakan mata yang belum dilakukan, keluar dari loop
        if (eyeMovementIndex == -1) {
            break;
        }

        // Debug print statement
        Serial.print("Executing eye movement: ");
        Serial.println(eyeMovementIndex);

        // Panggil fungsi gerakan mata yang belum dilakukan
        eyeMovements[eyeMovementIndex]();
        delay(1500); // moveAndWait(1500); // Tunggu setelah setiap gerakan mata

        // Tandai gerakan mata sebagai sudah dilakukan
        eyeMovementsDone[eyeMovementIndex] = true;
    }
}

// Fungsi untuk menggerakkan mata ke posisi tertentu
void moveEyeServos(uint16_t angle) {
    pwm.setPWM(SERVO_KANAN_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
    pwm.setPWM(SERVO_KIRI_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
}

// Fungsi untuk menggerakkan servo kelopak mata ke posisi tertentu
void moveEyelidServo(uint16_t angle) {
    pwm.setPWM(SERVO_KELAPAK_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
}

// Fungsi untuk menggerakkan mata ke kiri dengan kecepatan 10ms/normal
void moveEyetoLeftNormalSpeed() {
    for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
        moveEyeServos(radiusEyeAngle);
        delay(DELAY_BETWEEN_STEPS);
    }
}

// Fungsi untuk menggerakkan mata ke kanan dengan kecepatan 10ms/normal
void moveEyetoRightNormalSpeed() {
    for (int radiusEyeAngle = 50; radiusEyeAngle >= 0; radiusEyeAngle--) {
        moveEyeServos(radiusEyeAngle);
        delay(DELAY_BETWEEN_STEPS);
    }
}

// Fungsi untuk menggerakkan mata ke kiri dengan kecepatan 40ms/sedikit lebih lambat
void moveEyetoLeftSlowySpeed() {
    for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
        moveEyeServos(radiusEyeAngle);
        delay(DELAY_BETWEEN_STEPS + 30);
    }
}

// Fungsi untuk menggerakkan mata ke kanan dengan kecepatan 40ms/sedikit lebih lambat
void moveEyetoRightSlowySpeed() {
    for (int radiusEyeAngle = 50; radiusEyeAngle >= 0; radiusEyeAngle--) {
        moveEyeServos(radiusEyeAngle);
        delay(DELAY_BETWEEN_STEPS + 30);
    }
}

// Fungsi untuk menggerakkan mata ke tengah
void moveEyetoCenter() {
    for (int i = 0; i <= 25; i++) {
        moveEyeServos(i);                           
        delay(DELAY_BETWEEN_STEPS);                
    }
}

// Fungsi untuk menggerakkan mata ke tengah secara perlahan
void moveEyeToCenterSlowySpeed() {
    for (int i = 0; i <= 25; i++) {
        moveEyeServos(i);
        delay(DELAY_BETWEEN_STEPS + 30);
    }
}

// fungsi menggerakan satu mata(kiri) robot ke arah kiri
// void moveLeftEyeToLeft() {

//   // void moveEyeServos(uint16_t angle) {
//   //   pwm.setPWM(SERVO_KANAN_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
//   //   pwm.setPWM(SERVO_KIRI_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
//   // }

//   //  for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
//   //       moveEyeServos(radiusEyeAngle);
//   //       delay(DELAY_BETWEEN_STEPS + 30);
//   //   }

//     for (int leftEye = 25; leftEye <= 0; leftEye--) {
//         pwm.setPWM(SERVO_KIRI_PIN, 0, map(leftEye, 0, 180, SERVOMIN, SERVOMAX));
//         delay(DELAY_BETWEEN_STEPS + 50);
//     }
// }

// // fungsi menggerakan satu mata(kanan) robot ke arah kanan
// void moveRightEyeToRight() {

// }




//fungsi mengontrol mata secara berlawanan, mata kiri ke kiri - mata kanan ke kanan
void moveEyesToDifferentPosition() {


    /*
      pada kasus ini, 
      saya membuat posisi derajat mata robot =

      0  = posisi mata robot ke arah, Kanan.
      25 = posisi mata robot ke arah, Tengah.
      50 = posisi mata robot ke arah, Kiri.
    */

    // Gerakkan mata kiri menghadap ke arah hidung
    for (int lama2BotakCoyy = 25; lama2BotakCoyy <= 50; lama2BotakCoyy++) {
        pwm.setPWM(SERVO_KIRI_PIN, 0, map(lama2BotakCoyy, 0, 180, SERVOMIN, SERVOMAX));
        delay(DELAY_BETWEEN_STEPS);
    }

    // Gerakkan mata kanan menghadap ke arah hidung
    for (int pusingKepalaMinumBaygonn = 25; pusingKepalaMinumBaygonn >= 0; pusingKepalaMinumBaygonn--) {
        pwm.setPWM(SERVO_KANAN_PIN, 0, map(pusingKepalaMinumBaygonn, 0, 180, SERVOMIN, SERVOMAX));
        delay(DELAY_BETWEEN_STEPS);
    }
    
    // Tunggu sejenak setelah kedua mata mencapai batas maksimum
    delay(2000);

    for (int i = 50; i >= 0; i--) {
      pwm.setPWM(SERVO_KIRI_PIN, 0, map(0, 0, 180, SERVOMIN, SERVOMAX));
      pwm.setPWM(SERVO_KANAN_PIN, 0, map(50, 0, 180, SERVOMIN, SERVOMAX));
      delay(DELAY_BETWEEN_STEPS + 50);
    }

    delay(1200);
    // kedua mata bergerak menuju perlahan ke posisi tengah.
    moveEyetoCenter();
}
   
// Fungsi mengontrol kelopak mata untuk membuka dan tutup.
void openAndCloseEyelid() {
    moveEyelidServo(10); // menutup kelopak mata
    delay(500);
    moveEyelidServo(150); // membuka kelopak mata
    delay(500);
}


