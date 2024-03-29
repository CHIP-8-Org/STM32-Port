#include "ili9341.h"
#include "chip8.h"
#include "stm32f3xx_hal.h"
#include <stdint.h>

#define PIN_LOW(p) HAL_GPIO_WritePin(p.port, p.pin, GPIO_PIN_RESET)
#define PIN_HIGH(p) HAL_GPIO_WritePin(p.port, p.pin, GPIO_PIN_SET)

#define DELAY(x) HAL_Delay(x)

#define RD_ACTIVE(ili) PIN_LOW(ili->RD)
#define RD_IDLE(ili) PIN_HIGH(ili->RD)

#define WR_ACTIVE(ili) PIN_LOW(ili->WR)
#define WR_IDLE(ili) PIN_HIGH(ili->WR)

#define CD_COMMAND(ili) PIN_LOW(ili->RS)
#define CD_DATA(ili) PIN_HIGH(ili->RS)

#define CS_ACTIVE(ili) PIN_LOW(ili->CS)
#define CS_IDLE(ili) // PIN_HIGH(ili->CS)

#define WR_STROBE(ili)                                                         \
  {                                                                            \
    WR_ACTIVE(ili);                                                            \
    WR_IDLE(ili);                                                              \
  }

inline static void ILI9341_ConfigurePinForOutput(struct ILI9341_Pin_t p) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // GPIO_SPEED_FREQ_VERY_HIGH
  GPIO_InitStruct.Pin = p.pin;
  HAL_GPIO_Init(p.port, &GPIO_InitStruct);
}

inline static void ILI9341_ConfigurePinForInput(struct ILI9341_Pin_t p) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // GPIO_SPEED_FREQ_VERY_HIGH
  GPIO_InitStruct.Pin = p.pin;
  HAL_GPIO_Init(p.port, &GPIO_InitStruct);
}

inline static void ILI9341_PrepareDataPinsForReading(struct ILI9341_t *ili) {
  for (int i = 0; i < 8; i++) {
    ILI9341_ConfigurePinForInput(ili->DATA[i]);
  }
}

inline static void ILI9341_PrepareDataPinsForWriting(struct ILI9341_t *ili) {
  for (int i = 0; i < 8; i++) {
    ILI9341_ConfigurePinForOutput(ili->DATA[i]);
  }
}

inline static void ILI9341_WriteToDataPins(struct ILI9341_t *ili, uint8_t b) {
  for (int i = 0; i < 8; i++) {
    if (b & (1 << i))
      PIN_HIGH(ili->DATA[i]);
    else
      PIN_LOW(ili->DATA[i]);
  }
}

inline static uint8_t ILI9341_ReadFromDataPins(struct ILI9341_t *ili) {
  uint8_t b = 0;
  for (int i = 0; i < 8; i++) {
    if (HAL_GPIO_ReadPin(ili->DATA[i].port, ili->DATA[i].pin) == GPIO_PIN_SET)
      b |= 1 << i;
  }

  return b;
}

inline static void ILI9341_WriteCommand(struct ILI9341_t *ili,
                                        uint8_t command) {
  CD_COMMAND(ili);

  WR_ACTIVE(ili);
  ILI9341_WriteToDataPins(ili, command);
  WR_IDLE(ili);
}

inline static void ILI9341_WriteData(struct ILI9341_t *ili, uint8_t data) {
  CD_DATA(ili);

  WR_ACTIVE(ili);
  ILI9341_WriteToDataPins(ili, data);
  WR_IDLE(ili);
}

inline static void ILI9341_WriteCommandWithParameter(struct ILI9341_t *ili,
                                                     uint8_t command,
                                                     uint8_t param1) {
  ILI9341_WriteCommand(ili, command);
  ILI9341_WriteData(ili, param1);
}

inline static void ILI9341_WriteCommandWith2Parameters(struct ILI9341_t *ili,
                                                       uint8_t command,
                                                       uint8_t param1,
                                                       uint8_t param2) {
  ILI9341_WriteCommand(ili, command);
  ILI9341_WriteData(ili, param1);
  ILI9341_WriteData(ili, param2);
}

