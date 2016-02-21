// --------------------------------------------------------------------
// Copyright (c) 2005 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------
//
// Major Functions:	DE2 NIOS Reference Design
//
// --------------------------------------------------------------------
//
// Revision History :
// --------------------------------------------------------------------
//   Ver  :| Author            :| Mod. Date :| Changes Made:
//   V2.0 :| Johnny Chen       :| 06/07/19  :|      Initial Revision
// --------------------------------------------------------------------

module DE2_NIOS_HOST_MOUSE_VGA
	(
		////////////////////	Clock Input	 	////////////////////	 
		CLOCK_27,						//	On Board 27 MHz
		CLOCK_50,						//	On Board 50 MHz
		EXT_CLOCK,						//	External Clock
		////////////////////	Push Button		////////////////////
		KEY,							//	Pushbutton[3:0]
		////////////////////	DPDT Switch		////////////////////
		SW,								//	Toggle Switch[17:0]
		////////////////////	7-SEG Dispaly	////////////////////
		HEX0,							//	Seven Segment Digit 0
		HEX1,							//	Seven Segment Digit 1
		HEX2,							//	Seven Segment Digit 2
		HEX3,							//	Seven Segment Digit 3
		HEX4,							//	Seven Segment Digit 4
		HEX5,							//	Seven Segment Digit 5
		HEX6,							//	Seven Segment Digit 6
		HEX7,							//	Seven Segment Digit 7
		////////////////////////	LED		////////////////////////
		LEDG,							//	LED Green[8:0]
		LEDR,							//	LED Red[17:0]
		////////////////////////	UART	////////////////////////
		UART_TXD,						//	UART Transmitter
		UART_RXD,						//	UART Receiver
		////////////////////////	IRDA	////////////////////////
		IRDA_TXD,						//	IRDA Transmitter
		IRDA_RXD,						//	IRDA Receiver
		/////////////////////	SDRAM Interface		////////////////
		DRAM_DQ,						//	SDRAM Data bus 16 Bits
		DRAM_ADDR,						//	SDRAM Address bus 12 Bits
		DRAM_LDQM,						//	SDRAM Low-byte Data Mask 
		DRAM_UDQM,						//	SDRAM High-byte Data Mask
		DRAM_WE_N,						//	SDRAM Write Enable
		DRAM_CAS_N,						//	SDRAM Column Address Strobe
		DRAM_RAS_N,						//	SDRAM Row Address Strobe
		DRAM_CS_N,						//	SDRAM Chip Select
		DRAM_BA_0,						//	SDRAM Bank Address 0
		DRAM_BA_1,						//	SDRAM Bank Address 1
		DRAM_CLK,						//	SDRAM Clock
		DRAM_CKE,						//	SDRAM Clock Enable
		////////////////////	Flash Interface		////////////////
		FL_DQ,							//	FLASH Data bus 8 Bits
		FL_ADDR,						//	FLASH Address bus 20 Bits
		FL_WE_N,						//	FLASH Write Enable
		FL_RST_N,						//	FLASH Reset
		FL_OE_N,						//	FLASH Output Enable
		FL_CE_N,						//	FLASH Chip Enable
		////////////////////	SRAM Interface		////////////////
		SRAM_DQ,						//	SRAM Data bus 16 Bits
		SRAM_ADDR,						//	SRAM Address bus 18 Bits
		SRAM_UB_N,						//	SRAM High-byte Data Mask
		SRAM_LB_N,						//	SRAM Low-byte Data Mask  
		SRAM_WE_N,						//	SRAM Write Enable
		SRAM_CE_N,						//	SRAM Chip Enable
		SRAM_OE_N,						//	SRAM Output Enable
		////////////////////	ISP1362 Interface	////////////////
		OTG_DATA,						//	ISP1362 Data bus 16 Bits
		OTG_ADDR,						//	ISP1362 Address 2 Bits
		OTG_CS_N,						//	ISP1362 Chip Select
		OTG_RD_N,						//	ISP1362 Write
		OTG_WR_N,						//	ISP1362 Read
		OTG_RST_N,						//	ISP1362 Reset
		OTG_FSPEED,						//	USB Full Speed,	0 = Enable, Z = Disable
		OTG_LSPEED,						//	USB Low Speed, 	0 = Enable, Z = Disable
		OTG_INT0,						//	ISP1362 Interrupt 0
		OTG_INT1,						//	ISP1362 Interrupt 1
		OTG_DREQ0,						//	ISP1362 DMA Request 0
		OTG_DREQ1,						//	ISP1362 DMA Request 1
		OTG_DACK0_N,					//	ISP1362 DMA Acknowledge 0
		OTG_DACK1_N,					//	ISP1362 DMA Acknowledge 1
		////////////////////	LCD Module 16X2		////////////////
		LCD_ON,							//	LCD Power ON/OFF
		LCD_BLON,						//	LCD Back Light ON/OFF
		LCD_RW,							//	LCD Read/Write Select, 0 = Write, 1 = Read
		LCD_EN,							//	LCD Enable
		LCD_RS,							//	LCD Command/Data Select, 0 = Command, 1 = Data
		LCD_DATA,						//	LCD Data bus 8 bits
		////////////////////	SD_Card Interface	////////////////
		SD_DAT,							//	SD Card Data
		SD_DAT3,						//	SD Card Data 3
		SD_CMD,							//	SD Card Command Signal
		SD_CLK,							//	SD Card Clock
		////////////////////	USB JTAG link	////////////////////
		TDI,  							//	CPLD -> FPGA (Data in)
		TCK,  							//	CPLD -> FPGA (Clock)
		TCS,  							//	CPLD -> FPGA (CS)
	    TDO,  							//	FPGA -> CPLD (Data out)
		////////////////////	I2C		////////////////////////////
		I2C_SDAT,						//	I2C Data
		I2C_SCLK,						//	I2C Clock
		////////////////////	PS2		////////////////////////////
		PS2_DAT,						//	PS2 Data
		PS2_CLK,						//	PS2 Clock
		////////////////////	VGA		////////////////////////////
		VGA_CLK,   						//	VGA Clock
		VGA_HS,							//	VGA H_SYNC
		VGA_VS,							//	VGA V_SYNC
		VGA_BLANK,						//	VGA BLANK
		VGA_SYNC,						//	VGA SYNC
		VGA_R,   						//	VGA Red[9:0]
		VGA_G,	 						//	VGA Green[9:0]
		VGA_B,  						//	VGA Blue[9:0]
		////////////	Ethernet Interface	////////////////////////
		ENET_DATA,						//	DM9000A DATA bus 16Bits
		ENET_CMD,						//	DM9000A Command/Data Select, 0 = Command, 1 = Data
		ENET_CS_N,						//	DM9000A Chip Select
		ENET_WR_N,						//	DM9000A Write
		ENET_RD_N,						//	DM9000A Read
		ENET_RST_N,						//	DM9000A Reset
		ENET_INT,						//	DM9000A Interrupt
		ENET_CLK,						//	DM9000A Clock 25 MHz
		////////////////	Audio CODEC		////////////////////////
		AUD_ADCLRCK,					//	Audio CODEC ADC LR Clock
		AUD_ADCDAT,						//	Audio CODEC ADC Data
		AUD_DACLRCK,					//	Audio CODEC DAC LR Clock
		AUD_DACDAT,						//	Audio CODEC DAC Data
		AUD_BCLK,						//	Audio CODEC Bit-Stream Clock
		AUD_XCK,						//	Audio CODEC Chip Clock
		////////////////	TV Decoder		////////////////////////
		TD_DATA,    					//	TV Decoder Data bus 8 bits
		TD_HS,							//	TV Decoder H_SYNC
		TD_VS,							//	TV Decoder V_SYNC
		TD_RESET,						//	TV Decoder Reset
		////////////////////	GPIO	////////////////////////////
		GPIO_0,							//	GPIO Connection 0
		GPIO_1							//	GPIO Connection 1
	);

