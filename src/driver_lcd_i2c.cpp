#include "driver_lcd_i2c.h"

// Construtor
DriverLCD_I2C::DriverLCD_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
  : lcd(lcd_Addr, lcd_cols, lcd_rows), _lcdAddr(lcd_Addr), _lcdCols(lcd_cols), _lcdRows(lcd_rows) {
    // Inicializa o LCD com o endereço I2C, número de colunas e linhas
    lcd.init();  // Inicializa o LCD com a função init() que você especificou
    lcd.clear();  // Limpa o LCD logo após inicializar
    
    // Inicializa as variáveis de posição do cursor
    _cursorCol = 0;  // Coluna inicial do cursor
    _cursorRow = 0;  // Linha inicial do cursor
    
    // Posiciona o cursor no início
    lcd.setCursor(_cursorCol, _cursorRow);
}

// Destruidor
DriverLCD_I2C::~DriverLCD_I2C() {
}

// Getter para a coluna do cursor
uint8_t DriverLCD_I2C::getCursorCol() const {
    return _cursorCol;  // Retorna a coluna atual do cursor
}

// Getter para a linha do cursor
uint8_t DriverLCD_I2C::getCursorRow() const {
    return _cursorRow;  // Retorna a linha atual do cursor
}

// Setter para a coluna do cursor
void DriverLCD_I2C::setCursorCol(uint8_t col) {
    if (col < _lcdCols) {  // Verifica se a coluna está dentro dos limites
        _cursorCol = col;  // Atualiza a coluna
    }
}

// Setter para a linha do cursor
void DriverLCD_I2C::setCursorRow(uint8_t row) {
    if (row < _lcdRows) {  // Verifica se a linha está dentro dos limites
        _cursorRow = row;  // Atualiza a linha
    }
}

// Método para exibir o ângulo no LCD
void DriverLCD_I2C::postAngle(float angle) {
    // Cria a string "Angle: " mais o valor do ângulo
    char angleStr[10];  // Buffer para armazenar a string convertida

    // Usando sprintf para formatar o float em string com 2 casas decimais
    sprintf(angleStr, "%.2f", angle);  // Converte o valor float para string com 2 casas decimais

    String fullMessage = String("Angle: ") + angleStr;  // Junta "Angle: " com o valor do ângulo

    // Verifica se a mensagem cabe na linha
    if (fullMessage.length() > (_lcdCols - _cursorCol)) {
        // Caso não caiba, centraliza "Angle: " na primeira linha
        clear();
        int angleMessageLength = 7;  // "Angle:" tem 7 caracteres
        int angleStrLength = strlen(angleStr);
        
        // Centraliza "Angle: "
        lcd.setCursor((_lcdCols - angleMessageLength) / 2, _cursorRow);  // Calcula a posição para centralizar "Angle: "
        lcd.print("Angle:");
        _cursorRow++;
        // Centraliza o valor do ângulo na segunda linha
        lcd.setCursor((_lcdCols - angleStrLength) / 2, _cursorRow);  // Centraliza o valor do ângulo
        lcd.print(angleStr);  // Exibe o valor do ângulo
	_cursorRow++;
	_cursorCol = 0;
    } else {
        // Caso a mensagem caiba na linha, imprime tudo na mesma linha
        lcd.setCursor(_cursorCol, _cursorRow);  // Posiciona o cursor
        lcd.print("Angle: ");
        lcd.print(angleStr);  // Exibe o valor do ângulo
        
        // Atualiza o cursor para a próxima linha após imprimir
        _cursorCol = 0;
        _cursorRow++;
        lcd.setCursor(_cursorCol, _cursorRow);  // Atualiza o cursor no LCD
	_cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
    }
}

void DriverLCD_I2C::postTofRight(float distance) {
    // Cria a string "TOF Right: " mais o valor da distância
    char distanceStr[10];  // Buffer para armazenar a string convertida

    // Usando sprintf para formatar o float em string com 2 casas decimais
    sprintf(distanceStr, "%.2f", distance);  // Converte o valor float para string com 2 casas decimais

    String fullMessage = String("TOF Right: ") + distanceStr;  // Junta "TOF Right: " com o valor da distância

    // Verifica se a mensagem cabe na linha
    if (fullMessage.length() > (_lcdCols - _cursorCol)) {
	clear();  // Limpa a tela antes de imprimir
        // Caso não caiba, centraliza "TOF Right:" na primeira linha
        int tofMessageLength = 11;  // "TOF Right:" tem 11 caracteres
        int distanceStrLength = strlen(distanceStr);
        
        // Centraliza "TOF Right:"
        lcd.setCursor((_lcdCols - tofMessageLength) / 2, 0);  // Calcula a posição para centralizar "TOF Right:"
        lcd.print("TOF Right:");
        _cursorRow++;
        // Centraliza o valor da distância na segunda linha
        lcd.setCursor((_lcdCols - distanceStrLength) / 2, 1);  // Centraliza o valor da distância
        lcd.print(distanceStr);  // Exibe o valor da distância
	_cursorRow++;
        _cursorCol = 0;
    } else {
	// Caso a mensagem caiba na linha, imprime tudo na mesma linha
        lcd.setCursor(_cursorCol, _cursorRow);  // Posiciona o cursor
        lcd.print("TOF Right: ");
        lcd.print(distanceStr);  // Exibe o valor da distância
        // Atualiza o cursor interno
        _cursorCol = 0;
	_cursorRow++;
        _cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
    }
}

