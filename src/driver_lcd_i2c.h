#ifndef DRIVER_LCD_I2C_H
#define DRIVER_LCD_I2C_H

#include "LiquidCrystal_I2C.h"

class DriverLCD_I2C {
  private:
    LiquidCrystal_I2C lcd;  // Instância da classe LiquidCrystal_I2C para encapsular as funções do LCD.
    
    uint8_t _lcdAddr;  // Endereço I2C do display.
    uint8_t _lcdCols;  // Número de colunas do display.
    uint8_t _lcdRows;  // Número de linhas do display.

    uint8_t _cursorCol; // Coluna atual do cursor.
    uint8_t _cursorRow; // Linha atual do cursor.


  public:
    // Enum class para os modos do LCD
    enum class Modo{
        Manual,
        Automatico,
        Ensaio
    };
    // Construtor que inicializa o LCD com o endereço I2C, número de colunas e linhas
    DriverLCD_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

    // Destruidor
    ~DriverLCD_I2C();

    // Métodos getter para obter a posição do cursor
    uint8_t getCursorCol() const;
    uint8_t getCursorRow() const;

    // Métodos setter para definir a posição do cursor
    void setCursorCol(uint8_t col);
    void setCursorRow(uint8_t row);

    //Metodos Gerais
    void postAngle(float angle);
    void postTofRight(float distance);
    void postTofLeft(float distance);
    void postAccelerometer(float acceleration);
    void postSetPoint(float angle);
    void postOperatingMode(Modo modo);
    void postConsumption(float voltage, float current);

    // Método para limpar o LCD
    void clear();

};

#endif // DRIVER_LCD_I2C_H
