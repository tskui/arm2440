#ifndef S3C2410_H
#define S3C2410_H
#include <QCoreApplication>
// Memory control
#define rBWSCON    (0x48000000)	//Bus width & wait status
#define rBANKCON0  (0x48000004)	//Boot ROM control
#define rBANKCON1  (0x48000008)	//BANK1 control
#define rBANKCON2  (0x4800000c)	//BANK2 cControl
#define rBANKCON3  (0x48000010)	//BANK3 control
#define rBANKCON4  (0x48000014)	//BANK4 control
#define rBANKCON5  (0x48000018)	//BANK5 control
#define rBANKCON6  (0x4800001c)	//BANK6 control
#define rBANKCON7  (0x48000020)	//BANK7 control
#define rREFRESH   (0x48000024)	//DRAM/SDRAM refresh
#define rBANKSIZE  (0x48000028)	//Flexible Bank Size
#define rMRSRB6    (0x4800002c)	//Mode register set for SDRAM
#define rMRSRB7    (0x48000030)	//Mode register set for SDRAM


// USB Host


// INTERRUPT
#define rSRCPND     (0x4a000000)	//Interrupt request status
#define rINTMOD     (0x4a000004)	//Interrupt mode control
#define rINTMSK     (0x4a000008)	//Interrupt mask control
#define rPRIORITY   (0x4a00000c)	//IRQ priority control
#define rINTPND     (0x4a000010)	//Interrupt request status
#define rINTOFFSET  (0x4a000014)	//Interruot request source offset
#define rSUBSRCPND  (0x4a000018)	//Sub source pending
#define rINTSUBMSK  (0x4a00001c)	//Interrupt sub mask


// DMA
#define rDISRC0     (0x4b000000)	//DMA 0 Initial source
#define rDISRCC0    (0x4b000004)	//DMA 0 Initial source control
#define rDIDST0     (0x4b000008)	//DMA 0 Initial Destination
#define rDIDSTC0    (0x4b00000c)	//DMA 0 Initial Destination control
#define rDCON0      (0x4b000010)	//DMA 0 Control
#define rDSTAT0     (0x4b000014)	//DMA 0 Status
#define rDCSRC0     (0x4b000018)	//DMA 0 Current source
#define rDCDST0     (0x4b00001c)	//DMA 0 Current destination
#define rDMASKTRIG0 (0x4b000020)	//DMA 0 Mask trigger

#define rDISRC1     (0x4b000040)	//DMA 1 Initial source
#define rDISRCC1    (0x4b000044)	//DMA 1 Initial source control
#define rDIDST1     (0x4b000048)	//DMA 1 Initial Destination
#define rDIDSTC1    (0x4b00004c)	//DMA 1 Initial Destination control
#define rDCON1      (0x4b000050)	//DMA 1 Control
#define rDSTAT1     (0x4b000054)	//DMA 1 Status
#define rDCSRC1     (0x4b000058)	//DMA 1 Current source
#define rDCDST1     (0x4b00005c)	//DMA 1 Current destination
#define rDMASKTRIG1 (0x4b000060)	//DMA 1 Mask trigger

#define rDISRC2     (0x4b000080)	//DMA 2 Initial source
#define rDISRCC2    (0x4b000084)	//DMA 2 Initial source control
#define rDIDST2     (0x4b000088)	//DMA 2 Initial Destination
#define rDIDSTC2    (0x4b00008c)	//DMA 2 Initial Destination control
#define rDCON2      (0x4b000090)	//DMA 2 Control
#define rDSTAT2     (0x4b000094)	//DMA 2 Status
#define rDCSRC2     (0x4b000098)	//DMA 2 Current source
#define rDCDST2     (0x4b00009c)	//DMA 2 Current destination
#define rDMASKTRIG2 (0x4b0000a0)	//DMA 2 Mask trigger

