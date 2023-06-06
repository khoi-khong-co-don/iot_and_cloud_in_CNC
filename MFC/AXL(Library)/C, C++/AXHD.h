
#ifndef __AXT_AXHD_H__
#define __AXT_AXHD_H__

/* IP COMMAND LIST                            */
typedef enum _IPCOMMAND
{
     // PGM-1 Group Register
    IPxyRANGERead            = 0x00,                // PGM-1 RANGE READ, 16bit, 0xFFFF
    IPxyRANGEWrite           = 0x80,                // PGM-1 RANGE WRITE
    IPxySTDRead              = 0x01,                // PGM-1 START/STOP SPEED DATA READ, 16bit, 
    IPxySTDWrite             = 0x81,                // PGM-1 START/STOP SPEED DATA WRITE
    IPxyOBJRead              = 0x02,                // PGM-1 OBJECT SPEED DATA READ, 16bit, 
    IPxyOBJWrite             = 0x82,                // PGM-1 OBJECT SPEED DATA WRITE
    IPxyRATE1Read            = 0x03,                // PGM-1 RATE-1 DATA READ, 16bit, 0xFFFF
    IPxyRATE1Write           = 0x83,                // PGM-1 RATE-1 DATA WRITE
    IPxyRATE2Read            = 0x04,                // PGM-1 RATE-2 DATA READ, 16bit, 0xFFFF
    IPxyRATE2Write           = 0x84,                // PGM-1 RATE-2 DATA WRITE
    IPxyRATE3Read            = 0x05,                // PGM-1 RATE-3 DATA READ, 16bit, 0xFFFF
    IPxyRATE3Write           = 0x85,                // PGM-1 RATE-3 DATA WRITE
    IPxyRCP12Read            = 0x06,                // PGM-1 RATE CHANGE POINT 1-2 READ, 16bit, 0xFFFF
    IPxyRCP12Write           = 0x86,                // PGM-1 RATE CHANGE POINT 1-2 WRITE
    IPxyRCP23Read            = 0x07,                // PGM-1 RATE CHANGE POINT 2-3 READ, 16bit, 0xFFFF
    IPxyRCP23Write           = 0x87,                // PGM-1 RATE CHANGE POINT 2-3 WRITE
    IPxySW1Read              = 0x08,                // PGM-1 SW-1 DATA READ, 15bit, 0x7FFF
    IPxySW1Write             = 0x88,                // PGM-1 SW-1 DATA WRITE
    IPxySW2Read              = 0x09,                // PGM-1 SW-2 DATA READ, 15bit, 0x7FFF
    IPxySW2Write             = 0x89,                // PGM-1 SW-2 DATA WRITE
    IPxyPWMRead              = 0x0A,                // PGM-1 PWM output set DATA READ(0~6), 3bit, 0x00
    IPxyPWMWrite             = 0x8A,                // PGM-1 PWM output set DATA WRITE
    IPxyREARRead             = 0x0B,                // PGM-1 SLOW DOWN/REAR PULSE READ, 32bit, 0x00000000
    IPxyREARWrite            = 0x8B,                // PGM-1 SLOW DOWN/REAR PULSE WRITE
    IPxySPDRead              = 0x0C,                // PGM-1 현재 SPEED DATA READ, 16bit, 0x0000
    IPxyNoOperation_8C       = 0x8C,                // No operation
    IPxySPDCMPRead           = 0x0D,                // PGM-1 현재 SPEED 비교 DATA READ, 16bit, 0x0000
    IPxySPDCMPWrite          = 0x8D,                // PGM-1 현재 SPEED 비교 DATA WRITE
    IPxyDRVPULSERead         = 0x0E,                // PGM-1 DRIVE PULSE COUNTER READ, 32bit, 0x00000000
    IPxyNoOperation_8E       = 0x8E,                // No operation
    IPxyPRESETPULSERead      = 0x0F,                // PGM-1 PRESET PULSE DATA READ, 32bit, 0x00000000
    IPxyNoOperation_8F       = 0x8F,                // No operation

    // PGM-1 Update Group Register
    IPxyURANGERead           = 0x10,                // PGM-1 UP-DATE RANGE READ, 16bit, 0xFFFF
    IPxyURANGEWrite          = 0x90,                // PGM-1 UP-DATE RANGE WRITE
    IPxyUSTDRead             = 0x11,                // PGM-1 UP-DATE START/STOP SPEED DATA READ, 16bit, 
    IPxyUSTDWrite            = 0x91,                // PGM-1 UP-DATE START/STOP SPEED DATA WRITE
    IPxyUOBJRead             = 0x12,                // PGM-1 UP-DATE OBJECT SPEED DATA READ, 16bit, 
    IPxyUOBJWrite            = 0x92,                // PGM-1 UP-DATE OBJECT SPEED DATA WRITE
    IPxyURATE1Read           = 0x13,                // PGM-1 UP-DATE RATE-1 DATA READ, 16bit, 0xFFFF
    IPxyURATE1Write          = 0x93,                // PGM-1 UP-DATE RATE-1 DATA WRITE
    IPxyURATE2Read           = 0x14,                // PGM-1 UP-DATE RATE-2 DATA READ, 16bit, 0xFFFF
    IPxyURATE2Write          = 0x94,                // PGM-1 UP-DATE RATE-2 DATA WRITE
    IPxyURATE3Read           = 0x15,                // PGM-1 UP-DATE RATE-3 DATA READ, 16bit, 0xFFFF
    IPxyURATE3Write          = 0x95,                // PGM-1 UP-DATE RATE-3 DATA WRITE
    IPxyURCP12Read           = 0x16,                // PGM-1 UP-DATE RATE CHANGE POINT 1-2 READ, 16bit, 0xFFFF
    IPxyURCP12Write          = 0x96,                // PGM-1 UP-DATE RATE CHANGE POINT 1-2 WRITE
    IPxyURCP23Read           = 0x17,                // PGM-1 UP-DATE RATE CHANGE POINT 2-3 READ, 16bit, 0xFFFF
    IPxyURCP23Write          = 0x97,                // PGM-1 UP-DATE RATE CHANGE POINT 2-3 WRITE
    IPxyUSW1Read             = 0x18,                // PGM-1 UP-DATE SW-1 DATA READ, 15bit, 0x7FFF
    IPxyUSW1Write            = 0x98,                // PGM-1 UP-DATE SW-1 DATA WRITE
    IPxyUSW2Read             = 0x19,                // PGM-1 UP-DATE SW-2 DATA READ, 15bit, 0x7FFF
    IPxyUSW2Write            = 0x99,                // PGM-1 UP-DATE SW-2 DATA WRITE
    IPxyNoOperation_1A       = 0x1A,                // No operation
    IPxyNoOperation_9A       = 0x9A,                // No operation
    IPxyUREARRead            = 0x1B,                // PGM-1 UP-DATE SLOW DOWN/REAR PULSE READ, 32bit, 0x00000000
    IPxyUREARWrite           = 0x9B,                // PGM-1 UP-DATE SLOW DOWN/REAR PULSE WRITE
    IPxySPDRead_1C           = 0x1C,                // PGM-1 UP-DATA CURRENT SPEED READ(Same with 0x0C)
    IPxyNoOperation_9C       = 0x9C,                // No operation
    IPxySPDCMPRead_1D        = 0x1D,                // PGM-1 currently SPEED compare DATA READ(Same with 0x0D) 
    IPxySPDCMPWrite_9D       = 0x9D,                // PGM-1 currently SPEED compare DATA WRITE(Same with 0x8D) 
    IPxyACCPULSERead         = 0x1E,                // PGM-1 acceleration PULSE COUNTER READ, 32bit, 0x00000000
    IPxyNoOperation_9E       = 0x9E,                // No operation
    IPxyPRESETPULSERead_1F   = 0x1F,                // PGM-1 PRESET PULSE DATA READ(Same with 0x0F)
    IPxyNoOperation_9F       = 0x9F,                // No operation

    // PGM-2 Group Register
    IPxyNoOperation_20       = 0x20,                // No operation
    IPxyPPRESETDRV           = 0xA0,                // +PRESET PULSE DRIVE, 32
    IPxyNoOperation_21       = 0x21,                // No operation
    IPxyPCONTDRV             = 0xA1,                // +CONTINUOUS DRIVE
    IPxyNoOperation_22       = 0x22,                // No operation
    IPxyPSCH1DRV             = 0xA2,                // +SIGNAL SEARCH-1 DRIVE
    IPxyNoOperation_23       = 0x23,                // No operation
    IPxyPSCH2DRV             = 0xA3,                // +SIGNAL SEARCH-2 DRIVE
    IPxyNoOperation_24       = 0x24,                // No operation
    IPxyPORGDRV              = 0xA4,                // +ORIGIN(ORG) SEARCH DRIVE
    IPxyNoOperation_25       = 0x25,                // No operation
    IPxyMPRESETDRV           = 0xA5,                // -PRESET PULSE DRIVE, 32
    IPxyNoOperation_26       = 0x26,                // No operation
    IPxyMCONTDRV             = 0xA6,                // -CONTINUOUS DRIVE
    IPxyNoOperation_27       = 0x27,                // No operation
    IPxyMSCH1DRV             = 0xA7,                // -SIGNAL SEARCH-1 DRIVE
    IPxyNoOperation_28       = 0x28,                // No operation
    IPxyMSCH2DRV             = 0xA8,                // -SIGNAL SEARCH-2 DRIVE
    IPxyNoOperation_29       = 0x29,                // No operation
    IPxyMORGDRV              = 0xA9,                // -ORIGIN(ORG) SEARCH DRIVE
    IPxyPULSEOVERRead        = 0x2A,                // Preset/MPG drive override pulse data read
    IPxyPULSEOVERWrite       = 0xAA,                // PRESET PULSE DATA OVERRIDE(ON_BUSY)
    IPxyNoOperation_2B       = 0x2B,                // No operation
    IPxySSTOPCMD             = 0xAB,                // SLOW DOWN STOP
    IPxyNoOperation_2C       = 0x2C,                // No operation
    IPxyESTOPCMD             = 0xAC,                // EMERGENCY STOP
    IPxyDRIVEMODERead        = 0x2D,                // Drive setting DATA READ
    IPxyDRIVEMODEWrite       = 0xAD,                // Drive setting DATA WRITE
    IPxyMPGCONRead           = 0x2E,                // MPG OPERATION SETTING DATA READ, 3bit, 0x00    
    IPxyMPGCONWrite          = 0xAE,                // MPG OPERATION SETTING DATA WRITE                
    IPxyPULSEMPGRead         = 0x2F,                // MPG PRESET PULSE DATA READ, 32bit, 0x00000000
    IPxyPULSEMPGWrite        = 0xAF,                // MPG PRESET PULSE DATA WRITE                    
    
    /* Extension Group Register */
    IPxyNoOperation_30       = 0x30,                // No operation
    IPxyPSPO1DRV             = 0xB0,                // +SENSOR POSITIONING DRIVE I
    IPxyNoOperation_31       = 0x31,                // No operation
    IPxyMSPO1DRV             = 0xB1,                // -SENSOR POSITIONING DRIVE I
    IPxyNoOperation_32       = 0x32,                // No operation
    IPxyPSPO2DRV             = 0xB2,                // +SENSOR POSITIONING DRIVE II
    IPxyNoOperation_33       = 0x33,                // No operation
    IPxyMSPO2DRV             = 0xB3,                // -SENSOR POSITIONING DRIVE II
    IPxyNoOperation_34       = 0x34,                // No operation
    IPxyPSPO3DRV             = 0xB4,                // +SENSOR POSITIONING DRIVE III
    IPxyNoOperation_35       = 0x35,                // No operation
    IPxyMSPO3DRV             = 0xB5,                // -SENSOR POSITIONING DRIVE III
    IPxySWLMTCONRead         = 0x36,                // SOFT LIMIT 설정 READ, 3bit, 0x00
    IPxySWLMTCONWrite        = 0xB6,                // SOFT LIMIT 설정 WRITE
    IPxyMSWLMTCOMPRead       = 0x37,                // -SOFT LIMIT 비교 레지스터 설정 READ, 32bit, 0x80000000
    IPxyMSWLMTCOMPWrite      = 0xB7,                // -SOFT LIMIT 비교 레지스터 설정 WRITE
    IPxyPSWLMTCOMPRead       = 0x38,                // +SOFT LIMIT 비교 레지스터 설정 READ, 32bit, 0x7FFFFFFF
    IPxyPSWLMTCOMPWrite      = 0xB8,                // +SOFT LIMIT 비교 레지스터 설정 WRITE
    IPxyTRGCONRead           = 0x39,                // TRIGGER MODE 설정 READ, 32bit, 0x00010000
    IPxyTRGCONWrite          = 0xB9,                // TRIGGER MODE 설정 WRITE
    IPxyTRGCOMPRead          = 0x3A,                // TRIGGER 비교 데이터 설정 READ, 32bit, 0x00000000
    IPxyTRGCOMPWrite         = 0xBA,                // TRIGGER 비교 데이터 설정 WRITE
    IPxyICMRead              = 0x3B,                // INTERNAL M-DATA 설정 READ, 32bit, 0x80000000
    IPxyICMWrite             = 0xBB,                // INTERNAL M-DATA 설정 WRITE
    IPxyECMRead              = 0x3C,                // EXTERNAL M-DATA 설정 READ, 32bit, 0x80000000
    IPxyECMWrite             = 0xBC,                // EXTERNAL M-DATA 설정 WRITE
    IPxySTOPPWRead           = 0x3D,                // Stop pulse width Read
    IPxySTOPPWWrite          = 0xBD,                // Stop pulse width Write
    IPxyNoOperation_3E       = 0x3E,                // No operation
    IPxyNoOperation_BE       = 0xBE,                // No operation
    IPxyNoOperation_3F       = 0x3F,                // No operation
    IPxyTRGCMD               = 0xBF,                // TRIG output signal generation command
       
    /* Interpolation Group    Registers    */
    IPxCIRXCRead             = 0x40,                // Circular interpolation X axis center point read
    IPxCIRXCWrite            = 0xC0,                // Circular interpolation X axis center point write 
    IPxCIRYCRead             = 0x41,                // Circular interpolation Y axis center point read 
    IPxCIRYCWrite            = 0xC1,                // Circular interpolation Y axis center point write  
    IPxENDXRead              = 0x42,                // Interpolation X axis end point read 
    IPxENDXWrite             = 0xC2,                // Interpolation X axis end point write  
    IPxENDYRead              = 0x43,                // Interpolation Y axis end point read  
    IPxENDYWrite             = 0xC3,                // Interpolation Y axis end point write  
    IPxPTXENDRead            = 0x44,                // Pattern interpolation X Queue data read
    IPxPTXENDWrite           = 0xC4,                // Pattern interpolation X Queue data with queue push 
    IPxPTYENDRead            = 0x45,                // Pattern interpolation Y Queue data read 
    IPxPTYENDWrite           = 0xC5,                // Pattern interpolation Y Queue data write
    IPxPTQUEUERead           = 0x46,                // Pattern interpolation Queue index read
    IPxNoOperation_C6        = 0xC6,                // No operation
    IPxNoOperation_47        = 0x47,                // No operation
    IPxNoOperation_C7        = 0xC7,                // No operation
    IPxNoOperation_48        = 0x48,                // No operation
    IPxNoOperation_C8        = 0xC8,                // No operation
    IPxNoOperation_49        = 0x49,                // No operation
    IPxNoOperation_C9        = 0xC9,                // No operation
    IPxINPSTATUSRead         = 0x4A,                // Interpolation Status register read
    IPxNoOperation_CA        = 0xCA,                // No operation
    IPxINPMODE_4B            = 0x4B,                // Interpolation mode in Queue TOP contets
    IPxLINPDRV               = 0xCB,                // Linear interpolation with Queue push
    IPxINPMODE_4C            = 0x4C,                // Interpolation mode in Queue TOP contets
    IPxCINPDRV               = 0xCC,                // Circular interpolation with Queue push 
    IPxBPINPMODE             = 0x4D,                // Bit Pattern Interpolation mode in Queue TOP contets
    IPxBPINPDRV              = 0xCD,                // Bit pattern Drive
    IPxNoOperation_4E        = 0x4E,                // No Operation
    IPxNoOperation_CE        = 0xCE,                // No Operation 
    IPxNoOperation_4F        = 0x4F,                // No Operation 
    IPxNoOperation_CF        = 0xCF,                // No Operation 

    /* Arithemetic Group Register */
    IPxNoOperation_50        = 0x50,                // No Operation
    IPxINPCLR                = 0xD0,                // Initialize all interpolation control block
    IPxINPMPOINTRead         = 0x51,                // Interpolation deceleration manual point(unsigned) read
    IPxINPMPOINTWrite        = 0xD1,                // Interpolation deceleration manual point(unsigned) write
    IPxNoOperation_52        = 0x52,                // No Operation
    IPxINPCLRSWrite          = 0xD2,                // Initialize interpolation control block with target selection
    IPxNoOperation_53        = 0x53,                // No Operation
    IPxINPDRVWrite           = 0xD3,                // linear/circular drive start with queue data(Hold on mode), Restart on pause
    IPxNoOperation_54        = 0x54,                // No operation
    IPxNoOperation_D4        = 0xD4,                // No operation
    IPxNoOperation_55        = 0x55,                // No operation
    IPxARTSHOT               = 0xD5,                // Arithmetic block One time execution
    IPxARTSHOPERRead         = 0x56,                // Arithmetic block shift and operation selection Read
    IPxARTSHOPERWrite        = 0xD6,                // Arithmetic block shift and operation selection Write
    IPxARTSHRead             = 0x57,                // Arithmetic block shift amount data Read
    IPxARTSHWrite            = 0xD7,                // Arithmetic block shift amount data Write
    IPxARTSOURCERead         = 0x58,                // Arithmetic block operand configure data Read
    IPxARTSOURCEWrite        = 0xD8,                // Arithmetic block operand configure data Write
    IPxARTCRESULT1Read       = 0x59,                // Arithmetic first compare result data Read
    IPxNoOperation_D9        = 0xD9,                // No Operation
    IPxARTCRESULT2Read       = 0x5A,                // Arithmetic second compare result data Read
    IPxNoOperation_DA        = 0xDA,                // No Operation
    IPxARTARESULT1Read       = 0x5B,                // Arithmetic first algebraic result data Read
    IPxNoOperation_DB        = 0xDB,                // No Operation
    IPxARTARESULT2Read       = 0x5C,                // Arithmetic second algebraic result data Read
    IPxNoOperation_DC        = 0xDC,                // No operation
    IPxARTUSERARead          = 0x5D,                // Arithmetic block User operand A Read
    IPxARTUSERAWrite         = 0xDD,                // Arithmetic block User operand A Write
    IPxARTUSERBRead          = 0x5E,                // Arithmetic block User operand B Read
    IPxARTUSERBWrite         = 0xDE,                // Arithmetic block User operand B Write
    IPxARTUSERCRead          = 0x5F,                // Arithmetic block User operand C Read
    IPxARTUSERCWrite         = 0xDF,                // Arithmetic block User operand C Write

    /* Scripter Group Register            */
    IPySCRCON1Read           = 0x40,                // Sctipt configuration register-1 READ, 32bit, 0x00000000
    IPySCRCON1Write          = 0xC0,                // Sctipt configuration register-1 WRITE
    IPySCRCON2Read           = 0x41,                // Sctipt configuration register-2 READ, 32bit, 0x00000000
    IPySCRCON2Write          = 0xC1,                // Sctipt configuration register-2 WRITE
    IPySCRCON3Read           = 0x42,                // Sctipt configuration register-3 READ, 32bit, 0x00000000 
    IPySCRCON3Write          = 0xC2,                // Sctipt configuration register-3 WRITE
    IPySCRCONQRead           = 0x43,                // Sctipt configuration register-Queue READ, 32bit, 0x00000000
    IPySCRCONQWrite          = 0xC3,                // Sctipt configuration register-Queue WRITE
    IPySCRDATA1Read          = 0x44,                // Sctipt operation data register-1 READ, 32bit, 0x00000000 
    IPySCRDATA1Write         = 0xC4,                // Sctipt operation data register-1 WRITE
    IPySCRDATA2Read          = 0x45,                // Sctipt operation data register-2 READ, 32bit, 0x00000000 
    IPySCRDATA2Write         = 0xC5,                // Sctipt operation data register-2 WRITE
    IPySCRDATA3Read          = 0x46,                // Sctipt operation data register-3 READ, 32bit, 0x00000000 
    IPySCRDATA3Write         = 0xC6,                // Sctipt operation data register-3 WRITE
    IPySCRDATAQRead          = 0x47,                // Sctipt operation data register-Queue READ, 32bit, 0x00000000 
    IPySCRDATAQWrite         = 0xC7,                // Sctipt operation data register-Queue WRITE
    IPyNoOperation_48        = 0x48,                // No operation
    IPySCRQCLR               = 0xC8,                // Sctipt Queue clear
    IPySCRCQSIZERead         = 0x49,                // Sctipt configuration Queue index READ, 4bit, 0x00
    IPyNoOperation_C9        = 0xC9,                // No operation
    IPySCRDQSIZERead         = 0x4A,                // Sctiptoperation dat Queue index READ, 4bit, 0x00
    IPyNoOperation_CA        = 0xCA,                // No operation
    IPySCRQFLAGRead          = 0x4B,                // Sctipt Queue Full/Empty Flag READ, 4bit, 0x05
    IPyNoOperation_CB        = 0xCB,                // No operation
    IPySCRQSIZECONRead       = 0x4C,                // Sctipt Queue size register(0~13) READ, 16bit, 0xD0D0
    IPySCRQSIZECONWrite      = 0xCC,                // Sctipt Queue size register(0~13) WRITE
    IPySCRQSTATUSRead        = 0x4D,                // Sctipt Queue status READ, 12bit, 0x005
    IPyNoOperation_CD        = 0xCD,                // No operation
    IPyNoOperation_4E        = 0x4E,                // No operation
    IPyNoOperation_CE        = 0xCE,                // No operation
    IPyNoOperation_4F        = 0x4F,                // No operation
    IPyNoOperation_CF        = 0xCF,                // No operation

    /* Caption Group Register */
    IPyCAPCON1Read           = 0x50,                // Caption configuration register-1 READ, 32bit, 0x00000000
    IPyCAPCON1Write          = 0xD0,                // Caption configuration register-1 WRITE
    IPyCAPCON2Read           = 0x51,                // Caption configuration register-2 READ, 32bit, 0x00000000
    IPyCAPCON2Write          = 0xD1,                // Caption configuration register-2 WRITE
    IPyCAPCON3Read           = 0x52,                // Caption configuration register-3 READ, 32bit, 0x00000000 
    IPyCAPCON3Write          = 0xD2,                // Caption configuration register-3 WRITE
    IPyCAPCONQRead           = 0x53,                // Caption configuration register-Queue READ, 32bit, 0x00000000
    IPyCAPCONQWrite          = 0xD3,                // Caption configuration register-Queue WRITE
    IPyCAPDATA1Read          = 0x54,                // Caption operation data register-1 READ, 32bit, 0x00000000 
    IPyNoOperation_D4        = 0xD4,                // No operation
    IPyCAPDATA2Read          = 0x55,                // Caption operation data register-2 READ, 32bit, 0x00000000 
    IPyNoOperation_D5        = 0xD5,                // No operation
    IPyCAPDATA3Read          = 0x56,                // Caption operation data register-3 READ, 32bit, 0x00000000 
    IPyNoOperation_D6        = 0xD6,                // No operation
    IPyCAPDATAQRead          = 0x57,                // Caption operation data register-Queue READ, 32bit, 0x00000000 
    IPyNoOperation_D7        = 0xD7,                // No operation
    IPyNoOperation_58        = 0x58,                // No operation
    IPyCAPQCLR               = 0xD8,                // Caption Queue clear
    IPyCAPCQSIZERead         = 0x59,                // Caption configuration Queue 인덱스 READ, 4bit, 0x00
    IPyNoOperation_D9        = 0xD9,                // No operation
    IPyCAPDQSIZERead         = 0x5A,                // Caption configuration Queue 인덱스 READ, 4bit, 0x00
    IPyNoOperation_DA        = 0xDA,                // No operation
    IPyCAPQFLAGRead          = 0x5B,                // Caption Queue Full/Empty Flag READ, 4bit, 0x05
    IPyNoOperation_DB        = 0xDB,                // No operation
    IPyCAPQSIZECONRead       = 0x5C,                // Caption Queue size register(0~13) READ, 16bit, 0xD0D0
    IPyCAPQSIZECONWrite      = 0xDC,                // Caption Queue size register(0~13) WRITE
    IPyCAPQSTATUSRead        = 0x5D,                // Caption Queue status READ, 12bit, 0x005
    IPyNoOperation_DD        = 0xDD,                // No operation
    IPyNoOperation_5E        = 0x5E,                // No operation
    IPyNoOperation_DE        = 0xDE,                // No operation
    IPyNoOperation_5F        = 0x5F,                // No operation
    IPyNoOperation_DF        = 0xDF,                // No operation

    /* BUS - 1 Group Register            */
    IPxyINCNTRead            = 0x60,                // INTERNAL COUNTER DATA READ(Signed), 32bit, 0x00000000
    IPxyINCNTWrite           = 0xE0,                // INTERNAL COUNTER DATA WRITE(Signed)
    IPxyINCNTCMPRead         = 0x61,                // INTERNAL COUNTER COMPARATE DATA READ(Signed), 32bit, 0x00000000
    IPxyINCNTCMPWrite        = 0xE1,                // INTERNAL COUNTER COMPARATE DATA WRITE(Signed)
    IPxyINCNTSCALERead       = 0x62,                // INTERNAL COUNTER PRE-SCALE DATA READ, 8bit, 0x00
    IPxyINCNTSCALEWrite      = 0xE2,                // INTERNAL COUNTER PRE-SCALE DATA WRITE
    IPxyICPRead              = 0x63,                // INTERNAL COUNTER P-DATA READ, 32bit, 0x7FFFFFFF
    IPxyICPWrite             = 0xE3,                // INTERNAL COUNTER P-DATA WRITE
    IPxyEXCNTRead            = 0x64,                // EXTERNAL COUNTER DATA READ READ(Signed), 32bit, 0x00000000
    IPxyEXCNTWrite           = 0xE4,                // EXTERNAL COUNTER DATA READ WRITE(Signed)
    IPxyEXCNTCMPRead         = 0x65,                // EXTERNAL COUNTER COMPARATE DATA READ(Signed), 32bit, 0x00000000
    IPxyEXCNTCMPWrite        = 0xE5,                // EXTERNAL COUNTER COMPARATE DATA WRITE(Signed)
    IPxyEXCNTSCALERead       = 0x66,                // EXTERNAL COUNTER PRE-SCALE DATA READ, 8bit, 0x00
    IPxyEXCNTSCALEWrite      = 0xE6,                // EXTERNAL COUNTER PRE-SCALE DATA WRITE
    IPxyEXPRead              = 0x67,                // EXTERNAL COUNTER P-DATA READ, 32bit, 0x7FFFFFFF
    IPxyEXPWrite             = 0xE7,                // EXTERNAL COUNTER P-DATA WRITE
    IPxyEXSPDRead            = 0x68,                // EXTERNAL SPEED DATA READ, 32bit, 0x00000000
    IPxyNoOperation_E8       = 0xE8,                // No operation
    IPxyEXSPDCMPRead         = 0x69,                // EXTERNAL SPEED COMPARATE DATA READ, 32bit, 0x00000000
    IPxyEXSPDCMPWrite        = 0xE9,                // EXTERNAL SPEED COMPARATE DATA WRITE
    IPxyEXFILTERDRead        = 0x6A,                // EXTERNAL Sensor bandwidth DATA READ, 32bit, 0x00050005
    IPxyEXFILTERDWrite       = 0xEA,                // EXTERNAL Sensor bandwidth DATA WRITE
    IPxyOFFREGIONRead        = 0x6B,                // OFF-RANGE DATA READ, 8bit, 0x00
    IPxyOFFREGIONWrite       = 0xEB,                // OFF-RANGE DATA WRITE
    IPxyDEVIATIONRead        = 0x6C,                // DEVIATION DATA READ, 16bit, 0x0000
    IPxyNoOperation_EC       = 0xEC,                // No operation
    IPxyPGMCHRead            = 0x6D,                // PGM REGISTER CHANGE DATA READ
    IPxyPGMCHWrite           = 0xED,                // PGM REGISTER CHANGE DATA WRITE
    IPxyCOMPCONRead          = 0x6E,                // COMPARE REGISTER INPUT CHANGE DATA READ
    IPxyCOMPCONWrite         = 0xEE,                // COMPARE REGISTER INPUT CHANGE DATA WRITE
    IPxyNoOperation_6F       = 0x6F,                // No operation
    IPxyNoOperation_EF       = 0xEF,                // No operation

    /* BUS - 2 Group Register            */
    IPxyFUNCONRead           = 0x70,                // Function configuration DATA READ,
    IPxyFUNCONWrite          = 0xF0,                // Function configuration DATA WRITE
    IPxyMODE1Read            = 0x71,                // MODE1 DATA READ,
    IPxyMODE1Write           = 0xF1,                // MODE1 DATA WRITE
    IPxyMODE2Read            = 0x72,                // MODE2 DATA READ,
    IPxyMODE2Write           = 0xF2,                // MODE2 DATA WRITE
    IPxyUIODATARead          = 0x73,                // UNIVERSAL IN READ,
    IPxyUIODATAWrite         = 0xF3,                // UNIVERSAL OUT WRITE
    IPxyENDSTATUSRead        = 0x74,                // END STATUS DATA READ,
    IPxyCLIMCLR              = 0xF4,                // Complete limit stop clear command
    IPxyMECHRead             = 0x75,                // MECHANICAL SIGNAL DATA READ, 13bit
    IPxyNoOperation_F5       = 0xF5,                // No operation
    IPxyDRVSTATUSRead        = 0x76,                // DRIVE STATE DATA READ, 20bit
    IPxyNoOperation_F6       = 0xF6,                // No operation
    IPxyEXCNTCLRRead         = 0x77,                // EXTERNAL COUNTER configuration DATA READ, 9bit, 0x00
    IPxyEXCNTCLRWrite        = 0xF7,                // EXTERNAL COUNTER configuration DATA WRITE
    IPxyNoOperation_78       = 0x78,                // No operation
    IPxySWRESET              = 0xF8,                // REGISTER CLEAR(INITIALIZATION), Software reset
    IPxyINTFLAG1Read         = 0x79,                // Interrupt Flag1 READ, 32bit, 0x00000000
    IPxyINTFLAG1CLRWrite     = 0xF9,                // Interrupt Flag1 Clear data write command.
    IPxyINTMASK1Read         = 0x7A,                // Interrupt Mask1 READ, 32bit, 0x00000001
    IPxyINTMASK1Write        = 0xFA,                // Interrupt Mask1 WRITE
    IPxyUIOMODERead          = 0x7B,                // UIO MODE DATA READ, 12bit, 0x01F
    IPxyUIOMODEWrite         = 0xFB,                // UIO MODE DATA WRITE
    IPxyINTFLAG2Read         = 0x7C,                // Interrupt Flag2 READ, 32bit, 0x00000000
    IPxyINTFLAG2CLRWrite     = 0xFC,                // Interrupt Flag2 Clear data write command.
    IPxyINTMASK2Read         = 0x7D,                // Interrupt Mask2 READ, 32bit, 0x00000001
    IPxyINTMASK2Write        = 0xFD,                // Interrupt Mask2 WRITE
    IPxyINTUSERCONRead       = 0x7E,                // User interrupt selection control.
    IPxyINTUSERCONWrite      = 0xFE,                // User interrupt selection control. 
    IPxyNoOperation_7F       = 0x7F,                // No operation
    IPxyINTGENCMD            = 0xFF                 // Interrupt generation command.
} IPCOMMAND;

