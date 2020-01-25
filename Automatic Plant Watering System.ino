
int motor1 = 9;  //L293d"den gelen sinyal pinleri arduinodaki  9. ve 10. pine bağlanır
int motor2 = 10;
int led1 = 2;
int led2 = 3;
int led3 = 4;


;
int topraknemsensor = 0; //toprak nem sensöründen gelen veriler analog 0.pinden alınır
void setup() {

Serial.begin(9600); //Seri port başlatılır  (nem değerlerini okumak için)

pinMode(motor1, OUTPUT); //çıkış pinleri tanımlandı
pinMode(motor2, OUTPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);



}

void loop() {
//analog pini okutulur
int sensorValue = analogRead(topraknemsensor);

Serial.println(sensorValue);
if (sensorValue >= 820) //nem sensöründen gelen değerler 820nin üstünde olduğunda yapılan işlemler
{
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
digitalWrite(led1,LOW);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);




}
else if (sensorValue >= 615 && sensorValue < 820)
{

digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);


} 
else if (sensorValue >= 410 && sensorValue < 615)
{

digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,HIGH);


} 
else if (sensorValue >= 250 && sensorValue < 410)
{

digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,HIGH);


}
else if (sensorValue >= 0 && sensorValue < 250)
{

digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,HIGH);


}
delay(1000); //Her saniye nem değerleri okutulur
}
