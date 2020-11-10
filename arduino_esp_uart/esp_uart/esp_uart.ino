#include <ESP8266WiFi.h>

#define TIME1 30000             // thời gian 30s
#define ssid  "4G UFI_1AA"      // tên wifi
#define pass  "1234567890"      // pass wifi

String uartespd1="";            // biến để lưu trử chuỗi
unsigned long t1 =0;            // biến đếm theo hàm millis()

void setup()
{
  Serial.begin(9600);
  pinMode(D4, OUTPUT);          // D4 là chân out
  wifi(500);                    // kết nối wifi nếu sai sẽ chờ kết nối 0.5s
}

void loop()
{
  if(WiFi.status()!=WL_CONNECTED) {wifi(500);}    // nếu mất kết nối wifi sẽ tự động kết nối lại
  while(Serial.available()>0)                     // khi có dữ liệu trong bộ nhớ đệm
  {
    digitalWrite(D4,0);                           // bật led
    uartespd1 += (char)Serial.read();             // chuyển sang định dạng char và lưu vào chuỗi
    delay(10);                                    // phải có delay 10ms ở đây để không lỗi dữ liệu đọc
    if(Serial.available()==0)                     // đã đọc hết dữ liệu trong bộ nhớ đệm
    {
      if(uartespd1=="mega2560"){led(2,200);} else {digitalWrite(D4, 1);}        // nếu nhận đúng dữ liệu sẽ chớp tắt led báo hiệu
      uartespd1="";                                                             // reset biến lưu  
    }
  }
  if(millis()-t1>TIME1) { uart_char("esp8266d1"); t1=millis(); }                // đúng 30s gửi chuỗi esp8266d1
}

void led(int count, int interval)            //function bật tắt led n lần với delay 
{
  for(int i=0; i<count;i++)
  {
    digitalWrite(D4,0);
    delay(interval);
    digitalWrite(D4,1);
    delay(interval);
  }
}

void wifi(int interval)                     // hàm kết nối wifi và delay chờ kết nối lại
{
  WiFi.begin(ssid,pass);                    // bắt đầu kết nối wifi
  while(WiFi.status()!=WL_CONNECTED)        // khi chưa kết nối chờ để kết nối lại
  {
    digitalWrite(D4,0);                     // led bật khi chưa kết nối được wifi
    delay(interval);
  }
  digitalWrite(D4,1);                      // kết nối được wifi thì tắt led đi
}

void uart_char(String str)                  // function chuyển chuỗi sang char và gửi
{
  char buff[20];
  str.toCharArray(buff,str.length()+1);
  Serial.write(buff);
}

void uart_float(float num1)                 // chuyển float sang char và gửi
{
  char buff[20];
  String str=(String)num1;
  str.toCharArray(buff,str.length()+1);
  Serial.write(buff);
}

void uart_number(int num1)                  // chuyển int sang char và gửi
{
  char buff[20];
  String str=(String)num1;
  str.toCharArray(buff,str.length()+1);
  Serial.write(buff);
}