/* CAMC-QI COMMAND LIST                            */
typedef enum _QICOMMAND
{
    // Previous register and etc Registers
    QiPRANGERead             = 0x00,                // Previous RANGE READ
    QiPRANGEWrite            = 0x80,                // Previous RANGE WRITE
    QiPSTDRead               = 0x01,                // Previous START/STOP SPEED DATA READ
    QiPSTDWrite              = 0x81,                // Previous START/STOP SPEED DATA WRITE
    QiPOBJRead               = 0x02,                // Previous OBJECT SPEED DATA READ
    QiPOBJWrite              = 0x82,                // Previous OBJECT SPEED DATA WRITE
    QiPRATE1Read             = 0x03,                // Previous RATE-1 DATA READ
    QiPRATE1Write            = 0x83,                // Previous RATE-1 DATA WRITE
    QiPRATE2Read             = 0x04,                // Previous RATE-2 DATA READ
    QiPRATE2Write            = 0x84,                // Previous RATE-2 DATA WRITE
    QiPSW1Read               = 0x05,                // Previous SW-1 DATA READ
    QiPSW1Write              = 0x85,                // Previous SW-1 DATA WRITE
    QiPSW2Read               = 0x06,                // Previous SW-2 DATA READ
    QiPSW2Write              = 0x86,                // Previous SW-2 DATA WRITE
    QiPDCFGRead              = 0x07,                // Previous Drive configure data READ
    QiPDCFGWrite             = 0x87,                // Previous Drive configure data WRITE
    QiPREARRead              = 0x08,                // Previous SLOW DOWN/REAR PULSE READ
    QiPREARWrite             = 0x88,                // Previous SLOW DOWN/REAR PULSE WRITE
    QiPPOSRead               = 0x09,                // Previous Drive pulse amount data/Interpolation end position READ
    QiPPOSWrite              = 0x89,                // Previous Drive pulse amount data/Interpolation end position WRITE 
    QiPCENTRead              = 0x0A,                // Previous Circular Int. center/Master axis target position for multiple chip linear int. READ
    QiPCENTWrite             = 0x8A,                // Previous Circular Int. center/Master axis target position for multiple chip linear int. WRITE
    QiPISNUMRead             = 0x0B,                // Previous Interpolation step number READ
    QiPISNUMWrite            = 0x8B,                // Previous Interpolation step number WRITE
    QiNoOperation_0C         = 0x0C,                // No operation
    QiCLRPRE                 = 0x8C,                // Clear previous driving data Queue.
    QiNoOperation_0D         = 0x0D,                // No operation
    QiPOPPRE                 = 0x8D,                // Pop and shift data of previous driving data Queue.
    QiPPORTMARestore         = 0x0E,                // Restore data ports.
    QiPPORTMABackup          = 0x8E,                // Backup data ports.
    QiCURSPDRead             = 0x0F,                // Current SPEED DATA READ
    QiNoOperation_8F         = 0x8F,                // No operation

    // Working Registers
    QiRANGERead              = 0x10,                // RANGE READ
    QiRANGEWrite             = 0x90,                // RANGE WRITE
    QiSTDRead                = 0x11,                // START/STOP SPEED DATA READ
    QiSTDWrite               = 0x91,                // START/STOP SPEED DATA WRITE
    QiOBJRead                = 0x12,                // OBJECT SPEED DATA READ
    QiOBJWrite               = 0x92,                // OBJECT SPEED DATA WRITE
    QiRATE1Read              = 0x13,                // RATE-1 DATA READ
    QiRATE1Write             = 0x93,                // RATE-1 DATA WRITE
    QiRATE2Read              = 0x14,                // RATE-2 DATA READ
    QiRATE2Write             = 0x94,                // RATE-2 DATA WRITE
    QiSW1Read                = 0x15,                // SW-1 DATA READ
    QiSW1Write               = 0x95,                // SW-1 DATA WRITE
    QiSW2Read                = 0x16,                // SW-2 DATA READ
    QiSW2Write               = 0x96,                // SW-2 DATA WRITE
    QiDCFGRead               = 0x17,                // Drive configure data READ
    QiDCFGWrite              = 0x97,                // Drive configure data WRITE
    QiREARRead               = 0x18,                // SLOW DOWN/REAR PULSE READ
    QiREARWrite              = 0x98,                // SLOW DOWN/REAR PULSE WRITE
    QiPOSRead                = 0x19,                // Drive pulse amount data/Interpolation end position READ
    QiPOSWrite               = 0x99,                // Drive pulse amount data/Interpolation end position WRITE 
    QiCENTRead               = 0x1A,                // Circular Int. center/Master axis target position for multiple chip linear int. READ
    QiCENTWrite              = 0x9A,                // Circular Int. center/Master axis target position for multiple chip linear int. WRITE
    QiISNUMRead              = 0x1B,                // Interpolation step number READ
    QiISNUMWrite             = 0x9B,                // Interpolation step number WRITE
    QiREMAIN                 = 0x1C,                // Remain pulse data after stopping preset drive function abnormally.
    QiNoOperation_9C         = 0x9C,                // No operation
    QiOBJORGRead             = 0x1F,                // Original search object speed READ
    QiOBJORGWrite            = 0x9F,                // Original search object speed WRITE

    // Universal in/out setting
    QiUIOMRead               = 0x1D,                // Universal in/out terminal mode READ
    QiUIOMWrite              = 0x9D,                // Universal in/out terminal mode WRITE
    QiUIORead                = 0x1E,                // Universal in/out terminal mode READ
    QiUIOWrite               = 0x9E,                // Universal in/out terminal mode WRIT

    // Drive start command
    QiNoOperation_20         = 0x20,                // No operation.
    QiSTRN                   = 0xA0,                // Normal profile mode drive start.(STD => OBJ => STD)
    QiNoOperation_21         = 0x21,                // No operation.
    QiSTRO                   = 0xA0,                // Start at OBJ profile mode drive start.(OBJ => STD)
    QiNoOperation_22         = 0x22,                // No operation.
    QiSTRCO                  = 0xA0,                // Constant speed profile #1 drive start.(OBJ)
    QiNoOperation_23         = 0x23,                // No operation.
    QiSTRCS                  = 0xA0,                // Constant speed profile #2 drive start.(STD)
    QiNoOperation_60         = 0x5C,                // No operation.
    QiASTRN                  = 0xDC,                // Normal profile mode drive start with DCFG7~0 bit data in DATAPL0 port.(STD => OBJ => STD)
    QiNoOperation_61         = 0x5D,                // No operation.
    QiASTRO                  = 0xDD,                // Start at OBJ profile mode drive start with DCFG7~0 bit data in DATAPL0 port.(OBJ => STD)
    QiNoOperation_62         = 0x5E,                // No operation.
    QiASTRCO                 = 0xDE,                // Constant speed profile #1 drive start with DCFG7~0 bit data in DATAPL0 port.(OBJ)
    QiNoOperation_63         = 0x5F,                // No operation.
    QiASTRCS                 = 0xDF,                // Constant speed profile #2 drive start with DCFG7~0 bit data in DATAPL0 port.(STD)

    // Drive control command
    QiNoOperation_24         = 0x24,                // No operation.
    QiSSTOP                  = 0xA4,                // Slow Down stop.
    QiNoOperation_25         = 0x25,                // No operation.
    QiSTOP                   = 0xA5,                // Immediately stop.
    QiNoOperation_26         = 0x26,                // No operation.
    QiSQRO1                  = 0xA6,                // Output one shot of the start pulse form SQSTR1 terminal.
    QiNoOperation_27         = 0x27,                // No operation.
    QiSQRO2                  = 0xA7,                // Output one shot of the start pulse form SQSTR2 terminal.
    QiNoOperation_28         = 0x28,                // No operation.
    QiSQRI1                  = 0xA8,                // Execution sync start function same as SQSTR1 input.
    QiNoOperation_29         = 0x29,                // No operation.
    QiSQRI2                  = 0xA9,                // Execution sync start function same as SQSTR2 input.
    QiNoOperation_2A         = 0x2A,                // No operation
    QiSQSTP1                 = 0xAA,                // Output one shot of the stop pulse from SQSTP1 terminal.
    QiNoOperation_2B         = 0x2B,                // No operation.
    QiSQSTP2                 = 0xAB,                // Output one shot of the stop pulse from SQSTP2 terminal.
    QiISCNTRead              = 0x2C,                // Interpolation stop counter value READ.
    QiNoOperation_AC         = 0xAC,                // No operation.
    QiISACNTRead             = 0x2D,                // Interpolation step counter READ for advanced deceleration mode . 
    QiNoOperation_AD         = 0xAD,                // No operation.
    QiNoOperation_2E         = 0x2E,                // No operation.
    QiESTOP                  = 0xAE,                // Emergency stop all axis.
    QiNoOperation_2F         = 0x2F,                // No operation
    QiSWRESET                = 0xAF,                // Software reset(all axis).

    // QiNoOperation_30    = 0x30,                  // Driven pulse amount during last driving(Interpolation step counter for path move).
    // QiDRPCNTRead        = 0xB0,                  // No operation
    QiDRPCNTRead            = 0x30,                 // No operation
    QiNoOperation_B0        = 0xB0,                 // Driven pulse amount during last driving(Interpolation step counter for path move).
    QiNoOperation_31        = 0x31,                 // No operation
    QiINTGEN                = 0xB1,                 // Interrupt generation command.
                                                    
    // Peripheral function setting.                    
    QiNoOperation_33        = 0x32,                 // No operation.
    QiTRGQPOP               = 0xB2,                 // Pop and shift data in trigger position queue.
    QiTRTMCFRead            = 0x33,                 // Trigger/Timer configure READ.
    QiTRTMCFWrite           = 0xB3,                 // Trigger/Timer configure WRITE.
    QiSNSMTRead             = 0x34,                 // Software negative limit position READ.
    QiSNSMTWrite            = 0xB4,                 // Software negative limit position WRITE.
    QiSPSMTRead             = 0x35,                 // Software positive limit position READ.
    QiSPSMTWrite            = 0xB5,                 // Software positive limit position WRITE.
    QiTRGPWRead             = 0x36,                 // Trigger pulse width READ.
    QiTRGPWWrite            = 0xB6,                 // Trigger pulse width WRITE.
    QiTRGSPRead             = 0x37,                 // Trigger function start position READ.
    QiTRGSPWrite            = 0xB7,                 // Trigger function start position WRITE.
    QiTRGEPRead             = 0x38,                 // Trigger function end position READ.
    QiTRGEPWrite            = 0xB8,                 // Trigger function end position WRITE.
    QiPTRGPOSRead           = 0x39,                 // Trigger position or period queue data READ.
    QiPTRGPOSWrite          = 0xB9,                 // Push trigger position or period queue.
    QiNoOperation_3A        = 0x3A,                 // No operation.
    QiCLRTRIG               = 0xBA,                 // Clear trigger position or period queue.
    QiNoOperation_3B        = 0x3B,                 // No operation.
    QiTRGGEN                = 0xBB,                 // Generate one shot trigger pulse.
    QiTMRP1Read             = 0x3C,                 // Timer #1 period data READ.
    QiTMRP1Write            = 0xBC,                 // Timer #1 period data WRITE.
    QiTMRP2Read             = 0x3D,                 // Timer #2 period data READ.
    QiTMRP2Write            = 0xBD,                 // Timer #2 period data WRITE.
    QiTMR1GENstop           = 0x3E,                 // Timer #1 stop.
    QiTMR1GENstart          = 0xBE,                 // Timer #1 start.
    QiTMR2GENstop           = 0x3F,                 // Timer #2 stop.
    QiTMR2GENstart          = 0xBF,                 // Timer #2 start.
    QiERCReset              = 0x60,                 // ERC signal reset.
    QiERCSet                = 0xE0,                 // ERC signal set.
                                                    
    //Script1/2/3 setting registers                    
    QiSCRCON1Read           = 0x40,                 // Script1 control queue register READ.
    QiSCRCON1Write          = 0xC0,                 // Script1 control queue register WRITE.
    QiSCRCMD1Read           = 0x41,                 // Script1 command queue register READ.
    QiSCRCMD1Write          = 0xC1,                 // Script1 command queue register WRITE.
    QiSCRDAT1Read           = 0x42,                 // Script1 execution data queue register READ.
    QiSCRDAT1Write          = 0xC2,                 // Script1 execution data queue register WRITE.
    QiCQ1Read               = 0x43,                 // Script1 captured data queue register(top of depth 15 Queue)READ.
    QiNoOperation_C3        = 0xC3,                 // No operation.
    QiSCRCFG1Read           = 0x44,                 // Script1 flag control register READ.
    QiSCRCFG1Write          = 0xC4,                 // Script1 flag control register WRITE. 
    QiSCRCON2Read           = 0x45,                 // Script2 control queue register READ.
    QiSCRCON2Write          = 0xC5,                 // Script2 control queue register WRITE.
    QiSCRCMD2Read           = 0x46,                 // Script2 command queue register READ.
    QiSCRCMD2Write          = 0xC6,                 // Script2 command queue register WRITE.
    QiSCRDAT2Read           = 0x47,                 // Script2 execution data queue register READ.
    QiSCRDAT2Write          = 0xC7,                 // Script2 execution data queue register WRITE.
    QiCQ2Read               = 0x48,                 // Script2 captured data queue register(top of depth 15 Queue)READ.
    QiNoOperation_C8        = 0xC8,                 // No operation.
    QiSCRCFG2Read           = 0x49,                 // Script2 flag control register READ.
    QiSCRCFG2Write          = 0xC9,                 // Script2 flag control register WRITE. 
    QiSCRCON3Read           = 0x4A,                 // Script3 control register READ.
    QiSCRCON3Write          = 0xCA,                 // Script3 control register WRITE.
    QiSCRCMD3Read           = 0x4B,                 // Script3 command register READ.
    QiSCRCMD3Write          = 0xCB,                 // Script3 command register WRITE.
    QiSCRDAT3Read           = 0x4C,                 // Script3 execution data register READ.
    QiSCRDAT3Write          = 0xCC,                 // Script3 execution data register WRITE.
    QiCQ3Read               = 0x4D,                 // Script3 captured data register READ.
    QiNoOperation_CD        = 0xCD,                 // No operation.
    QiNoOperation_4E        = 0x4E,                 // No operation.
    QiNoOperation_CE        = 0xCE,                 // No operation.
    QiNoOperation_4F        = 0x4F,                 // No operation.
    QiNoOperation_CF        = 0xCF,                 // [No operation code for script reservation command].
                                                    
    //Script4 and Script status setting registers    
    QiSCRCON4Read           = 0x50,                 // Script4 control register READ.
    QiSCRCON4Write          = 0xD0,                 // Script4 control register WRITE.
    QiSCRCMD4Read           = 0x51,                 // Script4 command register READ.
    QiSCRCMD4Write          = 0xD1,                 // Script4 command register WRITE.
    QiSCRDAT4Read           = 0x52,                 // Script4 execution data register READ.
    QiSCRDAT4Write          = 0xD2,                 // Script4 execution data register WRITE.
    QiCQ4Read               = 0x53,                 // Script4 captured data register READ.
    QiNoOperation_D3        = 0xD3,                 // No operation.
    QiSCRTGRead             = 0x54,                 // Target source data setting READ.
    QiSCRTGWrite            = 0xD4,                 // Target source data setting WRITE.
    QiSCRSTAT1Read          = 0x55,                 // Script status #1 READ.
    QiNoOperation_D5        = 0xD5,                 // No operation.
    QiSCRSTAT2Read          = 0x56,                 // Script status #2 READ.
    QiNoOperation_D6        = 0xD6,                 // No operation.
    QiNoOperation_57        = 0x57,                 // No operation.
    QiINITSQWrite           = 0xD7,                 // Initialize script queues with target selection.
    QiNoOperation_58        = 0x58,                 // No operation.
    QiINITCQWrite           = 0xD8,                 // Initialize captured data queue with target selection.
    QiSCRMRead              = 0x59,                 // Set enable mode with target selection READ.
    QiSCRMWrite             = 0xD9,                 // Set enable mode with target selection WRITE.
    QiNoOperation_5A        = 0x5A,                 // No operation.
    QiSQ1POP                = 0xDA,                 // Pop and shift data of script1 queue.
    QiNoOperation_5B        = 0x5B,                 // No operation.
    QiSQ2POP                = 0xDB,                 // Pop and shift data of script2 queue.
                                                    
    //Counter function registers                    
    QiCNTLBRead             = 0x61,                 // Counter lower bound data READ.
    QiCNTLBWrite            = 0xE1,                 // Counter lower bound data WRITE.
    QiCNTUBRead             = 0x62,                 // Counter upper bound data READ.
    QiCNTUBWrite            = 0xE2,                 // Counter upper bound data WRITE.
    QiCNTCF1Read            = 0x63,                 // Counter configure #1 READ.
    QiCNTCF1Write           = 0xE3,                 // Counter configure #1 WRITE.
    QiCNTCF2Read            = 0x64,                 // Counter configure #2 READ.
    QiCNTCF2Write           = 0xE4,                 // Counter configure #2 WRITE.
    QiCNTCF3Read            = 0x65,                 // Counter configure #3 READ.
    QiCNTCF3Write           = 0xE5,                 // Counter configure #3 WRITE.
    QiCNT1Read              = 0x66,                 // Counter #1 data READ.
    QiCNT1Write             = 0xE6,                 // Counter #1 data WRITE.
    QiCNT2Read              = 0x67,                 // Counter #2 data READ.
    QiCNT2Write             = 0xE7,                 // Counter #2 data WRITE.
    QiCNT3Read              = 0x68,                 // Counter #3 data READ.
    QiCNT3Write             = 0xE8,                 // Counter #3 data WRITE.
    QiCNT4Read              = 0x69,                 // Counter #4 data READ.
    QiCNT4Write             = 0xE9,                 // Counter #4 data WRITE.
    QiCNT5Read              = 0x6A,                 // Counter #5 data READ.
    QiCNT5Write             = 0xEA,                 // Counter #5 data WRITE.
    QiCNTC1Read             = 0x6B,                 // Counter #1 comparator's data READ.
    QiCNTC1Write            = 0xEB,                 // Counter #1 comparator's data WRITE.
    QiCNTC2Read             = 0x6C,                 // Counter #2 comparator's data READ.
    QiCNTC2Write            = 0xEC,                 // Counter #2 comparator's data WRITE.
    QiCNTC3Read             = 0x6D,                 // Counter #3 comparator's data READ.
    QiCNTC3Write            = 0xED,                 // Counter #3 comparator's data WRITE.
    QiCNTC4Read             = 0x6E,                 // Counter #4 comparator's data READ.
    QiCNTC4Write            = 0xEE,                 // Counter #4 comparator's data WRITE.
    QiCNTC5Read             = 0x6F,                 // Counter #5 comparator's data READ.
    QiCNTC5Write            = 0xEF,                 // Counter #5 comparator's data WRITE.
                                                    
    // Configure and Status registers                
    QiUCFG1Read             = 0x70,                 // Configure register #1 READ.
    QiUCFG1Write            = 0xF0,                 // Configure register #1 WRITE.
    QiUCFG2Read             = 0x71,                 // Configure register #2 READ.
    QiUCFG2Write            = 0xF1,                 // Configure register #2 WRITE.
    QiUCFG3Read             = 0x72,                 // Configure register #3 READ.
    QiUCFG3Write            = 0xF2,                 // Configure register #3 WRITE.
    QiUCFG4Read             = 0x73,                 // Configure register #4 READ.
    QiUCFG4Write            = 0xF3,                 // Configure register #4 WRITE.
    QiNoOperation_74        = 0x74,                 // No operation.
    QiNoOperation_F4        = 0xF4,                 // No operation.
    QiNoOperation_75        = 0x75,                 // No operation.
    QiNoOperation_F5        = 0xF5,                 // No operation.
    QiNoOperation_76        = 0x76,                 // No operation.
    QiNoOperation_F6        = 0xF6,                 // No operation.
    QiIMASK1Read            = 0x77,                 // Interrupt bank#1 mask register READ.
    QiIMASK1Write           = 0xF7,                 // Interrupt bank#1 mask register WRITE.
    QiIMASK2Read            = 0x78,                 // Interrupt bank#2 mask register READ.
    QiIMASK2Write           = 0xF8,                 // Interrupt bank#2 mask register WRITE.
    QiSTAT1Read             = 0x79,                 // Status register #1(END STATUS)READ.
    QiESCLR                 = 0xF9,                 // Status register #1(END STATUS) Clear.
    QiSTAT2Read             = 0x7A,                 // Status register #2 READ.
    QiNoOperation_FA        = 0xFA,                 // No operation.
    QiSTAT3Read             = 0x7B,                 // Status register #3 READ.
    QiNoOperation_FB        = 0xFB,                 // No operation.
    QiSTAT4Read             = 0x7C,                 // Status register #4 READ.
    QiNoOperation_FC        = 0xFC,                 // No operation.
    QiSTAT5Read             = 0x7D,                 // Status register #5 READ.
    QiNoOperation_FD        = 0xFD,                 // No operation.
    QiIFLAG1Read            = 0x7E,                 // Interrupt bank #1 flag READ.
    QiIFLAG1Clear           = 0xFE,                 // Interrupt bank #1 flag Clear.
    QiIFLAG2Read            = 0x7F,                 // Interrupt bank #2 flag READ.
    QiIFLAG2Clear           = 0xFF,                 // Interrupt bank #2 flag Clear.
                                                    
} QICOMMAND;                                        
                                                    
                                                    
//--------------------------------------------------------------------------------------------//
// CAMC-QI Script/Caption Define                    
//--------------------------------------------------------------------------------------------//
#define QI_SCR_REG1                              1
#define QI_SCR_REG2                              2
#define QI_SCR_REG3                              3
#define QI_SCR_REG4                              4

