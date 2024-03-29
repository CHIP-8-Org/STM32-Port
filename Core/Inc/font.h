const unsigned char font[][10] = {
      // Standard 8x10 font
      {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
      {0x30, 0x78, 0x78, 0x78, 0x30, 0x30, 0x0, 0x30, 0x30, 0x0},
      {0x6c, 0x6c, 0x6c, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
      {0x6c, 0x6c, 0xfe, 0x6c, 0x6c, 0x6c, 0xfe, 0x6c, 0x6c, 0x0},
      {0x18, 0x7e, 0xd8, 0xd8, 0x7c, 0x36, 0x36, 0xfc, 0x30, 0x0},
      {0xc6, 0xcc, 0xc, 0x18, 0x38, 0x30, 0x60, 0x66, 0xc6, 0x0},
      {0x38, 0x6c, 0x6c, 0x38, 0x30, 0x76, 0xdc, 0xcc, 0x76, 0x0},
      {0xe0, 0xe0, 0x60, 0x60, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0},
      {0xc, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0xc, 0x0},
      {0x60, 0x30, 0x18, 0x18, 0x18, 0x18, 0x18, 0x30, 0x60, 0x0},
      {0x0, 0x0, 0xc6, 0x6c, 0x38, 0xfe, 0x38, 0x6c, 0xc6, 0x0},
      {0x0, 0x0, 0x0, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x0, 0x0},
      {0x0, 0x0, 0x0, 0x0, 0x70, 0x70, 0x30, 0x30, 0x60, 0x0},
      {0x0, 0x0, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x0},
      {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x30, 0x0},
      {0x0, 0xc, 0xc, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x0},
      {0x7c, 0xc6, 0xce, 0xde, 0xd6, 0xf6, 0xe6, 0xc6, 0x7c, 0x0},
      {0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x0},
      {0x7c, 0xc6, 0xc6, 0x6, 0xc, 0x38, 0x60, 0xc6, 0xfe, 0x0},
      {0x7c, 0xc6, 0xc6, 0x6, 0x3c, 0x6, 0xc6, 0xc6, 0x7c, 0x0},
      {0xc, 0xc, 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0xc, 0x1e, 0x0},
      {0xfe, 0xc0, 0xc0, 0xfc, 0x6, 0x6, 0x6, 0xc6, 0x7c, 0x0},
      {0x1c, 0x30, 0x60, 0xc0, 0xfc, 0xc6, 0xc6, 0xc6, 0x7c, 0x0},
      {0xfe, 0xc6, 0x6, 0xc, 0xc, 0x18, 0x18, 0x18, 0x18, 0x0},
      {0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0x0},
      {0x7c, 0xc6, 0xc6, 0xc6, 0x7e, 0x6, 0xc, 0x18, 0x70, 0x0},
      {0x0, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x30, 0x30, 0x0},
      {0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x30, 0x30, 0x60, 0x0},
      {0x0, 0x0, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0},
      {0x0, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x0, 0xfc, 0x0, 0x0},
      {0x0, 0x0, 0x60, 0x30, 0x18, 0xc, 0x18, 0x30, 0x60, 0x0},
      {0x7c, 0xc6, 0xc6, 0x6, 0xc, 0x18, 0x18, 0x0, 0x18, 0x0},
      {0x7c, 0xc6, 0xce, 0xda, 0xd6, 0xde, 0xc0, 0xc6, 0x7c, 0x0},
      {0x38, 0x7c, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x0},
      {0xfc, 0x66, 0x66, 0x66, 0x7c, 0x66, 0x66, 0x66, 0xfc, 0x0},
      {0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x0},
      {0xf8, 0x6c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x0},
      {0xfe, 0x62, 0x60, 0x68, 0x78, 0x68, 0x60, 0x62, 0xfe, 0x0},
      {0xfe, 0x62, 0x60, 0x68, 0x78, 0x68, 0x60, 0x60, 0xf0, 0x0},
      {0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0xce, 0xc6, 0x66, 0x3c, 0x0},
      {0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0xc6, 0x0},
      {0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x0},
      {0x1e, 0xc, 0xc, 0xc, 0xc, 0xc, 0xcc, 0xcc, 0x78, 0x0},
      {0xe6, 0x66, 0x6c, 0x6c, 0x78, 0x6c, 0x6c, 0x66, 0xe6, 0x0},
      {0xf0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x0},
      {0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6, 0xc6, 0x0},
      {0xc6, 0xe6, 0xe6, 0xf6, 0xde, 0xce, 0xce, 0xc6, 0xc6, 0x0},
      {0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x0},
      {0xfc, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0xf0, 0x0},
      {0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xce, 0x7c, 0xe, 0x0},
      {0xfc, 0x66, 0x66, 0x66, 0x78, 0x6c, 0x6c, 0x66, 0xe6, 0x0},
      {0x7c, 0xc6, 0xc0, 0x60, 0x38, 0xc, 0x6, 0xc6, 0x7c, 0x0},
      {0x7e, 0x5a, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x0},
      {0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x0},
      {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x0},
      {0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x0},
      {0xc6, 0xc6, 0x6c, 0x38, 0x10, 0x38, 0x6c, 0xc6, 0xc6, 0x0},
      {0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x30, 0x78, 0x0},
      {0xfe, 0xc6, 0x8c, 0x18, 0x30, 0x60, 0xc2, 0xc6, 0xfe, 0x0},
      {0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1e, 0x0},
      {0x0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0xc, 0xc, 0x0},
      {0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0x0},
      {0x10, 0x38, 0x6c, 0xc6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
      {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff},
      {0x30, 0x30, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
      {0x0, 0x0, 0x0, 0x78, 0xc, 0x7c, 0xcc, 0xcc, 0x76, 0x0},
      {0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x66, 0xdc, 0x0},
      {0x0, 0x0, 0x0, 0x7c, 0xc6, 0xc0, 0xc0, 0xc6, 0x7c, 0x0},
      {0x1c, 0xc, 0xc, 0x7c, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x0},
      {0x0, 0x0, 0x0, 0x7c, 0xc6, 0xfe, 0xc0, 0xc0, 0x7c, 0x0},
      {0x38, 0x6c, 0x60, 0xf0, 0x60, 0x60, 0x60, 0x60, 0xf0, 0x0},
      {0x0, 0x0, 0x0, 0x76, 0xcc, 0xcc, 0x7c, 0xc, 0xcc, 0x78},
      {0xe0, 0x60, 0x60, 0x6c, 0x76, 0x66, 0x66, 0x66, 0xe6, 0x0},
      {0x30, 0x30, 0x0, 0x70, 0x30, 0x30, 0x30, 0x30, 0x78, 0x0},
      {0xc, 0xc, 0x0, 0xc, 0xc, 0xc, 0xc, 0xcc, 0xcc, 0x78},
      {0xe0, 0x60, 0x60, 0x66, 0x6c, 0x78, 0x78, 0x6c, 0xe6, 0x0},
      {0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x0},
      {0x0, 0x0, 0x0, 0xcc, 0xfe, 0xfe, 0xd6, 0xd6, 0xd6, 0x0},
      {0x0, 0x0, 0x0, 0xdc, 0xe6, 0xc6, 0xc6, 0xc6, 0xc6, 0x0},
      {0x0, 0x0, 0x0, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x0},
      {0x0, 0x0, 0x0, 0xdc, 0x66, 0x66, 0x66, 0x7c, 0x60, 0xf0},
      {0x0, 0x0, 0x0, 0x76, 0xcc, 0xcc, 0xcc, 0x7c, 0xc, 0x1e},
      {0x0, 0x0, 0x0, 0xdc, 0x76, 0x66, 0x60, 0x60, 0xf0, 0x0},
      {0x0, 0x0, 0x0, 0x7c, 0xc6, 0x70, 0x1c, 0xc6, 0x7c, 0x0},
      {0x20, 0x60, 0x60, 0xfc, 0x60, 0x60, 0x60, 0x6c, 0x38, 0x0},
      {0x0, 0x0, 0x0, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x0},
      {0x0, 0x0, 0x0, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x0},
      {0x0, 0x0, 0x0, 0xc6, 0xd6, 0xd6, 0xfe, 0xfe, 0x6c, 0x0},
      {0x0, 0x0, 0x0, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x0},
      {0x0, 0x0, 0x0, 0xc6, 0xc6, 0xc6, 0x7e, 0x6, 0x6, 0xfc},
      {0x0, 0x0, 0x0, 0xfe, 0x8c, 0x18, 0x30, 0x62, 0xfe, 0x0},
      {0xe, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0xe, 0x0},
      {0x18, 0x18, 0x18, 0x18, 0x0, 0x18, 0x18, 0x18, 0x18, 0x0},
      {0xe0, 0x30, 0x30, 0x30, 0x1c, 0x30, 0x30, 0x30, 0xe0, 0x0},
      {0x76, 0xdc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
  };
