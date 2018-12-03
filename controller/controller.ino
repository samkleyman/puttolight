#include <SPI.h>
#include <Ethernet2.h>
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.timeapi.org";   
IPAddress ip(192, 168, 0, 2);
EthernetClient client;
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  // Дадим время шилду на инициализацию
  delay(1000);
  Serial.println("connecting...");
  if (client.connect(server, 80)) {
    Serial.println("---------------");
    // Создаем HTTP-запрос
    client.println("GET /utc/now HTTP/1.1");
    client.println("Host: www.timeapi.org");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
void loop() {
  // Если есть доступные биты, читаем их и выводим на экран
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  // Если соединение прервано, отключаем клиент
  if (!client.connected()) {
    Serial.println();
    Serial.println("---------------");
    Serial.println("disconnecting");
    client.stop();
    // Останавливаем выполнение программы
    while (true);
  }
}
