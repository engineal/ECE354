/* system.h
 *
 * Machine generated for a CPU named "cpu_0" as defined in:
 * c:\Users\ajlucia\code\ECE354\lab2\software\hello_led_0_syslib_0\..\..\system_0.ptf
 *
 * Generated: 2016-04-06 10:14:13.599
 *
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/*

DO NOT MODIFY THIS FILE

   Changing this file will have subtle consequences
   which will almost certainly lead to a nonfunctioning
   system. If you do modify this file, be aware that your
   changes will be overwritten and lost when this file
   is generated again.

DO NOT MODIFY THIS FILE

*/

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

/*
 * system configuration
 *
 */

#define ALT_SYSTEM_NAME "system_0"
#define ALT_CPU_NAME "cpu_0"
#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_DEVICE_FAMILY "CYCLONEII"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN_BASE 0x006810f0
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_PRESENT
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT_BASE 0x006810f0
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_PRESENT
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDERR_BASE 0x006810f0
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_PRESENT
#define ALT_CPU_FREQ 100000000
#define ALT_IRQ_BASE NULL
#define ALT_LEGACY_INTERRUPT_API_PRESENT

/*
 * processor configuration
 *
 */

#define NIOS2_CPU_IMPLEMENTATION "small"
#define NIOS2_BIG_ENDIAN 0
#define NIOS2_INTERRUPT_CONTROLLER_ID 0

#define NIOS2_ICACHE_SIZE 1024
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_FLUSHDA_SUPPORTED

#define NIOS2_EXCEPTION_ADDR 0x00600020
#define NIOS2_RESET_ADDR 0x00600000
#define NIOS2_BREAK_ADDR 0x00680020

#define NIOS2_HAS_DEBUG_STUB

#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0

/*
 * A define for each class of peripheral
 *
 */

#define __ALTERA_AVALON_TRI_STATE_BRIDGE
#define __ALTERA_AVALON_CFI_FLASH
#define __ALTERA_AVALON_EPCS_FLASH_CONTROLLER
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_UART
#define __ALTERA_AVALON_TIMER
#define __ALTERA_AVALON_LCD_16207
#define __ALTERA_AVALON_PIO
#define __SRAM_16BIT_512K
#define __DM9000A
#define __ISP1362
#define __BINARY_VGA_CONTROLLER
#define __AUDIO_DAC_FIFO
#define __CAMERA_IF

/*
 * tri_state_bridge_0 configuration
 *
 */

#define TRI_STATE_BRIDGE_0_NAME "/dev/tri_state_bridge_0"
#define TRI_STATE_BRIDGE_0_TYPE "altera_avalon_tri_state_bridge"
#define ALT_MODULE_CLASS_tri_state_bridge_0 altera_avalon_tri_state_bridge

/*
 * cfi_flash_0 configuration
 *
 */

#define CFI_FLASH_0_NAME "/dev/cfi_flash_0"
#define CFI_FLASH_0_TYPE "altera_avalon_cfi_flash"
#define CFI_FLASH_0_BASE 0x00000000
#define CFI_FLASH_0_SPAN 4194304
#define CFI_FLASH_0_SETUP_VALUE 40
#define CFI_FLASH_0_WAIT_VALUE 160
#define CFI_FLASH_0_HOLD_VALUE 40
#define CFI_FLASH_0_TIMING_UNITS "ns"
#define CFI_FLASH_0_UNIT_MULTIPLIER 1
#define CFI_FLASH_0_SIZE 4194304
#define ALT_MODULE_CLASS_cfi_flash_0 altera_avalon_cfi_flash

/*
 * epcs_controller configuration
 *
 */

#define EPCS_CONTROLLER_NAME "/dev/epcs_controller"
#define EPCS_CONTROLLER_TYPE "altera_avalon_epcs_flash_controller"
#define EPCS_CONTROLLER_BASE 0x00680800
#define EPCS_CONTROLLER_SPAN 2048
#define EPCS_CONTROLLER_IRQ 0
#define EPCS_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define EPCS_CONTROLLER_DATABITS 8
#define EPCS_CONTROLLER_TARGETCLOCK 20
#define EPCS_CONTROLLER_CLOCKUNITS "MHz"
#define EPCS_CONTROLLER_CLOCKMULT 1000000
#define EPCS_CONTROLLER_NUMSLAVES 1
#define EPCS_CONTROLLER_ISMASTER 1
#define EPCS_CONTROLLER_CLOCKPOLARITY 0
#define EPCS_CONTROLLER_CLOCKPHASE 0
#define EPCS_CONTROLLER_LSBFIRST 0
#define EPCS_CONTROLLER_EXTRADELAY 0
#define EPCS_CONTROLLER_TARGETSSDELAY 100
#define EPCS_CONTROLLER_DELAYUNITS "us"
#define EPCS_CONTROLLER_DELAYMULT "1e-006"
#define EPCS_CONTROLLER_PREFIX "epcs_"
#define EPCS_CONTROLLER_REGISTER_OFFSET 0x200
#define EPCS_CONTROLLER_IGNORE_LEGACY_CHECK 1
#define EPCS_CONTROLLER_USE_ASMI_ATOM 1
#define EPCS_CONTROLLER_CLOCKUNIT "kHz"
#define EPCS_CONTROLLER_DELAYUNIT "us"
#define ALT_MODULE_CLASS_epcs_controller altera_avalon_epcs_flash_controller