#define rDISRC3     (0x4b0000c0)	//DMA 3 Initial source
#define rDISRCC3    (0x4b0000c4)	//DMA 3 Initial source control
#define rDIDST3     (0x4b0000c8)	//DMA 3 Initial Destination
#define rDIDSTC3    (0x4b0000cc)	//DMA 3 Initial Destination control
#define rDCON3      (0x4b0000d0)	//DMA 3 Control
#define rDSTAT3     (0x4b0000d4)	//DMA 3 Status
#define rDCSRC3     (0x4b0000d8)	//DMA 3 Current source
#define rDCDST3     (0x4b0000dc)	//DMA 3 Current destination
#define rDMASKTRIG3 (0x4b0000e0)	//DMA 3 Mask trigger


// CLOCK & POWER MANAGEMENT
#define rLOCKTIME   (0x4c000000)	//PLL lock time counter
#define rMPLLCON    (0x4c000004)	//MPLL Control
#define rUPLLCON    (0x4c000008)	//UPLL Control
#define rCLKCON     (0x4c00000c)	//Clock generator control
#define rCLKSLOW    (0x4c000010)	//Slow clock control
#define rCLKDIVN    (0x4c000014)	//Clock divider control
#define rCAMDIVN    (0x4c000018)	//USB, CAM Clock divider control


// LCD CONTROLLER
#define rLCDCON1    (0x4d000000)	//LCD control 1
#define rLCDCON2    (0x4d000004)	//LCD control 2
#define rLCDCON3    (0x4d000008)	//LCD control 3
#define rLCDCON4    (0x4d00000c)	//LCD control 4
#define rLCDCON5    (0x4d000010)	//LCD control 5
#define rLCDSADDR1  (0x4d000014)	//STN/TFT Frame buffer start address 1
#define rLCDSADDR2  (0x4d000018)	//STN/TFT Frame buffer start address 2
#define rLCDSADDR3  (0x4d00001c)	//STN/TFT Virtual screen address set
#define rREDLUT     (0x4d000020)	//STN Red lookup table
#define rGREENLUT   (0x4d000024)	//STN Green lookup table
#define rBLUELUT    (0x4d000028)	//STN Blue lookup table
#define rDITHMODE   (0x4d00004c)	//STN Dithering mode
#define rTPAL       (0x4d000050)	//TFT Temporary palette
#define rLCDINTPND  (0x4d000054)	//LCD Interrupt pending
#define rLCDSRCPND  (0x4d000058)	//LCD Interrupt source
#define rLCDINTMSK  (0x4d00005c)	//LCD Interrupt mask
#define rTCONSEL     (0x4d000060)	//LPC3600 Control --- edited by junon
#define PALETTE     0x4d000400						//Palette start address


//Nand Flash
#define rNFCONF		(0x4E000000)		//NAND Flash configuration
#define rNFCONT		(0x4E000004)      //NAND Flash control
#define rNFCMD		(0x4E000008)      //NAND Flash command
#define rNFADDR		(0x4E00000C)      //NAND Flash address
#define rNFDATA		(0x4E000010)      //NAND Flash data
#define rNFDATA8	(0x4E000010)     //NAND Flash data
#define NFDATA		(0x4E000010)      //NAND Flash data address
#define rNFMECCD0	(0x4E000014)      //NAND Flash ECC for Main Area
#define rNFMECCD1	(0x4E000018)
#define rNFSECCD	(0x4E00001C)		//NAND Flash ECC for Spare Area
#define rNFSTAT		(0x4E000020)		//NAND Flash operation status
#define rNFESTAT0	(0x4E000024)
#define rNFESTAT1	(0x4E000028)
#define rNFMECC0	(0x4E00002C)
#define rNFMECC1	(0x4E000030)
#define rNFSECC		(0x4E000034)
#define rNFSBLK		(0x4E000038)		//NAND Flash Start block address
#define rNFEBLK		(0x4E00003C)		//NAND Flash End block address


