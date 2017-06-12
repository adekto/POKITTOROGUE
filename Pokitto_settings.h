/**************************************************************************/
/*!
    @file     Pokitto_settings.h
    @author   Jonne Valola

    @section LICENSE

    Pokitto development stage library
    Software License Agreement

    Copyright (c) 2015, Jonne Valola ("Author")
    All rights reserved.

    This library is intended solely for the purpose of Pokitto development.

    Redistribution and use in source and binary forms, with or without
    modification requires written permission from Author.
*/
/**************************************************************************/

#ifndef POKITTO_SETTINGS_H
#define POKITTO_SETTINGS_H

#ifdef PROJ_BOARDREV
 #define POK_BOARDREV PROJ_BOARDREV // which revision of Pokitto board
#else
 #define POK_BOARDREV 2 // default is boardrev 2 (the 4-layer board)
#endif

/** LOGO */
#ifdef PROJ_STARTUPLOGO
 #define POK_DISPLAYLOGO  PROJ_STARTUPLOGO// if enabled, show logo at start
#else
 #define POK_DISPLAYLOGO  1
#endif

#define POK_ENABLE_REFRESHWITHWAIT 0 // choose whether waiting in application refreshes display or not
#define POK_ENABLE_FPSCOUNTER 0 // turn off to save some cpu
#define POK_ENABLE_SD 1 // Define true to include SD library

#ifndef PROJ_ENABLESOUND
    #define POK_ENABLE_SOUND 1
#else
    #define POK_ENABLE_SOUND PROJ_ENABLE_SOUND
#endif

#ifndef PROJ_GBSOUND
    #define POK_GBSOUND 0
#else
    #define POK_GBSOUND PROJ_GBSOUND
#endif


#ifndef PROJ_STREAMING_MUSIC
    #define POK_STREAMING_MUSIC 1 // Define true to stream music from SD
#else
    #define POK_STREAMING_MUSIC PROJ_STREAMING_MUSIC
#endif // PROJ_STREAMING_MUSIC

#ifndef PROJ_ENABLE_SYNTH
    #define POK_ENABLE_SYNTH 0
#else
    #define POK_ENABLE_SYNTH PROJ_ENABLE_SYNTH
#endif // PROJ_ENABLE_SYNTH


/** CONSOLE **/
#define POK_USE_CONSOLE 0 //if debugging console is available or not
#define POK_CONSOLE_VISIBLE_AT_STARTUP 1 // whaddaya think ?
#define POK_CONSOLE_INTERVAL 1000 // interval in ms how often console is drawn
#if POK_USE_CONSOLE > 0 // this prevents trying to log messages if console is disabled
    #define POK_CONSOLE_LOG_BUTTONS 0 // if console logs keypresses
    #define POK_CONSOLE_LOG_COLLISIONS 1 // if console logs collisions
#endif // POK_USE_CONSOLE
#define CONSOLEBUFSIZE 20


/** PROJECT LIBRARY TYPE **/
#if PROJ_GAMEBUINO > 0
    #define POK_GAMEBUINO_SUPPORT PROJ_GAMEBUINO // Define true to support Gamebuino library calls
    #define PROJ_SCREENMODE MODE_GAMEBUINO_16COLOR
    #define POK_STRETCH 1
    #define PICOPALETTE 0
    #define POK_COLORDEPTH 4
#else
    #if PROJ_ARDUBOY > 0
        #define POK_ARDUBOY_SUPPORT PROJ_ARDUBOY // Define true to support Arduboy library calls
        #define PROJ_SCREENMODE MODE_ARDUBOY_16COLOR
        #define POK_COLORDEPTH 1
        #define POK_STRETCH 1
        #define POK_FPS 20
        #define PICOPALETTE 0
    #else
        #if PROJ_RBOY > 0
            #define PROJ_SCREENMODE MODE_GAMEBUINO_16COLOR
            #define POK_COLORDEPTH 1
            #define POK_STRETCH 0
            #define POK_FPS 40
            #define PICOPALETTE 0
        #else
            #if PROJ_GAMEBOY > 0
            #define PROJ_SCREENMODE MODE_GAMEBOY
            #define POK_COLORDEPTH 2
            #define POK_STRETCH 0
            #define POK_FPS 6
            #define PICOPALETTE 0
            #else
                #define POK_GAMEBUINO_SUPPORT 0
                #define POK_GAMEBOY_SUPPORT 0
                #define POK_ARDUBOY_SUPPORT 0
                #define PICOPALETTE 0
                #define POK_COLORDEPTH 4
            #endif // PROJ_GAMEBOY
        #endif // PROJ_RBOY
    #endif // PROJ_ARDUBOY
