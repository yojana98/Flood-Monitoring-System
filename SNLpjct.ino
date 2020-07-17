int MyValue1;
#include <SoftwareSerial.h>
SoftwareSerial Serial1(2,3);
const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
String number = "+917738702757";


void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial1.begin(9600);
    Serial.begin(9600);
 

}

void loop() {
Serial.println("Sensing Water Level...");
delay(2000);
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);
const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
int gapdistance= duration/29/2;
Serial.println(gapdistance);
delay(1000);
Serial.println("Establishing connection...");
delay(1000);
Connect2Server();      // Establishing connection

if(gapdistance<=14){
MyValue1= 13 - gapdistance;
}


Serial.println("Uploading value to the server...");
Field1(MyValue1);       // Uploading to field 1 of Thingspeak
Serial.println("Connection Ended...");
EndConnection();        // Terminating connection

if (gapdistance<=2){
  Serial.println("Value is");
  Serial.println(MyValue1);
  Serial.println("Sending SMS");
  Serial1.println("AT+CMGF=1");
  delay(1000);
  Serial1.println("AT+CMGS=\"+917738702757\"\r");
  delay(1000);
  String SMS = "Water Level Increased:" + String(MyValue1) ;
  Serial1.println(SMS);
  delay(1000);
  Serial1.println((char)26);
  delay(1000);
  Serial.println("SMS Sent");
}

delay(5000);
Serial.println("Restarting the Connection....");

}


void Connect2Server()
{
  Serial1.println("AT");
  delay(200);
  Serial1.println("AT+CPIN?");
  delay(200);
  Serial1.println("AT+CREG?");
  delay(200);
  Serial1.println("AT+CGATT?");
  delay(200);
  Serial1.println("AT+CIPSHUT");
  delay(200);
  Serial1.println("AT+CIPSTATUS");
  delay(1000);
  Serial1.println("AT+CIPMUX=0");
  delay(1000);
  ShowSerialData();
  Serial1.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(200);
  ShowSerialData(); 
  Serial1.println("AT+CIICR");//bring up wireless connection
  delay(2000);
  ShowSerialData();
  Serial1.println("AT+CIFSR");//get local IP adress
  delay(2000);
  ShowSerialData();
  Serial1.println("AT+CIPSPRT=0");
  delay(1000);
  ShowSerialData();
  Serial1.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(2000);
  ShowSerialData();
  Serial1.println("AT+CIPSEND");//begin send data to remote server
  delay(2000);
  ShowSerialData();
}

void Field1(int data) {
  
  String str = "GET http://api.thingspeak.com/update?api_key=PYN76ZOSDUFHPTTY&field2=" + String (data);
  Serial1.println(str);//begin send data to remote server
  delay(2000);
  ShowSerialData();
  Serial1.println((char)26);//sending
  delay(4000);//waitting for reply, important! the time is base on the condition of internet
  Serial1.println();
  ShowSerialData();
  
}

void SendMessage()
{
  
}

void EndConnection() {
  Serial1.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
  delay("5000");

}

void ShowSerialData()
{
  while(Serial1.available()!=0)
    Serial.write(Serial1.read());
}