//Camera Interface.  Edited for 2440A
#define rCISRCFMT           (0x4F000000)
#define rCIWDOFST           (0x4F000004)
#define rCIGCTRL            (0x4F000008)
#define rCICOYSA1           (0x4F000018)
#define rCICOYSA2           (0x4F00001C)
#define rCICOYSA3           (0x4F000020)
#define rCICOYSA4           (0x4F000024)
#define rCICOCBSA1          (0x4F000028)
#define rCICOCBSA2          (0x4F00002C)
#define rCICOCBSA3          (0x4F000030)
#define rCICOCBSA4          (0x4F000034)
#define rCICOCRSA1          (0x4F000038)
#define rCICOCRSA2          (0x4F00003C)
#define rCICOCRSA3          (0x4F000040)
#define rCICOCRSA4          (0x4F000044)
#define rCICOTRGFMT         (0x4F000048)
#define rCICOCTRL           (0x4F00004C)
#define rCICOSCPRERATIO     (0x4F000050)
#define rCICOSCPREDST       (0x4F000054)
#define rCICOSCCTRL         (0x4F000058)
#define rCICOTAREA          (0x4F00005C)
#define rCICOSTATUS         (0x4F000064)
#define rCIPRCLRSA1         (0x4F00006C)
#define rCIPRCLRSA2         (0x4F000070)
#define rCIPRCLRSA3         (0x4F000074)
#define rCIPRCLRSA4         (0x4F000078)
#define rCIPRTRGFMT         (0x4F00007C)
#define rCIPRCTRL           (0x4F000080)
#define rCIPRSCPRERATIO     (0x4F000084)
#define rCIPRSCPREDST       (0x4F000088)
#define rCIPRSCCTRL         (0x4F00008C)
#define rCIPRTAREA          (0x4F000090)
#define rCIPRSTATUS         (0x4F000098)
#define rCIIMGCPT           (0x4F0000A0)


// UART
#define rULCON0     (0x50000000)	//UART 0 Line control
#define rUCON0      (0x50000004)	//UART 0 Control
#define rUFCON0     (0x50000008)	//UART 0 FIFO control
#define rUMCON0     (0x5000000c)	//UART 0 Modem control
#define rUTRSTAT0   (0x50000010)	//UART 0 Tx/Rx status
#define rUERSTAT0   (0x50000014)	//UART 0 Rx error status
#define rUFSTAT0    (0x50000018)	//UART 0 FIFO status
#define rUMSTAT0    (0x5000001c)	//UART 0 Modem status
#define rUBRDIV0    (0x50000028)	//UART 0 Baud rate divisor

#define rULCON1     (0x50004000)	//UART 1 Line control
#define rUCON1      (0x50004004)	//UART 1 Control
#define rUFCON1     (0x50004008)	//UART 1 FIFO control
#define rUMCON1     (0x5000400c)	//UART 1 Modem control
#define rUTRSTAT1   (0x50004010)	//UART 1 Tx/Rx status
#define rUERSTAT1   (0x50004014)	//UART 1 Rx error status
#define rUFSTAT1    (0x50004018)	//UART 1 FIFO status
#define rUMSTAT1    (0x5000401c)	//UART 1 Modem status
#define rUBRDIV1    (0x50004028)	//UART 1 Baud rate divisor
#define rULCON2     (0x50008000)	//UART 2 Line control
#define rUCON2      (0x50008004)	//UART 2 Control
#define rUFCON2     (0x50008008)	//UART 2 FIFO control
#define rUMCON2     (0x5000800c)	//UART 2 Modem control
#define rUTRSTAT2   (0x50008010)	//UART 2 Tx/Rx status
#define rUERSTAT2   (0x50008014)	//UART 2 Rx error status
#define rUFSTAT2    (0x50008018)	//UART 2 FIFO status
#define rUMSTAT2    (0x5000801c)	//UART 2 Modem status
#define rUBRDIV2    (0x50008028)	//UART 2 Baud rate divisor


#define rUTXH0 (0x50000020)	//UART 0 Transmission Hold
#define rURXH0 (0x50000024)	//UART 0 Receive buffer
#define rUTXH1 (0x50004020)	//UART 1 Transmission Hold
#define rURXH1 (0x50004024)	//UART 1 Receive buffer
#define rUTXH2 (0x50008020)	//UART 2 Transmission Hold
#define rURXH2 (0x50008024)	//UART 2 Receive buffer

