#include <Arduino.h>
#include <Servo.h>

// PB1 tương ứng với Chân 9 trong môi trường Arduino
const int SERVO_PIN = 9; 
const int MIN_ANGLE = 0;
const int MAX_ANGLE = 180;

Servo myServo;

void setup() {
    // Khởi tạo truyền thông Serial ở tốc độ 9600 baud
    Serial.begin(9600);
    
    // Gán chân PB1 để xuất xung PWM điều khiển Servo
    myServo.attach(SERVO_PIN);
    
    // Đặt Servo về vị trí mặc định (0 độ)
    myServo.write(0);
    
    // Gửi thông báo hệ thống đã sẵn sàng
    Serial.println("=== ATMEGA328 SERVO CONTROL READY ===");
    Serial.println("Please enter an angle (0 - 180):");
}

void loop() {
    // Kiểm tra nếu có dữ liệu gửi từ máy tính
    if (Serial.available() > 0) {
        // Đọc giá trị số nguyên từ Serial
        int requestedAngle = Serial.parseInt();

        // Xóa các ký tự thừa (\n, \r) trong bộ đệm Serial
        while (Serial.available() > 0) {
            Serial.read();
        }

        // YÊU CẦU 2: Kiểm tra góc nhận được có nằm trong dải cho phép (0 - 180) không
        if (requestedAngle >= MIN_ANGLE && requestedAngle <= MAX_ANGLE) {
            // YÊU CẦU 3: Góc hợp lệ -> Quay Servo
            myServo.write(requestedAngle);

            // YÊU CẦU 5: Gửi thông báo xác nhận về máy tính
            Serial.print("[CONFIRM] Command accepted. Servo rotated to: ");
            Serial.print(requestedAngle);
            Serial.println(" deg.");
        } else {
            // YÊU CẦU 4: Góc ngoài dải -> Từ chối và gửi thông báo lỗi
            Serial.print("[REJECTED] Error: Angle ");
            Serial.print(requestedAngle);
            Serial.print(" is out of range! Permitted range: ");
            Serial.print(MIN_ANGLE);
            Serial.print(" to ");
            Serial.print(MAX_ANGLE);
            Serial.println(" deg.");
        }
    }
}