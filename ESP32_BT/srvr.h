/**
  ******************************************************************************
  * @file    srvr.h
  * @author  Waveshare Team
  * @version V2.0.0
  * @date    10-August-2018
  * @brief   ESP8266 WiFi server.
  *          This file provides firmware functions:
  *           + Sending web page of the tool to a client's browser
  *           + Uploading images from client part by part
  *
  ******************************************************************************
  */ 

/* Library includes ----------------------------------------------------------*/
#include <BluetoothSerial.h>

bool Srvr_btIsOn;// It's true when bluetooth is on
bool Srvr_btConn;// It's true when bluetooth has connected client 
// int  Srvr_msgPos;// Position in buffer from where data is expected
int  Srvr_length;// Length of loaded data

/* Client ---------------------------------------------------------------------*/
BluetoothSerial Srvr_btClient; // Bluetooth client 

/* Avaialble bytes in a stream ------------------------------------------------*/
int Srvr_available()
{
    return Srvr_btIsOn ? Srvr_btClient.available() : false;
}

void Srvr_write(const char*value)
{
    // Write data to bluetooth
    if (Srvr_btIsOn) Srvr_btClient.write((const uint8_t*)value, strlen(value));
}

int Srvr_read()
{
    return Srvr_btIsOn ? Srvr_btClient.read() : -1;
}

void Srvr_flush()
{
    // Clear Bluetooth's stream
    if (Srvr_btIsOn) Srvr_btClient.flush();  
}

/* Project includes ----------------------------------------------------------*/
#include "buff.h"       // POST request data accumulator
#include "epd.h"        // e-Paper driver

bool Srvr_btSetup()
{
    // Name shown in bluetooth device list of App part (PC or smartphone)
    String devName("ESP32-EPD");

    // Turning on
    Srvr_btIsOn = Srvr_btClient.begin(devName);

    // Show the connection result
    if (Srvr_btIsOn) Serial.println("Bluetooth is on");
    else Serial.println("Bluetooth is off");

    // There is no connection yet
    Srvr_btConn = false;

    // Return the connection result
    return Srvr_btIsOn;
}

/* The server state observation loop -------------------------------------------*/
bool Srvr_loop()
{
    // Bluetooh connection checking
    if (!Srvr_btIsOn) return false;

    // Show and update the state if it was changed
    if (Srvr_btConn != Srvr_btClient.hasClient())
    {
        Serial.print("Bluetooth status:");
        Srvr_btConn = !Srvr_btConn;
        if(Srvr_btConn)
            Serial.println("connected");
        else
            Serial.println("disconnected"); 
    }

    // Exit if there is no bluetooth connection
    if (!Srvr_btConn) return false; 

    // Waiting the client is ready to send data
    while(!Srvr_btClient.available()) 
    {
        delay(1);
    }

    // Set buffer's index to zero
    // It means the buffer is empty initially
    Buff_msgIndex = 0;

    // While the stream of 'client' has some data do...
    while (Srvr_available())
    {
        // Read a character from 'client'
        int q = Srvr_read();

        // Save it in the buffer and increment its index
        Buff_message[Buff_msgIndex++] = (byte)q;
        Serial.printf("0x%x ,",(byte)q);
        if(Buff_msgIndex % 16 == 0)
            Serial.println();
    }
    Serial.println();

    // Initialization
    if (Buff_message[0] == 'I')
    {
        Srvr_length = 0;

        // Getting of e-Paper's type
        EPD_dispIndex = Buff_message[1];

        // Print log message: initialization of e-Paper (e-Paper's type)
        Serial.printf("EPD %s", EPD_dispMass[EPD_dispIndex].title);


        // Initialization
        EPD_dispInit();

        Buff_msgIndex = 0;
        Srvr_flush();
    }

    // Loading of pixels' data
    else if (Buff_message[0] == 'L')
    {
        // Print log message: image loading
        Serial.print("LOAD");
        int dataSize = Buff_getWord(1);
        Srvr_length += dataSize;
                
        if ((Buff_msgIndex < dataSize) || Srvr_length != Buff_getN3(3))
        {
            Buff_msgIndex = 0;
            Srvr_flush();

            Serial.println(" - Failed.");
            Srvr_write("Error!");
            return true;
        }
       
        // Load data into the e-Paper 
        // if there is loading function for current channel (black or red)
        if (EPD_dispLoad != 0) EPD_dispLoad();     

        Buff_msgIndex = 0;
        Srvr_flush();
    }

    // Initialize next channel
    else if (Buff_message[0] == 'N')
    {
        // Print log message: next data channel
        Serial.println("NEXT");

        // Instruction code for for writting data into 
        // e-Paper's memory
        int code = EPD_dispMass[EPD_dispIndex].next;
        if(EPD_dispIndex == 34)
        {
            if(flag == 0)
                code = 0x26;
            else
                code = 0x13;
        }

        // e-Paper '2.7' (index 8) needs inverting of image data bits
        EPD_invert = (EPD_dispIndex == 8);

        // If the instruction code isn't '-1', then...
        if (code != -1)
        {
            // Print log message: instruction code
            Serial.printf(" %d", code);

            // Do the selection of the next data channel
            EPD_SendCommand(code);
            delay(2);
        }

        // Setup the function for loading choosen channel's data
        EPD_dispLoad = EPD_dispMass[EPD_dispIndex].chRd;

        Buff_msgIndex = 0;
        Srvr_flush();
    }

    // Show loaded picture
    else if (Buff_message[0] == 'S')
    {
        EPD_dispMass[EPD_dispIndex].show();
                
        Buff_msgIndex = 0;
        Srvr_flush();

        //Print log message: show
        Serial.println("SHOW");
    }

    // Send message "Ok!" to continue
    Srvr_write("[SERVER] Ready.");
    delay(1);

    // Print log message: the end of request processing
    return true;
}