/*
 * jtag_uart configuration
 *
 */

#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_BASE 0x006810f0
#define JTAG_UART_SPAN 8
#define JTAG_UART_IRQ 1
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_READ_CHAR_STREAM ""
#define JTAG_UART_SHOWASCII 1
#define JTAG_UART_READ_LE 0
#define JTAG_UART_WRITE_LE 0
#define JTAG_UART_ALTERA_SHOW_UNRELEASED_JTAG_UART_FEATURES 0
#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart

/*
 * uart configuration
 *
 */

#define UART_NAME "/dev/uart"
#define UART_TYPE "altera_avalon_uart"
#define UART_BASE 0x00681000
#define UART_SPAN 32
#define UART_IRQ 2
#define UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_BAUD 115200
#define UART_DATA_BITS 8
#define UART_FIXED_BAUD 1
#define UART_PARITY 'N'
#define UART_STOP_BITS 1
#define UART_USE_CTS_RTS 0
#define UART_USE_EOP_REGISTER 0
#define UART_SIM_TRUE_BAUD 0
#define UART_SIM_CHAR_STREAM ""
#define UART_FREQ 100000000
#define ALT_MODULE_CLASS_uart altera_avalon_uart

/*
 * timer_0 configuration
 *
 */

#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_TYPE "altera_avalon_timer"
#define TIMER_0_BASE 0x00681020
#define TIMER_0_SPAN 32
#define TIMER_0_IRQ 3
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_LOAD_VALUE 99999
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_MULT 0.0010
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_FREQ 100000000
#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer

/*
 * timer_1 configuration
 *
 */

#define TIMER_1_NAME "/dev/timer_1"
#define TIMER_1_TYPE "altera_avalon_timer"
#define TIMER_1_BASE 0x00681040
#define TIMER_1_SPAN 32
#define TIMER_1_IRQ 4
#define TIMER_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_1_ALWAYS_RUN 0
#define TIMER_1_FIXED_PERIOD 0
#define TIMER_1_SNAPSHOT 1
#define TIMER_1_PERIOD 1
#define TIMER_1_PERIOD_UNITS "ms"
#define TIMER_1_RESET_OUTPUT 0
#define TIMER_1_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_1_LOAD_VALUE 99999
#define TIMER_1_COUNTER_SIZE 32
#define TIMER_1_MULT 0.0010
#define TIMER_1_TICKS_PER_SEC 1000
#define TIMER_1_FREQ 100000000
#define ALT_MODULE_CLASS_timer_1 altera_avalon_timer

/*
 * lcd configuration
 *
 */

#define LCD_NAME "/dev/lcd"
#define LCD_TYPE "altera_avalon_lcd_16207"
#define LCD_BASE 0x00681060
#define LCD_SPAN 16
#define ALT_MODULE_CLASS_lcd altera_avalon_lcd_16207

/*
 * led_red configuration
 *
 */

#define LED_RED_NAME "/dev/led_red"
#define LED_RED_TYPE "altera_avalon_pio"
#define LED_RED_BASE 0x00681070
#define LED_RED_SPAN 16
#define LED_RED_DO_TEST_BENCH_WIRING 0
#define LED_RED_DRIVEN_SIM_VALUE 0
#define LED_RED_HAS_TRI 0
#define LED_RED_HAS_OUT 1
#define LED_RED_HAS_IN 0
#define LED_RED_CAPTURE 0
#define LED_RED_DATA_WIDTH 18
#define LED_RED_RESET_VALUE 0
#define LED_RED_EDGE_TYPE "NONE"
#define LED_RED_IRQ_TYPE "NONE"
#define LED_RED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_RED_FREQ 100000000
#define ALT_MODULE_CLASS_led_red altera_avalon_pio

/*
 * led_green configuration
 *
 */

