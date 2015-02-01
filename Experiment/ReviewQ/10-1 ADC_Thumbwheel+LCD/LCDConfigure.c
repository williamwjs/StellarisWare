#include "grlib/grlib.h"
#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "GPIODriverConfigure.h"
#include "LCDConfigure.h"

#ifdef LCD_KITRONIX320X240X16_SSD2119
//*****************************************************************************
//
// This driver operates in four different screen orientations.  They are:
//
// * Portrait - The screen is taller than it is wide, and the flex connector is
//              on the left of the display.  This is selected by defining
//              PORTRAIT.
//
// * Landscape - The screen is wider than it is tall, and the flex connector is
//               on the bottom of the display.  This is selected by defining
//               LANDSCAPE.
//
// * Portrait flip - The screen is taller than it is wide, and the flex
//                   connector is on the right of the display.  This is
//                   selected by defining PORTRAIT_FLIP.
//
// * Landscape flip - The screen is wider than it is tall, and the flex
//                    connector is on the top of the display.  This is
//                    selected by defining LANDSCAPE_FLIP.
//
// These can also be imagined in terms of screen rotation; if portrait mode is
// 0 degrees of screen rotation, landscape is 90 degrees of counter-clockwise
// rotation, portrait flip is 180 degrees of rotation, and landscape flip is
// 270 degress of counter-clockwise rotation.
//
// If no screen orientation is selected, "landscape flip" mode will be used.
//
//*****************************************************************************
#if ! defined(PORTRAIT) && ! defined(PORTRAIT_FLIP) && \
    ! defined(LANDSCAPE) && ! defined(LANDSCAPE_FLIP)
#define LANDSCAPE_FLIP
#endif

//*****************************************************************************
//
// Various definitions controlling coordinate space mapping and drawing
// direction in the four supported orientations.
//
//*****************************************************************************
#ifdef PORTRAIT
#define HORIZ_DIRECTION 0x28
#define VERT_DIRECTION 0x20
#define MAPPED_X(x, y) (319 - (y))
#define MAPPED_Y(x, y) (x)
#endif
#ifdef LANDSCAPE
#define HORIZ_DIRECTION 0x00
#define VERT_DIRECTION  0x08
#define MAPPED_X(x, y) (319 - (x))
#define MAPPED_Y(x, y) (239 - (y))
#endif
#ifdef PORTRAIT_FLIP
#define HORIZ_DIRECTION 0x18
#define VERT_DIRECTION 0x10
#define MAPPED_X(x, y) (y)
#define MAPPED_Y(x, y) (239 - (x))
#endif
#ifdef LANDSCAPE_FLIP
#define HORIZ_DIRECTION 0x30
#define VERT_DIRECTION  0x38
#define MAPPED_X(x, y) (x)
#define MAPPED_Y(x, y) (y)
#endif

//*****************************************************************************
//
// Macro used to set the LCD data bus in preparation for writing a byte to the
// device.
//
//*****************************************************************************
#define SET_LCD_DATA(ucByte)                                                  \
{                                                                             \
    HWREG(LCD_DATA_BASE + GPIO_O_DATA + (LCD_DATA_PINS << 2)) = (ucByte);   \
}
 
