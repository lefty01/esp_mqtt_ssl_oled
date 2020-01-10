/*
 * mosquitto log can be found here:
 * https://github.com/eclipse/mosquitto/
 * Copyright (c) Roger Light <roger@atchoo.org>
 *
 */

#define mqtt_width 53
#define mqtt_height 52
static unsigned char mqtt_bits[] = {
   0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00,
   0x38, 0x00, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x7c, 0x00, 0xe0, 0x0f, 0x00,
   0x00, 0x00, 0xfe, 0x00, 0xf0, 0x1e, 0x00, 0x00, 0x00, 0xef, 0x01, 0x70,
   0x3c, 0x00, 0x00, 0x80, 0xc7, 0x01, 0x78, 0x3c, 0x00, 0x00, 0x80, 0xc7,
   0x03, 0x38, 0x1e, 0x00, 0x00, 0x00, 0x8f, 0x03, 0x1c, 0x0e, 0x01, 0x00,
   0x18, 0x0e, 0x07, 0x1c, 0x8f, 0x07, 0x00, 0x38, 0x1e, 0x07, 0x1e, 0x87,
   0x0f, 0x00, 0x3e, 0x1c, 0x0f, 0x8e, 0xc7, 0x1f, 0x00, 0x7f, 0x3c, 0x0e,
   0x8e, 0xe3, 0x3d, 0x80, 0xf7, 0x38, 0x0e, 0x8e, 0xe3, 0x78, 0xc0, 0xe3,
   0x38, 0x0e, 0xc7, 0xe3, 0x38, 0x80, 0xe3, 0x78, 0x1c, 0xc7, 0x71, 0x1c,
   0x0e, 0xc7, 0x71, 0x1c, 0xc7, 0x71, 0x1c, 0x1f, 0xc7, 0x71, 0x1c, 0xc7,
   0x71, 0x9c, 0x3f, 0xc7, 0x71, 0x1c, 0xc7, 0x71, 0x8c, 0x3f, 0xce, 0x71,
   0x1c, 0xc7, 0x71, 0x8c, 0x3f, 0xc6, 0x71, 0x1c, 0xc7, 0x71, 0x9c, 0x3f,
   0xc7, 0x71, 0x1c, 0xc7, 0x71, 0x1c, 0x1f, 0xc7, 0x71, 0x1c, 0xc7, 0xf3,
   0x3c, 0x8e, 0xe7, 0x71, 0x1c, 0x8e, 0xe3, 0x78, 0x8e, 0xe3, 0x78, 0x0e,
   0x8e, 0xe3, 0xf0, 0xee, 0xe1, 0x38, 0x0e, 0x8e, 0xc3, 0xe1, 0xfd, 0x70,
   0x38, 0x0e, 0x0e, 0xe7, 0xc3, 0x75, 0xf8, 0x3c, 0x0e, 0x1c, 0xff, 0x00,
   0x0e, 0xe0, 0x1d, 0x07, 0x1c, 0x7f, 0x00, 0x06, 0xc0, 0x1f, 0x07, 0x3c,
   0x3e, 0x00, 0x0c, 0x80, 0x8f, 0x07, 0x38, 0x1c, 0x00, 0x04, 0x00, 0x87,
   0x03, 0x78, 0x0c, 0x00, 0x04, 0x00, 0xc6, 0x03, 0x70, 0x00, 0x00, 0x04,
   0x00, 0xc0, 0x01, 0xe0, 0x00, 0x00, 0x04, 0x00, 0xe0, 0x01, 0xe0, 0x01,
   0x00, 0x04, 0x00, 0xf0, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x40, 0x00,
   0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x26, 0xef, 0x1f, 0xe7, 0x82, 0x3b, 0x07, 0x34, 0x49, 0x08, 0x11,
   0x82, 0x88, 0x04, 0xba, 0x48, 0x08, 0x6e, 0x82, 0xb1, 0x07, 0x2a, 0x49,
   0x08, 0x84, 0x81, 0x60, 0x00, 0x22, 0x46, 0x08, 0x77, 0x8e, 0xab, 0x00,
   0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };
