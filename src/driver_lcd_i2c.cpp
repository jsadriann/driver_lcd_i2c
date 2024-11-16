#include "driver_lcd_i2c.h"

// Construtor
DriverLCD_I2C::DriverLCD_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
  : lcd(lcd_Addr, lcd_cols, lcd_rows), _lcdAddr(lcd_Addr), _lcdCols(lcd_cols), _lcdRows(lcd_rows) {
    // Inicializa o LCD com o endereço I2C, número de colunas e linhas
    lcd.init();  // Inicializa o LCD com a função init() que você especificou
    //lcd.clear();  // Limpa o LCD logo após inicializar
    
    // Inicializa as variáveis de posição do cursor
    _cursorCol = 0;  // Coluna inicial do cursor
    _cursorRow = 0;  // Linha inicial do cursor
    
    // Posiciona o cursor no início
    lcd.setCursor(_cursorCol, _cursorRow);
}

// Destruidor
DriverLCD_I2C::~DriverLCD_I2C() {
}

// Método para exibir o ângulo no LCD
void DriverLCD_I2C::postAngle(float angle) {
    // Cria a string "Angle: " mais o valor do ângulo
    char angleStr[10];  // Buffer para armazenar a string convertida

    // Usando sprintf para formatar o float em string com 2 casas decimais
    sprintf(angleStr, "%.2f", angle);  // Converte o valor float para string com 2 casas decimais

    String fullMessage = String("Angle: ") + angleStr;  // Junta "Angle: " com o valor do ângulo

    // Verifica se a mensagem cabe na linha
    if (fullMessage.length() > _lcdCols) {
        // Caso não caiba, centraliza "Angle: " na primeira linha
        ///lcd.clear();
        int angleMessageLength = 8;  // "Angle: " tem 8 caracteres
        int angleStrLength = strlen(angleStr);
        
        // Centraliza "Angle: "
        lcd.setCursor((_lcdCols - angleMessageLength) / 2, _cursorRow);  // Calcula a posição para centralizar "Angle: "
        lcd.print("Angle: ");
        
        // Centraliza o valor do ângulo na segunda linha
        _cursorRow = 1;  // Muda para a linha 1
        lcd.setCursor((_lcdCols - angleStrLength) / 2, _cursorRow);  // Centraliza o valor do ângulo
        lcd.print(angleStr);  // Exibe o valor do ângulo
    } else {
        // Caso a mensagem caiba na linha, imprime tudo na mesma linha
        //lcd.clear();  // Limpa a tela antes de imprimir
        lcd.setCursor(0, 0);  // Posiciona o cursor na linha 0, coluna 0
        lcd.print("Angle: ");
        lcd.print(angleStr);  // Exibe o valor do ângulo
        
        // Atualiza o cursor para a próxima linha após imprimir
        _cursorCol = 0;
        _cursorRow = 1;
        lcd.setCursor(_cursorCol, _cursorRow);  // Atualiza o cursor no LCD
    }
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
        lcd.setCursor(_cursorCol, _cursorRow);  // Atualiza a posição do cursor no LCD
    }
}

// Setter para a linha do cursor
void DriverLCD_I2C::setCursorRow(uint8_t row) {
    if (row < _lcdRows) {  // Verifica se a linha está dentro dos limites
        _cursorRow = row;  // Atualiza a linha
        lcd.setCursor(_cursorCol, _cursorRow);  // Atualiza a posição do cursor no LCD
    }
}