inline static void ILI9341_WriteCommandWith3Parameters(struct ILI9341_t *ili,
                                                       uint8_t command,
                                                       uint8_t param1,
                                                       uint8_t param2,
                                                       uint8_t param3) {
  ILI9341_WriteCommand(ili, command);
  ILI9341_WriteData(ili, param1);
  ILI9341_WriteData(ili, param2);
  ILI9341_WriteData(ili, param3);
}

inline static void
ILI9341_WriteCommandWith4Parameters(struct ILI9341_t *ili, uint8_t command,
                                    uint8_t param1, uint8_t param2,
                                    uint8_t param3, uint8_t param4) {
  ILI9341_WriteCommand(ili, command);
  ILI9341_WriteData(ili, param1);
  ILI9341_WriteData(ili, param2);
  ILI9341_WriteData(ili, param3);
  ILI9341_WriteData(ili, param4);
}

inline static uint8_t ILI9341_ReadData(struct ILI9341_t *ili) {
  CD_DATA(ili);

  RD_ACTIVE(ili);
  DELAY(5);
  uint8_t temp = ILI9341_ReadFromDataPins(ili);
  RD_IDLE(ili);

  return temp;
}

int ILI9341_Init(struct ILI9341_t *ili, struct ILI9341_Pin_t D7,
                 struct ILI9341_Pin_t D6, struct ILI9341_Pin_t D5,
                 struct ILI9341_Pin_t D4, struct ILI9341_Pin_t D3,
                 struct ILI9341_Pin_t D2, struct ILI9341_Pin_t D1,
                 struct ILI9341_Pin_t D0, struct ILI9341_Pin_t RST,
                 struct ILI9341_Pin_t CS, struct ILI9341_Pin_t RS,
                 struct ILI9341_Pin_t WR, struct ILI9341_Pin_t RD) {
  ili->RST = RST;
  ili->CS = CS;
  ili->RS = RS;
  ili->WR = WR;
  ili->RD = RD;
  ili->DATA[0] = D0;
  ili->DATA[1] = D1;
  ili->DATA[2] = D2;
  ili->DATA[3] = D3;
  ili->DATA[4] = D4;
  ili->DATA[5] = D5;
  ili->DATA[6] = D6;
  ili->DATA[7] = D7;

  ILI9341_ConfigurePinForOutput(ili->RST);
  ILI9341_ConfigurePinForOutput(ili->CS);
  ILI9341_ConfigurePinForOutput(ili->RS);
  ILI9341_ConfigurePinForOutput(ili->WR);
  ILI9341_ConfigurePinForOutput(ili->RD);

  CS_ACTIVE(ili);
  PIN_HIGH(ili->RST);
  WR_IDLE(ili);
  RD_IDLE(ili);
  CD_COMMAND(ili);

  // Hardware Reset
  PIN_HIGH(ili->RST);
  DELAY(50);
  PIN_LOW(ili->RST);
  DELAY(150);
  PIN_HIGH(ili->RST);
  DELAY(200);

  CS_IDLE(ili);

  return 0;
}

void ILI9341_SendInitializationSequence(struct ILI9341_t *ili) {
  ILI9341_PrepareDataPinsForWriting(ili);

  // Data transfer sync
  {
    CS_ACTIVE(ili);
    CD_COMMAND(ili);
    ILI9341_WriteData(ili, 0x00);
    for (int i = 0; i < 3; i++) {
      WR_ACTIVE(ili);
      WR_IDLE(ili);
    }
    CS_IDLE(ili);
  }

  CS_ACTIVE(ili);

  ILI9341_WriteCommand(ili, CMD_SOFTWARE_RESET);
  DELAY(150);
  ILI9341_WriteCommand(ili, CMD_DISPLAY_OFF);

  ILI9341_WriteCommandWithParameter(ili, CMD_POWER_CONTROL_1, 0x23);
  ILI9341_WriteCommandWithParameter(ili, CMD_POWER_CONTROL_2, 0x10);
  ILI9341_WriteCommandWith2Parameters(ili, CMD_VCOM_CONTROL_1, 0x2B, 0x2B);
  ILI9341_WriteCommandWithParameter(ili, CMD_VCOM_CONTROL_2, 0xC0);
  ILI9341_WriteCommandWithParameter(
      ili, CMD_MEMORY_ACCESS_CONTROL,
      PARAM_FLAG_MEMORY_ACCESS_CONTROL_ROW_ADDRESS_ORDER |
          PARAM_FLAG_MEMORY_ACCESS_CONTROL_ROW_BGR);
  ILI9341_WriteCommandWithParameter(
      ili, CMD_PIXEL_FORMAT_SET,
      PARAM_PIXEL_FORMAT_RGB_16_BITS_PER_PIXEL |
          PARAM_PIXEL_FORMAT_BGR_16_BITS_PER_PIXEL);
  ILI9341_WriteCommandWith2Parameters(ili, CMD_FRAME_RATE_CONTROL, 0x00, 0x1b);

  ILI9341_WriteCommandWithParameter(
      ili, CMD_ENTRY_MODE_SET,
      PARAM_FLAG_ENTRY_MODE_LOW_VOLTAGE_DETECTION_DISABLED |
          PARAM_FLAG_ENTRY_MODE_NORMAL_DISPLAY);

  ILI9341_WriteCommand(ili, CMD_SLEEP_OUT);
  DELAY(150);
  ILI9341_WriteCommand(ili, CMD_DISPLAY_ON);
  DELAY(500);

  CS_IDLE(ili);
}