#define QI_OPERATION_ONCE_RUN                    0x00000000                    // bit 24 OFF
#define QI_OPERATION_CONTINUE_RUN                0x01000000                    // bit 24 ON
#define QI_INPUT_DATA_FROM_SCRIPT_DATA           0x00000000                    // bit 23 OFF,
#define QI_INPUT_DATA_FROM_TARGET_REG            0x00800000                    // bit 23 ON,
//JEKIM. 070327
//#define QI_INTERRUPT_GEN_ENABLE                0x00000000                    // bit 22 OFF,
//#define QI_INTERRUPT_GEN_DISABLE               0x00400000                    // bit 22 ON,
#define QI_INTERRUPT_GEN_ENABLE                  0x00400000                    // bit 22 ON,
#define QI_INTERRUPT_GEN_DISABLE                 0x00000000                    // bit 22 OFF,
#define QI_OPERATION_EVENT_NONE                  0x00000000                    // bit 21=OFF, 20=OFF
//JEKIM. 070327
//#define QI_OPERATION_EVENT_OR                  0x00100000                    // bit 21=OFF, 20=ON
//#define QI_OPERATION_EVENT_AND                 0x00200000                    // bit 21=ON,  20=OF
#define QI_OPERATION_EVENT_AND                   0x00100000                    // bit 21=OFF, 20=ON
#define QI_OPERATION_EVENT_OR                    0x00200000                    // bit 21=ON,  20=OFF
#define QI_OPERATION_EVENT_XOR                   0x00300000                    // bit 21=ON,  20=ON
#define QI_SND_EVENT_AXIS(Axis)                  ((Axis % 4) << 18)            // bit 19~18 (00:X, 01:Y, 10:Z, 11:U)
#define QI_FST_EVENT_AXIS(Axis)                  ((Axis % 4) << 16)            // bit 17~16 (00:X, 01:Y, 10:Z, 11:U)
#define QI_OPERATION_EVENT_2(Event)              ((Event & 0xFF) << 8)         // bit 15..8
#define QI_OPERATION_EVENT_1(Event)              (Event & 0xFF)                // bit 7..0
#define QI_OPERATION_COMMAND(Command, Axis)      ((Command & 0xFF) << ((Axis % 4) * 8))        // bit 7..0 : enum _QISCOMMAND 참조

/* EVENT LIST                            */
typedef enum _IPEVENT
{
    EVENT_IPNONE                         = 0x00,
    EVENT_IPDRIVE_END                    = 0x01,
    EVENT_IPPRESETDRIVE_START            = 0x02,        
    EVENT_IPPRESETDRIVE_END              = 0x03,        
    EVENT_IPCONTINOUSDRIVE_START         = 0x04,            
    EVENT_IPCONTINOUSDRIVE_END           = 0x05,        
    EVENT_IPSIGNAL_SEARCH_1_START        = 0x06,            
    EVENT_IPSIGNAL_SEARCH_1_END          = 0x07,        
    EVENT_IPSIGNAL_SEARCH_2_START        = 0x08,            
    EVENT_IPSIGNAL_SEARCH_2_END          = 0x09,        
    EVENT_IPORIGIN_DETECT_START          = 0x0A,        
    EVENT_IPORIGIN_DETECT_END            = 0x0B,        
    EVENT_IPSPEED_UP                     = 0x0C,    
    EVENT_IPSPEED_CONST                  = 0x0D,    
    EVENT_IPSPEED_DOWN                   = 0x0E,    

    EVENT_IPICL                          = 0x0F,
    EVENT_IPICE                          = 0x10,
    EVENT_IPICG                          = 0x11,
    EVENT_IPECL                          = 0x12,
    EVENT_IPECE                          = 0x13,
    EVENT_IPECG                          = 0x14,
    EVENT_IPEPCE                         = 0x15,        
    EVENT_IPEPCL                         = 0x16,        
    EVENT_IPEPCG                         = 0x17,        
    EVENT_IPSPL                          = 0x18,    
    EVENT_IPSPE                          = 0x19,    
    EVENT_IPSPG                          = 0x1A,    
    EVENT_IPSP12L                        = 0x1B,        
    EVENT_IPSP12E                        = 0x1C,        
    EVENT_IPSP12G                        = 0x1D,        
    EVENT_IPSP23L                        = 0x1E,        
    EVENT_IPSP23E                        = 0x1F,        
    EVENT_IPSP23G                        = 0x20,        
    EVENT_IPOBJECT_SPEED                 = 0x21,            
    EVENT_IPSS_SPEED                     = 0x22,        
    EVENT_IPESTOP                        = 0x23,        
    EVENT_IPSSTOP                        = 0x24,        
    EVENT_IPPELM                         = 0x25,        
    EVENT_IPNELM                         = 0x26,        
    EVENT_IPPSLM                         = 0x27,        
    EVENT_IPNSLM                         = 0x28,        
    EVENT_IPDEVIATION_ERROR              = 0x29,            
    EVENT_IPDATA_ERROR                   = 0x2A,        
    EVENT_IPALARM_ERROR                  = 0x2B,        
    EVENT_IPESTOP_COMMAND                = 0x2C,            
    EVENT_IPSSTOP_COMMAND                = 0x2D,            
    EVENT_IPESTOP_SIGNAL                 = 0x2E,            
    EVENT_IPSSTOP_SIGNAL                 = 0x2F,            
    EVENT_IPELM                          = 0x30,    
    EVENT_IPSLM                          = 0x31,    
    EVENT_IPINPOSITION                   = 0x32,        
    EVENT_IPINOUT0_HIGH                  = 0x33,        
    EVENT_IPINOUT0_LOW                   = 0x34,        
    EVENT_IPINOUT1_HIGH                  = 0x35,        
    EVENT_IPINOUT1_LOW                   = 0x36,        
    EVENT_IPINOUT2_HIGH                  = 0x37,        
    EVENT_IPINOUT2_LOW                   = 0x38,        
    EVENT_IPINOUT3_HIGH                  = 0x39,        
    EVENT_IPINOUT3_LOW                   = 0x3A,        
    EVENT_IPINOUT4_HIGH                  = 0x3B,        
    EVENT_IPINOUT4_LOW                   = 0x3C,        
    EVENT_IPINOUT5_HIGH                  = 0x3D,        
    EVENT_IPINOUT5_LOW                   = 0x3E,        
    EVENT_IPINOUT6_HIGH                  = 0x3F,        
    EVENT_IPINOUT6_LOW                   = 0x40,        
    EVENT_IPINOUT7_HIGH                  = 0x41,        
    EVENT_IPINOUT7_LOW                   = 0x42,        
    EVENT_IPINOUT8_HIGH                  = 0x43,        
    EVENT_IPINOUT8_LOW                   = 0x44,        
    EVENT_IPINOUT9_HIGH                  = 0x45,        
    EVENT_IPINOUT9_LOW                   = 0x46,        
    EVENT_IPINOUT10_HIGH                 = 0x47,            
    EVENT_IPINOUT10_LOW                  = 0x48,        
    EVENT_IPINOUT11_HIGH                 = 0x49,            
    EVENT_IPINOUT11_LOW                  = 0x4A,        
    EVENT_IPSENSOR_DRIVE1_START          = 0x4B,            
    EVENT_IPSENSOR_DRIVE1_END            = 0x4C,            
    EVENT_IPSENSOR_DRIVE2_START          = 0x4D,            
    EVENT_IPSENSOR_DRIVE2_END            = 0x4E,            
    EVENT_IPSENSOR_DRIVE3_START          = 0x4F,            
    EVENT_IPSENSOR_DRIVE3_END            = 0x50,            
    EVENT_IP1STCOUNTER_NDATA_CLEAR       = 0x51,                
    EVENT_IP2NDCOUNTER_NDATA_CLEAR       = 0x52,                
    EVENT_IPMARK_SIGNAL_HIGH             = 0x53,            
    EVENT_IPMARK_SIGNAL_LOW              = 0x54,            
    EVENT_IPSOFTWARE_PLIMIT              = 0x55,            
    EVENT_IPSOFTWARE_NLIMIT              = 0x56,            
    EVENT_IPSOFTWARE_LIMIT               = 0x57,            
    EVENT_IPTRIGGER_ENABLE               = 0x58,            
    EVENT_IPINT_GEN_SOURCE               = 0x59,            
    EVENT_IPINT_GEN_CMDF9                = 0x5A,            
    EVENT_IPPRESETDRIVE_TRI_START        = 0x5B,                
    EVENT_IPBUSY_HIGH                    = 0x5C,        
    EVENT_IPBUSY_LOW                     = 0x5D,

    EVENT_IPLINP_START                   = 0x5E,
    EVENT_IPLINP_END                     = 0x5F,

    EVENT_IPCINP_START                   = 0x60,
    EVENT_IPCINP_END                     = 0x61,
    EVENT_IPPINP_START                   = 0x62,
    EVENT_IPPINP_END                     = 0x63,
    EVENT_IPPDATA_Q_EMPTY                = 0x64,        
    EVENT_IPS_C_INTERNAL_COMMAND_Q_EMPTY = 0x65,                
    EVENT_IPS_C_INTERNAL_COMMAND_Q_FULL  = 0x66,            
    EVENT_IPxSYNC_ACTIVATED              = 0x67,        
    EVENT_IPySYNC_ACTIVATED              = 0x68,        
    EVENT_IPINTERRUPT_GENERATED          = 0x69,        
    EVENT_IPINP_START                    = 0x6A,    
    EVENT_IPINP_END                      = 0x6B,    
    EVENT_IPALGEBRIC_RESULT_BIT0         = 0x6C,            
    EVENT_IPALGEBRIC_RESULT_BIT1         = 0x6D,            
    EVENT_IPALGEBRIC_RESULT_BIT2         = 0x6E,            
    EVENT_IPALGEBRIC_RESULT_BIT3         = 0x6F,            
    EVENT_IPALGEBRIC_RESULT_BIT4         = 0x70,            
    EVENT_IPALGEBRIC_RESULT_BIT5         = 0x71,            
    EVENT_IPALGEBRIC_RESULT_BIT6         = 0x72,            
    EVENT_IPALGEBRIC_RESULT_BIT7         = 0x73,            
    EVENT_IPALGEBRIC_RESULT_BIT8         = 0x74,            
    EVENT_IPALGEBRIC_RESULT_BIT9         = 0x75,            
    EVENT_IPALGEBRIC_RESULT_BIT10        = 0x76,            
    EVENT_IPALGEBRIC_RESULT_BIT11        = 0x77,            
    EVENT_IPALGEBRIC_RESULT_BIT12        = 0x78,            
    EVENT_IPALGEBRIC_RESULT_BIT13        = 0x79,            
    EVENT_IPALGEBRIC_RESULT_BIT14        = 0x7A,            
    EVENT_IPALGEBRIC_RESULT_BIT15        = 0x7B,            
    EVENT_IPALGEBRIC_RESULT_BIT16        = 0x7C,            
    EVENT_IPALGEBRIC_RESULT_BIT17        = 0x7D,            
    EVENT_IPALGEBRIC_RESULT_BIT18        = 0x7E,            
    EVENT_IPALGEBRIC_RESULT_BIT19        = 0x7F,            

    EVENT_IPALGEBRIC_RESULT_BIT20        = 0x80,            
    EVENT_IPALGEBRIC_RESULT_BIT21        = 0x81,            
    EVENT_IPALGEBRIC_RESULT_BIT22        = 0x82,            
    EVENT_IPALGEBRIC_RESULT_BIT23        = 0x83,            
    EVENT_IPALGEBRIC_RESULT_BIT24        = 0x84,            
    EVENT_IPALGEBRIC_RESULT_BIT25        = 0x85,            
    EVENT_IPALGEBRIC_RESULT_BIT26        = 0x86,            
    EVENT_IPALGEBRIC_RESULT_BIT27        = 0x87,            
    EVENT_IPALGEBRIC_RESULT_BIT28        = 0x88,            
    EVENT_IPALGEBRIC_RESULT_BIT29        = 0x89,            
    EVENT_IPALGEBRIC_RESULT_BIT30        = 0x8A,            
    EVENT_IPALGEBRIC_RESULT_BIT31        = 0x8B,            
    EVENT_IPCOMPARE_RESULT_BIT0          = 0x8C,        
    EVENT_IPCOMPARE_RESULT_BIT1          = 0x8D,        
    EVENT_IPCOMPARE_RESULT_BIT2          = 0x8E,        
    EVENT_IPCOMPARE_RESULT_BIT3          = 0x8F,        
    EVENT_IPCOMPARE_RESULT_BIT4          = 0x90,        
    EVENT_IPON_INTERPOLATION             = 0x91,        
    EVENT_IPON_LINEAR_INTERPOLATION      = 0x92,            
    EVENT_IPON_CIRCULAR_INTERPOLATION    = 0x93,            
    EVENT_IPON_PATTERN_INTERPOLATION     = 0x94,            
    EVENT_IPNONE_95                      = 0x95,    
    EVENT_IPL_C_INP_Q_EMPTY              = 0x96,        
    EVENT_IPL_C_INP_Q_LESS_4             = 0x97,        
    EVENT_IPP_INP_Q_EMPTY                = 0x98,        
    EVENT_IPP_INP_Q_LESS_4               = 0x99,        
    EVENT_IPINTERPOLATION_PAUSED         = 0x9A,            
    EVENT_IPP_INP_END_BY_END_PATTERN     = 0x9B,            
    EVENT_IPARITHMETIC_DATA_SEL          = 0xEE,        

    EVENT_IPEXECUTION_ALWAYS             = 0xFF    
} IPEVENT;

