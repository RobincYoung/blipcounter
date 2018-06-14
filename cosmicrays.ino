#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int last10sec[10];
int cursec = 0;
long wasprev;
char buff[100];
void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(8, INPUT_PULLUP);
}
int prevstat = 0;
int curstat = 0;
unsigned long lastmic;
void loop() {
  // put your main code here, to run repeatedly:
 curstat = digitalRead(8);
 if (curstat < prevstat)
  {
  if (wasprev <= 0)
   {
    wasprev=100000;
    lastmic = micros();
   }
  else
   {
      ++last10sec[cursec];
      wasprev=0;

   }
  }
  prevstat = curstat;
  if (wasprev>=0)
   {
    wasprev = wasprev - (micros() - lastmic);
    lastmic = micros();
   }
onceasec();
}

void onceasec()
{
  static const unsigned long REFRESH_INTERVAL = 1000; // ms
  static unsigned long lastRefreshTime = 0;

  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
    lastRefreshTime = millis();
                cursec = cursec + 1;
                if (cursec > 9)
                {
                  cursec = 0;
                }
                // Print a message to the LCD.
                int total=0;
                int i;
                for (i = 0;i<10;++i)
                  {
                  total = total + last10sec[i];
                  }
                //total = total / 10;
                last10sec[cursec] = 0;
                lcd.setCursor(0, 0);
                sprintf(buff,"blips/s: %d.%d   ",total/10,total%10);
                lcd.print(buff);


  }
}