void ILI9341_SetDrawingArea(struct ILI9341_t *ili, uint16_t x1, uint16_t x2,
                            uint16_t y1, uint16_t y2) {
  ILI9341_WriteCommand(ili, CMD_COLUMN_ADDRESS_SET);

  ILI9341_WriteData(ili, x1 >> 8);
  ILI9341_WriteData(ili, x1 & 0xff);

  ILI9341_WriteData(ili, x2 >> 8);
  ILI9341_WriteData(ili, x2 & 0xff);

  ILI9341_WriteCommand(ili, CMD_PAGE_ADDRESS_SET);

  ILI9341_WriteData(ili, y1 >> 8);
  ILI9341_WriteData(ili, y1 & 0xff);

  ILI9341_WriteData(ili, y2 >> 8);
  ILI9341_WriteData(ili, y2 & 0xff);
}

void ILI9341_SetOrientation(struct ILI9341_t *ili, enum ILI9341_Orientation o) {
  uint8_t b = PARAM_FLAG_MEMORY_ACCESS_CONTROL_ROW_BGR;
  switch (o) {
  case VERTICAL:
    b |= 0;
    break;
  case VERTICAL_REVERSE:
    b |= PARAM_FLAG_MEMORY_ACCESS_CONTROL_COLUMN_ADDRESS_ORDER;
    break;
  case HORIZONTAL:
    b |= PARAM_FLAG_MEMORY_ACCESS_CONTROL_ROW_COLUMN_EXCHANGE;
    break;
  case HORIZONTAL_REVERSE:
    b = PARAM_FLAG_MEMORY_ACCESS_CONTROL_ROW_COLUMN_EXCHANGE |
        PARAM_FLAG_MEMORY_ACCESS_CONTROL_COLUMN_ADDRESS_ORDER |
        PARAM_FLAG_MEMORY_ACCESS_CONTROL_ROW_ADDRESS_ORDER;
    break;
  }

  CS_ACTIVE(ili);
  ILI9341_WriteCommandWithParameter(ili, CMD_MEMORY_ACCESS_CONTROL, b);
  CS_IDLE(ili);
}

void ILI9341_FillScreen(struct ILI9341_t *ili, uint16_t fill_color) {
  ILI9341_SetDrawingArea(ili, 0, DISPLAY_WIDTH - 1, 0, DISPLAY_HEIGHT - 1);
  ILI9341_WriteCommand(ili, CMD_MEMORY_WRITE);

  for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
    ILI9341_WriteData(ili, fill_color >> 8); // First 8 significant bits
    ILI9341_WriteData(ili, fill_color);      // Last 8 significant bits
  }
}

// not scaled
void ILI9341_PrintScreen(struct ILI9341_t *ili, unsigned char screen[]) {
  ILI9341_SetDrawingArea(ili, 0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT - 1);
  ILI9341_WriteCommand(ili, CMD_MEMORY_WRITE);

  for (int i = 0; i < SCREEN_SIZE; i++) {
    for (int j = 0; j < 8; j++) {
      if (!!((screen[i] << j) & 0x80) == 1) {
        ILI9341_WriteData(ili, 0xFFFF >> 8);
        ILI9341_WriteData(ili, 0xFFFF);
      } else {
        ILI9341_WriteData(ili, 0x0000 >> 8);
        ILI9341_WriteData(ili, 0x0000);
      }
    }
  }
}