////////////////////////	Clock Input	 	////////////////////////
input			CLOCK_27;				//	On Board 27 MHz
input			CLOCK_50;				//	On Board 50 MHz
input			EXT_CLOCK;				//	External Clock
////////////////////////	Push Button		////////////////////////
input	[3:0]	KEY;					//	Pushbutton[3:0]
////////////////////////	DPDT Switch		////////////////////////
input	[17:0]	SW;						//	Toggle Switch[17:0]
////////////////////////	7-SEG Display	////////////////////////
output	[6:0]	HEX0;					//	Seven Segment Digit 0
output	[6:0]	HEX1;					//	Seven Segment Digit 1
output	[6:0]	HEX2;					//	Seven Segment Digit 2
output	[6:0]	HEX3;					//	Seven Segment Digit 3
output	[6:0]	HEX4;					//	Seven Segment Digit 4
output	[6:0]	HEX5;					//	Seven Segment Digit 5
output	[6:0]	HEX6;					//	Seven Segment Digit 6
output	[6:0]	HEX7;					//	Seven Segment Digit 7
////////////////////////////	LED		////////////////////////////
output	[8:0]	LEDG;					//	LED Green[8:0]
output	[17:0]	LEDR;					//	LED Red[17:0]
////////////////////////////	UART	////////////////////////////
output			UART_TXD;				//	UART Transmitter
input			UART_RXD;				//	UART Receiver
////////////////////////////	IRDA	////////////////////////////
output			IRDA_TXD;				//	IRDA Transmitter
input			IRDA_RXD;				//	IRDA Receiver
///////////////////////		SDRAM Interface	////////////////////////
inout	[15:0]	DRAM_DQ;				//	SDRAM Data bus 16 Bits
output	[11:0]	DRAM_ADDR;				//	SDRAM Address bus 12 Bits
output			DRAM_LDQM;				//	SDRAM Low-byte Data Mask 
output			DRAM_UDQM;				//	SDRAM High-byte Data Mask
output			DRAM_WE_N;				//	SDRAM Write Enable
output			DRAM_CAS_N;				//	SDRAM Column Address Strobe
output			DRAM_RAS_N;				//	SDRAM Row Address Strobe
output			DRAM_CS_N;				//	SDRAM Chip Select
output			DRAM_BA_0;				//	SDRAM Bank Address 0
output			DRAM_BA_1;				//	SDRAM Bank Address 0
output			DRAM_CLK;				//	SDRAM Clock
output			DRAM_CKE;				//	SDRAM Clock Enable
////////////////////////	Flash Interface	////////////////////////
inout	[7:0]	FL_DQ;					//	FLASH Data bus 8 Bits
output	[21:0]	FL_ADDR;				//	FLASH Address bus 22 Bits
output			FL_WE_N;				//	FLASH Write Enable
output			FL_RST_N;				//	FLASH Reset
output			FL_OE_N;				//	FLASH Output Enable
output			FL_CE_N;				//	FLASH Chip Enable
////////////////////////	SRAM Interface	////////////////////////
inout	[15:0]	SRAM_DQ;				//	SRAM Data bus 16 Bits
output	[17:0]	SRAM_ADDR;				//	SRAM Address bus 18 Bits
output			SRAM_UB_N;				//	SRAM Low-byte Data Mask 
output			SRAM_LB_N;				//	SRAM High-byte Data Mask 
output			SRAM_WE_N;				//	SRAM Write Enable
output			SRAM_CE_N;				//	SRAM Chip Enable
output			SRAM_OE_N;				//	SRAM Output Enable
////////////////////	ISP1362 Interface	////////////////////////
inout	[15:0]	OTG_DATA;				//	ISP1362 Data bus 16 Bits
output	[1:0]	OTG_ADDR;				//	ISP1362 Address 2 Bits
output			OTG_CS_N;				//	ISP1362 Chip Select
output			OTG_RD_N;				//	ISP1362 Write
output			OTG_WR_N;				//	ISP1362 Read
output			OTG_RST_N;				//	ISP1362 Reset
output			OTG_FSPEED;				//	USB Full Speed,	0 = Enable, Z = Disable
output			OTG_LSPEED;				//	USB Low Speed, 	0 = Enable, Z = Disable
input			OTG_INT0;				//	ISP1362 Interrupt 0
input			OTG_INT1;				//	ISP1362 Interrupt 1
input			OTG_DREQ0;				//	ISP1362 DMA Request 0
input			OTG_DREQ1;				//	ISP1362 DMA Request 1
output			OTG_DACK0_N;			//	ISP1362 DMA Acknowledge 0
output			OTG_DACK1_N;			//	ISP1362 DMA Acknowledge 1
////////////////////	LCD Module 16X2	////////////////////////////
inout	[7:0]	LCD_DATA;				//	LCD Data bus 8 bits
output			LCD_ON;					//	LCD Power ON/OFF
output			LCD_BLON;				//	LCD Back Light ON/OFF
output			LCD_RW;					//	LCD Read/Write Select, 0 = Write, 1 = Read
output			LCD_EN;					//	LCD Enable
output			LCD_RS;					//	LCD Command/Data Select, 0 = Command, 1 = Data
////////////////////	SD Card Interface	////////////////////////
inout			SD_DAT;					//	SD Card Data
inout			SD_DAT3;				//	SD Card Data 3
inout			SD_CMD;					//	SD Card Command Signal
output			SD_CLK;					//	SD Card Clock
////////////////////////	I2C		////////////////////////////////
inout			I2C_SDAT;				//	I2C Data
output			I2C_SCLK;				//	I2C Clock
////////////////////////	PS2		////////////////////////////////
input		 	PS2_DAT;				//	PS2 Data
input			PS2_CLK;				//	PS2 Clock
////////////////////	USB JTAG link	////////////////////////////
input  			TDI;					// CPLD -> FPGA (data in)
input  			TCK;					// CPLD -> FPGA (clk)
input  			TCS;					// CPLD -> FPGA (CS)
output 			TDO;					// FPGA -> CPLD (data out)
////////////////////////	VGA			////////////////////////////
output			VGA_CLK;   				//	VGA Clock
output			VGA_HS;					//	VGA H_SYNC
output			VGA_VS;					//	VGA V_SYNC
output			VGA_BLANK;				//	VGA BLANK
output			VGA_SYNC;				//	VGA SYNC
output	[9:0]	VGA_R;   				//	VGA Red[9:0]
output	[9:0]	VGA_G;	 				//	VGA Green[9:0]
output	[9:0]	VGA_B;   				//	VGA Blue[9:0]
////////////////	Ethernet Interface	////////////////////////////
inout	[15:0]	ENET_DATA;				//	DM9000A DATA bus 16Bits
output			ENET_CMD;				//	DM9000A Command/Data Select, 0 = Command, 1 = Data
output			ENET_CS_N;				//	DM9000A Chip Select
output			ENET_WR_N;				//	DM9000A Write
output			ENET_RD_N;				//	DM9000A Read
output			ENET_RST_N;				//	DM9000A Reset
input			ENET_INT;				//	DM9000A Interrupt
output			ENET_CLK;				//	DM9000A Clock 25 MHz
////////////////////	Audio CODEC		////////////////////////////
inout			AUD_ADCLRCK;			//	Audio CODEC ADC LR Clock
input			AUD_ADCDAT;				//	Audio CODEC ADC Data
inout			AUD_DACLRCK;			//	Audio CODEC DAC LR Clock
output			AUD_DACDAT;				//	Audio CODEC DAC Data
inout			AUD_BCLK;				//	Audio CODEC Bit-Stream Clock
output			AUD_XCK;				//	Audio CODEC Chip Clock
////////////////////	TV Devoder		////////////////////////////
input	[7:0]	TD_DATA;    			//	TV Decoder Data bus 8 bits
input			TD_HS;					//	TV Decoder H_SYNC
input			TD_VS;					//	TV Decoder V_SYNC
output			TD_RESET;				//	TV Decoder Reset
////////////////////////	GPIO	////////////////////////////////
inout	[35:0]	GPIO_0;					//	GPIO Connection 0
inout	[35:0]	GPIO_1;					//	GPIO Connection 1