#define WrUTXH0(ch) (0x50000020)=(unsigned char)(ch)
#define RdURXH0()   (0x50000024)
#define WrUTXH1(ch) (0x50004020)=(unsigned char)(ch)
#define RdURXH1()   (0x50004024)
#define WrUTXH2(ch) (0x50008020)=(unsigned char)(ch)
#define RdURXH2()   (0x50008024)

#define UTXH0       (0x50000020)    //Byte_access address by DMA
#define URXH0       (0x50000024)
#define UTXH1       (0x50004020)
#define URXH1       (0x50004024)
#define UTXH2       (0x50008020)
#define URXH2       (0x50008024)


// PWM TIMER
#define rTCFG0  (0x51000000)	//Timer 0 configuration
#define rTCFG1  (0x51000004)	//Timer 1 configuration
#define rTCON   (0x51000008)	//Timer control
#define rTCNTB0 (0x5100000c)	//Timer count buffer 0
#define rTCMPB0 (0x51000010)	//Timer compare buffer 0
#define rTCNTO0 (0x51000014)	//Timer count observation 0
#define rTCNTB1 (0x51000018)	//Timer count buffer 1
#define rTCMPB1 (0x5100001c)	//Timer compare buffer 1
#define rTCNTO1 (0x51000020)	//Timer count observation 1
#define rTCNTB2 (0x51000024)	//Timer count buffer 2
#define rTCMPB2 (0x51000028)	//Timer compare buffer 2
#define rTCNTO2 (0x5100002c)	//Timer count observation 2
#define rTCNTB3 (0x51000030)	//Timer count buffer 3
#define rTCMPB3 (0x51000034)	//Timer compare buffer 3
#define rTCNTO3 (0x51000038)	//Timer count observation 3
#define rTCNTB4 (0x5100003c)	//Timer count buffer 4
#define rTCNTO4 (0x51000040)	//Timer count observation 4





// WATCH DOG TIMER
#define rWTCON   (0x53000000)	//Watch-dog timer mode
#define rWTDAT   (0x53000004)	//Watch-dog timer data
#define rWTCNT   (0x53000008)	//Eatch-dog timer count


// IIC
#define rIICCON		(0x54000000)	//IIC control
#define rIICSTAT	(0x54000004)	//IIC status
#define rIICADD		(0x54000008)	//IIC address
#define rIICDS		(0x5400000c)	//IIC data shift
#define rIICLC		(0x54000010)	//IIC multi-master line control


// IIS
#define rIISCON  (0x55000000)	//IIS Control
#define rIISMOD  (0x55000004)	//IIS Mode
#define rIISPSR  (0x55000008)	//IIS Prescaler
#define rIISFCON (0x5500000c)	//IIS FIFO control

#define IISFIFO  (0x55000010)	//IIS FIFO entry


//AC97, Added for S3C2440A
#define rAC_GLBCTRL		0x5b000000
#define rAC_GLBSTAT		0x5b000004
#define rAC_CODEC_CMD		0x5b000008
#define rAC_CODEC_STAT		0x5b00000C
#define rAC_PCMADDR		0x5b000010
#define rAC_MICADDR		0x5b000014
#define rAC_PCMDATA		0x5b000018
#define rAC_MICDATA		0x5b00001C

#define AC_PCMDATA		0x5b000018
#define AC_MICDATA		0x5b00001C

// I/O PORT
#define rGPACON    (0x56000000)	//Port A control
#define rGPADAT    (0x56000004)	//Port A data

#define rGPBCON    (0x56000010)	//Port B control
#define rGPBDAT    (0x56000014)	//Port B data
#define rGPBUP     (0x56000018)	//Pull-up control B

#define rGPCCON    (0x56000020)	//Port C control
#define rGPCDAT    (0x56000024)	//Port C data
#define rGPCUP     (0x56000028)	//Pull-up control C

#define rGPDCON    (0x56000030)	//Port D control
#define rGPDDAT    (0x56000034)	//Port D data
#define rGPDUP     (0x56000038)	//Pull-up control D

#define rGPECON    (0x56000040)	//Port E control
#define rGPEDAT    (0x56000044)	//Port E data
#define rGPEUP     (0x56000048)	//Pull-up control E