#define LED_GREEN_NAME "/dev/led_green"
#define LED_GREEN_TYPE "altera_avalon_pio"
#define LED_GREEN_BASE 0x00681080
#define LED_GREEN_SPAN 16
#define LED_GREEN_DO_TEST_BENCH_WIRING 0
#define LED_GREEN_DRIVEN_SIM_VALUE 0
#define LED_GREEN_HAS_TRI 0
#define LED_GREEN_HAS_OUT 1
#define LED_GREEN_HAS_IN 0
#define LED_GREEN_CAPTURE 0
#define LED_GREEN_DATA_WIDTH 9
#define LED_GREEN_RESET_VALUE 0
#define LED_GREEN_EDGE_TYPE "NONE"
#define LED_GREEN_IRQ_TYPE "NONE"
#define LED_GREEN_BIT_CLEARING_EDGE_REGISTER 0
#define LED_GREEN_FREQ 100000000
#define ALT_MODULE_CLASS_led_green altera_avalon_pio

/*
 * button_pio configuration
 *
 */

#define BUTTON_PIO_NAME "/dev/button_pio"
#define BUTTON_PIO_TYPE "altera_avalon_pio"
#define BUTTON_PIO_BASE 0x00681090
#define BUTTON_PIO_SPAN 16
#define BUTTON_PIO_IRQ 5
#define BUTTON_PIO_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTON_PIO_DO_TEST_BENCH_WIRING 0
#define BUTTON_PIO_DRIVEN_SIM_VALUE 0
#define BUTTON_PIO_HAS_TRI 0
#define BUTTON_PIO_HAS_OUT 0
#define BUTTON_PIO_HAS_IN 1
#define BUTTON_PIO_CAPTURE 1
#define BUTTON_PIO_DATA_WIDTH 4
#define BUTTON_PIO_RESET_VALUE 0
#define BUTTON_PIO_EDGE_TYPE "FALLING"
#define BUTTON_PIO_IRQ_TYPE "EDGE"
#define BUTTON_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_PIO_FREQ 100000000
#define ALT_MODULE_CLASS_button_pio altera_avalon_pio

/*
 * switch_pio configuration
 *
 */

#define SWITCH_PIO_NAME "/dev/switch_pio"
#define SWITCH_PIO_TYPE "altera_avalon_pio"
#define SWITCH_PIO_BASE 0x006810a0
#define SWITCH_PIO_SPAN 16
#define SWITCH_PIO_DO_TEST_BENCH_WIRING 0
#define SWITCH_PIO_DRIVEN_SIM_VALUE 0
#define SWITCH_PIO_HAS_TRI 0
#define SWITCH_PIO_HAS_OUT 0
#define SWITCH_PIO_HAS_IN 1
#define SWITCH_PIO_CAPTURE 0
#define SWITCH_PIO_DATA_WIDTH 18
#define SWITCH_PIO_RESET_VALUE 0
#define SWITCH_PIO_EDGE_TYPE "NONE"
#define SWITCH_PIO_IRQ_TYPE "NONE"
#define SWITCH_PIO_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_PIO_FREQ 100000000
#define ALT_MODULE_CLASS_switch_pio altera_avalon_pio

/*
 * ssram configuration
 *
 */

#define SSRAM_NAME "/dev/ssram"
#define SSRAM_TYPE "sram_16bit_512k"
#define SSRAM_BASE 0x00600000
#define SSRAM_SPAN 524288
#define SSRAM_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ssram sram_16bit_512k

/*
 * DM9000A configuration
 *
 */

#define DM9000A_NAME "/dev/DM9000A"
#define DM9000A_TYPE "dm9000a"
#define DM9000A_BASE 0x006810f8
#define DM9000A_SPAN 8
#define DM9000A_IRQ 6
#define DM9000A_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DM9000A_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_DM9000A dm9000a

/*
 * ISP1362/avalon_slave_0 configuration
 *
 */

#define ISP1362_AVALON_SLAVE_0_NAME "/dev/ISP1362"
#define ISP1362_AVALON_SLAVE_0_TYPE "isp1362"
#define ISP1362_AVALON_SLAVE_0_BASE 0x006810b0
#define ISP1362_AVALON_SLAVE_0_SPAN 16
#define ISP1362_AVALON_SLAVE_0_IRQ 7
#define ISP1362_AVALON_SLAVE_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ISP1362_AVALON_SLAVE_0_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ISP1362 isp1362

/*
 * ISP1362/avalon_slave_1 configuration
 *
 */

#define ISP1362_AVALON_SLAVE_1_NAME "/dev/ISP1362"
#define ISP1362_AVALON_SLAVE_1_TYPE "isp1362"
#define ISP1362_AVALON_SLAVE_1_IRQ 8
#define ISP1362_AVALON_SLAVE_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ISP1362_AVALON_SLAVE_1_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ISP1362 isp1362

/*
 * VGA_0 configuration
 *
 */

