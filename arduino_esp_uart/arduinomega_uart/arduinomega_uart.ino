#define TIME1 20000         // thời gian 20s

String uartmega="";         // biến lưu trữ chuỗi
unsigned long t1;           // biến lưu theo hàm millis()

void setup()
{
  Serial.begin(9600);       // bật serial 0
  Serial2.begin(9600);      // bật serial 2
}

void loop()
{
  while(Serial2.available()>0)                                  // khi có dữ liệu trong bộ nhớ đệm
  {
    uartmega += (char)Serial2.read();                           // chuyển sang char và lưu vào chuỗi
    delay(10);                                                  // phải delay ở đây để không bị mất dữ liệu khi đọc
    if(Serial2.available()==0)                                  // khi đã đọc hết dữ liệu trong bộ nhớ đệm
    {
      Serial.println("giá trị nhận được là: "+uartmega);        // hiện ra màn hình dữ liệu nhận được
      uartmega=(uartmega=="esp8266d1")?"dung roi":"sai";        // nếu dữ liệu nhận được là esp8266d1 thì hiển thị "dung roi" ngược lại thì hiển thị "sai"
      Serial.println(uartmega);                                 // hiển thị "dung roi" hoặc "sai" 
      uartmega="";                                              // reset biến lưu trữ
    }
  }
  if(millis()-t1>TIME1)                                         // nếu được 20s
  {
    Serial2.write("mega2560");                                  // serial2 gửi chuỗi mega2560
    Serial.println("da gui gia tri tu mega: mega2560");         // in ra màn hình thông báo đã gửi đi dữ liệu : mega2560
    t1=millis();                                                // cập nhật lại hàm millis() t1
  }
}
