#define WEBSOCKETS_SAVE_RAM

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t len)
{
  switch (type)
  {
  case WStype_TEXT:
    Serial.write(payload, len);
    break;
  case WStype_BIN:
    Serial.write(payload, len);
    break;
  default:
    break;
  }
}

esp8266::MDNSImplementation::MDNSResponder::hMDNSService service;

char hostString[16] = {0};
char buf[256] = {0};
char *buf_ptr = 0;
bool err_flag = 0;

void setup()
{
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);

  if (!wifiManager.autoConnect("WirelessCNC", HOTSPOT_PW))
  {
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  sprintf(hostString, "ESP_%06X", ESP.getChipId());
  if (MDNS.begin(hostString))
  {
    service = MDNS.addService(0, "http", "tcp", 81);
    MDNS.addServiceTxt(service, "type", "cnc");
    MDNS.addServiceTxt(service, "name", hostString);
  }
  buf_ptr = buf;
}

bool processSerialLine(bool &err)
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    if (inChar == '\n')
    {
      *buf_ptr = 0;
      return true;
    }
    else
    {
      *buf_ptr = inChar;
      buf_ptr++;
      if (buf_ptr - buf >= 256)
      {
        err = true;
      }
    }
  }
  return false;
}

void loop()
{
  webSocket.loop();
  MDNS.update();
  if (processSerialLine(err_flag))
  {
    webSocket.broadcastTXT(buf, strlen(buf));
    buf_ptr = buf;
    *buf_ptr = 0;
  }
  if (err_flag)
  {
    webSocket.broadcastTXT("err:256");
    err_flag = false;
    buf_ptr = buf;
    *buf_ptr = 0;
  }
}