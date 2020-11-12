//外接blinker软件and小爱初始化
#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
#define BLINKER_MIOT_MULTI_OUTLET
#include <Blinker.h>

// 定义接口
#define ENA    5         //GPIO 5(D1)
#define ENB    0         //GPIO 0(D3)
#define IN_1  14         //GPIO14(D5)
#define IN_2  12         //GPIO12(D6)
#define IN_3  13         //GPIO13(D7)
#define IN_4  15         //GPIO15(D7)

//连接WIFI控制
char auth[] = "6fc944165781";
char ssid[] = "lusr-xiaomi";
char pswd[] = "15327376750";
int counter = 0;

// 预定义

int speedCar = 450;         // 0 - 1023.
int speedInterval = 180;     // 速度间隔
int speedTrun = 1.5;        // 转弯系数
int NUM = 0;              //初速度最小

// 新建组件对象
BlinkerButton Button1("btn-1");//左上
BlinkerButton Button2("btn-2");//前
BlinkerButton Button3("btn-3");//右上
BlinkerButton Button4("btn-4");//左
BlinkerButton Button5("btn-5");//停
BlinkerButton Button6("btn-6");//右
BlinkerButton Button7("btn-7");//左下
BlinkerButton Button8("btn-8");//后
BlinkerButton Button9("btn-9");//右下
BlinkerButton Button10("btn-10");//慢速
BlinkerButton Button11("btn-11");//中速
BlinkerButton Button12("btn-12");//快速
BlinkerButton Button13("btn-13");//开关
BlinkerNumber Number1("num-abc");

// 各个方向函数
void FL() 
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar / speedTrun);
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1); 
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
}
 
void F2() 
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
 
}
 
void FR() 
{
  analogWrite(ENA, speedCar / speedTrun);
  analogWrite(ENB, speedCar);
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1); 
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
}
 
void L2() 
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 1); 
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
}
 
void S2() 
{
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 0);
}
 
void R2() 
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 1);
}
 
void BL() 
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar / speedTrun);
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
}
 
void B2() 
{
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
}
 
void BR() 
{
  analogWrite(ENA, speedCar / speedTrun);
  analogWrite(ENB, speedCar);
  digitalWrite(IN_1, 1);
  digitalWrite(IN_2, 0); 
  digitalWrite(IN_3, 1);
  digitalWrite(IN_4, 0);
}
 
void CS(int NUM) 
{
  speedCar = 1023 - (5 - NUM) * speedInterval;
  analogWrite(ENA, speedCar);
  analogWrite(ENB, speedCar);
}

// 按下按键即会执行该函数
void button1_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    FL(); 

}
void button2_callback(const String & state) //小车轮子前转
{
    BLINKER_LOG("get button state: ", state); 
    F2(); 
}
void button3_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    FR(); 

}
void button4_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    L2(); 

}
void button5_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    S2();
}
void button6_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    R2();
}
void button7_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state); 
    BL();
}
void button8_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    B2();
}
void button9_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    BR();
}
void button10_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    CS(1);

}
void button11_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    CS(2);
}
void button12_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    CS(3);
}
void button13_callback(const String & state) 
{
    BLINKER_LOG("get button state: ", state);
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}
// 启动点灯操作

void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(LED_BUILTIN, LOW);

        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(IN_1, 0);
        digitalWrite(IN_2, 0);
        digitalWrite(IN_3, 0);
        digitalWrite(IN_4, 0);
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}
// 启动多模式操作

void miotMode(uint8_t mode)
{
    BLINKER_LOG("need set mode: ", mode);

    if (mode == BLINKER_CMD_MIOT_DAY) 
    {
       F2();
    }
    else if (mode == BLINKER_CMD_MIOT_NIGHT) 
    {
       L2(); 
    }
    else if (mode == BLINKER_CMD_MIOT_COLOR) 
    {
       R2();
    }
    else if (mode == BLINKER_CMD_MIOT_WARMTH) 
    {
       B2();
    }
    else if (mode == BLINKER_CMD_MIOT_TV) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_MIOT_READING) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_MIOT_COMPUTER) {
        // Your mode function
    }

    //wsMode = mode;

    BlinkerMIOT.mode(mode);
    BlinkerMIOT.print();
}


   

void setup() {
// 初始化串口
    Serial.begin(115200);
    
// 重定义避免
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

// 初始化IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    pinMode(ENA, OUTPUT);
    digitalWrite(ENA, 0);
    pinMode(ENB, OUTPUT);
    digitalWrite(ENB, 0);
    pinMode(IN_1, OUTPUT);
    digitalWrite(IN_1, 0);
    pinMode(IN_2, OUTPUT);
    digitalWrite(IN_2, 0);
    pinMode(IN_3, OUTPUT);
    digitalWrite(IN_3, 0);
    pinMode(IN_4, OUTPUT);
    digitalWrite(IN_4, 0);

    
// 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    
// 各个按钮设置回调函数    
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Button4.attach(button4_callback);
    Button5.attach(button5_callback);
    Button6.attach(button6_callback);
    Button7.attach(button7_callback);
    Button8.attach(button8_callback);
    Button9.attach(button9_callback);
    Button10.attach(button10_callback);
    Button11.attach(button11_callback);
    Button12.attach(button12_callback);
    Button13.attach(button13_callback);

//小爱语音模式调用    
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachMode(miotMode);
}

void loop() 
{
    Blinker.run();
}