wire	CPU_CLK;
wire	CPU_RESET;
wire	CLK_18_4;
wire	CLK_25;

//	Flash
assign	FL_RST_N	=	1'b1;

//	16*2 LCD Module
assign	LCD_ON		=	1'b1;	//	LCD ON
assign	LCD_BLON	=	1'b1;	//	LCD Back Light	

//	All inout port turn to tri-state
assign	SD_DAT		=	1'bz;
assign	AUD_ADCLRCK	=	AUD_DACLRCK;
assign	GPIO_0		=	36'hzzzzzzzzz;
assign	GPIO_1		=	36'hzzzzzzzzz;

//	Disable USB speed select
assign	OTG_FSPEED	=	1'bz;
assign	OTG_LSPEED	=	1'bz;

//	Turn On TV Decoder
assign	TD_RESET	=	1'b1;

//	Set SD Card to SD Mode
assign	SD_DAT3		=	1'b1;

Reset_Delay	delay1	(.iRST(KEY[0]),.iCLK(CLOCK_50),.oRESET(CPU_RESET));

SDRAM_PLL 	PLL1	(.inclk0(CLOCK_50),.c0(DRAM_CLK),.c1(CPU_CLK),.c2(CLK_25));
Audio_PLL 	PLL2	(.areset(!CPU_RESET),.inclk0(CLOCK_27),.c0(CLK_18_4));