#define rGPFCON    (0x56000050)	//Port F control
#define rGPFDAT    (0x56000054)	//Port F data
#define rGPFUP     (0x56000058)	//Pull-up control F

#define rGPGCON    (0x56000060)	//Port G control
#define rGPGDAT    (0x56000064)	//Port G data
#define rGPGUP     (0x56000068)	//Pull-up control G

#define rGPHCON    (0x56000070)	//Port H control
#define rGPHDAT    (0x56000074)	//Port H data
#define rGPHUP     (0x56000078)	//Pull-up control H

#define rGPJCON    (0x560000d0)	//Port J control
#define rGPJDAT    (0x560000d4)	//Port J data
#define rGPJUP     (0x560000d8)	//Pull-up control J

#define rMISCCR    (0x56000080)	//Miscellaneous control
#define rDCLKCON   (0x56000084)	//DCLK0/1 control
#define rEXTINT0   (0x56000088)	//External interrupt control register 0
#define rEXTINT1   (0x5600008c)	//External interrupt control register 1
#define rEXTINT2   (0x56000090)	//External interrupt control register 2
#define rEINTFLT0  (0x56000094)	//Reserved
#define rEINTFLT1  (0x56000098)	//Reserved
#define rEINTFLT2  (0x5600009c)	//External interrupt filter control register 2
#define rEINTFLT3  (0x560000a0)	//External interrupt filter control register 3
#define rEINTMASK  (0x560000a4)	//External interrupt mask
#define rEINTPEND  (0x560000a8)	//External interrupt pending
#define rGSTATUS0  (0x560000ac)	//External pin status
#define rGSTATUS1  (0x560000b0)	//Chip ID(0x32440000)
#define rGSTATUS2  (0x560000b4)	//Reset type
#define rGSTATUS3  (0x560000b8)	//Saved data0(32-bit) before entering POWER_OFF mode
#define rGSTATUS4  (0x560000bc)	//Saved data0(32-bit) before entering POWER_OFF mode

// Added for 2440
#define rFLTOUT		(0x560000c0)	// Filter output(Read only)
#define rDSC0			(0x560000c4)	// Strength control register 0
#define rDSC1			(0x560000c8)	// Strength control register 1
#define rMSLCON		(0x560000cc)	// Memory sleep control register


#define rRTCCON    (0x57000040)	//RTC control
#define rTICNT     (0x57000044)	//Tick time count
#define rRTCALM    (0x57000050)	//RTC alarm control
#define rALMSEC    (0x57000054)	//Alarm second
#define rALMMIN    (0x57000058)	//Alarm minute
#define rALMHOUR   (0x5700005c)	//Alarm Hour
#define rALMDATE   (0x57000060)	//Alarm date  // edited by junon
#define rALMMON    (0x57000064)	//Alarm month
#define rALMYEAR   (0x57000068)	//Alarm year
#define rRTCRST    (0x5700006c)	//RTC round reset
#define rBCDSEC    (0x57000070)	//BCD second
#define rBCDMIN    (0x57000074)	//BCD minute
#define rBCDHOUR   (0x57000078)	//BCD hour
#define rBCDDATE   (0x5700007c)	//BCD date  //edited by junon
#define rBCDDAY    (0x57000080)	//BCD day   //edited by junon
#define rBCDMON    (0x57000084)	//BCD month
#define rBCDYEAR   (0x57000088)	//BCD year



// ADC
#define rADCCON    (0x58000000)	//ADC control
#define rADCTSC    (0x58000004)	//ADC touch screen control
#define rADCDLY    (0x58000008)	//ADC start or Interval Delay
#define rADCDAT0   (0x5800000c)	//ADC conversion data 0
#define rADCDAT1   (0x58000010)	//ADC conversion data 1
#define rADCUPDN   (0x58000014)	//Stylus Up/Down interrupt status


// SPI
#define rSPCON0    (0x59000000)	//SPI0 control
#define rSPSTA0    (0x59000004)	//SPI0 status
#define rSPPIN0    (0x59000008)	//SPI0 pin control
#define rSPPRE0    (0x5900000c)	//SPI0 baud rate prescaler
#define rSPTDAT0   (0x59000010)	//SPI0 Tx data
#define rSPRDAT0   (0x59000014)	//SPI0 Rx data

