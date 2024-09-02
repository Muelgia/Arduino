#include <LiquidCrystal_I2C.h>
#define botao 13


LiquidCrystal_I2C lcd_1(33, 16, 2);

int obstaculo1 = 15;
int obstaculo2 = 19;
int obstaculo3 = 23;
bool parar = false;


void setup()
{	
  	//clique no botao 
  	pinMode(13, INPUT);
  	//declara as dimensoes do lcd
    lcd_1.init();
    lcd_1.backlight();

}



void loop()
{	 

  //para o loop
  if (parar != true){  
    delay(200);
    //apaga primeiro pixel
    lcd_1.setCursor(0, 0);	
  	lcd_1.print(" ");
    lcd_1.setCursor(0, 1);	
  	lcd_1.print(" ");
    
    //escreve no letreiro os obstaculos
  	lcd_1.setCursor(obstaculo1, 1);
  	lcd_1.print("o");	
  	lcd_1.print(" ");
    lcd_1.setCursor(obstaculo2, 0);
  	lcd_1.print("o");	
  	lcd_1.print(" ");
    lcd_1.setCursor(obstaculo3, 1);
  	lcd_1.print("o");	
  	lcd_1.print(" ");
	
    //volta o obstaculo para o final do lcd
    if(obstaculo1 == 0){obstaculo1 = 15;}
  	if(obstaculo2 == 0){obstaculo2 = 15;}
    if(obstaculo3 == 0){obstaculo3 = 15;}
    
  	obstaculo1 -= 1;
  	obstaculo2 -= 1;
    obstaculo3 -= 1;
    
    //se o botao estiver pressionado sobe o personagem
    if(digitalRead(botao) == 1)
  	{
        lcd_1.setCursor(2, 1);
  		lcd_1.print(" ");
    	lcd_1.setCursor(2, 0);
  		lcd_1.print("|");
     }
    //se o botao não estiver pressionado desce o personagem
  	else if(digitalRead(botao) == 0){
  		lcd_1.setCursor(2, 1);
  		lcd_1.print("|");
    	lcd_1.setCursor(2, 0);
  		lcd_1.print(" ");
    }
    
    //se o personagem encostar no obstaculo perde
    if((digitalRead(botao) == 0 && obstaculo1 == 2) || 
       (digitalRead(botao) == 1 && obstaculo2 == 2) ||
       (digitalRead(botao) == 0 && obstaculo3 == 2)){
    	
      	lcd_1.setCursor(0, 0);
  		lcd_1.print("      VOCE       ");
    	lcd_1.setCursor(0, 1); 
  		lcd_1.print("     PERDEU!     ");
      	parar = true;   	
}    
} 	 	
}