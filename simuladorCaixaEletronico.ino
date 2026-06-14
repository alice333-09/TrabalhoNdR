#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String usuCadastrado = "";
int senhaCadastrada = 0;
bool temCadastro = false; 
int saldo = 100;
int valor = 0;

void setup() {
  lcd.begin(16, 2); 
  Serial.begin(9600);
  
  lcd.print("Iniciando...");
  Serial.println("Iniciando...");
  delay(1000);
}

void loop() {
	lcd.clear();
	lcd.setCursor(0, 0);
    lcd.print("1-Cadastrar");
    Serial.println("1 - Cadastrar");

    lcd.setCursor(0, 1);
    lcd.print("2-Entrar");
    Serial.println("2 - Entrar");

    while (Serial.available() == 0) {} 
    int opcao = Serial.parseInt();

    switch (opcao) {
    
      case 1:
        lcd.clear();
        lcd.print("Cadastrando...");
        Serial.println("Cadastrando...");
        delay(1000);

        lcd.clear();
        lcd.print("Nome do usuario:");
        Serial.println("Nome do usuario:");
      

        while (Serial.available() == 0) {}
        usuCadastrado = Serial.readString();
        usuCadastrado.trim(); 

        lcd.setCursor(0, 1);
        lcd.print(usuCadastrado);
        Serial.println(usuCadastrado);
        delay(1500);

        lcd.clear();
        lcd.print("Digite a senha:");
        Serial.println("Digite a senha:");


        while (Serial.available() == 0) {}
        senhaCadastrada = Serial.parseInt();

        lcd.setCursor(0, 1);
        lcd.print(senhaCadastrada);
        Serial.println(senhaCadastrada);
        delay(1500);

        temCadastro = true; 

        lcd.clear();
        lcd.print("Sucesso!");
        Serial.println("Cadastrado com sucesso!");
        delay(2000);
        return;
      
   	  case 2: { 
      	if (!temCadastro) {
          lcd.clear();
          lcd.print("Sem cadastros!");
          lcd.setCursor(0, 1);
          lcd.print("Cadastre-se.");
          Serial.println("Erro: Nenhum usuario cadastrado.");
          delay(2000);
          return; 
      	}

        lcd.clear();
        lcd.print("Entrando...");
        Serial.println("Entrando...");
        delay(1000);

        lcd.clear();
        lcd.print("Nome do usuario:");
        Serial.println("Nome do usuario:");

        while (Serial.available() == 0) {}
        String usuLogin = Serial.readString();
        usuLogin.trim();

        lcd.setCursor(0, 1);
        lcd.print(usuLogin);
        Serial.println(usuLogin);
        delay(1500);

        lcd.clear();
        lcd.print("Digite a senha:");
        Serial.println("Digite a senha:");

        while (Serial.available() == 0) {}
        int senhaLogin = Serial.parseInt();

        lcd.setCursor(0, 1);
        lcd.print(senhaLogin);
        Serial.println(senhaLogin);
        delay(1000);

        lcd.clear();
      
        if (usuLogin == usuCadastrado && senhaLogin == senhaCadastrada) {
          lcd.print("Usuario valido");
          lcd.setCursor(0, 1);
          lcd.print("Acesso liberado");
          Serial.println("Login efetuado com sucesso!");
          delay(3000);
          break;
        } else {
          lcd.print("Usuario invalido");
          lcd.setCursor(0, 1);
          lcd.print("Tente novamente");
          Serial.println("Erro: Usuario ou senha incorretos.");
          delay(3000);

        }
        return;
      } 

      default:
        Serial.println("Opcao invalida!");
        lcd.clear();
        lcd.print("Opcao invalida!");
        delay(1500);
        return;
    }

	
  	bool logado = true;
  	while (logado) {
      while(Serial.available() > 0) { Serial.read();}

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1-Saldo");
      Serial.println("1 - Saldo");

      lcd.setCursor(0, 1);
      lcd.print("2-Saque");
      Serial.println("2 - Saque");

      lcd.setCursor(8, 0);
      lcd.print("3-Depo.");
      Serial.println("3 - Deposito");

      lcd.setCursor(8, 1);
      lcd.print("4-Sair");
      Serial.println("4 - Sair");

      while (Serial.available() == 0) {} 
      int opcao1 = Serial.parseInt();

      switch (opcao1) {
          case 1:{
              lcd.setCursor(0, 0);
              lcd.clear();
              lcd.print("Seu saldo e de:");
              Serial.println("Seu saldo e de:");
              lcd.setCursor(0, 1);
              lcd.print(saldo);
              Serial.println(saldo);
              delay(3000);
              break;
          }
          case 2:{
            lcd.setCursor(0, 0);
            lcd.clear();
            lcd.print("Digite o valor:");
            Serial.println("Digite o valor:");

            while (Serial.available() == 0) {} 
            int valor = Serial.parseInt();

            lcd.setCursor(0, 1);
            lcd.print(valor);
            Serial.println(valor);
            delay(2000);

            lcd.clear();
            lcd.print("Em andamento...");
            Serial.println("Em andamento...");
            delay(2000);

            if(saldo > 0 && saldo > valor) {
              bool senhaCorreta = false;
              lcd.clear();
              for (int tentativas = 0; tentativas < 3; tentativas++) {
                
                lcd.print("Digite a senha:");
                Serial.println("Digite a senha:");
                
                while (Serial.available() == 0) {} 
                int senha = Serial.parseInt();
                
                lcd.setCursor(0, 1);
                lcd.print(senha);
                Serial.println(senha);
                delay(2000);

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Em andamento...");
                Serial.println("Em andamento...");
                delay(2000);

                if (senha == senhaCadastrada){
                  	senhaCorreta = true;
                  	break;
                }else{
                    lcd.clear();
                    lcd.print("Senha incorreta");
                    Serial.println("Senha incorreta");
                    delay(2000);
                  	lcd.clear();
                }
               
              }
                
                if(senhaCorreta){
                    saldo = saldo - valor;
                    lcd.clear();
                    lcd.print("saque realizado!");
                    Serial.println("saque realizado!");
                    delay(2000);
                }else{
                	lcd.clear();
                    lcd.print("Saque Cancelado");
                    lcd.setCursor(0, 1);
                    lcd.print("Chances esgotadas");
                    Serial.println("Saque Cancelado: 3 tentativas incorretas.");
                    delay(3000);
                }
              
            }else{
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Saldo negativo");
                lcd.setCursor(0, 1);
                lcd.print("Deposite.");
                Serial.println("Atencao: Saldo insuficiente!");
                delay(2000);
            }
          }
          break;
        case 3:{
          lcd.setCursor(0, 0);
            lcd.clear();
            lcd.print("Digite o valor:");
            Serial.println("Digite o valor:");

            while (Serial.available() == 0) {} 
            int valor = Serial.parseInt();

            lcd.setCursor(0, 1);
            lcd.print(valor);
            Serial.println(valor);
            delay(2000);

            lcd.clear();
            lcd.print("Em andamento...");
            Serial.println("Em andamento...");
            delay(2000);

           
              bool senhaCorreta = false;
              lcd.clear();
              for (int tentativas = 0; tentativas < 3; tentativas++) {
                
                lcd.print("Digite a senha:");
                Serial.println("Digite a senha:");
                
                while (Serial.available() == 0) {} 
                int senha = Serial.parseInt();
                
                lcd.setCursor(0, 1);
                lcd.print(senha);
                Serial.println(senha);
                delay(2000);

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Em andamento...");
                Serial.println("Em andamento...");
                delay(2000);

                if (senha == senhaCadastrada){
                  	senhaCorreta = true;
                  	break;
                }else{
                    lcd.clear();
                    lcd.print("Senha incorreta");
                    Serial.println("Senha incorreta");
                    delay(2000);
                  	lcd.clear();
                }
               
              }
                
                if(senhaCorreta){
                    saldo = saldo + valor;
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Deposito");
                    lcd.setCursor(0, 1);
                    lcd.print("realizado!");
                    Serial.println("deposito realizado com Sucesso!");
                    delay(2000);
                }else{
                	lcd.clear();
                    lcd.print("deposito negado");
                    lcd.setCursor(0, 1);
                    lcd.print("Chances esgotadas");
                    Serial.println("depósito Cancelado: 3 tentativas incorretas.");
                    delay(3000);
                }
          }
          break;
         

         case 4:{
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Sessao encerrada");
              Serial.println("Sessão encerrada");
              delay(1500);
           return;
          }
      default:
            Serial.println("Opcao invalida!");
            lcd.clear();
            lcd.print("Opcao invalida!");
            delay(1500);
            break;
 
        }
      }
}