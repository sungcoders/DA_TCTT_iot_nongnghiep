
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
  uart_send("AT\r\n",5000);
  uart_send("AT+GMR\r\n",5000);
  uart_send("AT+RST\r\n",5000);
}

void loop()
{
  
}

char* uart_send(String str,int interval)
{
  static char cvc[200];
  str.toCharArray(cvc,str.length()+1);
  Serial2.write(cvc);
  delay(interval);
  return (cvc);
}
