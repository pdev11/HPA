#include <FirebaseArduino.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
// Set these to run example.
#define FIREBASE_HOST "smartparking-62de8.firebaseio.com"
#define FIREBASE_AUTH "r4IE5XR8AJAXPIeqAcLmjOKJYaa0t4YKKsYHztTy"

const int trigPin = D0;
const int echoPin = D1;
const int echoPin1 = D2;

const int led = D6;
const int led1 = D7;

// defines variables
long duration;
double distance;
bool space1 = false;
bool space2 = false;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  delay(10);
  pinMode(trigPin, OUTPUT);  
  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(echoPin1, INPUT); 

  pinMode(led,OUTPUT);
  pinMode(led1,OUTPUT);
  setupWiFi();
}
void setupWiFi(){
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Ri", "rinku9957");
  WiFiMulti.addAP("ssid", "jigneshkumar");
  WiFiMulti.addAP("123456", "12345678");
  
  Serial.print("connecting");
  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  BeginFirebase(); 
  }
void BeginFirebase(){
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.setString("Ultrasonic sensor 1", "0");
Firebase.setString("Ultrasonic sensor 2", "0");

 if(Firebase.success()){
    Serial.print("Firebase write success!");
  } else {
      Serial.print("Firebase write failed!");
      Serial.println("");
      Serial.print(Firebase.error());
  }
  Serial.println("");
}

void loop() {  
  if(Firebase.success()){
  String val = Firebase.getString("Ultrasonic sensor 1");
  if(val=="1"){
    digitalWrite(led,HIGH);
    distance = triggerRadar(trigPin,echoPin);
    if(distance<20){
      Firebase.setBool("space/space1",true);
    }
    else{
      Firebase.setBool("space/space1",false);  
          }  
      }
  String val1 = Firebase.getString("Ultrasonic sensor 2");
  if(val1=="1"){
    digitalWrite(led1,HIGH);
    distance = triggerRadar(trigPin,echoPin1);
    if(distance<20)
      Firebase.setBool("space/space2",true);
    else{
     // Firebase.setString("Ultrasonic sensor 2", "0");
     // digitalWrite(led1,LOW); 
      Firebase.setBool("space/space2",false); 
          }  
      }
  
  if(val=="0"){
    digitalWrite(led,LOW);
    Firebase.setBool("space/space1",false);
  }
  if(val1=="0"){
    digitalWrite(led1,LOW);
    Firebase.setBool("space/space2",false);
  } 
      Serial.println(distance);
      delay(100);
  }
    if (Firebase.failed())
    {
    Serial.println("Connecting again in 3sec");
    delay(3000);
    setupWiFi();
    }
}
double triggerRadar(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  double d = duration*0.0343/2;
  return d;
}
