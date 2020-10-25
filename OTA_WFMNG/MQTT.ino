
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("MQTT again...");
    if(client.connect("ESP01"))
    {
      Serial.println(F("MQTT Connected"));
      client.publish("outTopic", "hello world");
      client.subscribe("inTopic");
    }
    else
    {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again..."));
      delay(5000);
    }
  }
}


//void reconnect() {
//  // Loop until we're reconnected
//  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
//    // Create a random client ID
//    String clientId = "ESP8266Client-";
//    clientId += String(random(0xffff), HEX);
//    // Attempt to connect
//    if (client.connect(clientId.c_str())) {
//      Serial.println("connected");
//      // Once connected, publish an announcement...
//      client.publish("outTopic", "hello world");
//      // ... and resubscribe
//      client.subscribe("inTopic");
//    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
//      // Wait 5 seconds before retrying
//      delay(5000);
//    }
//  }
//}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print(F("Message arrived ["));
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  switch((char)payload[1])
  {
    case '1': {digitalWrite(BUILTIN_LED, LOW); Serial.println(F("Đã bật led")); break;}
    case '2': {digitalWrite(BUILTIN_LED, HIGH); Serial.println(F("Đã tắt led")); break;}
  }
}
