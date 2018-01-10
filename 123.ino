#include <LWiFi.h>
#include <LBLE.h>
#include <LBLEPeriphral.h>

const char* ssid     = "9 mi";           // insert your SSID
const char* pass     = "0123456789";    // insert your password

WiFiClient client;

const char* server = "maker.ifttt.com";  
const char* resource ="/trigger/LINE_Test/with/key/bo0S03SpH5KPQvbyK7eOXV"; //輸入key

// Define a simple GATT service with only 1 characteristic
LBLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214");
LBLECharacteristicInt switchCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", LBLE_READ | LBLE_WRITE);

void setup() {

  Serial.begin(115200);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println();

  LBLE.begin();
  while (!LBLE.ready()) {
    delay(100);
  }
  Serial.println("BLE ready");

  Serial.print("Device Address = [");
  Serial.print(LBLE.getDeviceAddress());
  Serial.println("]");

  // configure our advertisement data.
  // In this case, we simply create an advertisement that represents an
  // connectable device with a device name
  LBLEAdvertisementData advertisement;
  advertisement.configAsConnectableDevice("BLE LED");

  // Configure our device's Generic Access Profile's device name
  // Ususally this is the same as the name in the advertisement data.
  LBLEPeripheral.setName("BLE LED");

  // Add characteristics into ledService
  ledService.addAttribute(switchCharacteristic);

  // Add service to GATT server (peripheral)
  LBLEPeripheral.addService(ledService);

  // start the GATT server - it is now 
  // available to connect
  LBLEPeripheral.begin();

  // start advertisment
  LBLEPeripheral.advertise(advertisement);
}

void loop() {
   // connect to server  
  while(!client.connect(server, 80)){
    // wait for connecting server...
  }
  delay(1000);
  Serial.print("conected=");
  Serial.println(LBLEPeripheral.connected());

  if (switchCharacteristic.isWritten()) {
    const char value = switchCharacteristic.getValue();
    
    switch (value) {
      
      case 0:
        client.print("GET ");
        client.print(resource);
        client.print("?value1=");
        client.print("HUNGRY");
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
        Serial.print(0); 
        break;
      case 1:
        client.print("GET ");
        client.print(resource);
        client.print("?value1=");
        client.print("SICK");
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
        Serial.print(1);  
        break;
      case 2:
        client.print("GET ");
        client.print(resource);
        client.print("?value1=");
        client.print("LONELY");
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
        Serial.print(2);  
        break;
      case 3:
        client.print("GET ");
        client.print(resource);
        client.print("?value1=");
        client.print("SOS");
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
        Serial.print(3);  
        break;
      default:
        Serial.println("Unknown value written");
        break;
   }
 }
 
  delay(3000);
  
client.stop(); // disconnect from server

}