//*****************************************************************************
//
// Various internal SD2119 registers name labels
//
//*****************************************************************************
#define SSD2119_DEVICE_CODE_READ_REG  0x00
#define SSD2119_OSC_START_REG         0x00
#define SSD2119_OUTPUT_CTRL_REG       0x01
#define SSD2119_LCD_DRIVE_AC_CTRL_REG 0x02
#define SSD2119_PWR_CTRL_1_REG        0x03
#define SSD2119_DISPLAY_CTRL_REG      0x07
#define SSD2119_FRAME_CYCLE_CTRL_REG  0x0B
#define SSD2119_PWR_CTRL_2_REG        0x0C
#define SSD2119_PWR_CTRL_3_REG        0x0D
#define SSD2119_PWR_CTRL_4_REG        0x0E
#define SSD2119_GATE_SCAN_START_REG   0x0F
#define SSD2119_SLEEP_MODE_1_REG      0x10
#define SSD2119_ENTRY_MODE_REG        0x11
#define SSD2119_SLEEP_MODE_2_REG      0x12
#define SSD2119_GEN_IF_CTRL_REG       0x15
#define SSD2119_PWR_CTRL_5_REG        0x1E
#define SSD2119_RAM_DATA_REG          0x22
#define SSD2119_FRAME_FREQ_REG        0x25
#define SSD2119_ANALOG_SET_REG        0x26
#define SSD2119_VCOM_OTP_1_REG        0x28
#define SSD2119_VCOM_OTP_2_REG        0x29
#define SSD2119_GAMMA_CTRL_1_REG      0x30
#define SSD2119_GAMMA_CTRL_2_REG      0x31
#define SSD2119_GAMMA_CTRL_3_REG      0x32
#define SSD2119_GAMMA_CTRL_4_REG      0x33
#define SSD2119_GAMMA_CTRL_5_REG      0x34
#define SSD2119_GAMMA_CTRL_6_REG      0x35
#define SSD2119_GAMMA_CTRL_7_REG      0x36
#define SSD2119_GAMMA_CTRL_8_REG      0x37
#define SSD2119_GAMMA_CTRL_9_REG      0x3A
#define SSD2119_GAMMA_CTRL_10_REG     0x3B
#define SSD2119_V_RAM_POS_REG         0x44
#define SSD2119_H_RAM_START_REG       0x45
#define SSD2119_H_RAM_END_REG         0x46
#define SSD2119_X_RAM_ADDR_REG        0x4E
#define SSD2119_Y_RAM_ADDR_REG        0x4F

#define ENTRY_MODE_DEFAULT 0x6830
#define MAKE_ENTRY_MODE(x) ((ENTRY_MODE_DEFAULT & 0xFF00) | (x))

//*****************************************************************************
//
// The dimensions of the LCD panel.
//
//*****************************************************************************
#define LCD_VERTICAL_MAX 240
#define LCD_HORIZONTAL_MAX 320

//*****************************************************************************
//
// Translates a 24-bit RGB color to a display driver-specific color.
//
// \param c is the 24-bit RGB color.  The least-significant byte is the blue
// channel, the next byte is the green channel, and the third byte is the red
// channel.
//
// This macro translates a 24-bit RGB color into a value that can be written
// into the display's frame buffer in order to reproduce that color, or the
// closest possible approximation of that color.
//
// \return Returns the display-driver specific color.
//
//*****************************************************************************
#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8) |               \
                                 (((c) & 0x0000fc00) >> 5) |               \
                                 (((c) & 0x000000f8) >> 3))


//*****************************************************************************
//
// Writes a data word to the SSD2119.  This function implements the basic GPIO
// interface to the LCD display.
//
//*****************************************************************************
static void
LCDWriteData(unsigned short usData)
{
/***********************Complete the Code*************************************/
    SET_LCD_DATA(usData>>8);		//将待写入数据的高8位送到总线（通过移位获取高位）

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//拉低写使能信号WR
	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//为满足写入操作的时序要求，需要将WR重复拉低两次以延时

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = LCD_WR_PIN;//拉高写使能信号WR

	SET_LCD_DATA(usData);		//将待写入数据的低8位送到总线

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//拉低写使能信号WR
	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//为满足写入操作的时序要求，需要将WR重复拉低两次

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = LCD_WR_PIN;//拉高写使能信号WR
/*****************************************************************************/
}

