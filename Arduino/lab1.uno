const int trigPin_B = 9;
const int echoPin_B = 8;
const int trigPin_F = 10;
const int echoPin_F = 11;
int red_led = 13;
int green_led = 7;
int buzzer = 12;
int distance_F, distance_B;
void setup()
{
    pinMode(trigPin_F, OUTPUT);
    pinMode(echoPin_F, INPUT);
    pinMode(trigPin_B, OUTPUT);
    pinMode(echoPin_B, INPUT);
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(trigPin_F, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin_F, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_F, LOW);
    distance_F = pulseIn(echoPin_F, HIGH) / 58;
    Serial.print("Distance_F: ");
    Serial.print(distance_F);
    Serial.println("cm");
    digitalWrite(trigPin_B, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin_B, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_B, LOW);
    distance_B = pulseIn(echoPin_B, HIGH) / 58;
    Serial.print("Distance_B: ");
    Serial.print(distance_B);
    Serial.println("cm");
    delay(500);

    if (((distance_F > 50) && (distance_F < 300)) || ((distance_B > 50) && (distance_B < 300)))
    {
        if (((distance_F > 50) && (distance_F < 300)) && ((distance_B > 50) && (distance_B < 300)))
        {
            digitalWrite(red_led, LOW);
            digitalWrite(green_led, HIGH);
            goto out;
        }
        else if ((distance_F > 300) || (distance_B > 300))
        {
            digitalWrite(red_led, LOW);
            digitalWrite(green_led, HIGH);
            goto out;
        }
    }
    else
    {
        digitalWrite(green_led, LOW);
    }

    if (distance_F < 50 || distance_B < 50)
    {
        if (distance_F < 25 || distance_B < 25)
        {
            if (distance_F < 10 || distance_B < 10)
            {
                digitalWrite(green_led, LOW);
                digitalWrite(red_led, HIGH);
                digitalWrite(buzzer, HIGH);
                goto out;
            }
            digitalWrite(green_led, LOW);
            digitalWrite(red_led, HIGH);
            digitalWrite(buzzer, HIGH);
            delay(100);
            digitalWrite(red_led, LOW);
            digitalWrite(buzzer, LOW);
            delay(100);
            goto out;
        }
        digitalWrite(green_led, LOW);
        digitalWrite(red_led, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(300);
        digitalWrite(red_led, LOW);
        digitalWrite(buzzer, LOW);
        delay(300);
    }
	out:delay(20);
}
