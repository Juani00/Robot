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
Servo servo;

const int soundSensorPin = A0;
const int servoPin = 9;

unsigned long previousMillis = 0;
const long interval = 500; // interval untuk kontrol mata dan mulut (ms)

int storedAngles[] = {30, 55, 180};

void setup() {
  pinMode(soundSensorPin, INPUT);
  servo.attach(servoPin);

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set frekuensi PWM
  
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Gerakan mata dan mulut secara bersamaan
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    controlEyes();
    // controlMouth();
  }
}

void controlEyes() {
  // Variabel lokal static untuk menyimpan gerakan sebelumnya
  static int previousMove = -1;

  // Variabel lokal static untuk melacak jumlah case yang sudah terpanggil
  static int callCount = 0;

  // Gerakan mata secara acak
  int randomMove;
  do {
    randomMove = random(0, 5); // Dapatkan nilai acak dari 0 hingga 4
  } while (randomMove == previousMove); // Ulangi jika gerakan saat ini sama dengan gerakan sebelumnya

  // Simpan gerakan saat ini sebagai gerakan sebelumnya untuk penggunaan di iterasi berikutnya
  previousMove = randomMove;

  switch (randomMove) {
    case 0:
      moveEyetoLeftNormalSpeed();
      break;
    case 1:
      moveEyetoRightSlowySpeed();
      break;
    case 2:
      moveEyetoLeftSlowySpeed();
      break;
    case 3:
      moveEyetoRightNormalSpeed();
      break;
    case 4:
      moveEyetoCenter();
      openAndCloseEyelid();
      break;
    default:
      break;
  }

  // Tambahkan 1 ke hitungan pemanggilan
  callCount++;

  // Jika sudah terpanggil 3 atau 4 kali, tambahkan delay dan reset hitungan
  if (callCount == 6) {
    delay(3000); // Delay 2 detik
    callCount = 0; // Reset hitungan
  }
}




// Fungsi untuk menggerakkan servo mata ke posisi tertentu
void moveEyeServos(uint16_t angle) {
  pwm.setPWM(SERVO_KANAN_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(SERVO_KIRI_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
}

// Fungsi untuk menggerakkan servo kelopak mata ke posisi tertentu
void moveEyelidServo(uint16_t angle) {
  pwm.setPWM(SERVO_KELAPAK_PIN, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
}

// fungsi untuk menggerakan mata ke kiri dengan kecepatan 10ms/normal
void moveEyetoLeftNormalSpeed() {
  for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS);
  }
}

// fungsi untuk menggerakan mata ke kanan dengan kecepatan 10ms/normal
void moveEyetoRightNormalSpeed() {
  for (int radiusEyeAngle = 50; radiusEyeAngle >= 0; radiusEyeAngle--) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS);
  }
}

// fungsi untuk menggerakan mata ke kiri dengan kecepatan 40ms/sedikit lebih lambat
void moveEyetoLeftSlowySpeed() {
  for (int radiusEyeAngle = 0; radiusEyeAngle <= 50; radiusEyeAngle++) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS + 30);
  }
}

//fungsi untuk menggerakan mata ke kanan dengan kecepatan 40ms/sedikit lebih lambat
void moveEyetoRightSlowySpeed() {
  for (int radiusEyeAngle = 50; radiusEyeAngle >= 0; radiusEyeAngle--) {
    moveEyeServos(radiusEyeAngle);
    delay(DELAY_BETWEEN_STEPS + 30);
  }
}

// fungsi untuk menggerakan mata ke tengah
void moveEyetoCenter() {
  for (int i = 0; i <= 25; i++) {
    moveEyeServos(i);                           
    delay(DELAY_BETWEEN_STEPS);                
  }
  delay(1000); // Tunggu sebentar di posisi tengah
}

// fungsi mengontrol kelopak mata untuk membuka dan tutup.
void openAndCloseEyelid() {
  moveEyelidServo(10); // menutup kelopak mata
  delay(500);
  moveEyelidServo(150); // membuka kelopak mata
  delay(500);
}



// 1. kiri
// 2. tengah
// 3. kiri
// 4. kanan
//    break
// 5. tengah
// 6. kanan
// 7. kiri
// 8. tengah
//    break