//*****************************************************************************
//
// Writes a command to the SSD2119.  This function implements the basic GPIO
// interface to the LCD display.
//
//*****************************************************************************
static void
LCDWriteCommand(unsigned char ucData)
{
/***********************Complete the Code*************************************/
	SET_LCD_DATA(0);		//将待写入命令的高位送到总线
						//一般指令的高8位都是0

    HWREG(LCD_DC_BASE + GPIO_O_DATA + (LCD_DC_PIN<<2)) = ~LCD_DC_PIN;//拉低DC

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//拉低WR
	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//重复上一步

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = LCD_WR_PIN;//拉高WR

	SET_LCD_DATA(ucData);		//将待写入命令的低8位送到总线

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//拉低WR
	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = ~LCD_WR_PIN;//重复上一步

	HWREG(LCD_WR_BASE + GPIO_O_DATA + (LCD_WR_PIN<<2)) = LCD_WR_PIN;//拉高WR

	HWREG(LCD_DC_BASE + GPIO_O_DATA + (LCD_DC_PIN<<2)) = LCD_DC_PIN;//拉高DC
/*****************************************************************************/
}


//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the SSD2119 display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void
LCDInitial(void)
{
    unsigned long ulCount;
    //
    // Enter sleep mode (if we are not already there).
    //
    LCDWriteCommand(SSD2119_SLEEP_MODE_1_REG);
    LCDWriteData(0x0001);

    //
    // Set initial power parameters.
    //
    LCDWriteCommand(SSD2119_PWR_CTRL_5_REG);
    LCDWriteData(0x00B2);
    LCDWriteCommand(SSD2119_VCOM_OTP_1_REG);
    LCDWriteData(0x0006);

    //
    // Start the oscillator.
    //
    LCDWriteCommand(SSD2119_OSC_START_REG);
    LCDWriteData(0x0001);

    //
    // Set pixel format and basic display orientation (scanning direction).
    //
    LCDWriteCommand(SSD2119_OUTPUT_CTRL_REG);
    LCDWriteData(0x30EF);
    LCDWriteCommand(SSD2119_LCD_DRIVE_AC_CTRL_REG);
    LCDWriteData(0x0600);

    //
    // Exit sleep mode.
    //
    LCDWriteCommand(SSD2119_SLEEP_MODE_1_REG);
    LCDWriteData(0x0000);

    //
    // Delay 30mS
    //
    SysCtlDelay(TheSysClock/100);

    //
    // Configure pixel color format and MCU interface parameters.
    //
    LCDWriteCommand(SSD2119_ENTRY_MODE_REG);
    LCDWriteData(ENTRY_MODE_DEFAULT);

	//
    // Set analog parameters.
    //
    LCDWriteCommand(SSD2119_SLEEP_MODE_2_REG);
    LCDWriteData(0x0999);
    LCDWriteCommand(SSD2119_ANALOG_SET_REG);
    LCDWriteData(0x3800);

    //
    // Enable the display.
    //
    LCDWriteCommand(SSD2119_DISPLAY_CTRL_REG);
    LCDWriteData(0x0033);

    //
    // Set VCIX2 voltage to 6.1V.
    //
    LCDWriteCommand(SSD2119_PWR_CTRL_2_REG);
    LCDWriteData(0x0005);

    //
    // Configure gamma correction.
    //
    LCDWriteCommand(SSD2119_GAMMA_CTRL_1_REG);
    LCDWriteData(0x0000);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_2_REG);
    LCDWriteData(0x0303); 
    LCDWriteCommand(SSD2119_GAMMA_CTRL_3_REG);
    LCDWriteData(0x0407);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_4_REG);
    LCDWriteData(0x0301);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_5_REG);
    LCDWriteData(0x0301);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_6_REG);
    LCDWriteData(0x0403);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_7_REG);
    LCDWriteData(0x0707);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_8_REG);
    LCDWriteData(0x0400);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_9_REG);
    LCDWriteData(0x0A00);
    LCDWriteCommand(SSD2119_GAMMA_CTRL_10_REG);
    LCDWriteData(0x1000);

    //
    // Configure Vlcd63 and VCOMl.
    //
    LCDWriteCommand(SSD2119_PWR_CTRL_3_REG);
    LCDWriteData(0x000A);//7
    LCDWriteCommand(SSD2119_PWR_CTRL_4_REG);
    LCDWriteData(0x2E00);//2E

    //
    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    //
    LCDWriteCommand(SSD2119_V_RAM_POS_REG);
    LCDWriteData((LCD_VERTICAL_MAX-1) << 8);
    LCDWriteCommand(SSD2119_H_RAM_START_REG);
    LCDWriteData(0x0000);
    LCDWriteCommand(SSD2119_H_RAM_END_REG);
    LCDWriteData(LCD_HORIZONTAL_MAX-1);
    LCDWriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCDWriteData(0x00);
    LCDWriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCDWriteData(0x00);

    //
    // Clear the contents of the display buffer.
    //
    LCDWriteCommand(SSD2119_RAM_DATA_REG);
    for(ulCount = 0; ulCount < (320 * 240); ulCount++)
    {
        LCDWriteData(0x0000);
    }
}