void DriverLCD_I2C::postTofLeft(float distance) {
    // Cria a string "TOF Left: " mais o valor da distancia
    char distanceStr[10];  // Buffer para armazenar a string convertida

    // Usando sprintf para formatar o float em string com 2 casas decimais
    sprintf(distanceStr, "%.2f", distance);  // Converte o valor float para string com 2 casas decimais

    String fullMessage = String("TOF Left: ") + distanceStr;  // Junta "TOF Left: " com o valor da distancia

    // Verifica se a mensagem cabe na linha
    if (fullMessage.length() > (_lcdCols - _cursorCol)) {
	clear();  // Limpa a tela antes de imprimir
        // Caso não caiba, centraliza "TOF Left:" na primeira linha
        int tofMessageLength = 10;  // "TOF Left:" tem 10 caracteres
        int distanceStrLength = strlen(distanceStr);
        // Centraliza "TOF Left:"
        lcd.setCursor((_lcdCols - tofMessageLength) / 2, _cursorRow);  // Calcula a posição para centralizar "TOF Left:"
        lcd.print("TOF Left:");
        _cursorRow++;
        // Centraliza o valor da distância na segunda linha
        lcd.setCursor((_lcdCols - distanceStrLength) / 2, _cursorRow);  // Centraliza o valor da distância
        lcd.print(distanceStr);  // Exibe o valor da distância
        // Atualiza o cursor interno
        _cursorRow++;
        _cursorCol = 0;
    } else {
	// Caso a mensagem caiba na linha, imprime tudo na mesma linha
        lcd.setCursor(_cursorCol, _cursorRow);  // Posiciona o cursor
        lcd.print("TOF Left: ");
        lcd.print(distanceStr);  // Exibe o valor da distância
        
        // Atualiza o cursor interno
        _cursorCol = 0;
	_cursorRow++;
        _cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
    }
}

void DriverLCD_I2C::postAccelerometer(float acceleration) {
    // Cria a string "Acceleration: " mais o valor da aceleração
    char accelerationStr[10];  // Buffer para armazenar a string convertida

    // Usando sprintf para formatar o float em string com 2 casas decimais
    sprintf(accelerationStr, "%.2f", acceleration);  // Converte o valor float para string com 2 casas decimais

    String fullMessage = String("TOF Right: ") + accelerationStr;  // Junta "Acceleration: " com o valor da aceleração

    // Verifica se a mensagem cabe na linha
    if (fullMessage.length() > (_lcdCols - _cursorCol)) {
	clear();  // Limpa a tela antes de imprimir
        // Caso não caiba, centraliza "Acceleration:" na primeira linha
        int tofMessageLength = 14;  // "Acceleration:" tem 14 caracteres
        int accelerationStrLength = strlen(accelerationStr);
        // Centraliza "Acceleration:"
        lcd.setCursor((_lcdCols - tofMessageLength) / 2, _cursorRow);  // Calcula a posição para centralizar "Acceleration:"
        lcd.print("Acceleration:");
        _cursorRow++;
        // Centraliza o valor da distância na segunda linha
        lcd.setCursor((_lcdCols - accelerationStrLength) / 2, _cursorRow);  // Centraliza o valor da aceleraçã
        lcd.print(accelerationStr);  // Exibe o valor da aceleração
        // Atualiza o cursor interno
        _cursorRow++;
        _cursorCol = 0;
    } else {
	// Caso a mensagem caiba na linha, imprime tudo na mesma linha
        lcd.setCursor(_cursorCol, _cursorRow);  // Posiciona o cursor
        lcd.print("Acceleration: ");
        lcd.print(accelerationStr);  // Exibe o valor da aceleração
        
        // Atualiza o cursor interno
        _cursorCol = 0;
	_cursorRow++;
        _cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
    }
}