#define rSPCON1    (0x59000020)	//SPI1 control
#define rSPSTA1    (0x59000024)	//SPI1 status
#define rSPPIN1    (0x59000028)	//SPI1 pin control
#define rSPPRE1    (0x5900002c)	//SPI1 baud rate prescaler
#define rSPTDAT1   (0x59000030)	//SPI1 Tx data
#define rSPRDAT1   (0x59000034)	//SPI1 Rx data


// SD Interface
#define rSDICON     (0x5a000000)	//SDI control
#define rSDIPRE     (0x5a000004)	//SDI baud rate prescaler
#define rSDICARG    (0x5a000008)	//SDI command argument
#define rSDICCON    (0x5a00000c)	//SDI command control
#define rSDICSTA    (0x5a000010)	//SDI command status
#define rSDIRSP0    (0x5a000014)	//SDI response 0
#define rSDIRSP1    (0x5a000018)	//SDI response 1
#define rSDIRSP2    (0x5a00001c)	//SDI response 2
#define rSDIRSP3    (0x5a000020)	//SDI response 3
#define rSDIDTIMER  (0x5a000024)	//SDI data/busy timer
#define rSDIBSIZE   (0x5a000028)	//SDI block size
#define rSDIDCON    (0x5a00002c)	//SDI data control
#define rSDIDCNT    (0x5a000030)	//SDI data remain counter
#define rSDIDSTA    (0x5a000034)	//SDI data status
#define rSDIFSTA    (0x5a000038)	//SDI FIFO status
#define rSDIIMSK    (0x5a00003c)	//SDI interrupt mask. edited for 2440A

#define rSDIDAT    (0x5a000040)	//SDI data
#define SDIDAT     0x5a000040



// Exception vector
#define pISR_RESET		(_ISR_STARTADDRESS+0x0))
#define pISR_UNDEF		(_ISR_STARTADDRESS+0x4))
#define pISR_SWI		(_ISR_STARTADDRESS+0x8))
#define pISR_PABORT		(_ISR_STARTADDRESS+0xc))
#define pISR_DABORT		(_ISR_STARTADDRESS+0x10))
#define pISR_RESERVED	(_ISR_STARTADDRESS+0x14))
#define pISR_IRQ		(_ISR_STARTADDRESS+0x18))
#define pISR_FIQ		(_ISR_STARTADDRESS+0x1c))
// Interrupt vector
#define pISR_EINT0		(_ISR_STARTADDRESS+0x20))
#define pISR_EINT1		(_ISR_STARTADDRESS+0x24))
#define pISR_EINT2		(_ISR_STARTADDRESS+0x28))
#define pISR_EINT3		(_ISR_STARTADDRESS+0x2c))
#define pISR_EINT4_7	(_ISR_STARTADDRESS+0x30))
#define pISR_EINT8_23	(_ISR_STARTADDRESS+0x34))
#define pISR_CAM		(_ISR_STARTADDRESS+0x38))		// Added for 2440.
#define pISR_BAT_FLT	(_ISR_STARTADDRESS+0x3c))
#define pISR_TICK		(_ISR_STARTADDRESS+0x40))
#define pISR_WDT_AC97		(_ISR_STARTADDRESS+0x44))   //Changed to pISR_WDT_AC97 for 2440A
#define pISR_TIMER0	 	(_ISR_STARTADDRESS+0x48))
#define pISR_TIMER1	 	(_ISR_STARTADDRESS+0x4c))
#define pISR_TIMER2		(_ISR_STARTADDRESS+0x50))
#define pISR_TIMER3		(_ISR_STARTADDRESS+0x54))
#define pISR_TIMER4		(_ISR_STARTADDRESS+0x58))
#define pISR_UART2		(_ISR_STARTADDRESS+0x5c))
#define pISR_LCD		(_ISR_STARTADDRESS+0x60))
#define pISR_DMA0		(_ISR_STARTADDRESS+0x64))
#define pISR_DMA1		(_ISR_STARTADDRESS+0x68))
#define pISR_DMA2		(_ISR_STARTADDRESS+0x6c))
#define pISR_DMA3		(_ISR_STARTADDRESS+0x70))
#define pISR_SDI		(_ISR_STARTADDRESS+0x74))
#define pISR_SPI0		(_ISR_STARTADDRESS+0x78))
#define pISR_UART1		(_ISR_STARTADDRESS+0x7c))
#define pISR_NFCON		(_ISR_STARTADDRESS+0x80))		// Added for 2440.
#define pISR_USBD		(_ISR_STARTADDRESS+0x84))
#define pISR_USBH		(_ISR_STARTADDRESS+0x88))
#define pISR_IIC		(_ISR_STARTADDRESS+0x8c))
#define pISR_UART0		(_ISR_STARTADDRESS+0x90))
#define pISR_SPI1		(_ISR_STARTADDRESS+0x94))
#define pISR_RTC		(_ISR_STARTADDRESS+0x98))
#define pISR_ADC		(_ISR_STARTADDRESS+0x9c))


