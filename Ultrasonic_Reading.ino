/* Hi everyone, welcome back. In this project we are going to make an ultrasonic beeper. Here we are going to setup an


#define TRIG_PIN 13  // Trigger pin connected to D13
#define ECHO_PIN 12  // Echo pin connected to D12



void setup() {
    Serial.begin(9600); // Initialize serial communication
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
        

}


void loop() {
    long duration;
    float distance;

    // Send a 10µs pulse to trigger the sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure the echo pulse duration
    duration = pulseIn(ECHO_PIN, HIGH);

    // Convert time to distance (speed of sound is 343 m/s or 0.0343 cm/µs)
    distance = (duration * 0.0343) / 2;

    


    // Print the distance to Serial Monitor
 Serial.print("Distance: ");
    Serial.print(distance);
     Serial.println(" cm");

    delay(500); // Wait before next measurement
}