// scaled
void ILI9341_PrintScreenScaled(struct ILI9341_t *ili, unsigned char screen[],
                         int scale) {
  int RX = 32;
  int RY = 52;
  int CX = SCREEN_WIDTH * scale - 1 + RX;
  int CY = SCREEN_HEIGHT * scale - 1 + RY;
  ILI9341_SetDrawingArea(ili, RX, CX, RY, CY);
  ILI9341_WriteCommand(ili, CMD_MEMORY_WRITE);

  int ROW_LEN = SCREEN_WIDTH / 8; // 128 / 8 = 16;
  unsigned char ROW[ROW_LEN];

  for (int ch = 0; ch < SCREEN_SIZE; ch++) {
    ROW[ch % ROW_LEN] = screen[ch];
    if ((ch + 1) % ROW_LEN == 0) {
      for (int sy = 0; sy < scale; sy++) {
        for (int r = 0; r < ROW_LEN; r++) {
          for (int p = 0; p < 8; p++) {
            for (int sx = 0; sx < scale; sx++) {
              if (!!((ROW[r] << p) & 0x80) == 1) {
                ILI9341_WriteData(ili, 0xFFFF >> 8);
                ILI9341_WriteData(ili, 0xFFFF);
              } else {
                ILI9341_WriteData(ili, 0x0000 >> 8);
                ILI9341_WriteData(ili, 0x0000);
              }
            }
          }
        }
      }
    }
  }
}

void PIN_LOW_METAL(struct ILI9341_Pin_t p) {
  p.port->BSRR = (uint32_t)p.pin << 16U;
}

void PIN_HIGH_METAL(struct ILI9341_Pin_t p) {
    p.port->BSRR = p.pin;
}

static void ILI9341_WriteToDataPinsMetal(struct ILI9341_t *ili, uint8_t b) {
  for (int i = 0; i < 8; i++) {
    if (b & (1 << i))
      PIN_HIGH_METAL(ili->DATA[i]);
    else
      PIN_LOW_METAL(ili->DATA[i]);
  }
}

static void ILI9341_WriteDataMetal(struct ILI9341_t *ili, uint8_t data) {
  CD_DATA(ili);

  WR_ACTIVE(ili);
  ILI9341_WriteToDataPinsMetal(ili, data);
  WR_IDLE(ili);
}

void ILI9341_PrintScreenMetal(struct ILI9341_t *ili, unsigned char screen[],
                             int scale) {
  int RX = 32;
  int RY = 52;
  int CX = SCREEN_WIDTH * scale - 1 + RX;
  int CY = SCREEN_HEIGHT * scale - 1 + RY;
  ILI9341_SetDrawingArea(ili, RX, CX, RY, CY);
  ILI9341_WriteCommand(ili, CMD_MEMORY_WRITE);

  int ROW_LEN = SCREEN_WIDTH / 8; // 128 / 8 = 16;
  unsigned char ROW[ROW_LEN];

  for (int ch = 0; ch < SCREEN_SIZE; ch++) {
    ROW[ch % ROW_LEN] = screen[ch];
    if ((ch + 1) % ROW_LEN == 0) {
      for (int sy = 0; sy < scale; sy++) {
        for (int r = 0; r < ROW_LEN; r++) {
          for (int p = 0; p < 8; p++) {
            for (int sx = 0; sx < scale; sx++) {
              if (!!((ROW[r] << p) & 0x80) == 1) {
                ILI9341_WriteDataMetal(ili, 0xFFFF >> 8);
                ILI9341_WriteDataMetal(ili, 0xFFFF);
              } else {
                ILI9341_WriteDataMetal(ili, 0x0000 >> 8);
                ILI9341_WriteDataMetal(ili, 0x0000);
              }
            }
          }
        }
      }
    }
  }
}

void ILI9341_WriteChar(struct ILI9341_t *ili, int f_width,
                       unsigned char (*font)[f_width], int RX, int RY, int FW,
                       int FH) {
  int CX = FW + RX - 1;
  int CY = FH + RY - 1;
  ILI9341_SetDrawingArea(ili, RX, CX, RY, CY);
  ILI9341_WriteCommand(ili, CMD_MEMORY_WRITE);

  for (int sy = 0; sy < FH; sy++) {
    for (int sx = 0; sx < 8; sx++) {
      if (!!(((*font)[sy] << sx) & 0x80) == 1) {
        ILI9341_WriteData(ili, 0xFFFF >> 8);
        ILI9341_WriteData(ili, 0xFFFF);
      } else {
        ILI9341_WriteData(ili, 0x0000 >> 8);
        ILI9341_WriteData(ili, 0x0000);
      }
    }
  }
}