//	CCD
wire	[11:0]	CCD_DATA;
wire			CCD_SDAT;
wire			CCD_SCLK;
wire			CCD_FLASH;
wire			CCD_FVAL;
wire			CCD_LVAL;
wire			CCD_PIXCLK;
wire			CCD_MCLK;				//	CCD Master Clock

wire	[15:0]	Read_DATA1;
wire	[15:0]	Read_DATA2;
wire			VGA_CTRL_CLK;
wire	[11:0]	mCCD_DATA;
wire			mCCD_DVAL;
wire			mCCD_DVAL_d;
wire	[15:0]	X_Cont;
wire	[15:0]	Y_Cont;
wire	[9:0]	X_ADDR;
wire	[31:0]	Frame_Cont;
wire			DLY_RST_0;
wire			DLY_RST_1;
wire			DLY_RST_2;
wire			Read;
reg		[11:0]	rCCD_DATA;
reg				rCCD_LVAL;
reg				rCCD_FVAL;
wire	[11:0]	sCCD_R;
wire	[11:0]	sCCD_G;
wire	[11:0]	sCCD_B;
wire			sCCD_DVAL;
wire	[9:0]	VGA_R;   				//	VGA Red[9:0]
wire	[9:0]	VGA_G;	 				//	VGA Green[9:0]
wire	[9:0]	VGA_B;   				//	VGA Blue[9:0]
reg		[1:0]	rClk;
wire			sdram_ctrl_clk;

