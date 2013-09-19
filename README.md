HUD
===

Arduino Based Heads-Up Display

//Code for HUD

int  d=1000,fuel=60,sp=0,time=0;

void distance()
{  
char p,*I;  
Serial.println("Enter the distance of travel");
if(Serial.available()>0)
      {
        p=Serial.read();
        *I=p;
        d=atoi(I);
Serial.print(d);
delay(2000);
     }
Serial.println("The distance of travel is");
Serial.println(d);
}

voidmilage()
{
int m=d/fuel;
Serial.println("The expected milage is");
Serial.println(m);
}
voidspd()
{
sp=random(0,20);
Serial.println(sp);
fuel=fuel-2;
time++;  
delay(1000);

sp=random(10,25);
Serial.println(sp);
fuel=fuel-2;
time++;  
delay(1000);

sp=random(20,40);
Serial.println(sp);
fuel=fuel-2;
time++;  
delay(1000);

sp=random(30,45);
Serial.println(sp);
fuel=fuel-2;
time++;  
delay(1000);
}

voidrefil()
{
if(fuel<=45)
  {
Serial.println(" FUEL LEVEL : LOW DETECTED");
delay(3500);
int b=Serial.read();
if(b==114)
       {
while(!Serial.available())
          {
Serial.println(" HOW MUCH FUEL TO BE REFILLED..??");
Serial.println(" Press 'a' for 60 litres");
Serial.println(" Press 'b' for 55 litres");
Serial.println(" Press 'c' for 51 litres");
Serial.println(" Press 'd' for 45 litres");
delay(4000);
          }
int c=Serial.read();
switch(c)
         {
case 97:{Serial.println(" FILLED 60 Ltrs");
fuel=60;
delay(2000);
break;}
case 98:{Serial.println(" FILLED 55 Ltrs");
fuel=55;
delay(2000);
break;}
case 99:{Serial.println(" FILLED 51 Ltrs");
fuel=50;
delay(2000);
break;}
case 100:{Serial.println(" FILLED 45 Ltrs");
fuel=45;
delay(2000);
break;}

        }
     }
   }
}
void destination()
{

if(d==0)
  {
Serial.println("Destination Reached");
while(1){}   
}
else
  {
Serial.println("Keep Driving");

  }
}
void setup()
{
Serial.begin(9600);
distance();
milage();
}
void loop()
{ 
if(fuel>45)
  {
spd();
  }
else
  {
refil();
  }

d-=100;
Serial.println("Distance Remaining to Destination:");
Serial.println(d);
milage();
destination(); }