#endif // PROJ_GAMEBUINO


/** SCREEN MODES TABLE -- DO NOT CHANGE THESE **/

#define POK_LCD_W 220 //<- do not change !!
#define POK_LCD_H 176 //<- do not change !!

#define MODE_NOBUFFER               0   //Size: 0
#define BUFSIZE_NOBUFFER            0
#define MODE_HI_4COLOR              1   //Size: 9680
#define BUFSIZE_HI_4                9680
#define MODE_FAST_16COLOR           2   //Size: 4840
#define BUFSIZE_FAST_16             4840
#define MODE_256_COLOR              3
#define BUFSIZE_MODE_3              4176 // 72 x 58
#define MODE_GAMEBUINO_16COLOR      4   //Size: 2016
#define BUFSIZE_GAMEBUINO_16        2016
#define MODE_ARDUBOY_16COLOR        5   //Size: 4096
#define BUFSIZE_ARDUBOY_16          4096
#define MODE_HI_MONOCHROME          6   //Size: 4840
#define BUFSIZE_HI_MONO             4840
#define MODE_HI_GRAYSCALE           7   //Size: 9680
#define BUFSIZE_HI_GS               9680
#define MODE_GAMEBOY                8
#define BUFSIZE_GAMEBOY             5760
#define MODE_UZEBOX                 9
#define MODE_TVOUT                  10
#define MODE_LAMENES                111
#define BUFSIZE_LAMENES             7680

/** SCREENMODE - USE THIS SELECTION FOR YOUR PROJECT **/

#ifndef PROJ_SCREENMODE
    #ifdef PROJ_HIRES
        #if PROJ_HIRES > 0
            #define POK_SCREENMODE MODE_HI_4COLOR
            #define POK_COLORDEPTH 2
        #elif PROJ_HICOLOR > 0
            #define POK_SCREENMODE MODE_256_COLOR
            #define POK_COLORDEPTH 8
        #else
            #define POK_SCREENMODE MODE_FAST_16COLOR
            #define POK_COLORDEPTH 4
        #endif // PROJ_HIRES
    #else
        #define POK_SCREENMODE MODE_FAST_16COLOR
        #define POK_COLORDEPTH 4
    #endif // PROJ_HIRES
#else
    #define POK_SCREENMODE PROJ_SCREENMODE
#endif
/* DEFINE SCREENMODE AS THE MAXIMUM SCREEN SIZE NEEDED BY YOUR APP ... SEE SIZES LISTED ABOVE */

/** AUTOMATIC COLOR DEPTH SETTING - DO NOT CHANGE **/
#ifndef POK_COLORDEPTH
    #define POK_COLORDEPTH 4 // 1...5 is valid
#endif // POK_COLORDEPTH

/** AUTOMATIC SCREEN BUFFER SIZE CALCULATION - DO NOT CHANGE **/
#if POK_SCREENMODE == MODE_HI_MONOCHROME
    #define POK_SCREENBUFFERSIZE POK_LCD_W*POK_LCD_H*POK_COLORDEPTH/8
    #define LCDWIDTH POK_LCD_W
    #define LCDHEIGHT POK_LCD_H
    #define POK_BITFRAME 4840
#elif POK_SCREENMODE == MODE_HI_4COLOR || POK_SCREENMODE == MODE_HI_GRAYSCALE
    #define POK_SCREENBUFFERSIZE POK_LCD_W*POK_LCD_H*POK_COLORDEPTH/4
    #define LCDWIDTH POK_LCD_W
    #define LCDHEIGHT POK_LCD_H
    #define POK_BITFRAME 4840