void ILI9341_WriteString(struct ILI9341_t *ili, int f_width, int f_height,
                         unsigned char (*fonts)[f_height][f_width], int RX,
                         int RY, int FW, int FH, char *str) {
  for (int i = 0; i < strlen(str); i++) {
    ILI9341_WriteChar(ili, f_width, &((*fonts)[(int)str[i] - 32]), RX + i * FW,
                      RY, FW, FH);
  }
}

void ILI9341_WriteMenu(struct ILI9341_t *ili, int f_width, int f_height,
                       unsigned char (*fonts)[f_height][f_width], int FW,
                       int FH, int g_size, char *games[g_size], int page) {
  for (int i = 0; i < g_size; i++) {
    ILI9341_WriteString(ili, f_width, f_height, fonts, 0, i * 10, FW, FH,
                        games[i]);
  }
}

void ILI9341_WriteMenu_array(struct ILI9341_t *ili, int f_width, int f_height,
                             unsigned char (*fonts)[f_height][f_width], int FW,
                             int FH, int g_size, char (*games)[g_size][13],
                             int page, char mode[], char freq[]) {
  char buttons[][16] = {"0", "1", "2", "3", "4", "5", "6", "7",
                        "8", "9", "A", "B", "C", "D", "E", "F"};

  int offset = page * 12;


  char MODE[16] = "MODE: "; strcat(MODE, mode);
  char FREQ[16] = "FREQ: "; strcat(FREQ, freq);

  ILI9341_WriteString(ili, f_width, f_height, fonts, 32, 45, FW, FH,
                      buttons[0]);
  ILI9341_WriteString(ili, f_width, f_height, fonts, 32 + 16, 45, FW, FH, MODE);
  for (int i = 0 + offset; i < 6 + offset; i++) {
    if (i >= g_size) {
      break;
    }
    ILI9341_WriteString(ili, f_width, f_height, fonts, 32,
                        (i + 1 - offset) * 20 + 45, FW, FH,
                        buttons[i + 1 - offset]);
    ILI9341_WriteString(ili, f_width, f_height, fonts, 32 + 16,
                        (i + 1 - offset) * 20 + 45, FW, FH, (*games)[i]);
  }
  ILI9341_WriteString(ili, f_width, f_height, fonts, 32, 8 * 20 + 25, FW, FH,
                      buttons[7]);
  ILI9341_WriteString(ili, f_width, f_height, fonts, 32 + 16, 8 * 20 + 25, FW,
                      FH, "PREV");

  ILI9341_WriteString(ili, f_width, f_height, fonts, 32 * 5 + 8, 45, FW, FH,
                      buttons[8]);
  ILI9341_WriteString(ili, f_width, f_height, fonts, 32 * 5 + 8 + 16, 45, FW,
                      FH, FREQ);
  for (int i = 6 + offset; i < 12 + offset; i++) {
    if (i >= g_size) {
      break;
    }
    ILI9341_WriteString(ili, f_width, f_height, fonts, 32 * 5 + 8,
                        (i - 6 - offset) * 20 + 65, FW, FH,
                        buttons[i + 3 - offset]);
    ILI9341_WriteString(ili, f_width, f_height, fonts, 32 * 5 + 8 + 16,
                        (i - 6 - offset) * 20 + 65, FW, FH, (*games)[i]);
  }
  ILI9341_WriteString(ili, f_width, f_height, fonts, 32 * 5 + 8, 8 * 20 + 25,
                      FW, FH, buttons[15]);
  ILI9341_WriteString(ili, f_width, f_height, fonts, 32 * 5 + 8 + 16,
                      8 * 20 + 25, FW, FH, "NEXT");

  // for (int i = 0; i < g_size; i++) {
  // ILI9341_WriteString(ili, f_width, f_height, fonts, 32 + 16, i * 20 + 60,
  // FW, FH, (*games)[i]);
  // }
}
