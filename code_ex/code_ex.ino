#include <ESP8266WiFi.h>

#define TIME1 30000
#define ssid  "4G UFI_1AA"
#define pass  "1234567890"

String uartespd1="";
unsigned long t1 =0;
String _ipserver = "IoTlab.net.vn"; 
String _StationCode="khsFndSJrM";  //Cong Kenh Lau
String _StationSecret="tPdmHDkfeb";
String _ServerPort="3000";

String sendESP8266(String ATCommand, int timeout, boolean debug)
{
  String response = "";
  Serial.print(ATCommand);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial.available())
    {
      byte c = Serial.read();
      response += (char)c;
    }
  }
  return response;
}

void setup()
{
  Serial.begin(9600);
  pinMode(D4, OUTPUT);
  wifi(500);
  digitalWrite(D4, 1);
}

void loop()
{
  if(WiFi.status()!=WL_CONNECTED) {wifi(500);}
  String url = getData();
  sendESP8266("AT+CIPSTART=\"TCP\",\"" + _ipserver + "\","+_ServerPort+"\r\n", 1000, true); //1000 Set port 3000
  String cipsend = "AT+CIPSEND=";
  cipsend += url.length();

  cipsend += "\r\n";
//  while(Serial.available()>0)
//  {
//    digitalWrite(D4,0);
//    uartespd1 += (char)Serial.read();
//    delay(10);
//    if(Serial.available()==0)
//    {
//      if(uartespd1=="mega2560"){led(2,200);} else {digitalWrite(D4, 1);}
//      uartespd1="";
//    }
//  }
  if(millis()-t1>TIME1) { uart_char("Seriald1"); t1=millis(); }
}

void led(int count, int interval)
{
  for(int i=0; i<count;i++)
  {
    digitalWrite(D4,0);
    delay(interval);
    digitalWrite(D4,1);
    delay(interval);
  }
}

void wifi(int interval)
{
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    digitalWrite(D4,0);
    delay(interval);
  }
  digitalWrite(D4,1);
}

void uart_char(String str)
{
  char buff[20];
  str.toCharArray(buff,str.length()+1);
  Serial.write(buff);
}

void uart_float(float num1)
{
  char buff[20];
  String str=(String)num1;
  str.toCharArray(buff,str.length()+1);
  Serial.write(buff);
}

void uart_number(int num1)
{
  char buff[20];
  String str=(String)num1;
  str.toCharArray(buff,str.length()+1);
  Serial.write(buff);
}

String getData(){
 float DO=-1.0;   
 
  
//    //DO sensor
//    turnOnDO(TIME30S);
//    delay(TIME30S);
//    delay(TIME30S);
// 
//  
//  float DO_Intercept = -0.4444; // hieu chuan CTU
//  float DO_Slope = 4.444;       // hieu chuan CTU
//
//
//  float DO_Voltage=getVoltage(A_DO,AVGTIME, TIME10S,5.0);
//  DO = DO_Intercept + DO_Voltage * DO_Slope; //converts voltage to sensor reading
//  
  DO=4.0;
//  if (DEBUG){
//     Serial.print("DO: ");
//     Serial.println(DO);
//  }
//Temperature sensor
  float Temp = 32.0;
//  turnOnTEMP(TIME30S);
//  float Temp = Thermistor(A_TEMP,AVGTIME, 500);   // and  convert it to CelsiusSerial.print(Time/1000); //display in seconds, not milliseconds

  
//  if (DEBUG){
//    Serial.print("Temperature: ");
//    Serial.println(Temp); 
//  }

    //Salinity sensor
    float SAL = 1.0;
//  turnOnSAL(TIME30S);
//  float SAL_Intercept = 0.0; // nhà cung cấp
//  float SAL_Slope = 16.3;       // nhà cung cấp  
//  float SAL_Voltage = getVoltage(A_SAL,AVGTIME,500,5.0);
//  float SAL = SAL_Intercept + SAL_Voltage * SAL_Slope; //converts voltage to sensor reading

// if (DEBUG){
//  Serial.print("SAL: ");
//  Serial.println(SAL);    
//  }  
  //PH sensor
  float PH=7.6;
//  turnOnPH(TIME30S);
////  float PH_Intercept = 16.237; // nhà cung cấp
////  float PH_Slope = -7.752;     // nhà cung cấp
//  
//  float PH_Intercept = 16.34; // nhà cung cấp
//  float PH_Slope = -7.78;     // nhà cung cấp
//  
//  float PH_Voltage = getVoltage(A_PH,AVGTIME,500,5.0);
//  float PH = PH_Intercept + PH_Voltage * PH_Slope; //converts voltage to sensor reading
//  


  String url = "POST /api/data/insertmulti?station_code=";
  url +=_StationCode +"&station_secret="+_StationSecret+"&data_stationType=1&Items[0][data_value]=";
  url += PH;
  url += "&Items[0][datatype_id]=001&Items[1][data_value]=";
  url += DO;
  url += "&Items[1][datatype_id]=002&Items[2][data_value]=";
  url += Temp;
  url += "&Items[2][datatype_id]=003&Items[3][data_value]=";
  //  tam khong su dung
  /*
  url += NH4;
  url += "&Items[3][datatype_id]=004&Items[4][data_value]=";
  */
  url += SAL;
  url += "&Items[3][datatype_id]=006";
 
  url += " HTTP/1.1\r\nHost: ";
  url += _ipserver;
  url += "\r\n";
  url += " Connection: close";
  url += "\r\n\r\n";

  return url;
}

String sendESP8266(String ATCommand, int timeout)
{
  String response = "";

  Serial.print(ATCommand);

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (Serial.available()>0)
    {
      response = (char)Serial.read();
    }
  }
  return response;
}
