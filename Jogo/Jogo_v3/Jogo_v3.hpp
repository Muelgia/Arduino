#include <LiquidCrystal_I2C.h>
#define botao 13
#define potenciometro A0
#define buzzer 12
#define TRIGGER 11
#define ECHO 10

LiquidCrystal_I2C lcd_1(33, 16, 2);


int obstaculo1 = 15;
int obstaculo2 = 19;
int obstaculo3 = 23;
int pontuacao = 0;
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
	
  //reinicia o jogo
  if(digitalRead(botao) == 1 && parar == true){
    
    //reseta todas as informacoes do game
    parar = false;
    pontuacao = 0;
   	lcd_1.clear();
    obstaculo1 = 15;
	obstaculo2 = 19;
	obstaculo3 = 23;
      	
  } 	
 
  //para o loop
  if (parar != true){  
    
    //dificuldade do jogo de acordo com o valor do potenciometro
    int valorPotenciometro = analogRead(potenciometro);
    int dificuldade = map(valorPotenciometro, 0 ,1023, 200, 500);
    
    delay(dificuldade);
    
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
    

    //se o personagem encostar no obstaculo perde
    if((digitalRead(botao) == 0 && obstaculo1 == 2) || 
       (digitalRead(botao) == 1 && obstaculo2 == 2) ||
       (digitalRead(botao) == 0 && obstaculo3 == 2)){
    	
      	
      	tone(buzzer, 349, 200);
      	
      	//mensagem de derrota
      	lcd_1.clear();
      	lcd_1.setCursor(0, 0);
  		lcd_1.print("      VOCE       ");
      	
  		
      	//musica de derrota
    	
    	delay(200);
    	tone(buzzer, 329, 200);
  		delay(200);
    	tone(buzzer, 293, 200);
  		delay(200);
  		tone(buzzer, 261, 2000); 
      	
      
      	//continuacao da mensagem de derrota
    	lcd_1.setCursor(0, 1); 
  		lcd_1.print("     PERDEU!     ");
      	parar = true;
      	
      	delay(500);
      	noTone(buzzer);
      
      	delay(3000);
      	lcd_1.clear();  
      
        //imprime a pontacao
        lcd_1.setCursor(0, 0);
  		lcd_1.print("     PONTOS:       ");
    	lcd_1.setCursor(7, 1); 
  		lcd_1.print(pontuacao);
      	
  		
    }
     
    // aumenta a pontuacao
    if(obstaculo1 == 1 || obstaculo2 == 1 || obstaculo3 == 1){  	
      	
    	pontuacao += 1;	 
	
    }    
  } 	 	
}
