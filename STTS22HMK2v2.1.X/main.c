/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F46K20
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"

/*
                         Main application
 */
void main(void){
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    #define STTS22H_ADDR 0x3F       // wenn Addr gleich GND
    
    #define WHOAMI          0x01
    #define TEMP_H_LIMIT    0x02
    #define TEMP_L_LIMIT    0x03
    #define CTRL            0x04
    #define STATUS          0x05
    #define TEMP_L_OUT      0x06
    #define TEMP_H_OUT      0x07
    #define SOFTWARE_RESET  0x0c
                       
    uint16_t temperature;
    uint8_t temperature_low;
    uint8_t Data;
    float temperatureAnz;
    
    I2C_Write1ByteRegister(STTS22H_ADDR,SOFTWARE_RESET,0x30);               // schreibt "0x30" in "SOFTWARE_RESET"
    
    __delay_ms(500);                                                        // warte 500ms
    
    while (1){                                                              // Endlosscheife
        I2C_Write1ByteRegister(STTS22H_ADDR,SOFTWARE_RESET,0x02);           // schreibt "0x02" in "SOFTWARE_RESET"
        I2C_Write1ByteRegister(STTS22H_ADDR,SOFTWARE_RESET,0x00);           // schreibt "0x00" in "SOFTWARE_RESET"
        Data = I2C_Read2ByteRegister(STTS22H_ADDR,CTRL);                    // "Data" = inhalt von "CTRL"
        Data = Data + 1;                                                    // "Data" + 1
        I2C_Write1ByteRegister(STTS22H_ADDR,CTRL,Data);                     // schreibt "Data" in "CTRL"
        
        temperature_low = I2C_Read1ByteRegister(STTS22H_ADDR,TEMP_L_OUT);   // "temperature_low" = inhalt von "TEMP_L_OUT"
        temperature =     I2C_Read1ByteRegister(STTS22H_ADDR,TEMP_H_OUT);   // "temperature" = inhalt von "TEMP_H_OUT"
        temperature = (temperature << 8) + temperature_low;                 // "temperature" = 
        
        if((temperature & 0x1000) == 0x1000){                               // wenn "temperature" maskiert mit 0x1000 gleich 0x1000 ist
            temperature = 256 - temperature;                                // "temperature" - 256
            printf("-");                                                    // schreibt "-" an UART
        }                                                                   // 
        
        temperatureAnz = temperature / 100.00;                              // "temperatureAnz" gleich "temperature" geteilt druch 100.0
        
        printf("%4.2f°C\r\n",temperatureAnz);                               // schreibt den Inhalt von "tempDataAnz" an UART
        __delay_ms(500);                                                    // warte 500ms
    }                                                                       // 
}                                                                           // 
/**
 End of File
*/