//========== interface to SDRAM read port ============
wire		[15:0]			PORT_READ_DATA_1;
wire		[15:0]			PORT_READ_DATA_2;
wire						PORT_READ;
wire		[22:0]			PORT_ADDR;
wire		[22:0]			PORT_MAX_ADDR;
wire		[8:0]			PORT_LENGTH;
wire						PORT_LOAD;
wire						PORT_CLK;

//wire	CLK_25;
//=============================================================================
// Structural coding
//=============================================================================
assign	CCD_DATA[0]	=	GPIO_1[13];
assign	CCD_DATA[1]	=	GPIO_1[12];
assign	CCD_DATA[2]	=	GPIO_1[11];
assign	CCD_DATA[3]	=	GPIO_1[10];
assign	CCD_DATA[4]	=	GPIO_1[9];
assign	CCD_DATA[5]	=	GPIO_1[8];
assign	CCD_DATA[6]	=	GPIO_1[7];
assign	CCD_DATA[7]	=	GPIO_1[6];
assign	CCD_DATA[8]	=	GPIO_1[5];
assign	CCD_DATA[9]	=	GPIO_1[4];
assign	CCD_DATA[10]=	GPIO_1[3];
assign	CCD_DATA[11]=	GPIO_1[1];
assign	GPIO_1[16]	=	CCD_MCLK;
assign	CCD_FVAL	=	GPIO_1[22];
assign	CCD_LVAL	=	GPIO_1[21];
assign	CCD_PIXCLK	=	GPIO_1[0];
assign	GPIO_1[19]	=	1'b1;  // tRIGGER
assign	GPIO_1[17]	=	DLY_RST_1;

always@(posedge CCD_PIXCLK)
begin
	rCCD_DATA	<=	CCD_DATA;
	rCCD_LVAL	<=	CCD_LVAL;
	rCCD_FVAL	<=	CCD_FVAL;
end
assign	LEDG		=	Y_Cont;

always@(posedge CLOCK_50)	rClk	<=	rClk+1;

assign CCD_MCLK = rClk[0];

// sopc ip export pin
wire		[1:0]		camera_addr;
wire					camera_clk;
wire					camera_read;
wire		[31:0]		camera_readdata;
wire					camera_reset;
wire					camera_write;
wire		[31:0]		camera_writedata;