typedef enum _QIEVENT
{
    EVENT_QINOOP                        = 0x00,                // No operation.
    EVENT_QIDRVEND                      = 0x01,                // Drive end event(inposition function excluded).
    EVENT_QIDECEL                       = 0X02,                // Deceleration state.
    EVENT_QICONST                       = 0x03,                // Constant speed state.
    EVENT_QIACCEL                       = 0X04,                // Acceleration state.
    EVENT_QICNT1L                       = 0x05,                // Counter1 < Comparater1 state.
    EVENT_QICNT1E                       = 0X06,                // Counter1 = Comparater1 state.
    EVENT_QICNT1G                       = 0x07,                // Counter1 > Comparater1 state.
    EVENT_QICNT1LE                      = 0x08,                // Counter1 ≤ Comparater1 state.
    EVENT_QICNT1GE                      = 0x09,                // Counter1 ≥ Comparater1 state.
    EVENT_QICNT1EUP                     = 0x0A,                // Counter1 = Comparater1 event during counting up.
    EVENT_QICNT1EDN                     = 0x0B,                // Counter1 = Comparater1 event during counting down.
    EVENT_QICNT1BND                     = 0x0C,                // Counter1 is same with boundary value.

    EVENT_QICNT2L                       = 0x0D,                // Counter2 < Comparater2 state.
    EVENT_QICNT2E                       = 0x0E,                // Counter2 = Comparater2 state.
    EVENT_QICNT2G                       = 0x0F,                // Counter2 > Comparater2 state.
    EVENT_QICNT2LE                      = 0x10,                // Counter2 ≤ Comparater2 state.
    EVENT_QICNT2GE                      = 0x11,                // Counter2 ≥ Comparater2 state.
    EVENT_QICNT2EUP                     = 0x12,                // Counter2 = Comparater2 event during counting up.
    EVENT_QICNT2EDN                     = 0x13,                // Counter2 = Comparater2 event during counting down.
    EVENT_QICNT2BND                     = 0x14,                // Counter2 is same with boundary value.


    EVENT_QICNT3L                       = 0x15,                // Counter3 < Comparater3 state.
    EVENT_QICNT3E                       = 0x16,                // Counter3 = Comparater3 state.
    EVENT_QICNT3G                       = 0x17,                // Counter3 > Comparater3 state.
    EVENT_QICNT3LE                      = 0x18,                // Counter3 ≤ Comparater3 state.
    EVENT_QICNT3GE                      = 0x19,                // Counter3 ≥ Comparater3 state.
    EVENT_QICNT3EUP                     = 0x1A,                // Counter3 = Comparater3 event during counting up.
    EVENT_QICNT3EDN                     = 0x1B,                // Counter3 = Comparater3 event during counting down.
    EVENT_QICNT3BND                     = 0x1C,                // Counter3 is same with boundary value.
    EVENT_QICNT4L                       = 0x1D,                // Counter4 < Comparater4 state.
    EVENT_QICNT4E                       = 0x1E,                // Counter4 = Comparater4 state.
    EVENT_QICNT4G                       = 0x1F,                // Counter4 > Comparater4 state.
    EVENT_QICNT4LE                      = 0x20,                // Counter4 ≤ Comparater4 state.
    EVENT_QICNT4GE                      = 0x21,                // Counter4 ≥ Comparater4 state.
    EVENT_QICNT4EUP                     = 0x22,                // Counter4 = Comparater4 event during counting up.
    EVENT_QICNT4EDN                     = 0x23,                // Counter4 = Comparater4 event during counting down.
    EVENT_QICNT4BND                     = 0x24,                // Counter4 is same with boundary value.
    EVENT_QICNT5L                       = 0x25,                // Counter5 < Comparater5 state.
    EVENT_QICNT5E                       = 0x26,                // Counter5 = Comparater5 state.
    EVENT_QICNT5G                       = 0x27,                // Counter5 > Comparater5 state.
    EVENT_QICNT5LE                      = 0x28,                // Counter5 ≤ Comparater5 state.
    EVENT_QICNT5GE                      = 0x29,                // Counter5 ≥ Comparater5 state.
    EVENT_QICNT5EUP                     = 0x2A,                // Counter5 = Comparater5 event during counting up.
    EVENT_QICNT5EDN                     = 0x2B,                // Counter5 = Comparater5 event during counting down.
    EVENT_QICNT5BND                     = 0x2C,                // Counter5 is same with boundary value.
    EVENT_QIDEVL                        = 0x2D,                // DEVIATION value < Comparater4 state.
    EVENT_QIDEVE                        = 0x2E,                // DEVIATION value = Comparater4 state.
    EVENT_QIDEVG                        = 0x2F,                // DEVIATION value > Comparater4 state.
    EVENT_QIDEVLE                       = 0x30,                // DEVIATION value ≤ Comparater4 state.
    EVENT_QIDEVGE                       = 0x31,                // DEVIATION value ≥ Comparater4 state.
    EVENT_QIPELM                        = 0x32,                // PELM input signal is activated state.
    EVENT_QINELM                        = 0x33,                // NELM input signal is activated state.
    EVENT_QIPSLM                        = 0x34,                // PSLM input signal is activated state.
    EVENT_QINSLM                        = 0x35,                // NSLM input signal is activated state.
    EVENT_QIALARM                       = 0x36,                // ALAMR input signal is activated state.
    EVENT_QIINPOS                       = 0x37,                // INPOSITION input signal ia activated state.
    EVENT_QIESTOP                       = 0x38,                // ESTOP input signal is activated state.
    EVENT_QIORG                         = 0x39,                // ORG input signal is activated state.
    EVENT_QIZ_PHASE                     = 0x3A,                // Z_PHASE input signal is activated state.
    EVENT_QIECUP                        = 0x3B,                // ECUP input signal is high level state.
    EVENT_QIECDN                        = 0x3C,                // ECDN input signal is high level state.
    EVENT_QIEXPP                        = 0x3D,                // EXPP input signal is high level state.
    EVENT_QIEXMP                        = 0x3E,                // EXMP input signal is high level state.
    EVENT_QISQSTR1                      = 0x3F,                // SYNC Start1 input signal is activated state(activated).
    EVENT_QISQSTR2                      = 0x40,                // SYNC Start2 input signal is activated state(activated).
    EVENT_QISQSTP1                      = 0x41,                // SYNC STOP1 input signal is activated state(activated).
    EVENT_QISQSTP2                      = 0x42,                // SYNC STOP2 input signal is activated state(activated).
    EVENT_QIALARMS                      = 0x43,                // At least one alarm signal of each axis is activated state.
    EVENT_QIUIO0                        = 0x44,                // UIO0 data is high state.
    EVENT_QIUIO1                        = 0x45,                // UIO1 data is high state.
    EVENT_QIUIO2                        = 0x46,                // UIO2 data is high state.
    EVENT_QIUIO3                        = 0x47,                // UIO3 data is high state.
    EVENT_QIUIO4                        = 0x48,                // UIO4 data is high state.
    EVENT_QIUIO5                        = 0x49,                // UIO5 data is high state.
    EVENT_QIUIO6                        = 0x4A,                // UIO6 data is high state.
    EVENT_QIUIO7                        = 0x4B,                // UIO7 data is high state.
    EVENT_QIUIO8                        = 0x4C,                // UIO8 data is high state.
    EVENT_QIUIO9                        = 0x4D,                // UIO9 data is high state.
    EVENT_QIUIO10                       = 0x4E,                // UIO10 data is high state.
    EVENT_QIUIO11                       = 0x4F,                // UIO11 data is high state.
    EVENT_QIERC                         = 0x50,                // ERC output is activated.
    EVENT_QITRG                         = 0x51,                // TRIGGER signal is activated.
    EVENT_QIPREQI0                      = 0x52,                // Previous queue data index 0 bit is high state.
    EVENT_QIPREQI1                      = 0x53,                // Previous queue data index 1 bit is high state.
    EVENT_QIPREQI2                      = 0x54,                // Previous queue data index 2 bit is high state.
    EVENT_QIPREQZ                       = 0x55,                // Previous queue is empty state.
    EVENT_QIPREQF                       = 0x56,                // Previous queue is full state.
    EVENT_QIMPGE1                       = 0x57,                // MPG first stage is overflowed state.
    EVENT_QIMPGE2                       = 0x58,                // MPG second stage is overflowed state.
    EVENT_QIMPGE3                       = 0x59,                // MPG third stage is overflowed state.
    EVENT_QIMPGERR                      = 0x5A,                // MPG all state is overflowed state.
    EVENT_QITRGCNT0                     = 0x5B,                // TRIGGER queue index bit 0 is high state.
    EVENT_QITRGCNT1                     = 0x5C,                // TRIGGER queue index bit 1 is high state.
    EVENT_QITRGCNT2                     = 0x5D,                // TRIGGER queue index bit 2 is high state.
    EVENT_QITRGCNT3                     = 0x5E,                // TRIGGER queue index bit 3 is high state.
    EVENT_QITRGQEPT                     = 0x5F,                // TRIGGER queue is empty state.
    EVENT_QITRGQFULL                    = 0x60,                // TRIGGER queue is full state.
    EVENT_QIDPAUSE                      = 0x61,                // Drive paused state.
    EVENT_QIESTOPEXE                    = 0x62,                // Emergency stop occurred
    EVENT_QISSTOPEXE                    = 0x63,                // Slowdown stop occurred
    EVENT_QIPLMTSTOP                    = 0x64,                // Limit stop event occurred during positive driving.
    EVENT_QINLMTSTOP                    = 0x65,                // Limit stop event occurred during negative driving.
    EVENT_QIOPLMTSTOP                   = 0x66,                // Optional limit stop event occurred during positive driving.
    EVENT_QIONLMTSTOP                   = 0x67,                // Optional limit stop event occurred during negative driving.
    EVENT_QIPSWESTOP                    = 0x68,                // Software emergency limit stop event occurred.(CW)
    EVENT_QINSWESTOP                    = 0x69,                // Software emergency limit stop event occurred.(CCW)
    EVENT_QIPSWSSTOP                    = 0x6A,                // Software slowdown limit stop event occurred.(CW)
    EVENT_QINSWSSTOP                    = 0x6B,                // Software slowdown limit stop event occurred.(CCW)
    EVENT_QIALMSTOP                     = 0x6C,                // Emergency stop event occurred by alarm signal function.
    EVENT_QIESTOPSTOP                   = 0x6D,                // Emergency stop event occurred by estop signal function.
    EVENT_QIESTOPCMD                    = 0x6E,                // Emergency stop event occurred by command.
    EVENT_QISSTOPCMD                    = 0x6F,                // Slowdown stop event occurred by command.
    EVENT_QIALLSTCMD                    = 0x70,                // Emergency stop event occurred by all stop command.
    EVENT_QISYSTOP1                     = 0x71,                // SYNC stop1 event occurred.
    EVENT_QISYSTOP2                     = 0x72,                // SYNC stop2 event occurred.
    EVENT_QIENCODERR                    = 0x73,                // Encoder input error event occurred.
    EVENT_QIMPGOVERFLOW                 = 0x74,                // MPG input error event occurred.
    EVENT_QIORGOK                       = 0x75,                // Original drive is executed successfully.
    EVENT_QISSCHOK                      = 0x76,                // Signal search drive is executed successfully.
    EVENT_QIUIO0LOW                     = 0x77,                // UIO0 data is low state.
    EVENT_QIUIO1LOW                     = 0x78,                // UIO1 data is low state.
    EVENT_QIUIO2LOW                     = 0x79,                // UIO2 data is low state.
    EVENT_QIUIO3LOW                     = 0x7A,                // UIO3 data is low state.
    EVENT_QIUIO4LOW                     = 0x7B,                // UIO4 data is low state.
    EVENT_QIUIO5LOW                     = 0x7C,                // UIO5 data is low state.
    EVENT_QIUIO6LOW                     = 0x7D,                // UIO6 data is low state.
    EVENT_QIUIO7LOW                     = 0x7E,                // UIO7 data is low state.
    EVENT_QIUIO8LOW                     = 0x7F,                // UIO8 data is low state.
    EVENT_QIUIO9LOW                     = 0x80,                // UIO9 data is low state.
    EVENT_QIUIO10LOW                    = 0x81,                // UIO10 data is low state.
    EVENT_QIUIO11LOW                    = 0x82,                // UIO11 data is low state.
    EVENT_QIUIO0RISING                  = 0x83,                // UIO0 rising edge event occurred.
    EVENT_QIUIO1RISING                  = 0x84,                // UIO1 rising edge event occurred.
    EVENT_QIUIO2RISING                  = 0x85,                // UIO2 rising edge event occurred.
    EVENT_QIUIO3RISING                  = 0x86,                // UIO3 rising edge event occurred.
    EVENT_QIUIO4RISING                  = 0x87,                // UIO4 rising edge event occurred.
    EVENT_QIUIO5RISING                  = 0x88,                // UIO5 rising edge event occurred.
    EVENT_QIUIO6RISING                  = 0x89,                // UIO6 rising edge event occurred.
    EVENT_QIUIO7RISING                  = 0x8A,                // UIO7 rising edge event occurred.
    EVENT_QIUIO8RISING                  = 0x8B,                // UIO8 rising edge event occurred.
    EVENT_QIUIO9RISING                  = 0x8C,                // UIO9 rising edge event occurred.
    EVENT_QIUIO10RISING                 = 0x8D,                // UIO10 rising edge event occurred.
    EVENT_QIUIO11RISING                 = 0x8E,                // UIO11 rising edge event occurred.
    EVENT_QIUIO0FALLING                 = 0x8F,                // UIO0 falling edge event occurred.
    EVENT_QIUIO1FALLING                 = 0x90,                // UIO1 falling edge event occurred.
    EVENT_QIUIO2FALLING                 = 0x91,                // UIO2 falling edge event occurred.
    EVENT_QIUIO3FALLING                 = 0x92,                // UIO3 falling edge event occurred.
    EVENT_QIUIO4FALLING                 = 0x93,                // UIO4 falling edge event occurred.
    EVENT_QIUIO5FALLING                 = 0x94,                // UIO5 falling edge event occurred.
    EVENT_QIUIO6FALLING                 = 0x95,                // UIO6 falling edge event occurred.
    EVENT_QIUIO7FALLING                 = 0x96,                // UIO7 falling edge event occurred.
    EVENT_QIUIO8FALLING                 = 0x97,                // UIO8 falling edge event occurred.
    EVENT_QIUIO9FALLING                 = 0x98,                // UIO9 falling edge event occurred.
    EVENT_QIUIO10FALLING                = 0x99,                // UIO10 falling edge event occurred.
    EVENT_QIUIO11FALLING                = 0x9A,                // UIO11 falling edge event occurred.
    EVENT_QIDRVSTR                      = 0x9B,                // Drive started.
    EVENT_QIDNSTR                       = 0x9C,                // Speed down event occurred.
    EVENT_QICOSTR                       = 0x9D,                // Constant speed event occurred.
    EVENT_QIUPSTR                       = 0x9E,                // Speed up event occurred.
    EVENT_QICONTISTR                    = 0x9F,                // Continuous drive started.
    EVENT_QIPRESETSTR                   = 0xA0,                // Preset drive started.
    EVENT_QIMPGSTR                      = 0xA1,                // MPG drive started.
    EVENT_QIORGSTR                      = 0Xa2,                // Original drive started.
    EVENT_QISSCHSTR                     = 0xA3,                // Signal search drive started.
    EVENT_QIPATHSTR                     = 0xA4,                // Interpolation drive started.
    EVENT_QISLAVESTR                    = 0xA5,                // Slave drive started.
    EVENT_QICCWSTR                      = 0xA6,                // CCW direction drive started.
    EVENT_QIINPWAIT                     = 0xA7,                // Inposition wait event occurred.
    EVENT_QILINSTR                      = 0xA8,                // Linear drive stated.
    EVENT_QICIRSTR                      = 0xA9,                // Circular drive started.
    EVENT_QIDRVENDII                    = 0xAA,                // Drive stopped.(Inposition state included)
    EVENT_QIDNEND                       = 0xAB,                // Speed down end event occurred.
    EVENT_QICOEND                       = 0xAC,                // Constant speed end event occurred.
    EVENT_QIUPEND                       = 0xAD,                // Speed up end event occurred.
    EVENT_QICONTIEND                    = 0xAE,                // Continuous drive ended.
    EVENT_QIPRESETEND                   = 0xAF,                // Preset drive ended.
    EVENT_QIMPGEND                      = 0xB0,                // MPG drive ended.
    EVENT_QIORGEND                      = 0xB1,                // Original drive ended.
    EVENT_QISSCHEND                     = 0XB2,                // Signal search drive ended.
    EVENT_QIPATHEND                     = 0xB3,                // Interpolation drive ended.
    EVENT_QISLAVEEND                    = 0xB4,                // Slave drive ended.
    EVENT_QICCWEND                      = 0xB5,                // CCW direction drive ended.
    EVENT_QIINPEND                      = 0xB6,                // Escape from Inposition waiting.
    EVENT_QILINEND                      = 0xB7,                // Linear drive ended.
    EVENT_QICIREND                      = 0xB8,                // Circular drive ended.
    EVENT_QIBUSY                        = 0xB9,                // During driving state.
    EVENT_QINBUSY                       = 0xBA,                // During not driving state.
    EVENT_QITMR1EX                      = 0xBB,                // Timer1 expired event.
    EVENT_QITMR2EX                      = 0xBC,                // Timer2 expired event.
    EVENT_QIDRVENDIII                   = 0xBD,                // Drive(that interrupt enable bit is set to high) end event 
    EVENT_QIERROR                       = 0xBE,                // Error stop occurred.
//    EVENT_QINOP                       = 0xBF,                // NOP.
    EVENT_QIALWAYS                      = 0xFF                 // Always Generate.

} QIEVENT;

//========================================================================================================================;
#endif    //__AXT_AXHD_H__
