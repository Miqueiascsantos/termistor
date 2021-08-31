long tempoinicial = 0; // VARIAVEL GLOBAL DE TEMPO INICIAL.
int flagledacesso = 0; // VARIAVEL GLOBAL DE FLAG BOTÃO ACESSO.
float valorlido;
float temperatura;
int i = 0;

void setup() 
{
  
  pinMode(9, INPUT_PULLUP); //START
  pinMode(8, INPUT_PULLUP); //STOP
  pinMode(10, OUTPUT); //LED VERDE
  pinMode(11, OUTPUT); //LED AZUL

  digitalWrite(11, HIGH); // LED AZUL BOTÃO Ñ PRESSIONADO.
  digitalWrite(10, LOW); // LED AMARELO BOTÃO PRESSIONADO.

  Serial.begin(9600);
}

  void termistor()
  {
    for(i=0; i>=100; i++)
    {
      valorlido = analogRead(A2);
      Serial.print("Leitura do pino A2= ");
      Serial.println(valorlido);
    
      temperatura = (valorlido * 0.2027) - 87;
      Serial.print("Temperatura aproximada em Celsius = ");
      Serial.println(temperatura);
      Serial.println("");
    }
  }

  void estado_original()
  {
      digitalWrite(11, HIGH); // LED AZUL BOTÃO Ñ PRESSIONADO.
      digitalWrite(10, LOW); // LED AMARELO BOTÃO PRESSIONADO.
      flagledacesso = 0; //ZERA A BANDEIRA;
  }

  void estado_acionado()
  {
    digitalWrite(11, LOW); // DESLIGA LED AZUL.
    digitalWrite(10, HIGH); // ACENDE LED VERDE.
    termistor();
    tempoinicial = millis(); // MARCA O TEMPO NAQUELE INSTANTE.
    flagledacesso = 1; // DIZ QUE O BOTÃO FOI PRESSIONADO.
  }

void loop() 
{
  int bstart = digitalRead(9); //LÊ O ESTADO NO PINO 9.
  
  if(bstart == LOW) // AO PRESSIONAR O BOTÃO;
  {
    estado_acionado(); // invoca a função.
  }

  if(flagledacesso == 1) // VERIFICA SE O BOTÃO FOI PRESSIONADO.
  {
    long tempopassado = millis() - tempoinicial; // VERIFICA A QUANTIDADE DE TEMPO QUE PASSOU.
    int bstop = digitalRead(8);
    
    if(bstop == LOW) // BOTÃO DE PARADA IMEDIATA, SEM NECESSIDADE DE TEMPO!
    {
      estado_original();
    }
    else if(tempopassado >= 10000 || temperatura >= 30) // SE TEMPO MAIOR QUE 10S VOLTA AO ESTADO ORIGINAL.
    {
      estado_original();
    } 
  }
}