system_0 	u0	(
				// 1) global signals:
                 .clk(CPU_CLK),
				 //.clk_50(CLOCK_50),
                 .reset_n(CPU_RESET),

                // the_Audio_0
                 .iCLK_18_4_to_the_Audio_0(CLK_18_4),
                 .oAUD_BCK_from_the_Audio_0(AUD_BCLK),
                 .oAUD_DATA_from_the_Audio_0(AUD_DACDAT),
                 .oAUD_LRCK_from_the_Audio_0(AUD_DACLRCK),
                 .oAUD_XCK_from_the_Audio_0(AUD_XCK),

                // the_VGA_0
                 .VGA_BLANK_from_the_VGA_0(VGA_BLANK),
                 .VGA_B_from_the_VGA_0(VGA_B),
                 .VGA_CLK_from_the_VGA_0(VGA_CLK),
                 .VGA_G_from_the_VGA_0(VGA_G),
                 .VGA_HS_from_the_VGA_0(VGA_HS),
                 .VGA_R_from_the_VGA_0(VGA_R),
                 .VGA_SYNC_from_the_VGA_0(VGA_SYNC),
                 .VGA_VS_from_the_VGA_0(VGA_VS),
                 .iCLK_25_to_the_VGA_0(CLK_25),

                // the_SD_CLK
                 .out_port_from_the_SD_CLK(SD_CLK),

                // the_SD_CMD
                 .bidir_port_to_and_from_the_SD_CMD(SD_CMD),

                // the_SD_DAT
                 .bidir_port_to_and_from_the_SD_DAT(SD_DAT),

                // the_SEG7_Display
                /*
                 .oSEG0_from_the_SEG7_Display(HEX0),
                 .oSEG1_from_the_SEG7_Display(HEX1),
                 .oSEG2_from_the_SEG7_Display(HEX2),
                 .oSEG3_from_the_SEG7_Display(HEX3),
                 .oSEG4_from_the_SEG7_Display(HEX4),
                 .oSEG5_from_the_SEG7_Display(HEX5),
                 .oSEG6_from_the_SEG7_Display(HEX6),
                 .oSEG7_from_the_SEG7_Display(HEX7),
*/
                // the_DM9000A
				 .ENET_CLK_from_the_DM9000A(ENET_CLK),
                 .ENET_CMD_from_the_DM9000A(ENET_CMD),
                 .ENET_CS_N_from_the_DM9000A(ENET_CS_N),
                 .ENET_DATA_to_and_from_the_DM9000A(ENET_DATA),
                 .ENET_INT_to_the_DM9000A(ENET_INT),
                 .ENET_RD_N_from_the_DM9000A(ENET_RD_N),
                 .ENET_RST_N_from_the_DM9000A(ENET_RST_N),
                 .ENET_WR_N_from_the_DM9000A(ENET_WR_N),
				 .iOSC_50_to_the_DM9000A(CLOCK_50),
				
                // the_ISP1362
                 .OTG_ADDR_from_the_ISP1362(OTG_ADDR),
                 .OTG_CS_N_from_the_ISP1362(OTG_CS_N),
                 .OTG_DATA_to_and_from_the_ISP1362(OTG_DATA),
                 .OTG_INT0_to_the_ISP1362(OTG_INT0),
                 .OTG_INT1_to_the_ISP1362(OTG_INT1),
                 .OTG_RD_N_from_the_ISP1362(OTG_RD_N),
                 .OTG_RST_N_from_the_ISP1362(OTG_RST_N),
                 .OTG_WR_N_from_the_ISP1362(OTG_WR_N),

                // the_button_pio
                 .in_port_to_the_button_pio(KEY),

                // the_lcd_16207_0
/*
                 .LCD_E_from_the_lcd_16207_0(LCD_EN),
                 .LCD_RS_from_the_lcd_16207_0(LCD_RS),
                 .LCD_RW_from_the_lcd_16207_0(LCD_RW),
                 .LCD_data_to_and_from_the_lcd_16207_0(LCD_DATA),
*/
                // the_led_green
//                 .out_port_from_the_led_green(LEDG),

                // the_led_red
//                 .out_port_from_the_led_red(LEDR),

/*
                // the_sdram_0
                 .zs_addr_from_the_sdram_0(DRAM_ADDR),
                 .zs_ba_from_the_sdram_0({DRAM_BA_1,DRAM_BA_0}),
                 .zs_cas_n_from_the_sdram_0(DRAM_CAS_N),
                 .zs_cke_from_the_sdram_0(DRAM_CKE),
                 .zs_cs_n_from_the_sdram_0(DRAM_CS_N),
                 .zs_dq_to_and_from_the_sdram_0(DRAM_DQ),
                 .zs_dqm_from_the_sdram_0({DRAM_UDQM,DRAM_LDQM}),
                 .zs_ras_n_from_the_sdram_0(DRAM_RAS_N),
                 .zs_we_n_from_the_sdram_0(DRAM_WE_N),
*/
                  // the_sram_0
                 .SRAM_ADDR_from_the_ssram(SRAM_ADDR),
                 .SRAM_CE_N_from_the_ssram(SRAM_CE_N),
                 .SRAM_DQ_to_and_from_the_ssram(SRAM_DQ),
                 .SRAM_LB_N_from_the_ssram(SRAM_LB_N),
                 .SRAM_OE_N_from_the_ssram(SRAM_OE_N),
                 .SRAM_UB_N_from_the_ssram(SRAM_UB_N),
                 .SRAM_WE_N_from_the_ssram(SRAM_WE_N),

                // the_switch_pio
                 .in_port_to_the_switch_pio(SW),

                // the_tri_state_bridge_0_avalon_slave
                 .select_n_to_the_cfi_flash_0(FL_CE_N),
                 .tri_state_bridge_0_address(FL_ADDR),
                 .tri_state_bridge_0_data(FL_DQ),
                 .tri_state_bridge_0_readn(FL_OE_N),
                 .write_n_to_the_cfi_flash_0(FL_WE_N),

                     // the_camera
                      .avs_s1_export_address_from_the_camera(camera_addr),
                      .avs_s1_export_clk_from_the_camera(camera_clk),
                      .avs_s1_export_read_from_the_camera(camera_read),
                      .avs_s1_export_readdata_to_the_camera(camera_readdata),
                      .avs_s1_export_reset_from_the_camera(camera_reset),
                      .avs_s1_export_write_from_the_camera(camera_write),
                      .avs_s1_export_writedata_from_the_camera(camera_writedata),
                      
                      
                // the_uart_0
                 .rxd_to_the_uart(UART_RXD),
                 .txd_from_the_uart(UART_TXD)
                );

