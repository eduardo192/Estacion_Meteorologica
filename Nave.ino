
//Es obligatorio seguir el orden indicado en la inclusion de las librerias.
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//#include "DHT.h"
/*#include <Ticker.h>
Ticker tiempo_1;
*/
#define FIREBASE_HOST "estacion-86bac.firebaseio.com" //Sin http:// o https:// 
#define FIREBASE_AUTH "PN0mJrKE4A71GH47PdKabGG4jrFTsngVj1iUqZu4"
//#define WIFI_SSID "AE76F3" 
#define WIFI_SSID "INFINITUME3EC8D"
//#define WIFI_PASSWORD "L21503731612565" 
#define WIFI_PASSWORD "04F7DA4B5B"


//BMP180
#include <SFE_BMP180.h>
#include <Wire.h>
SFE_BMP180 bmp180;

//Servomotor libreria
#include <Servo.h>

// Variable para controlar Servomotor
Servo servoMotor;

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 Dht22...
//#define DHTPIN 2 

String path = "/Nave 1";
//Define un objeto de Firebase
FirebaseData firebaseData;

void printResult(FirebaseData &data);
void CausaError(void);
void InforSetLuzSensor(void);
void InforGetLuzSensor(void);

// Initialize DHT sensor.
//DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a ....");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado con la IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Establezca el tiempo de espera de lectura de la base de datos en 1 minuto (máximo 15 minutos)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  
  //Tamaño y  tiempo de espera de escritura, tiny (1s), small (10s), medium (30s) and large (60s).
  //tiny, small, medium, large and unlimited.
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  //dht.begin();

   //Iniciar el BMP180
  if (bmp180.begin()) Serial.println("BMP180 se ha iniciado");
  else Serial.println("BMP180 no se ha iniciado correctamente\n\n");

  //Servomotor se iniciara en el pin 12 (D6)
  servoMotor.attach(12);
}

void loop()
{
  //Leer humedad
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  //if (Firebase.setFloat(firebaseData, path + "/Sensores/Humedad", h)){InforSetLuzSensor();}else{CausaError(h, "humedad");} 
  //if (Firebase.setFloat(firebaseData, path + "/Sensores/Temperatura", t)){InforSetLuzSensor();}else{CausaError(t, "temperatura");} 
  //delay(5000);

  char status;
  double T,P; // Temperatura y presion

  status = bmp180.startTemperature();//Inicio de lectura de temperatura
  if (status != 0)
  {   
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {        
        delay(status);//Pausa para que finalice la lectura        
        status = bmp180.getPressure(P,T); //Obtenemos la presión
        if (status != 0)
        {                  
          Serial.print("Temperatura: ");
          Serial.print(T,2);
          Serial.print(" *C , ");
          Serial.print("Presion: ");
          Serial.print(P,2);
          Serial.println(" mb");          
        }      
      }      
    }   
  }
    //Servomotor -> Se activara cada que la temperatura aumente a 29.0 C
    Serial.print("R2:"+ false);
          if( T>= 29.0){
            servoMotor.write(180);
            Serial.print(1, false);
          }
          else{
           servoMotor.write(0); 
           Serial.print(0, false);
          } 
  delay(2000);
  if (Firebase.setDouble(firebaseData, path + "/Sensores/Presion", P)){InforSetLuzSensor();}else{CausaError(P, "presion");} 
  if (Firebase.setDouble(firebaseData, path + "/Sensores/Temperatura", T)){InforSetLuzSensor();}else{CausaError(T, "temperatura");}
  //if(Firebase.setBool(firebaseData, path + "/Relay/Servo",)) Quiero poner el servo para que reciba datos xd
}

void InforGetLuzSensor(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println(); 
}

void InforSetLuzSensor(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println(); 
}

void CausaError(double valor, String sensor)
{
  if(sensor == "temperatura"){
    if(isnan(valor))Serial.println(F("fallo lectura de Temperatura del sensor BMP180 !"));
  }else{
    if(isnan(valor))Serial.println(F("Fallo lectura de Presion del sensor BMP180!"));
  }
  Serial.println("FAILED");
  Serial.println("REASON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}

void printResult(FirebaseData &data)
{
    if (data.dataType() == "int")
        Serial.println(data.intData());
    else if (data.dataType() == "float")
        Serial.println(data.floatData(), 5);
    else if (data.dataType() == "double")
        printf("%.9lf\n", data.doubleData());
    else if (data.dataType() == "boolean")
        Serial.println(data.boolData() == 1 ? "true" : "false");
    else if (data.dataType() == "string")
        Serial.println(data.stringData());
}
