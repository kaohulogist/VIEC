/*
 TCPIPClient
 Write sine wave data values to the tcpserver object created in MATLAB.
 */

#include <SPI.h>
#include <Ethernet.h>

// Specify the MAC address printed on the Ethernet shield.
// If no MAC address is printed, then use the address shown below.
byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};

// Specify the server IP address that is used to create the tcpserver object in MATLAB.
// This is the IP address of the router or network adapter that the Arduino Ethernet Shield is connected to.
// In this example, 192.168.1.81 is the IP address for the server.
IPAddress server(192,168,1,81);

// Set the static IP address for the Arduino Ethernet Shield to act as a TCP/IP client.
// Choose an IP address that is in the same subnet or private network as the server IP address.
// In this example, 192.168.1.177 is the IP address for the Arduino Ethernet Shield. It is in the same subnet as the server IP address.
IPAddress ip(192,168,1,177);
IPAddress myDns(192,168,1,1);

// Ethernet client library.
EthernetClient client;

// Command sent by the server.
byte command;

// Sine wave data buffer.
float sineWaveBuffer[250];

// The setup routine runs once when you press reset.
void setup()
{
  // Initialize serial communication.
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // Wait for serial port to connect.
  }
  
  Ethernet.begin(mac,ip,myDns);
  Serial.print("Manually assigned the following IP address to the Arduino:");
  Serial.println();
  Serial.println(Ethernet.localIP());

  // Check for Ethernet hardware.
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("Ethernet shield was not found.");
  }

  // Check for Ethernet cable connection.
  if (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Ethernet cable is not connected.");
  }

  Serial.print("Attempting connection to ");
  Serial.print(server);
  Serial.println("...");

  // Attempt to connect to the server running at IP address 192.168.1.81 and port 5000.
  if (client.connect(server,5000))
  {
    Serial.print("Connected to server running at ");
    Serial.println(client.remoteIP());
  }
  else 
  {
    Serial.println("Connection to server failed.");
  }

  // Store sine wave data as 250 float values.
  for (int j = 0;j < 250;j++) 
  {
    sineWaveBuffer[j] = sin(j*50.0/360.0);
  }
}

// Main processing loop
void loop() 
{
  // Block until data is sent by server.
  if (client.available() > 0)
  {
    // Read the command sent by the server.
    command = client.read();

    // Print the command sent by the server.
    Serial.println("The server sent the following command:");
    Serial.println(command);

    if (client.connected() && command == 1)
    {
        // Write sine wave data to the server.
        client.write((const uint8_t *) & sineWaveBuffer, sizeof(sineWaveBuffer));
    }
  }
}