// PENDING BIT
#define BIT_EINT0		(0x1)
#define BIT_EINT1		(0x1<<1)
#define BIT_EINT2		(0x1<<2)
#define BIT_EINT3		(0x1<<3)
#define BIT_EINT4_7		(0x1<<4)
#define BIT_EINT8_23	(0x1<<5)
#define BIT_CAM			(0x1<<6)		// Added for 2440.
#define BIT_BAT_FLT		(0x1<<7)
#define BIT_TICK		(0x1<<8)
#define BIT_WDT_AC97	(0x1<<9)	// Changed from BIT_WDT to BIT_WDT_AC97 for 2440A
#define BIT_TIMER0		(0x1<<10)
#define BIT_TIMER1		(0x1<<11)
#define BIT_TIMER2		(0x1<<12)
#define BIT_TIMER3		(0x1<<13)
#define BIT_TIMER4		(0x1<<14)
#define BIT_UART2		(0x1<<15)
#define BIT_LCD			(0x1<<16)
#define BIT_DMA0		(0x1<<17)
#define BIT_DMA1		(0x1<<18)
#define BIT_DMA2		(0x1<<19)
#define BIT_DMA3		(0x1<<20)
#define BIT_SDI			(0x1<<21)
#define BIT_SPI0		(0x1<<22)
#define BIT_UART1		(0x1<<23)
#define BIT_NFCON		(0x1<<24)		// Added for 2440.
#define BIT_USBD		(0x1<<25)
#define BIT_USBH		(0x1<<26)
#define BIT_IIC			(0x1<<27)
#define BIT_UART0		(0x1<<28)
#define BIT_SPI1		(0x1<<29)
#define BIT_RTC			(0x1<<30)
#define BIT_ADC			(0x1<<31)
#define BIT_ALLMSK		(0xffffffff)

#define BIT_SUB_ALLMSK	(0x7fff)			//Changed from 0x7ff to 0x7fff for 2440A
#define BIT_SUB_AC97	(0x1<<14)		//Added for 2440A
#define BIT_SUB_WDT	(0x1<<13)		//Added for 2440A
#define BIT_SUB_CAM_P	(0x1<<12)		// edited for 2440A.
#define BIT_SUB_CAM_C   (0x1<<11)       // edited for 2440A
#define BIT_SUB_ADC		(0x1<<10)
#define BIT_SUB_TC		(0x1<<9)
#define BIT_SUB_ERR2	(0x1<<8)
#define BIT_SUB_TXD2	(0x1<<7)
#define BIT_SUB_RXD2	(0x1<<6)
#define BIT_SUB_ERR1	(0x1<<5)
#define BIT_SUB_TXD1	(0x1<<4)
#define BIT_SUB_RXD1	(0x1<<3)
#define BIT_SUB_ERR0	(0x1<<2)
#define BIT_SUB_TXD0	(0x1<<1)
#define BIT_SUB_RXD0	(0x1<<0)
void memcontrol(quint32 addr,bool isread,quint32 & taget,quint8 size=4);
#endif  //__2440ADDR_H__

