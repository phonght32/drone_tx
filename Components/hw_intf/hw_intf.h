// MIT License

// Copyright (c) 2024 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __HW_INTF_H__
#define __HW_INTF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"
#include "nrf24l01.h"
#include "joystick.h"

err_code_t hw_intf_nrf24l01_spi_send(uint8_t *buf_send, uint16_t len, uint32_t timeout_ms);
err_code_t hw_intf_nrf24l01_spi_recv(uint8_t *buf_recv, uint16_t len, uint32_t timeout_ms);
err_code_t hw_intf_nrf24l01_set_cs(uint8_t level);
err_code_t hw_intf_nrf24l01_set_ce(uint8_t level);

err_code_t hw_intf_left_joystick_get_pos_x(uint16_t *pos_x);
err_code_t hw_intf_left_joystick_get_pos_y(uint16_t *pos_y);
err_code_t hw_intf_left_joystick_get_bt_status(uint8_t *bt_status);
err_code_t hw_intf_right_joystick_get_pos_x(uint16_t *pos_x);
err_code_t hw_intf_right_joystick_get_pos_y(uint16_t *pos_y);
err_code_t hw_intf_right_joystick_get_bt_status(uint8_t *bt_status);

err_code_t hw_init_nrf24l01(void);
err_code_t hw_init_joystick(void);

#ifdef __cplusplus
}
#endif

#endif /* __HW_INTF_H__ */