I2C_AV_Config 	u1	(	//	Host Side
						.iCLK(CLOCK_50),
						.iRST_N(KEY[0]),
						//	I2C Side
						.I2C_SCLK(I2C_SCLK),
						.I2C_SDAT(I2C_SDAT)	);



// port define
`define DATA_PORT		0
`define CMD_PORT		1
`define STATUS_PORT		2
`define TIGGLE_CNT_END	5

// ccd control
wire					CCD_CAPTURE_START;
wire					CCD_CAPTURE_STOP;
reg		[3:0]			tiggle_cnt;
reg		[3:0]			nios_tiggle_cnt;
reg						start_triggle;
reg						stop_triggle;
assign CCD_CAPTURE_START = !KEY[3] | start_triggle;
assign CCD_CAPTURE_STOP = !KEY[2] | stop_triggle;

//========== control start/stop triggle ==========
always @ (posedge CCD_PIXCLK)
begin
	if (DLY_RST_1 || (!start_triggle && !stop_triggle))
		tiggle_cnt = 0;
	else if (tiggle_cnt < `TIGGLE_CNT_END)
		tiggle_cnt = tiggle_cnt + 1;
end

//========== interface to nios2 ==========
always @ (negedge camera_clk)
begin
	if (camera_reset)
	begin
		start_triggle = 0;
		stop_triggle = 0;
		nios_tiggle_cnt = 0;
	end
	else 
	begin
		if (nios_tiggle_cnt < `TIGGLE_CNT_END)
			nios_tiggle_cnt = nios_tiggle_cnt + 1;
		
		if (camera_write && (camera_addr == `CMD_PORT))
		begin
			start_triggle = camera_writedata[0];
			stop_triggle = camera_writedata[1];
			nios_tiggle_cnt = 0;
		end
		else if ((tiggle_cnt == `TIGGLE_CNT_END) || (nios_tiggle_cnt == `TIGGLE_CNT_END) )
		begin
			start_triggle = 0;
			stop_triggle = 0;
		end
	end
end

//assign	camera_readdata = (camera_addr == `DATA_PORT)?{PORT_READ_DATA_2,PORT_READ_DATA_1}:32'hzzzzzzzz;
assign	camera_readdata = (camera_addr == `DATA_PORT)?{2'b00,PORT_READ_DATA_2[9:0],PORT_READ_DATA_1[14:10],PORT_READ_DATA_2[14:10],PORT_READ_DATA_1[9:0],PORT_READ_DATA_1}:32'hzzzzzzzz;
assign	PORT_READ = (camera_read && (camera_addr == `DATA_PORT))?1:0;
assign	PORT_CLK = ~camera_clk;
assign	PORT_ADDR = 0;


I2C_CCD_Config 		u8	(	//	Host Side
							.iCLK(CLOCK_50),
							.iRST_N(DLY_RST_2),
							.iZOOM_MODE_SW(SW[16]),
							.iEXPOSURE_ADJ(KEY[1]),
							.iEXPOSURE_DEC_p(SW[0]),
							//	I2C Side
							.I2C_SCLK(GPIO_1[24]),
							.I2C_SDAT(GPIO_1[23])
						);
						
C_Reset_Delay			u2	(	.iCLK(CLOCK_50),
							.iRST(KEY[0]),
							.oRST_0(DLY_RST_0),
							.oRST_1(DLY_RST_1),
							.oRST_2(DLY_RST_2)
						);

