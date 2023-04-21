#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <string>
#include <sstream>
#include "vehicle-counter.h"

const int UPDATE_TIME = 5000; //5 segundos

String ssid;
String password;
String server;
String device_id;
int cycle_counter;
int trigger_pin = -1;
int echo_pin = -1;
int min_distance;
std::stringstream stream;

HTTPClient http = HTTPClient();
WiFiClient wifi = WiFiClient();
VehicleCounter sensor;

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
  configure_from_serial();
  Serial.print("Data recived: NET ");
  Serial.print(ssid.c_str());
  Serial.print(" #");
  Serial.print(password.c_str());
  Serial.print("# at ");
  Serial.print(server.c_str());
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

  const char *id = config_doc["id"],
  *new_ssid = config_doc["ssid"],
  *new_password = config_doc["password"],
  *new_distance = config_doc["distance"],
  *new_trigger = config_doc["trigger"],
  *new_echo = config_doc["echo"],
  *new_server = config_doc["server"];

  bool network_changed = false;
  int trigger, echo, distance;
  if(new_trigger != nullptr){
    trigger = std::stoi(new_trigger);
  }

  if(new_echo != nullptr){
    echo = std::stoi(new_echo);
  }

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

  if(trigger != trigger_pin || echo != echo_pin || distance != min_distance){
    sensor = VehicleCounter(trigger, echo, distance);
    sensor.configure();
    sensor.measure_base_distance();
    trigger_pin = trigger;
    echo_pin = echo;
    min_distance = distance;
  }
}

int send_JSON(){
  char buffer[300];
  int response;
  stream << '{' 
   << "\"count\":" << sensor.get_count() << ','
   << "\"id\":" << '"' << device_id.c_str() << '"'
   << '}';
  stream.getline(buffer, 200);
  http.begin(wifi, server);
  http.addHeader("Content-Type", "application/json");
  response = http.POST(buffer);
  http.end();
  return response;
}

bool transmit_data() {
  if(WiFi.status() != WL_CONNECTED){
    return false;
  }

  Serial.println("SENDING DATA");
  int response_code = send_JSON();
  if(response_code == HTTP_CODE_OK){
    Serial.println("OK");
    return true;
  }
  Serial.print("ERROR (");
  Serial.print(response_code);
  Serial.print(") ");
  Serial.println(http.errorToString(response_code));
  delay(UPDATE_TIME);
  return false;
}

void loop(){
  sensor.measure();
  Serial.println(sensor.get_count());
}