#elif POK_SCREENMODE == MODE_FAST_16COLOR
    #define POK_SCREENBUFFERSIZE (POK_LCD_W/2)*(POK_LCD_H/2)*POK_COLORDEPTH/8
    #define XCENTER POK_LCD_W/4
    #define YCENTER POK_LCD_H/4
    #define LCDWIDTH 110
    #define LCDHEIGHT 88
    #define POK_BITFRAME 1210
#elif POK_SCREENMODE == MODE_256_COLOR
    #define POK_SCREENBUFFERSIZE 72*58
    #define XCENTER 36
    #define YCENTER 29
    #define LCDWIDTH 72
    #define LCDHEIGHT 58
    #define POK_BITFRAME 72*58
#elif POK_SCREENMODE == MODE_GAMEBUINO_16COLOR
    #define POK_SCREENBUFFERSIZE (84/2)*(48/2)*POK_COLORDEPTH/8
    #define LCDWIDTH 84
    #define LCDHEIGHT 48
    #define POK_BITFRAME 504
#elif POK_SCREENMODE == MODE_ARDUBOY_16COLOR
    #define POK_SCREENBUFFERSIZE (128/2)*(64/2)*POK_COLORDEPTH/8
    #define LCDWIDTH 128
    #define LCDHEIGHT 64
    #define POK_BITFRAME 1024
#elif POK_SCREENMODE == MODE_LAMENES
    #define POK_SCREENBUFFERSIZE (128)*(120)*POK_COLORDEPTH/8
    #define LCDWIDTH 128
    #define LCDHEIGHT 120
    #define POK_BITFRAME 1210
#elif POK_SCREENMODE == MODE_GAMEBOY
    #define POK_SCREENBUFFERSIZE (160)*(144)/4
    #define LCDWIDTH 160
    #define LCDHEIGHT 144
    #define POK_BITFRAME 2880
#else
    #define POK_SCREENBUFFERSIZE 0
#endif // POK_SCREENMODE

#ifndef POK_STRETCH
    #define POK_STRETCH 1 // Stretch Gamebuino display
#endif
#ifndef POK_FPS
    #define POK_FPS 20
#endif
#define POK_FRAMEDURATION 1000/POK_FPS

/** AUDIO **/
#define POK_AUD_PIN P2_19
#define POK_AUD_PWM_US 31
#define POK_AUD_FREQ 11025 //16000 //14285 //24000 // 14285 // 57143 // 8000 //11025// audio update frequency in Hz
#define POK_CINC_MULTIPLIER 2 // multiplies synth cycle table
#define POK_STREAMFREQ_HALVE  1  // if true, stream update freq is half audio freq
#define POK_STREAM_LOOP 1 //master switch

#define POK_USE_DAC 1 // is DAC in use in this project
#define POK_USE_EXT 0 // if extension port is in use or not
#define POK_STREAM_TO_DAC 1  // 1 = stream from SD to DAC, synthesizer to PWM,  0 = opposite
#define POK_STREAM_MOVE 0


#define POK_BACKLIGHT_PIN P2_2
#define POK_BACKLIGHT_INITIALVALUE 0.3f

#define POK_BATTERY_PIN1 P0_22 // read battery level through these pins
#define POK_BATTERY_PIN2 P0_23

#define POK_BTN_A_PIN   P1_9
#define POK_BTN_B_PIN   P1_4
#define POK_BTN_C_PIN   P1_10
#define POK_BTN_UP_PIN   P1_13
#define POK_BTN_DOWN_PIN   P1_3
#define POK_BTN_LEFT_PIN   P1_25
#define POK_BTN_RIGHT_PIN   P1_7

#define UPBIT    0
#define DOWNBIT  1
#define LEFTBIT  2
#define RIGHTBIT 3
#define ABIT     4
#define BBIT     5
#define CBIT     6

#endif // POKITTO_SETTINGS_H