RAW2RGB				u4	(	.iCLK(CCD_PIXCLK),
							.iRST(DLY_RST_1),
							.iDATA(mCCD_DATA),
							.iDVAL(mCCD_DVAL),
							.oRed(sCCD_R),
							.oGreen(sCCD_G),
							.oBlue(sCCD_B),
							.oDVAL(sCCD_DVAL),
//							.iZoom(SW[17:16]),
							.iX_Cont(X_Cont),
							.iY_Cont(Y_Cont)
						);
						
CCD_Capture			u3	(	.oDATA(mCCD_DATA),
							.oDVAL(mCCD_DVAL),
							.oX_Cont(X_Cont),
							.oY_Cont(Y_Cont),
							.oFrame_Cont(Frame_Cont),
							.iDATA(rCCD_DATA),
							.iFVAL(rCCD_FVAL),
							.iLVAL(rCCD_LVAL),
//							.iSTART(!KEY[3]),
							.iSTART(CCD_CAPTURE_START),
//							.iEND(!KEY[2]),
							.iEND(CCD_CAPTURE_STOP),
							.iCLK(CCD_PIXCLK),
							.iRST(DLY_RST_2)
						);


Sdram_Control_4Port	u7	(	//	HOST Side						
						    .REF_CLK(CLOCK_50),
						    .RESET_N(1'b1),
							.CLK(DRAM_CLK),

							//	FIFO Write Side 1
							.WR1_DATA({1'b0,sCCD_G[11:7],sCCD_B[11:2]}),
//							.WR1_DATA(0),
							.WR1(sCCD_DVAL),
							.WR1_ADDR(0),
							.WR1_MAX_ADDR(640*480),
							.WR1_LENGTH(9'h100),
							.WR1_LOAD(!DLY_RST_0),
							.WR1_CLK(~CCD_PIXCLK),

							//	FIFO Write Side 2
							.WR2_DATA(	{1'b0,sCCD_G[6:2],sCCD_R[11:2]}),
//							.WR2_DATA(0),
							.WR2(sCCD_DVAL),
							.WR2_ADDR(22'h100000),
							.WR2_MAX_ADDR(22'h100000+640*480),
							.WR2_LENGTH(9'h100),
							.WR2_LOAD(!DLY_RST_0),
							.WR2_CLK(~CCD_PIXCLK),

`ifndef DISABLE_VGA
							//	FIFO Read Side 1
//						    .RD1_DATA(Read_DATA1),
						    .RD1_DATA(PORT_READ_DATA_1),
//				        	.RD1(Read),
				        	.RD1(PORT_READ),
				        	.RD1_ADDR(0),
							.RD1_MAX_ADDR(640*480),
							.RD1_LENGTH(9'h100),
							.RD1_LOAD(!DLY_RST_0),
//							.RD1_CLK(~VGA_CTRL_CLK),
							.RD1_CLK(PORT_CLK),
							//	FIFO Read Side 2
//						    .RD2_DATA(Read_DATA2),
						    .RD2_DATA(PORT_READ_DATA_2),
//							.RD2(Read),
							.RD2(PORT_READ),
							.RD2_ADDR(22'h100000),
							.RD2_MAX_ADDR(22'h100000+640*480),
							.RD2_LENGTH(9'h100),
				        	.RD2_LOAD(!DLY_RST_0),
//							.RD2_CLK(~VGA_CTRL_CLK),
							.RD2_CLK(PORT_CLK),
`endif //DISABLE_VGA							
							
							//	SDRAM Side
						    .SA(DRAM_ADDR),
						    .BA({DRAM_BA_1,DRAM_BA_0}),
        					.CS_N(DRAM_CS_N),
        					.CKE(DRAM_CKE),
        					.RAS_N(DRAM_RAS_N),
        					.CAS_N(DRAM_CAS_N),
        					.WE_N(DRAM_WE_N),
        					.DQ(DRAM_DQ),
        					.DQM({DRAM_UDQM,DRAM_LDQM})
						);


						
SEG7_LUT_8 			u5	(	.oSEG0(HEX0),.oSEG1(HEX1),
							.oSEG2(HEX2),.oSEG3(HEX3),
							.oSEG4(HEX4),.oSEG5(HEX5),
							.oSEG6(HEX6),.oSEG7(HEX7),
							.iDIG(Frame_Cont[31:0])
						);

reg dbg_reg;
always @ (negedge camera_clk)
begin
	if(camera_write)
	dbg_reg <= 1;
end						
//DEBUGING with LED
//assign LEDR[0] = CLK_25;
assign LEDR[1] = dbg_reg;
//assign LEDR[0] = camera_clk;
endmodule