#define VGA_0_NAME "/dev/VGA_0"
#define VGA_0_TYPE "binary_vga_controller"
#define VGA_0_BASE 0x00400000
#define VGA_0_SPAN 2097152
#define ALT_MODULE_CLASS_VGA_0 binary_vga_controller

/*
 * Audio_0 configuration
 *
 */

#define AUDIO_0_NAME "/dev/Audio_0"
#define AUDIO_0_TYPE "audio_dac_fifo"
#define AUDIO_0_BASE 0x00681104
#define AUDIO_0_SPAN 4
#define ALT_MODULE_CLASS_Audio_0 audio_dac_fifo

/*
 * SD_DAT configuration
 *
 */

#define SD_DAT_NAME "/dev/SD_DAT"
#define SD_DAT_TYPE "altera_avalon_pio"
#define SD_DAT_BASE 0x006810c0
#define SD_DAT_SPAN 16
#define SD_DAT_DO_TEST_BENCH_WIRING 0
#define SD_DAT_DRIVEN_SIM_VALUE 0
#define SD_DAT_HAS_TRI 1
#define SD_DAT_HAS_OUT 0
#define SD_DAT_HAS_IN 0
#define SD_DAT_CAPTURE 0
#define SD_DAT_DATA_WIDTH 1
#define SD_DAT_RESET_VALUE 0
#define SD_DAT_EDGE_TYPE "NONE"
#define SD_DAT_IRQ_TYPE "NONE"
#define SD_DAT_BIT_CLEARING_EDGE_REGISTER 0
#define SD_DAT_FREQ 100000000
#define ALT_MODULE_CLASS_SD_DAT altera_avalon_pio

/*
 * SD_CMD configuration
 *
 */

#define SD_CMD_NAME "/dev/SD_CMD"
#define SD_CMD_TYPE "altera_avalon_pio"
#define SD_CMD_BASE 0x006810d0
#define SD_CMD_SPAN 16
#define SD_CMD_DO_TEST_BENCH_WIRING 0
#define SD_CMD_DRIVEN_SIM_VALUE 0
#define SD_CMD_HAS_TRI 1
#define SD_CMD_HAS_OUT 0
#define SD_CMD_HAS_IN 0
#define SD_CMD_CAPTURE 0
#define SD_CMD_DATA_WIDTH 1
#define SD_CMD_RESET_VALUE 0
#define SD_CMD_EDGE_TYPE "NONE"
#define SD_CMD_IRQ_TYPE "NONE"
#define SD_CMD_BIT_CLEARING_EDGE_REGISTER 0
#define SD_CMD_FREQ 100000000
#define ALT_MODULE_CLASS_SD_CMD altera_avalon_pio

/*
 * SD_CLK configuration
 *
 */

#define SD_CLK_NAME "/dev/SD_CLK"
#define SD_CLK_TYPE "altera_avalon_pio"
#define SD_CLK_BASE 0x006810e0
#define SD_CLK_SPAN 16
#define SD_CLK_DO_TEST_BENCH_WIRING 0
#define SD_CLK_DRIVEN_SIM_VALUE 0
#define SD_CLK_HAS_TRI 0
#define SD_CLK_HAS_OUT 1
#define SD_CLK_HAS_IN 0
#define SD_CLK_CAPTURE 0
#define SD_CLK_DATA_WIDTH 1
#define SD_CLK_RESET_VALUE 0
#define SD_CLK_EDGE_TYPE "NONE"
#define SD_CLK_IRQ_TYPE "NONE"
#define SD_CLK_BIT_CLEARING_EDGE_REGISTER 0
#define SD_CLK_FREQ 100000000
#define ALT_MODULE_CLASS_SD_CLK altera_avalon_pio

/*
 * camera configuration
 *
 */

#define CAMERA_NAME "/dev/camera"
#define CAMERA_TYPE "CAMERA_IF"
#define CAMERA_BASE 0x00681110
#define CAMERA_SPAN 16
#define CAMERA_TERMINATED_PORTS ""
#define ALT_MODULE_CLASS_camera CAMERA_IF

/*
 * system library configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK none

/*
 * Devices associated with code sections.
 *
 */

#define ALT_TEXT_DEVICE       SSRAM
#define ALT_RODATA_DEVICE     SSRAM
#define ALT_RWDATA_DEVICE     SSRAM
#define ALT_EXCEPTIONS_DEVICE SSRAM
#define ALT_RESET_DEVICE      SSRAM

/*
 * The text section is initialised so no bootloader will be required.
 * Set a variable to tell crt0.S to provide code at the reset address and
 * to initialise rwdata if appropriate.
 */

#define ALT_NO_BOOTLOADER


#endif /* __SYSTEM_H_ */