//*****************************************************************************
//
//! Draws a pixel on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the pixel.
//! \param lY is the Y coordinate of the pixel.
//! \param ulValue is the color of the pixel.
//!
//! This function sets the given pixel to a particular color.  The coordinates
//! of the pixel are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
Kitronix320x240x16_SSD2119PixelDraw(void *pvDisplayData, long lX, long lY,
                                   unsigned long ulValue)
{
    //
    // Set the X address of the display cursor.
    //
    LCDWriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCDWriteData(MAPPED_X(lX, lY));

    //
    // Set the Y address of the display cursor.
    //
    LCDWriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCDWriteData(MAPPED_Y(lX, lY));

    //
    // Write the pixel value.
    //
    LCDWriteCommand(SSD2119_RAM_DATA_REG);
    LCDWriteData(ulValue);
}

//*****************************************************************************
//
//! Draws a horizontal sequence of pixels on the screen.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the first pixel.
//! \param lY is the Y coordinate of the first pixel.
//! \param lX0 is sub-pixel offset within the pixel data, which is valid for 1
//! or 4 bit per pixel formats.
//! \param lCount is the number of pixels to draw.
//! \param lBPP is the number of bits per pixel; must be 1, 4, or 8.
//! \param pucData is a pointer to the pixel data.  For 1 and 4 bit per pixel
//! formats, the most significant bit(s) represent the left-most pixel.
//! \param pucPalette is a pointer to the palette used to draw the pixels.
//!
//! This function draws a horizontal sequence of pixels on the screen, using
//! the supplied palette.  For 1 bit per pixel format, the palette contains
//! pre-translated colors; for 4 and 8 bit per pixel formats, the palette
//! contains 24-bit RGB values that must be translated before being written to
//! the display.
//!
//! \return None.
//
//*****************************************************************************
static void
Kitronix320x240x16_SSD2119PixelDrawMultiple(void *pvDisplayData, long lX,
                                           long lY, long lX0, long lCount,
                                           long lBPP,
                                           const unsigned char *pucData,
                                           const unsigned char *pucPalette)
{
    unsigned long ulByte;

    //
    // Set the cursor increment to left to right, followed by top to bottom.
    //
    LCDWriteCommand(SSD2119_ENTRY_MODE_REG);
    LCDWriteData(MAKE_ENTRY_MODE(HORIZ_DIRECTION));

    //
    // Set the starting X address of the display cursor.
    //
    LCDWriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCDWriteData(MAPPED_X(lX, lY));

    //
    // Set the Y address of the display cursor.
    //
    LCDWriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCDWriteData(MAPPED_Y(lX, lY));

    //
    // Write the data RAM write command.
    //
    LCDWriteCommand(SSD2119_RAM_DATA_REG);

    //
    // Determine how to interpret the pixel data based on the number of bits
    // per pixel.
    //
    switch(lBPP)
    {
        //
        // The pixel data is in 1 bit per pixel format.
        //
        case 1:
        {
            //
            // Loop while there are more pixels to draw.
            //
            while(lCount)
            {
                //
                // Get the next byte of image data.
                //
                ulByte = *pucData++;

                //
                // Loop through the pixels in this byte of image data.
                //
                for(; (lX0 < 8) && lCount; lX0++, lCount--)
                {
                    //
                    // Draw this pixel in the appropriate color.
                    //
                    LCDWriteData(((unsigned long *)pucPalette)[(ulByte >>
                                                             (7 - lX0)) & 1]);
                }

                //
                // Start at the beginning of the next byte of image data.
                //
                lX0 = 0;
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // The pixel data is in 4 bit per pixel format.
        //
        case 4:
        {
            //
            // Loop while there are more pixels to draw.  "Duff's device" is
            // used to jump into the middle of the loop if the first nibble of
            // the pixel data should not be used.  Duff's device makes use of
            // the fact that a case statement is legal anywhere within a
            // sub-block of a switch statement.  See
            // http://en.wikipedia.org/wiki/Duff's_device for detailed
            // information about Duff's device.
            //
            switch(lX0 & 1)
            {
                case 0:
                    while(lCount)
                    {
                        //
                        // Get the upper nibble of the next byte of pixel data
                        // and extract the corresponding entry from the
                        // palette.
                        //
                        ulByte = (*pucData >> 4) * 3;
                        ulByte = (*(unsigned long *)(pucPalette + ulByte) &
                                  0x00ffffff);

                        //
                        // Translate this palette entry and write it to the
                        // screen.
                        //
                        LCDWriteData(DPYCOLORTRANSLATE(ulByte));

                        //
                        // Decrement the count of pixels to draw.
                        //
                        lCount--;

                        //
                        // See if there is another pixel to draw.
                        //
                        if(lCount)
                        {
                case 1:
                            //
                            // Get the lower nibble of the next byte of pixel
                            // data and extract the corresponding entry from
                            // the palette.
                            //
                            ulByte = (*pucData++ & 15) * 3;
                            ulByte = (*(unsigned long *)(pucPalette + ulByte) &
                                      0x00ffffff);

                            //
                            // Translate this palette entry and write it to the
                            // screen.
                            //
                            LCDWriteData(DPYCOLORTRANSLATE(ulByte));

                            //
                            // Decrement the count of pixels to draw.
                            //
                            lCount--;
                        }
                    }
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // The pixel data is in 8 bit per pixel format.
        //
        case 8:
        {
            //
            // Loop while there are more pixels to draw.
            //
            while(lCount--)
            {
                //
                // Get the next byte of pixel data and extract the
                // corresponding entry from the palette.
                //
                ulByte = *pucData++ * 3;
                ulByte = *(unsigned long *)(pucPalette + ulByte) & 0x00ffffff;

                //
                // Translate this palette entry and write it to the screen.
                //
                LCDWriteData(DPYCOLORTRANSLATE(ulByte));
            }

            //
            // The image data has been drawn.
            //
            break;
        }

        //
        // We are being passed data in the display's native format.  Merely
        // write it directly to the display.  This is a special case which is
        // not used by the graphics library but which is helpful to
        // applications which may want to handle, for example, JPEG images.
        //
        case 16:
        {
            unsigned short usByte;

            //
            // Loop while there are more pixels to draw.
            //
            while(lCount--)
            {
                //
                // Get the next byte of pixel data and extract the
                // corresponding entry from the palette.
                //
                usByte = *((unsigned short *)pucData);
                pucData += 2;

                //
                // Translate this palette entry and write it to the screen.
                //
                LCDWriteData(usByte);
            }
        }
    }
}

//*****************************************************************************
//
//! Draws a horizontal line.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX1 is the X coordinate of the start of the line.
//! \param lX2 is the X coordinate of the end of the line.
//! \param lY is the Y coordinate of the line.
//! \param ulValue is the color of the line.
//!
//! This function draws a horizontal line on the display.  The coordinates of
//! the line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
Kitronix320x240x16_SSD2119LineDrawH(void *pvDisplayData, long lX1, long lX2,
                                   long lY, unsigned long ulValue)
{
    //
    // Set the cursor increment to left to right, followed by top to bottom.
    //
    LCDWriteCommand(SSD2119_ENTRY_MODE_REG);
    LCDWriteData(MAKE_ENTRY_MODE(HORIZ_DIRECTION));

    //
    // Set the starting X address of the display cursor.
    //
    LCDWriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCDWriteData(MAPPED_X(lX1, lY));

    //
    // Set the Y address of the display cursor.
    //
    LCDWriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCDWriteData(MAPPED_Y(lX1, lY));

    //
    // Write the data RAM write command.
    //
    LCDWriteCommand(SSD2119_RAM_DATA_REG);

    //
    // Loop through the pixels of this horizontal line.
    //
    while(lX1++ <= lX2)
    {
        //
        // Write the pixel value.
        //
        LCDWriteData(ulValue);
    }
}

//*****************************************************************************
//
//! Draws a vertical line.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param lX is the X coordinate of the line.
//! \param lY1 is the Y coordinate of the start of the line.
//! \param lY2 is the Y coordinate of the end of the line.
//! \param ulValue is the color of the line.
//!
//! This function draws a vertical line on the display.  The coordinates of the
//! line are assumed to be within the extents of the display.
//!
//! \return None.
//
//*****************************************************************************
static void
Kitronix320x240x16_SSD2119LineDrawV(void *pvDisplayData, long lX, long lY1,
                                   long lY2, unsigned long ulValue)
{
    //
    // Set the cursor increment to top to bottom, followed by left to right.
    //
    LCDWriteCommand(SSD2119_ENTRY_MODE_REG);
    LCDWriteData(MAKE_ENTRY_MODE(VERT_DIRECTION));

    //
    // Set the X address of the display cursor.
    //
    LCDWriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCDWriteData(MAPPED_X(lX, lY1));

    //
    // Set the starting Y address of the display cursor.
    //
    LCDWriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCDWriteData(MAPPED_Y(lX, lY1));

    //
    // Write the data RAM write command.
    //
    LCDWriteCommand(SSD2119_RAM_DATA_REG);

    //
    // Loop through the pixels of this vertical line.
    //
    while(lY1++ <= lY2)
    {
        //
        // Write the pixel value.
        //
        LCDWriteData(ulValue);
    }
}

//*****************************************************************************
//
//! Fills a rectangle.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param pRect is a pointer to the structure describing the rectangle.
//! \param ulValue is the color of the rectangle.
//!
//! This function fills a rectangle on the display.  The coordinates of the
//! rectangle are assumed to be within the extents of the display, and the
//! rectangle specification is fully inclusive (in other words, both sXMin and
//! sXMax are drawn, along with sYMin and sYMax).
//!
//! \return None.
//
//*****************************************************************************
static void
Kitronix320x240x16_SSD2119RectFill(void *pvDisplayData, const tRectangle *pRect,
                                  unsigned long ulValue)
{
    long lCount;

    //
    // Write the Y extents of the rectangle.
    //
    LCDWriteCommand(SSD2119_ENTRY_MODE_REG);
    LCDWriteData(MAKE_ENTRY_MODE(HORIZ_DIRECTION));

    //
    // Write the X extents of the rectangle.
    //
    LCDWriteCommand(SSD2119_H_RAM_START_REG);
#if (defined PORTRAIT) || (defined LANDSCAPE)
    LCDWriteData(MAPPED_X(pRect->sXMax, pRect->sYMax));
#else
    LCDWriteData(MAPPED_X(pRect->sXMin, pRect->sYMin));
#endif

    LCDWriteCommand(SSD2119_H_RAM_END_REG);
#if (defined PORTRAIT) || (defined LANDSCAPE)
    LCDWriteData(MAPPED_X(pRect->sXMin, pRect->sYMin));
#else
    LCDWriteData(MAPPED_X(pRect->sXMax, pRect->sYMax));
#endif

    //
    // Write the Y extents of the rectangle
    //
    LCDWriteCommand(SSD2119_V_RAM_POS_REG);
#if (defined LANDSCAPE_FLIP) || (defined PORTRAIT)
    LCDWriteData(MAPPED_Y(pRect->sXMin, pRect->sYMin) |
             	(MAPPED_Y(pRect->sXMax, pRect->sYMax) << 8));
#else
    LCDWriteData(MAPPED_Y(pRect->sXMax, pRect->sYMax) |
             	(MAPPED_Y(pRect->sXMin, pRect->sYMin) << 8));
#endif

    //
    // Set the display cursor to the upper left of the rectangle (in application
    // coordinate space).
    //
    LCDWriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCDWriteData(MAPPED_X(pRect->sXMin, pRect->sYMin));

    LCDWriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCDWriteData(MAPPED_Y(pRect->sXMin, pRect->sYMin));

    //
    // Tell the controller we are about to write data into its RAM.
    //
    LCDWriteCommand(SSD2119_RAM_DATA_REG);

    //
    // Loop through the pixels of this filled rectangle.
    //
    for(lCount = ((pRect->sXMax - pRect->sXMin + 1) *
                  (pRect->sYMax - pRect->sYMin + 1)); lCount >= 0; lCount--)
    {
        //
        // Write the pixel value.
        //
        LCDWriteData(ulValue);
    }

    //
    // Reset the X extents to the entire screen.
    //
    LCDWriteCommand(SSD2119_H_RAM_START_REG);
    LCDWriteData(0x0000);
    LCDWriteCommand(SSD2119_H_RAM_END_REG);
    LCDWriteData(0x013F);

    //
    // Reset the Y extent to the full screen
    //
    LCDWriteCommand(SSD2119_V_RAM_POS_REG);
    LCDWriteData(0xEF00);
}

//*****************************************************************************
//
//! Translates a 24-bit RGB color to a display driver-specific color.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//! \param ulValue is the 24-bit RGB color.  The least-significant byte is the
//! blue channel, the next byte is the green channel, and the third byte is the
//! red channel.
//!
//! This function translates a 24-bit RGB color into a value that can be
//! written into the display's frame buffer in order to reproduce that color,
//! or the closest possible approximation of that color.
//!
//! \return Returns the display-driver specific color.
//
//*****************************************************************************
static unsigned long
Kitronix320x240x16_SSD2119ColorTranslate(void *pvDisplayData,
                                        unsigned long ulValue)
{
    //
    // Translate from a 24-bit RGB color to a 5-6-5 RGB color.
    //
    return(DPYCOLORTRANSLATE(ulValue));
}

//*****************************************************************************
//
//! Flushes any cached drawing operations.
//!
//! \param pvDisplayData is a pointer to the driver-specific data for this
//! display driver.
//!
//! This functions flushes any cached drawing operations to the display.  This
//! is useful when a local frame buffer is used for drawing operations, and the
//! flush would copy the local frame buffer to the display.  For the SSD2119
//! driver, the flush is a no operation.
//!
//! \return None.
//
//*****************************************************************************
static void
Kitronix320x240x16_SSD2119Flush(void *pvDisplayData)
{
    //
    // There is nothing to be done.
    //
}

//*****************************************************************************
//
//! The display structure that describes the driver for the Kitronix
//! K350QVG-V1-F TFT panel with an SSD2119 controller.
//
//*****************************************************************************
const tDisplay g_sKitronix320x240x16_SSD2119 =
{
    sizeof(tDisplay),
    0,
#if defined(PORTRAIT) || defined(PORTRAIT_FLIP)
    240,
    320,
#else
    320,
    240,
#endif
    Kitronix320x240x16_SSD2119PixelDraw,
    Kitronix320x240x16_SSD2119PixelDrawMultiple,
    Kitronix320x240x16_SSD2119LineDrawH,
    Kitronix320x240x16_SSD2119LineDrawV,
    Kitronix320x240x16_SSD2119RectFill,
    Kitronix320x240x16_SSD2119ColorTranslate,
    Kitronix320x240x16_SSD2119Flush
};

#endif
