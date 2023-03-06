#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <string>
#include <sstream>

const int UPDATE_TIME = 5000; //5 segundos

String ssid;
String password;
String server;
String device_id;

HTTPClient http = HTTPClient();
WiFiClient wifi = WiFiClient();


void connect_wifi(){
  Serial.println("CONECTING");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(2000);
    Serial.print(".");
  }
  Serial.println("CONECTED");
  Serial.println(WiFi.localIP().toString());
}

void setup() {
  Serial.begin(9600);
  while(!Serial){
    delay(200);
  }

  Serial.println("Waiting for configuration from Serial");
  while(Serial.peek() == -1){ //Mientras no haya datos
    delay(500);
  }
  Serial.print("Data recived: NET");
  Serial.print(ssid.c_str());
  Serial.print(" #");
  Serial.print(password.c_str());
  Serial.print("# at ");
  Serial.print(server.c_str());
  configure_from_serial();
  pinMode(A0, INPUT);
}

/* Lee en formato JSON las opciones desde el Serial
 * ssid: string
 * password: string
 * server: string
 */
void configure_from_serial(){
  String line = Serial.readString();
  StaticJsonDocument<200> config_doc;
  DeserializationError error = deserializeJson(config_doc, line);
  if(error){
    Serial.print("ERROR DE CONFIGURACION:");
    Serial.println(error.f_str());
    return;
  }

  const char* id = config_doc["id"];
  const char* new_ssid = config_doc["ssid"];
  const char* new_password = config_doc["password"];
  const char* new_server = config_doc["server"];
  bool network_changed = false;

  if(id != nullptr){
    device_id = id;
  }

  if(new_server != nullptr){
    server = String(new_server);
  }

  if(new_ssid != nullptr){
    ssid = String(new_ssid);
    network_changed = true;
  }

  if(new_password != nullptr){
    password = String(new_password);
    network_changed = true;
  }

  if(network_changed){
    wifi.stop();
    connect_wifi();
  }
}


int send_JSON(String name, String value){
  char buffer[300];
  int response;
  std::stringstream stream;
  stream << '{' 
    << '"' << name.c_str() << "\":" << value.c_str() << ','
    << "\"id\":" << '"' << device_id.c_str() << '"'
    << '}';
  stream.getline(buffer, 200);
  http.begin(wifi, server);
  http.addHeader("Content-Type", "application/json");
  response = http.POST(buffer);
  http.end();
  return response;
}

void loop() {
  if(Serial.peek() != -1){
    configure_from_serial();
  }

  if(WiFi.status() != WL_CONNECTED){
    return;
  }

  Serial.println("SENDING DATA");
  int response_code = send_JSON("humidity", String(analogRead(A0)));
  if(response_code == HTTP_CODE_OK){
    Serial.println("OK");
  }
  else{
    Serial.print("ERROR (");
    Serial.print(response_code);
    Serial.print(") ");
    Serial.println(http.errorToString(response_code));
  }
  delay(UPDATE_TIME);
}