void DriverLCD_I2C::postSetPoint(float angle) {
    // Cria a string "SetPoint: " mais o valor da angulação
    char setPointStr[10];  // Buffer para armazenar a string convertida

    // Usando sprintf para formatar o float em string com 2 casas decimais
    sprintf(setPointStr, "%.2f", angle);  // Converte o valor float para string com 2 casas decimais

    String fullMessage = String("SetPoint: ") + setPointStr;  // Junta "SetPoint: " com o valor da angulação

    // Verifica se a mensagem cabe na linha
    if (fullMessage.length() > (_lcdCols - _cursorCol)) {
	clear();  // Limpa a tela antes de imprimir
        // Caso não caiba, centraliza "SetPoint:" na primeira linha
        int tofMessageLength = 10;  // "SetPoint:" tem 10 caracteres
        int setPointStrLength = strlen(setPointStr);
        // Centraliza "SetPoint:"
        lcd.setCursor((_lcdCols - tofMessageLength) / 2, _cursorRow);  // Calcula a posição para centralizar "SetPoint:"
        lcd.print("SetPoint:");
        _cursorRow++;
        // Centraliza o valor da angulação na segunda linha
        lcd.setCursor((_lcdCols - setPointStrLength) / 2, _cursorRow);  // Centraliza o valor da angulação
        lcd.print(setPointStr);  // Exibe o valor da angulação
        // Atualiza o cursor interno
        _cursorRow++;
        _cursorCol = 0;
    } else {
	// Caso a mensagem caiba na linha, imprime tudo na mesma linha
        lcd.setCursor(_cursorCol, _cursorRow);  // Posiciona o cursor
        lcd.print("SetPoint: ");
        lcd.print(setPointStr);  // Exibe o valor da angulação
        
        // Atualiza o cursor interno
        _cursorCol = 0;
	_cursorRow++;
        _cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
    }
}

void DriverLCD_I2C::postOperatingMode(Modo modo) {
    // Declara as strings para os modos
    const char* modeLine1 = nullptr;
    const char* modeLine2 = nullptr;

    // Determina as mensagens a serem exibidas com base no modo
    switch (modo) {
        case Modo::Manual:
            modeLine1 = "MANUAL";
            modeLine2 = "MODE";
            break;
        case Modo::Automatico:
            modeLine1 = "AUTOMATIC";
            modeLine2 = "MODE";
            break;
        case Modo::Ensaio:
            modeLine1 = "REHEARSAL";
            modeLine2 = "MODE";
            break;
    }

    // Centraliza e imprime a primeira linha
    lcd.setCursor((_lcdCols - strlen(modeLine1)) / 2, _cursorRow);
    lcd.print(modeLine1);
    _cursorRow++;
    // Centraliza e imprime a segunda linha
    lcd.setCursor((_lcdCols - strlen(modeLine2)) / 2, _cursorRow);
    lcd.print(modeLine2);

    // Atualiza o cursor interno
    _cursorCol = 0;
    _cursorRow++;
    _cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
}

void DriverLCD_I2C::postConsumption(float voltage, float current, const char* voltageUnit, const char* currentUnit) {
    // Imprime "Consumption:" centralizado na primeira linha
    const char* title = "Consumption:";
    lcd.setCursor((_lcdCols - strlen(title)) / 2, _cursorRow);  // Configura o cursor na linha 0
    lcd.print(title);  // Imprime o título
    _cursorRow++;

    // Formata os valores de voltagem e corrente com 3 casas decimais inicialmente
    char voltageStr[10], currentStr[10];
    sprintf(voltageStr, "%.3f", voltage);  // Converte a voltagem para string com 3 casas decimais
    sprintf(currentStr, "%.3f", current);  // Converte a corrente para string com 3 casas decimais

    // Monta a linha de saída inicial
    String line2 = String(voltageStr) + voltageUnit + " " + currentStr + currentUnit;

    // Verifica se a linha cabe no LCD
    if (line2.length() > _lcdCols) {
        // Reduz para 2 casas decimais
        sprintf(voltageStr, "%.2f", voltage);
        sprintf(currentStr, "%.2f", current);
        // Atualiza a linha com valores reduzidos
        line2 = String(voltageStr) + voltageUnit + " " + currentStr + currentUnit;
    }

    if (line2.length() > _lcdCols) {
        line2 = line2.substring(0, _lcdCols);  // Trunca caso necessario
    }

    // Centraliza a segunda linha
    lcd.setCursor((_lcdCols - line2.length()) / 2, _cursorRow);  // Configura o cursor
    lcd.print(line2);

    // Atualiza o cursor interno
    _cursorCol = 0;
    _cursorRow++;
    _cursorRow = (_cursorRow >= _lcdRows) ? 0 : _cursorRow;
}

void DriverLCD_I2C::dashboardLightOn(){
    lcd.noBacklight();
}

void DriverLCD_I2C::dashboardLightOff(){
    lcd.backlight();
}

void DriverLCD_I2C::clear(){
    lcd.clear();
    _cursorRow = 0;
    _cursorCol = 0;
}
void DriverLCD_I2C::clearLine(uint8_t line) {
    // Verifica se a linha está dentro do limite do LCD
    if (line >= _lcdRows) return;

    // Move o cursor para o início da linha desejada
    lcd.setCursor(0, line);
    _cursorRow = line;
    _cursorCol = 0;
    // Sobrescreve a linha com espaços
    for (uint8_t i = 0; i < _lcdCols; i++) {
        lcd.print(" ");
    }

    // atualiza o cursor
    lcd.setCursor(_cursorCol , _cursorRow);
}