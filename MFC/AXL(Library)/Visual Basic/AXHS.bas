Attribute VB_Name = "AXHS"
'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXHS.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Resource Define Header File
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Source Change Indices
'** ---------------------
'**
'** (None)
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Website
'** ---------------------
'**
'** http://www.ajinextek.com
'**
'*****************************************************************************
'*****************************************************************************
'*

' Define Baseboard
Public Const AXT_UNKNOWN = &H0                              ' Unknown Baseboard                                                  
Public Const AXT_BIHR = &H1                                 ' ISA bus, Half size                                                 
Public Const AXT_BIFR = &H2                                 ' ISA bus, Full size                                                 
Public Const AXT_BPHR = &H3                                 ' PCI bus, Half size                                                 
Public Const AXT_BPFR = &H4                                 ' PCI bus, Full size                                                 
Public Const AXT_BV3R = &H5                                 ' VME bus, 3U size                                                   
Public Const AXT_BV6R = &H6                                 ' VME bus, 6U size                                                   
Public Const AXT_BC3R = &H7                                 ' cPCI bus, 3U size                                                  
Public Const AXT_BC6R = &H8                                 ' cPCI bus, 6U size                                                  
Public Const AXT_BEHR = &H9                                 ' PCIe bus, Half size
Public Const AXT_BEFR = &HA                                 ' PCIe bus, Full size
Public Const AXT_BEHD = &HB                                ' PCIe bus, Half size, DB-32T
Public Const AXT_FMNSH4D = &H52                             ' ISA bus, Full size, DB-32T, SIO-2V03 * 2                           
Public Const AXT_PCI_DI64R = &H43                           ' PCI bus, Digital IN 64 point
Public Const AXT_PCIE_DI64R = &H44                         ' PCIe bus, Digital IN 64 point
Public Const AXT_PCI_DO64R = &H53                           ' PCI bus, Digital OUT 64 point
Public Const AXT_PCIE_DO64R = &H54                         ' PCIe bus, Digital OUT 64 point
Public Const AXT_PCI_DB64R = &H63                           ' PCI bus, Digital IN 32 point, OUT 32 point
Public Const AXT_PCIE_DB64R = &H64                         ' PCIe bus, Digital IN 32 point, OUT 32 point                       
Public Const AXT_PCIN204 = &H82                             ' PCI bus, Half size On-Board 2 Axis controller.
Public Const AXT_BPHD = &H83                                ' PCI bus, Half size, DB-32T                                         
Public Const AXT_PCIN404 = &H84                             ' PCI bus, Half size On-Board 4 Axis controller.                     
Public Const AXT_PCIN804 = &H85                             ' PCI bus, Half size On-Board 8 Axis controller.                     
Public Const AXT_PCIEN804 = &H86                            ' PCIe bus, Half size On-Board 8 Axis controller.
Public Const AXT_PCIEN404 = &H87S                           ' PCIe bus, Half size On-Board 4 Axis controller.
Public Const AXT_PCI_AIO1602HR = &H93                       ' PCI bus, Half size, AI-16ch, AO-2ch AI16HR                         
Public Const AXT_PCI_R1604 = &HC1                           ' PCI bus[PCI9030], Half size, RTEX based 16 axis controller         
Public Const AXT_PCI_R3204 = &HC2                           ' PCI bus[PCI9030], Half size, RTEX based 32 axis controller         
Public Const AXT_PCI_R32IO = &HC3                           ' PCI bus[PCI9030], Half size, RTEX based IO only.
Public Const AXT_PCI_REV2 = &HC4                            ' Reserved.                                                          
Public Const AXT_PCI_R1604MLII = &HC5                       ' PCI bus[PCI9030], Half size, Mechatrolink-II 16/32 axis controller.
Public Const AXT_PCI_R0804MLII = &HC6                       ' PCI bus[PCI9030], Half size, Mechatrolink-II 08 axis controller.
Public Const AXT_PCI_Rxx00MLIII = &HC7                     ' Master PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 Slave module support
Public Const AXT_PCIE_Rxx00MLIII = &HC8                    ' Master PCI Express Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
Public Const AXT_PCP2_Rxx00MLIII = &HC9                    ' Master PCI/104-Plus Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
Public Const AXT_PCI_R1604SIIIH = &HCA                      ' PCI bus[PCI9030], Half size, SSCNET III / H 16/32 axis controller.  
Public Const AXT_PCI_R32IOEV = &HCB                        ' PCI bus[PCI9030], Half size, RTEX based IO only. Economic version.
Public Const AXT_PCIE_R0804RTEX = &HCC                     ' PCIe bus, Half size, Half size, RTEX based 08 axis controller.
Public Const AXT_PCIE_R1604RTEX = &HCD                     ' PCIe bus, Half size, Half size, RTEX based 16 axis controller.
Public Const AXT_PCIE_R2404RTEX = &HCE                     ' PCIe bus, Half size, Half size, RTEX based 24 axis controller.
Public Const AXT_PCIE_R3204RTEX = &HCF                     ' PCIe bus, Half size, Half size, RTEX based 32 axis controller.
Public Const AXT_PCIE_Rxx04SIIIH = &HD0                    ' PCIe bus, Half size, SSCNET III / H 16(or 32)-axis(CAMC-QI based) controller.
Public Const AXT_PCIE_Rxx00SIIIH = &HD1                    ' PCIe bus, Half size, SSCNET III / H Max. 32-axis(DSP Based) controller.
Public Const AXT_ETHERCAT_RTOSV5 = &HD2                    ' EtherCAT, RTOS(On Time), Version 5.29
Public Const AXT_PCI_Nx04_A = &HD3                         ' PCI bus, Half size On-Board x Axis controller For Rtos.
Public Const AXT_PCI_R3200MLIII_IO = &HD4                  ' PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 IO only	controller
Public Const AXT_PCIE_R3205MLIII = &HD5                    ' PCIe bus, Half size, Mechatrolink III / H Max. 32-axis(DSP Based) controller.

' Define Module
Public Const AXT_SMC_2V01 = &H1                             ' CAMC-5M, 2 Axis
Public Const AXT_SMC_2V02 = &H2                             ' CAMC-FS, 2 Axis
Public Const AXT_SMC_1V01 = &H3                             ' CAMC-5M, 1 Axis
Public Const AXT_SMC_1V02 = &H4                             ' CAMC-FS, 1 Axis
Public Const AXT_SMC_2V03 = &H5                             ' CAMC-IP, 2 Axis
Public Const AXT_SMC_4V04 = &H6                             ' CAMC-QI, 4 Axis
Public Const AXT_SMC_R1V04A4 = &H7                          ' CAMC-QI, 1 Axis, For RTEX A4 slave only
Public Const AXT_SMC_1V03 = &H8                             ' CAMC-IP, 1 Axis
Public Const AXT_SMC_R1V04 = &H9                            ' CAMC-QI, 1 Axis, For RTEX SLAVE only
Public Const AXT_SMC_R1V04MLIISV = &HA                      ' CAMC-QI, 1 Axis, For Sigma-X series.
Public Const AXT_SMC_R1V04MLIIPM = &HB                      ' 2 Axis, For Pulse output series(JEPMC-PL2910).
Public Const AXT_SMC_2V04 = &HC                             ' CAMC-QI, 2 Axis
Public Const AXT_SMC_R1V04A5 = &HD                          ' CAMC-QI, 1 Axis, For RTEX A5N slave only
Public Const AXT_SMC_R1V04MLIICL = &HE                      ' CAMC-QI, 1 Axis, For MLII Convex Linear Driver.
Public Const AXT_SMC_R1V04MLIICR = &HF                      ' CAMC-QI, 1 Axis, For MLII Convex Rotary Driver.
Public Const AXT_SMC_R1V04PM2Q = &H10                       ' CAMC-QI, 2 Axis, For RTEX SLAVE only(Pulse Output Module)
Public Const AXT_SMC_R1V04PM2QE = &H11                      ' CAMC-QI, 4 Axis, For RTEX SLAVE only(Pulse Output Module)
Public Const AXT_SMC_R1V04MLIIORI = &H12                    ' CAMC-QI, 1 Axis, For MLII Oriental Step Driver only
Public Const AXT_SMC_R1V04SIIIHMIV = &H14                   ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
Public Const AXT_SMC_R1V04SIIIHMIV_R = &H15                 ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
Public Const AXT_SMC_R1V04MLIIISV = &H20                    ' DSP, 1 Axis, For ML-3 SigmaV/YASKAWA only 
Public Const AXT_SMC_R1V04MLIIIPM = &H21                    ' DSP, 1 Axis, For ML-3 SLAVE/AJINEXTEK only(Pulse Output Module)
Public Const AXT_SMC_R1V04MLIIISV_MD = &H22                 ' DSP, 1 Axis, For ML-3 SigmaV-MD/YASKAWA only (Multi-Axis Control amp)
Public Const AXT_SMC_R1V04MLIIIS7S = &H23                   ' DSP, 1 Axis, For ML-3 Sigma7S/YASKAWA only
Public Const AXT_SMC_R1V04MLIIIS7W = &H24                   ' DSP, 2 Axis, For ML-3 Sigma7W/YASKAWA only(Dual-Axis control amp)
Public Const AXT_SIO_RDI32MLIII = &H70                      ' DI slave module, MechatroLink III AXT, IN 32-Channel NPN
Public Const AXT_SIO_RDO32MLIII = &H71                      ' DO slave module, MechatroLink III AXT, OUT 32-Channel  NPN
Public Const AXT_SIO_RDB32MLIII = &H72                      ' DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  NPN
Public Const AXT_SIO_RDI32MSMLIII = &H73                    ' DI slave module, MechatroLink III M-SYSTEM, IN 32-Channel
Public Const AXT_SIO_RDO32AMSMLIII = &H74                   ' DO slave module, MechatroLink III M-SYSTEM, OUT 32-Channel
Public Const AXT_SIO_RDI32PMLIII = &H75                     ' DI slave module, MechatroLink III AXT, IN 32-Channel PNP
Public Const AXT_SIO_RDO32PMLIII = &H76                     ' DO slave module, MechatroLink III AXT, OUT 32-Channel  PNP
Public Const AXT_SIO_RDB32PMLIII = &H77                     ' DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  PNP
Public Const AXT_SIO_RDB32PMLIII = &H78                     ' DI slave module, MechatroLink III M-SYSTEM, IN 16-Channel
Public Const AXT_SIO_UNDEFINEMLIII = &H79                   ' IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
Public Const AXT_SIO_RDI32MLIIISFA = &H7A                   ' DI slave module, MechatroLink III AXT(SFA), IN 32-Channel NPN
Public Const AXT_SIO_RDO32MLIIISFA = &H7B                   ' DO slave module, MechatroLink III AXT(SFA), OUT 32-Channel  NPN
Public Const AXT_SIO_RDB32MLIIISFA = &H7C                   ' DB slave module, MechatroLink III AXT(SFA), IN 16-Channel, OUT 16-Channel  NPN
Public Const AXT_SIO_RDB128MLIIIAI = &H7D                   ' Intelligent I/O (Product by IAI), For MLII only
Public Const AXT_SIO_RSIMPLEIOMLII = &H7E                   ' Digital IN/Out xx??, Simple I/O sereies, MLII ????.
Public Const AXT_SIO_RDO16AMLIII = &H7F                     ' DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, NPN
Public Const AXT_SIO_RDI16MLII = &H80                       ' DISCRETE INPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RDO16AMLII = &H81                      ' NPN TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RDO16BMLII = &H82                      ' PNP TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only	
Public Const AXT_SIO_RDB96MLII = &H83                       ' Digital IN/OUT(Selectable), MAX 96 points, For MLII only
Public Const AXT_SIO_RDO32RTEX = &H84                       ' Digital OUT  32 point
Public Const AXT_SIO_RDI32RTEX = &H85                       ' Digital IN  32 point
Public Const AXT_SIO_RDB32RTEX = &H86                       ' Digital IN/OUT  32 point
Public Const AXT_SIO_RDO16BMLIII = &H8A                     ' DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, PNP
Public Const AXT_SIO_RDB32ML2NT1 = &H8B                     ' DB slave module, MechatroLink2 AJINEXTEK NT1 Series
Public Const AXT_SIO_RDB128YSMLIII = &H8C                   ' IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
Public Const AXT_SIO_DI32_P = &H92                          ' Digital IN  32 point, PNP type(source type)
Public Const AXT_SIO_DO32T_P = &H93                         ' Digital OUT 32 point, Power TR, PNT type(source type)
Public Const AXT_SIO_RDB128MLII = &H94                      ' Digital IN 64 / OUT 64, MLII (JEPMC-IO2310)
Public Const AXT_SIO_RDI32 = &H95                           ' Digital IN  32 point, For RTEX only
Public Const AXT_SIO_RDO32 = &H96                           ' Digital OUT 32 point, For RTEX only
Public Const AXT_SIO_DI32 = &H97                            ' Digital IN  32 point
Public Const AXT_SIO_DO32P = &H98                           ' Digital OUT 32 point
Public Const AXT_SIO_DB32P = &H99                           ' Digital IN 16 point / OUT 16 point
Public Const AXT_SIO_RDB32T = &H9A                          ' Digital IN 16point / OUT 16point, For RTEX only
Public Const AXT_SIO_DO32T = &H9E                           ' Digital OUT 16 point, Power TR output
Public Const AXT_SIO_DB32T = &H9F                           ' Digital IN 16 point / OUT 16 point, Power TR output
Public Const AXT_SIO_RAI16RB = &HA0                         ' A0h(160) : AI 16Ch, 16 bit, For RTEX only
Public Const AXT_SIO_AI4RB = &HA1                           ' A1h(161) : AI 4Ch, 12 bit
Public Const AXT_SIO_AO4RB = &HA2                           ' A2h(162) : AO 4Ch, 12 bit
Public Const AXT_SIO_AI16H = &HA3                           ' A3h(163) : AI 4Ch, 16 bit
Public Const AXT_SIO_AO8H = &HA4                            ' A4h(164) : AO 4Ch, 16 bit
Public Const AXT_SIO_AI16HB = &HA5                          ' A5h(165) : AI 16Ch, 16 bit (SIO-AI16HR(input module))
Public Const AXT_SIO_AO2HB = &HA6                           ' A6h(166) : AO 2Ch, 16 bit  (SIO-AI16HR(output module))
Public Const AXT_SIO_RAI8RB = &HA7                          ' A1h(167) : AI 8Ch, 16 bit, For RTEX only
Public Const AXT_SIO_RAO4RB = &HA8                          ' A2h(168) : AO 4Ch, 16 bit, For RTEX only
Public Const AXT_SIO_RAI4MLII = &HA9                        ' A9h(169) : AI 4Ch, 16 bit, For MLII only
Public Const AXT_SIO_RAI16RB = &HA0                         ' A0h(160) : AI 16Ch, 16 bit, For RTEX only
Public Const AXT_SIO_RAO2MLII = &HAA                        ' AAh(170) : AO 2Ch, 16 bit, For MLII only
Public Const AXT_SIO_RAVCI4MLII = &HAB                      ' DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RAVO2MLII = &HAC                       ' DC VOLTAGE OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RACO2MLII = &HAD                       ' DC CURRENT OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RATI4MLII = &HAE                       ' THERMOCOUPLE INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RARTDI4MLII = &HAF                     ' RTD INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RCNT2MLII = &HB0                       ' Counter Module Reversible counter, 2 channels (Product by YASKWA)
Public Const AXT_SIO_CN2CH = &HB1                           ' Counter Module, 2 channels, Remapped ID, Actual ID is (0xA8)
Public Const AXT_SIO_RCNT2RTEX = &HB2                       ' Counter slave module, Reversible counter, 2 channels, For RTEX Only
Public Const AXT_SIO_RCNT2MLIII = &HB3                      ' Counter slave moudle, MechatroLink III AXT, 2 ch, Trigger per channel
Public Const AXT_SIO_RHPC4MLIII = &HB4                      ' Counter slave moudle, MechatroLink III AXT, 4 ch
Public Const AXT_SIO_RAI16RTEX = &HC0                       ' ANALOG VOLTAGE INPUT(+- 10V) 16 Channel RTEX
Public Const AXT_SIO_RAO08RTEX = &HC1                       ' ANALOG VOLTAGE OUTPUT(+- 10V) 08 Channel RTEX
Public Const AXT_SIO_RAI8MLIII = &HC2                       ' AI slave module, MechatroLink III AXT, Analog IN 8ch, 16 bit
Public Const AXT_SIO_RAI16MLIII = &HC3                      ' AI slave module, MechatroLink III AXT, Analog IN 16ch, 16 bit
Public Const AXT_SIO_RAO4MLIII = &HC4                       ' A0 slave module, MechatroLink III AXT, Analog OUT 4ch, 16 bit
Public Const AXT_SIO_RAO8MLIII = &HC5                       ' A0 slave module, MechatroLink III AXT, Analog OUT 8ch, 16 bit
Public Const AXT_SIO_RAVO4MLII = &HC6                       ' DC VOLTAGE OUTPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RAV04MLIII = &HC7                      ' AO Slave module, MechatroLink III M-SYSTEM Voltage output module
Public Const AXT_SIO_RAVI4MLIII = &HC8                      ' AI Slave module, MechatroLink III M-SYSTEM Voltage/Current input module
Public Const AXT_SIO_RAI16MLIIISFA = &HC9                   ' AI slave module, MechatroLink III AXT(SFA), Analog IN 16ch, 16 bit
Public Const AXT_SIO_RDB32MSMLIII = &HCA                    ' DIO slave module, MechatroLink III M-SYSTEM, IN 16-Channel, OUT 16-Channel
Public Const AXT_COM_234R = &HD3                            ' COM-234R
Public Const AXT_COM_484R = &HD4                            ' COM-484R
Public Const AXT_SIO_RPI2 = &HD5                            ' Pulse counter module(JEPMC-2900)
Public Const AXT_SIO_HPC4 = &HD6                            ' External Encoder module for 4Channel with Trigger function.
Public Const AXT_SIO_AO4HB = &HD7                           ' AO 4Ch, 16 bit
Public Const AXT_SIO_AI8HB = &HD8                           ' AI 8Ch, 16 bit
Public Const AXT_SIO_AI8AO4HB = &HD9                        ' AI 8Ch, AO 4Ch, 16 bit

' Define Function Result
Public Const AXT_RT_SUCCESS = 0                             ' API function executed successfully
Public Const AXT_RT_OPEN_ERROR = 1001                       ' Library is not open
Public Const AXT_RT_OPEN_ALREADY = 1002                     ' Library is already open
Public Const AXT_RT_NOT_OPEN = 1053                         ' Failed to initialize the library
Public Const AXT_RT_NOT_SUPPORT_VERSION = 1054              ' Hardware not supported
Public Const AXT_RT_LOCK_FILE_MISMATCH = 1055               ' Lock file mismatch

Public Const AXT_RT_INVALID_BOARD_NO = 1101                 ' IInvalide board number
Public Const AXT_RT_INVALID_MODULE_POS = 1102               ' Invalid module position
Public Const AXT_RT_INVALID_LEVEL = 1103                    ' Invalid level
Public Const AXT_RT_INVALID_VARIABLE = 1104                 ' Invalid Variable
Public Const AXT_RT_ERROR_VERSION_READ = 1151               ' Failed to read library version
Public Const AXT_RT_NETWORK_ERROR = 1152                    ' Hardware network error
Public Const AXT_RT_NETWORK_LOCK_MISMATCH = 1153

Public Const AXT_RT_1ST_BELOW_MIN_VALUE = 1160              ' First parameter is below the minimum value
Public Const AXT_RT_1ST_ABOVE_MAX_VALUE = 1161              ' First parameter is above the maximum value
Public Const AXT_RT_2ND_BELOW_MIN_VALUE = 1170              ' Second parameter is below the minimum value
Public Const AXT_RT_2ND_ABOVE_MAX_VALUE = 1171              ' Second parameter is above the maximum value
Public Const AXT_RT_3RD_BELOW_MIN_VALUE = 1180              ' Third parameter is below the minimum value
Public Const AXT_RT_3RD_ABOVE_MAX_VALUE = 1181              ' Third parameter is above the maximum value
Public Const AXT_RT_4TH_BELOW_MIN_VALUE = 1190              ' Fourth parameter is below the minimum value
Public Const AXT_RT_4TH_ABOVE_MAX_VALUE = 1191              ' Fourth parameter is above the maximum value
Public Const AXT_RT_5TH_BELOW_MIN_VALUE = 1200              ' Fifth parameter is below the minimum value
Public Const AXT_RT_5TH_ABOVE_MAX_VALUE = 1201              ' Fifth parameter is above the maximum value
Public Const AXT_RT_6TH_BELOW_MIN_VALUE = 1210              ' Sixth parameter is below the minimum value
Public Const AXT_RT_6TH_ABOVE_MAX_VALUE = 1211              ' Sixth parameter is above the maximum value
Public Const AXT_RT_7TH_BELOW_MIN_VALUE = 1220              ' Seventh parameter is below the minimum value
Public Const AXT_RT_7TH_ABOVE_MAX_VALUE = 1221              ' Seventh parameter is above the maximum value
Public Const AXT_RT_8TH_BELOW_MIN_VALUE = 1230              ' Eighth parameter is below the minimum value
Public Const AXT_RT_8TH_ABOVE_MAX_VALUE = 1231              ' Eighth parameter is above the maximum value
Public Const AXT_RT_9TH_BELOW_MIN_VALUE = 1240              ' Ninth parameter is below the minimum value
Public Const AXT_RT_9TH_ABOVE_MAX_VALUE = 1241              ' Ninth parameter is above the maximum value
Public Const AXT_RT_10TH_BELOW_MIN_VALUE = 1250             ' Tenth parameter is above the minimum value
Public Const AXT_RT_10TH_ABOVE_MAX_VALUE = 1251             ' Tenth parameter is above the maximum value

Public Const AXT_RT_AIO_OPEN_ERROR = 2001                   ' Filed to open AIO module
Public Const AXT_RT_AIO_NOT_MODULE = 2051                   ' No AIO module
Public Const AXT_RT_AIO_NOT_EVENT = 2052                    ' Failed to read AIO event
Public Const AXT_RT_AIO_INVALID_MODULE_NO = 2101            ' Invalid AIO module
Public Const AXT_RT_AIO_INVALID_CHANNEL_NO = 2102           ' Invalid AIO channel number
Public Const AXT_RT_AIO_INVALID_USE = 2106                  ' Can not use AIO
Public Const AXT_RT_AIO_INVALID_TRIGGER_MODE = 2107         ' Invalid trigger mode
Public Const AXT_RT_AIO_EXTERNAL_DATA_EMPTY = 2108

Public Const AXT_RT_DIO_OPEN_ERROR = 3001                   ' Failed to open DIO module
Public Const AXT_RT_DIO_NOT_MODULE = 3051                   ' No DIO module
Public Const AXT_RT_DIO_NOT_INTERRUPT = 3052                ' DIO Interrupt not set
Public Const AXT_RT_DIO_INVALID_MODULE_NO = 3101            ' Invalid DIO module number
Public Const AXT_RT_DIO_INVALID_OFFSET_NO = 3102            ' Invalid DIO OFFSET number
Public Const AXT_RT_DIO_INVALID_LEVEL = 3103                ' Invalid DIO level
Public Const AXT_RT_DIO_INVALID_MODE = 3104                 ' Invalid DIO mode
Public Const AXT_RT_DIO_INVALID_VALUE = 3105                ' Invalid setting value
Public Const AXT_RT_DIO_INVALID_USE = 3106                  ' Can not use DIO API function

Public Const AXT_RT_CNT_OPEN_ERROR = 3201                   ' Fail to open CND module
Public Const AXT_RT_CNT_NOT_MODULE = 3251                   ' No CNT module
Public Const AXT_RT_CNT_NOT_INTERRUPT = 3252                ' CNT Interrupt not set
Public Const AXT_RT_CNT_INVALID_MODULE_NO = 3301            ' Invalid CNT module number
Public Const AXT_RT_CNT_INVALID_OFFSET_NO = 3302            ' Invalid CNT OFFSET number
Public Const AXT_RT_CNT_INVALID_LEVEL = 3303                ' Invalid CNT level
Public Const AXT_RT_CNT_INVALID_MODE = 3304                 ' Invalid CNT mode
Public Const AXT_RT_CNT_INVALID_VALUE = 3305                ' Invalid setting value
Public Const AXT_RT_CNT_INVALID_USE = 3306                  ' Can not use CNT API function

Public Const AXT_RT_MOTION_OPEN_ERROR = 4001                ' Failed to open motion library
Public Const AXT_RT_MOTION_NOT_MODULE = 4051                ' No motion module is installed in the system
Public Const AXT_RT_MOTION_NOT_INTERRUPT = 4052             ' Failed to read the result of interrupt
Public Const AXT_RT_MOTION_NOT_INITIAL_AXIS_NO = 4053       ' Failed to initialize the motion of corresponding axis
Public Const AXT_RT_MOTION_NOT_IN_CONT_INTERPOL = 4054      ' Command to stop continuous interpolation while not in continuous interpolation motion
Public Const AXT_RT_MOTION_NOT_PARA_READ = 4055             ' Failed to load parameters for home return drive
Public Const AXT_RT_MOTION_INVALID_AXIS_NO = 4101           ' Corresponding axis does not exist
Public Const AXT_RT_MOTION_INVALID_METHOD = 4102            ' Invalid setting for corresponding axis drive
Public Const AXT_RT_MOTION_INVALID_USE = 4103               ' Invalid setting for 'uUse' parameter
Public Const AXT_RT_MOTION_INVALID_LEVEL = 4104             ' Invalid setting for 'uLevel' parameter
Public Const AXT_RT_MOTION_INVALID_BIT_NO = 4105            ' Invalid setting for general purpose input/output bit
Public Const AXT_RT_MOTION_INVALID_STOP_MODE = 4106         ' Invalid setting values for motion stop mode
Public Const AXT_RT_MOTION_INVALID_TRIGGER_MODE = 4107      ' Invalid setting for trigger setting mode
Public Const AXT_RT_MOTION_INVALID_TRIGGER_LEVEL = 4108     ' Invalid setting for trigger output level
Public Const AXT_RT_MOTION_INVALID_SELECTION = 4109         ' 'uSelection' parameter is set to a value other than COMMAND or ACTUAL
Public Const AXT_RT_MOTION_INVALID_TIME = 4110              ' Invalid setting for Trigger output time value
Public Const AXT_RT_MOTION_INVALID_FILE_LOAD = 4111         ' Failed to load the file containing motion setting values
Public Const AXT_RT_MOTION_INVALID_FILE_SAVE = 4112         ' Failed to save the file containing motion setting values
Public Const AXT_RT_MOTION_INVALID_VELOCITY = 4113          ' Motion error occurred since the motion drive velocity value is set as zero
Public Const AXT_RT_MOTION_INVALID_ACCELTIME = 4114         ' Motion error occurred since motion drive acceleration time value is set as zero
Public Const AXT_RT_MOTION_INVALID_PULSE_VALUE = 4115       ' Input pulse value is set to a value less than zero when setting motion unit
Public Const AXT_RT_MOTION_INVALID_NODE_NUMBER = 4116       ' Called position or velocity override function while not in motion
Public Const AXT_RT_MOTION_INVALID_TARGET = 4117            ' Flag indicating the cause of multi axis motion stop

Public Const AXT_RT_MOTION_ERROR_IN_NONMOTION = 4151        ' Not in motion drive when it should be
Public Const AXT_RT_MOTION_ERROR_IN_MOTION = 4152           ' Called another motion drive function before the completion of current motion
Public Const AXT_RT_MOTION_ERROR = 4153                     ' Error occurred during the execution of multi axis motion stop function
Public Const AXT_RT_MOTION_ERROR_GANTRY_ENABLE = 4154       ' Gantry-enable is activated again while in motion with gantry enabled
Public Const AXT_RT_MOTION_ERROR_GANTRY_AXIS = 4155         ' Invalid input of gantry axis master channel (axis) number (starting from zero)
Public Const AXT_RT_MOTION_ERROR_MASTER_SERVOON = 4156      ' Servo ON is not enabled for the master axis
Public Const AXT_RT_MOTION_ERROR_SLAVE_SERVOON = 4157       ' Servo ON is not enabled for the slave axis
Public Const AXT_RT_MOTION_INVALID_POSITION = 4158          ' Not in a valid position
Public Const AXT_RT_ERROR_NOT_SAME_MODULE = 4159            ' Not in the same module
Public Const AXT_RT_ERROR_NOT_SAME_BOARD = 4160             ' Not in the same board
Public Const AXT_RT_ERROR_NOT_SAME_PRODUCT = 4161           ' When products are different each other
Public Const AXT_RT_NOT_CAPTURED = 4162                     ' Failed to capture the position
Public Const AXT_RT_ERROR_NOT_SAME_IC = 4163                ' Not in the same chip
Public Const AXT_RT_ERROR_NOT_GEARMODE = 4164               ' Failed to change to the gear mode
Public Const AXT_ERROR_CONTI_INVALID_AXIS_NO = 4165         ' Invalid axis during continuous interpolation axes mapping
Public Const AXT_ERROR_CONTI_INVALID_MAP_NO = 4166          ' Invalid mapping number during continuous interpolation mapping
Public Const AXT_ERROR_CONTI_EMPTY_MAP_NO = 4167            ' Continuous interpolation mapping number is empty
Public Const AXT_RT_MOTION_ERROR_CACULATION = 4168          ' Error in calculation
Public Const AXT_RT_ERROR_MOVE_SENSOR_CHECK = 4169          

Public Const AXT_ERROR_HELICAL_INVALID_AXIS_NO = 4170       ' Invalid axis for helical axis mapping
Public Const AXT_ERROR_HELICAL_INVALID_MAP_NO = 4171        ' Invalid mapping number for helical mapping
Public Const AXT_ERROR_HELICAL_EMPTY_MAP_NO = 4172          ' Helical mapping number is empty

Public Const AXT_ERROR_SPLINE_INVALID_AXIS_NO = 4180        ' Invalid axis for spline axis mapping
Public Const AXT_ERROR_SPLINE_INVALID_MAP_NO = 4181         ' Invalid mapping number for spline mapping
Public Const AXT_ERROR_SPLINE_EMPTY_MAP_NO = 4182           ' Spline Mapping number is empty
Public Const AXT_ERROR_SPLINE_NUM_ERROR = 4183              ' Spline point value is inapplicable
Public Const AXT_RT_MOTION_INTERPOL_VALUE = 4184            ' Invalid input value for interpolation
Public Const AXT_RT_ERROR_NOT_CONTIBEGIN = 4185             ' CONTIBEGIN function is not called in continuous interpolation
Public Const AXT_RT_ERROR_NOT_CONTIEND = 4186               ' CONTIEND function is not called in continuous interpolation

Public Const AXT_RT_MOTION_HOME_SEARCHING = 4201            ' Other function is called while in home search motion
Public Const AXT_RT_MOTION_HOME_ERROR_SEARCHING = 4202      ' Home search motion is forced to stop by the user or something from external
Public Const AXT_RT_MOTION_HOME_ERROR_START = 4203          ' Failed to start home search drive due to Initialization  problem
Public Const AXT_RT_MOTION_HOME_ERROR_GANTRY = 4204         ' Failed to execute Gantry enable during home search motion

Public Const AXT_RT_MOTION_READ_ALARM_WAITING = 4210        
Public Const AXT_RT_MOTION_READ_ALARM_NO_REQUEST = 4211     
Public Const AXT_RT_MOTION_READ_ALARM_TIMEOUT = 4212        
Public Const AXT_RT_MOTION_READ_ALARM_FAILED = 4213         
Public Const AXT_RT_MOTION_READ_ALARM_UNKNOWN = 4220        
Public Const AXT_RT_MOTION_READ_ALARM_FILES = 4221          

Public Const AXT_RT_MOTION_POSITION_OUTOFBOUND = 4251       ' Configured position is either above the maximum value or below the minimum value
Public Const AXT_RT_MOTION_PROFILE_INVALID = 4252           ' Invalid setting for velocity profile
Public Const AXT_RT_MOTION_VELOCITY_OUTOFBOUND = 4253       ' Configured velocity is either above the maximum value or below the minimum value
Public Const AXT_RT_MOTION_MOVE_UNIT_IS_ZERO = 4254         ' Unit of the motion values is set as zero
Public Const AXT_RT_MOTION_SETTING_ERROR = 4255             ' Invalid setting for Velocity, Acceleration, Jerk, or Profile
Public Const AXT_RT_MOTION_IN_CONT_INTERPOL = 4256          ' Execution of motion start or restart function before the completion of current continuous interpolated motion
Public Const AXT_RT_MOTION_DISABLE_TRIGGER = 4257           ' Trigger output is disabled
Public Const AXT_RT_MOTION_INVALID_CONT_INDEX = 4258        ' Invalid setting for continuous interpolation index value
Public Const AXT_RT_MOTION_CONT_QUEUE_FULL = 4259           ' Continuous Interpolation queue of motion chip is full
Public Const AXT_RT_PROTECTED_DURING_SERVOON = 4260         ' Protected during servo-on
Public Const AXT_RT_HW_ACCESS_ERROR = 4261                  ' Failed memory Read / Write
Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV1 = 4262     ' DPRAM Command Write fail Level1
Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV2 = 4263     ' DPRAM Command Write fail Level2
Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV3 = 4264     ' DPRAM Command Write fail Level3
Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV1 = 4265      ' DPRAM Command Read fail Level1
Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV2 = 4266      ' DPRAM Command Read fail Level2
Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV3 = 4267      ' DPRAM Command Read fail Level3

Public Const AXT_RT_COMPENSATION_SET_PARAM_FIRST = 4300

Public Const AXT_RT_SEQ_NOT_IN_SERVICE = 4400
Public Const AXT_ERROR_SEQ_INVALID_MAP_NO = 4401
Public Const AXT_ERROR_INVALID_AXIS_NO = 4402
Public Const AXT_RT_ERROR_NOT_SEQ_NODE_BEGIN = 4403
Public Const AXT_RT_ERROR_NOT_SEQ_NODE_END = 4404
Public Const AXT_RT_ERROR_NO_NODE = 4405
Public Const AXT_RT_ERROR_SEQ_STOP_TIMEOUT = 4406

Public Const AXT_RT_M3_COMMUNICATION_FAILED = 4500             ' ML3 Only 
Public Const AXT_RT_MOTION_ONE_OF_AXES_IS_NOT_M3 = 4501        ' ML3 Only
Public Const AXT_RT_MOTION_BIGGER_VEL_THEN_MAX_VEL = 4502      ' ML3 Only
Public Const AXT_RT_MOTION_SMALLER_VEL_THEN_MAX_VEL = 4503     ' ML3 Only
Public Const AXT_RT_MOTION_ACCEL_MUST_BIGGER_THEN_ZERO = 4504  ' ML3 Only
Public Const AXT_RT_MOTION_SMALL_ACCEL_WITH_UNIT_PULSE = 4505  ' ML3 Only
Public Const AXT_RT_MOTION_INVALID_INPUT_ACCEL = 4506          ' ML3 Only
Public Const AXT_RT_MOTION_SMALL_DECEL_WITH_UNIT_PULSE = 4507  ' ML3 Only
Public Const AXT_RT_MOTION_INVALID_INPUT_DECEL = 4508          ' ML3 Only
Public Const AXT_RT_MOTION_SAME_START_AND_CENTER_POS = 4509    ' ML3 Only
Public Const AXT_RT_MOTION_INVALID_JERK = 4510                 ' ML3 Only
Public Const AXT_RT_MOTION_INVALID_INPUT_VALUE = 4511          ' ML3 Only
Public Const AXT_RT_MOTION_NOT_SUPPORT_PROFILE = 4512          ' ML3 Only
Public Const AXT_RT_MOTION_INPOS_UNUSED = 4513                 ' ML3 Only
Public Const AXT_RT_MOTION_AXIS_IN_SLAVE_STATE = 4514          ' ML3 Only
Public Const AXT_RT_MOTION_AXES_ARE_NOT_SAME_BOARD = 4515      ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_IN_ALARM = 4516               ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_IN_EMGN = 4517                ' ML3 Only
Public Const AXT_RT_MOTION_CAN_NOT_CHANGE_COORD_NO = 4518      ' ML3 Only
Public Const AXT_RT_MOTION_INVALID_INTERNAL_RADIOUS = 4519     ' ML3 Only
Public Const AXT_RT_MOTION_CONTI_QUEUE_FULL = 4521             ' ML3 Only
Public Const AXT_RT_MOTION_SAME_START_AND_END_POSITION = 4522  ' ML3 Only
Public Const AXT_RT_MOTION_INVALID_ANGLE = 4523                ' ML3 Only
Public Const AXT_RT_MOTION_CONTI_QUEUE_EMPTY = 4524            ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_GEAR_ENABLE = 4525            ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_GEAR_AXIS = 4526              ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_NO_GANTRY_ENABLE = 4527       ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_NO_GEAR_ENABLE = 4528         ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_GANTRY_ENABLE_FULL = 4529     ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_GEAR_ENABLE_FULL = 4530       ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_NO_GANTRY_SLAVE = 4531        ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_NO_GEAR_SLAVE = 4532          ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_MASTER_SLAVE_SAME = 4533      ' ML3 Only
Public Const AXT_RT_MOTION_NOT_SUPPORT_HOMESIGNAL = 4534       ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_NOT_SYNC_CONNECT = 4535       ' ML3 Only
Public Const AXT_RT_MOTION_OVERFLOW_POSITION = 4536            ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_INVALID_CONTIMAPAXIS = 4537   ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_INVALID_CONTIMAPSIZE = 4538   ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_IN_SERVO_OFF = 4539           ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_POSITIVE_LIMIT = 4540         ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_NEGATIVE_LIMIT = 4541         ' ML3 Only
Public Const AXT_RT_MOTION_ERROR_OVERFLOW_SWPROFILE_NUM = 4542 ' ML3 Only
Public Const AXT_RT_PROTECTED_DURING_INMOTION = 4543           ' ML3 Only

Public Const AXT_RT_DATA_FLASH_NOT_EXIST = 5000
Public Const AXT_RT_DATA_FLASH_BUSY = 5001

Public Const WM_USER = &H400
Public Const WM_AXL_INTERRUPT = (WM_USER + 1001)
' Define Log Level
Public Const LEVEL_NONE = 0
Public Const LEVEL_ERROR = 1
Public Const LEVEL_RUNSTOP = 2
Public Const LEVEL_FUNCTION = 3
' Define Axis Status
Public Const STATUS_NOTEXIST = 0
Public Const STATUS_EXIST = 1
' Define Use Flag
Public Const DISABLE = 0
Public Const ENABLE = 1
' Define Analog Input Trigger Mode
Public Const DISABLE_MODE = 0
Public Const NORMAL_MODE = 1
Public Const TIMER_MODE = 2
Public Const EXTERNAL_MODE = 3
' Define Analog Input Fifo Control
Public Const NEW_DATA_KEEP = 0
Public Const CURR_DATA_KEEP = 1
' Define Analog Input Event Mask
Public Const DATA_EMPTY = &H1
Public Const DATA_MANY = &H2
Public Const DATA_SMALL = &H4
Public Const DATA_FULL = &H8
' Define Analog Input Interrupt Mask
Public Const ADC_DONE = &H0
Public Const SCAN_END = &H1
Public Const FIFO_HALF_FULL = &H2
Public Const NO_SIGNAL = &H3
' Define Analog Input Queue Event
Public Const AIO_EVENT_DATA_RESET = &H0
Public Const AIO_EVENT_DATA_UPPER = &H1
Public Const AIO_EVENT_DATA_LOWER = &H2
Public Const AIO_EVENT_DATA_FULL = &H3
Public Const AIO_EVENT_DATA_EMPTY = &H4
' AI Module H/W FIFO Status Define
Public Const FIFO_DATA_EXIST = 0
Public Const FIFO_DATA_EMPTY = 1
Public Const FIFO_DATA_HALF = 2
Public Const FIFO_DATA_FULL = 6
' AI Module Conversion Status Define
Public Const EXTERNAL_DATA_DONE = 0
Public Const EXTERNAL_DATA_FINE = 1
Public Const EXTERNAL_DATA_HALF = 2
Public Const EXTERNAL_DATA_FULL = 3
Public Const EXTERNAL_COMPLETE = 4
' Define Digital Input Edge
Public Const DOWN_EDGE = 0
Public Const UP_EDGE = 1
' Define DIO Contact Status
Public Const OFF_STATE = 0
Public Const ON_STATE = 1
' Define Motion Stop Mode
Public Const EMERGENCY_STOP = 0
Public Const SLOWDOWN_STOP = 1
' Define Motion Edge
Public Const SIGNAL_UP_EDGE = 0
Public Const SIGNAL_DOWN_EDGE = 1
Public Const SIGNAL_LOW_LEVEL = 2
Public Const SIGNAL_HIGH_LEVEL = 3
' Define Motion Position Type
Public Const COMMAND = 0
Public Const ACTUAL = 1
' Define Motion Trigger Type
Public Const PERIOD_MODE = 0
Public Const ABS_POS_MODE = 1
Public Const POS_ABS_LONG_MODE = 2
' Define Motion Signal Level
Public Const LOW = 0
Public Const HIGH = 1
Public Const UNUSED = 2
Public Const USED = 3
' Define Motion Coordinate Type
Public Const POS_ABS_MODE = 0
Public Const POS_REL_MODE = 1
' Define Motion Profile Type
Public Const SYM_TRAPEZOIDE_MODE = 0
Public Const ASYM_TRAPEZOIDE_MODE = 1
Public Const QUASI_S_CURVE_MODE = 2
Public Const SYM_S_CURVE_MODE = 3
Public Const ASYM_S_CURVE_MODE = 4
' Define Motion Signal Status
Public Const INACTIVE = 0
Public Const ACTIVE = 1
' Define Motion Home Result
Public Const HOME_RESERVED = &H0       
Public Const HOME_SUCCESS = &H1
Public Const HOME_SEARCHING = &H2
Public Const HOME_ERR_GNT_RANGE = &H10
Public Const HOME_ERR_USER_BREAK = &H11
Public Const HOME_ERR_VELOCITY = &H12
Public Const HOME_ERR_AMP_FAULT = &H13
Public Const HOME_ERR_NEG_LIMIT = &H14
Public Const HOME_ERR_POS_LIMIT = &H15
Public Const HOME_ERR_NOT_DETECT = &H16
Public Const HOME_ERR_SETTING = &H17
Public Const HOME_ERR_SERVO_OFF = &H18
Public Const HOME_ERR_TIMEOUT = &H20
Public Const HOME_ERR_FUNCALL = &H30
Public Const HOME_ERR_COUPLING = &H40
Public Const HOME_ERR_UNKNOWN = &HFF
' Define Motion Universal Input
Public Const UIO_INP0 = 0
Public Const UIO_INP1 = 1
Public Const UIO_INP2 = 2
Public Const UIO_INP3 = 3
Public Const UIO_INP4 = 4
Public Const UIO_INP5 = 5
' Define Motion Universal Output
Public Const UIO_OUT0 = 0
Public Const UIO_OUT1 = 1
Public Const UIO_OUT2 = 2
Public Const UIO_OUT3 = 3
Public Const UIO_OUT4 = 4
Public Const UIO_OUT5 = 5
' Define Motion Deceleration Method
Public Const AutoDetect = 0
Public Const RestPulse = 1
' Define Motion Pulse Output Method
Public Const OneHighLowHigh = &H0                           ' 1 pulse method, PULSE(Active High), forward direction(DIR=Low)  / reverse direction(DIR=High)
Public Const OneHighHighLow = &H1                           ' 1 pulse method, PULSE(Active High), forward direction (DIR=High) / reverse direction (DIR=Low)
Public Const OneLowLowHigh = &H2                            ' 1 pulse method, PULSE(Active Low), forward direction (DIR=Low)  / reverse direction (DIR=High)
Public Const OneLowHighLow = &H3                            ' 1 pulse method, PULSE(Active Low), forward direction (DIR=High) / reverse direction (DIR=Low)
Public Const TwoCcwCwHigh = &H4                             ' 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active High
Public Const TwoCcwCwLow = &H5                              ' 2 pulse method, PULSE(CCW: reverse direction),  DIR(CW: forward direction),  Active Low
Public Const TwoCwCcwHigh = &H6                             ' 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active High
Public Const TwoCwCcwLow = &H7                              ' 2 pulse method, PULSE(CW: forward direction),   DIR(CCW: reverse direction), Active Low
Public Const TwoPhase = &H8                                 ' 2 phase (90' phase difference),  PULSE lead DIR(CW: forward direction), PULSE lag DIR(CCW: reverse direction)
Public Const TwoPhaseReverse = &H9                          ' 2 phase(90' phase difference),  PULSE lead DIR(CCW: Forward direction), PULSE lag DIR(CW: Reverse direction)
' Define Motion Encoder Input Method
Public Const ObverseUpDownMode = &H0                        ' Forward direction Up/Down
Public Const ObverseSqr1Mode = &H1                          ' Forward direction 1 multiplication
Public Const ObverseSqr2Mode = &H2                          ' Forward direction 2 multiplication
Public Const ObverseSqr4Mode = &H3                          ' Forward direction 4 multiplication
Public Const ReverseUpDownMode = &H4                        ' Reverse direction Up/Down
Public Const ReverseSqr1Mode = &H5                          ' Reverse direction 1 multiplication
Public Const ReverseSqr2Mode = &H6                          ' Reverse direction 2 multiplication
Public Const ReverseSqr4Mode = &H7                          ' Reverse direction 4 multiplication
' Define Motion Acceleration Unit
Public Const UNIT_SEC2 = &H0                                ' unit/sec2
Public Const SEC = &H1                                      ' sec
Public Const RPM_SEC2 = &H2                                 ' rpm/sec2
' Define Motion Move Direction
Public Const DIR_CCW = &H0                                  ' Counterclockwise direction
Public Const DIR_CW = &H1                                   ' Clockwise direction
' Define Motion Move Circular Method
Public Const SHORT_DISTANCE = &H0                           ' Short distance circular movement
Public Const LONG_DISTANCE = &H1                            ' Lone distance circular movement
' Define Motion Interpolation Axis
Public Const INTERPOLATION_AXIS2 = &H0                      ' When 2 axis is used for interpolation
Public Const INTERPOLATION_AXIS3 = &H1                      ' When 3 axis is used for interpolation
Public Const INTERPOLATION_AXIS4 = &H2                      ' When 4 axis is used for interpolation
' Define Motion Interpolation Method
Public Const CONTI_NODE_VELOCITY = &H0                      ' Velocity assigned interpolation mode
Public Const CONTI_NODE_MANUAL = &H1                        ' Node acceleration and deceleration interpolation mode
Public Const CONTI_NODE_AUTO = &H2                          ' Automatic acceleration and deceleration interpolation mode
' Define Motion Home Detect Signal
Public Const PosEndLimit = &H0                              ' +Elm(End limit) + direction limit sensor signal
Public Const NegEndLimit = &H1                              ' -Elm(End limit) - direction limit sensor signal
Public Const PosSloLimit = &H2                              ' +Slm(Decelerate limit) signal - Not-used
Public Const NegSloLimit = &H3                              ' -Slm(Decelerate limit) signal - Not-used
Public Const HomeSensor = &H4                               ' IN0(ORG)  home sensor signal
Public Const EncodZPhase = &H5                              ' IN1(Z phase)  Encoder Z phase signal
Public Const UniInput02 = &H6                               ' IN2(universal) universal input number 2 signal
Public Const UniInput03 = &H7                               ' IN3(universal) universal input number 3 signal
Public Const UniInput04 = &H8                               ' IN4(universal) universal input number 4 signal
Public Const UniInput05 = &H9                               ' IN5(universal) universal input number 5 signal
' Define Motion Input Filter Signal
Public Const END_LIMIT = &H10                               ' End limit +/-���� ����Ʈ ���� ��ȣ
Public Const INP_ALARM = &H11                               ' Inposition/Alarm ��ȣ
Public Const UIN_00_01 = &H12                               ' Home/Z-Phase ��ȣ
Public Const UIN_02_04 = &H13                               ' UIN 2, 3, 4 ��ȣ
' Define Motion MPG Input Method
Public Const MPG_DIFF_ONE_PHASE = &H0                       ' MPG input method One Phase
Public Const MPG_DIFF_TWO_PHASE_1X = &H1                    ' MPG input method TwoPhase1
Public Const MPG_DIFF_TWO_PHASE_2X = &H2                    ' MPG input method TwoPhase2
Public Const MPG_DIFF_TWO_PHASE_4X = &H3                    ' MPG input method TwoPhase4
Public Const MPG_LEVEL_ONE_PHASE = &H4                      ' MPG input method Level One Phase
Public Const MPG_LEVEL_TWO_PHASE_1X = &H5                   ' MPG input method Level Two Phase1
Public Const MPG_LEVEL_TWO_PHASE_2X = &H6                   ' MPG input method Level Two Phase2
Public Const MPG_LEVEL_TWO_PHASE_4X = &H7                   ' MPG input method Level Two Phase4
' Define Motion Sensor Move Mode
Public Const SENSOR_METHOD1 = &H0                           ' General drive
Public Const SENSOR_METHOD2 = &H1                           ' Slow speed drive before sensor signal detection. General drive after signal detection
Public Const SENSOR_METHOD3 = &H2                           ' Slow speed drive
' Define Motion CRC Use Method
Public Const CRC_SELECT1 = &H0                              ' No use of position clear, no use of remaining pulse clear
Public Const CRC_SELECT2 = &H1                              ' Use of position clear, no use of remaining pulse clear
Public Const CRC_SELECT3 = &H2                              ' No use of position clear, use of remaining pulse clear
Public Const CRC_SELECT4 = &H3                              ' Use of position clear, use of remaining pulse clear
' Define Motion Detect Signal Type
Public Const PElmNegativeEdge = &H0                         ' +Elm(End limit) falling edge
Public Const NElmNegativeEdge = &H1                         ' -Elm(End limit) falling edge
Public Const PSlmNegativeEdge = &H2                         ' +Slm(Slowdown limit) falling edge
Public Const NSlmNegativeEdge = &H3                         ' -Slm(Slowdown limit) falling edge
Public Const In0DownEdge = &H4                              ' IN0(ORG) falling edge
Public Const In1DownEdge = &H5                              ' IN1(Z phase) falling edge
Public Const In2DownEdge = &H6                              ' IN2(universal) falling edge
Public Const In3DownEdge = &H7                              ' IN3(universal) falling edge
Public Const PElmPositiveEdge = &H8                         ' +Elm(End limit) rising edge
Public Const NElmPositiveEdge = &H9                         ' -Elm(End limit) rising edge
Public Const PSlmPositiveEdge = &HA                         ' +Slm(Slowdown limit) rising edge
Public Const NSlmPositiveEdge = &HB                         ' -Slm(Slowdown limit) rising edge
Public Const In0UpEdge = &HC                                ' IN0(ORG) rising edge
Public Const In1UpEdge = &HD                                ' IN1(Z phase) rising edge
Public Const In2UpEdge = &HE                                ' IN2(universal) rising edge
Public Const In3UpEdge = &HF                                ' IN3(universal) rising edge
' Define Motion IP(2V03) End Status
Public Const IPEND_STATUS_SLM = &H1                         ' Bit 0, exit by limit decelerate stop signal input
Public Const IPEND_STATUS_ELM = &H2                         ' Bit 1, exit by limit emergency stop signal input
Public Const IPEND_STATUS_SSTOP_SIGNAL = &H4                ' Bit 2, exit by decelerate stop signal input
Public Const IPEND_STATUS_ESTOP_SIGANL = &H8                ' Bit 3, exit by emergency stop signal input
Public Const IPEND_STATUS_SSTOP_COMMAND = &H10              ' Bit 4, exit by decelerate stop command
Public Const IPEND_STATUS_ESTOP_COMMAND = &H20              ' Bit 5, exit by emergency stop command
Public Const IPEND_STATUS_ALARM_SIGNAL = &H40               ' Bit 6, exit by Alarm signal input
Public Const IPEND_STATUS_DATA_ERROR = &H80                 ' Bit 7, exit by data setting error
Public Const IPEND_STATUS_DEVIATION_ERROR = &H100           ' Bit 8, exit by deviation error
Public Const IPEND_STATUS_ORIGIN_DETECT = &H200             ' Bit 9, exit by home search
Public Const IPEND_STATUS_SIGNAL_DETECT = &H400             ' Bit 10, exit by signal search(Signal search-1/2 drive exit)
Public Const IPEND_STATUS_PRESET_PULSE_DRIVE = &H800        ' Bit 11, Preset pulse drive exit
Public Const IPEND_STATUS_SENSOR_PULSE_DRIVE = &H1000       ' Bit 12, Sensor pulse drive exit
Public Const IPEND_STATUS_LIMIT = &H2000                    ' Bit 13, exit by Limit complete stop
Public Const IPEND_STATUS_SOFTLIMIT = &H4000                ' Bit 14, exit by Soft limit
Public Const IPEND_STATUS_INTERPOLATION_DRIVE = &H8000      ' Bit 15, Interpolation drive exit
' Define Motion IP(2V03)Drive Status
Public Const IPDRIVE_STATUS_BUSY = &H1                      ' Bit 0, BUSY (in DRIVE)
Public Const IPDRIVE_STATUS_DOWN = &H2                      ' Bit 1, DOWN(in deceleration DRIVE)
Public Const IPDRIVE_STATUS_CONST = &H4                     ' Bit 2, CONST(in constant speed DRIVE)
Public Const IPDRIVE_STATUS_UP = &H8                        ' Bit 3, UP(in acceleration DRIVE)
Public Const IPDRIVE_STATUS_ICL = &H10                      ' Bit 4, ICL(ICM < INCNT)
Public Const IPDRIVE_STATUS_ICG = &H20                      ' Bit 5, ICG(ICM < INCNT)
Public Const IPDRIVE_STATUS_ECL = &H40                      ' Bit 6, ECL(ECM > EXCNT)
Public Const IPDRIVE_STATUS_ECG = &H80                      ' Bit 7, ECG(ECM < EXCNT)
Public Const IPDRIVE_STATUS_DRIVE_DIRECTION = &H100         ' Bit 8, drive direction signal (0=CW/1=CCW)
Public Const IPDRIVE_STATUS_COMMAND_BUSY = &H200            ' Bit 9, In execution of command
Public Const IPDRIVE_STATUS_PRESET_DRIVING = &H400          ' Bit 10, In drive of a specific pulse number
Public Const IPDRIVE_STATUS_CONTINUOUS_DRIVING = &H800      ' Bit 11, In continuous drive
Public Const IPDRIVE_STATUS_SIGNAL_SEARCH_DRIVING = &H1000  ' Bit 12, In signal search drive
Public Const IPDRIVE_STATUS_ORG_SEARCH_DRIVING = &H2000     ' Bit 13, In home search drive
Public Const IPDRIVE_STATUS_MPG_DRIVING = &H4000            ' Bit 14, In MPG drive
Public Const IPDRIVE_STATUS_SENSOR_DRIVING = &H8000         ' Bit 15, In sensor position drive
Public Const IPDRIVE_STATUS_L_C_INTERPOLATION = &H10000     ' Bit 16, In straight/circular interpolation drive
Public Const IPDRIVE_STATUS_PATTERN_INTERPOLATION = &H20000 ' Bit 17, In pattern interpolation drive
Public Const IPDRIVE_STATUS_INTERRUPT_BANK1 = &H40000       ' Bit 18, Interrupt occurrence in BANK1
Public Const IPDRIVE_STATUS_INTERRUPT_BANK2 = &H80000       ' Bit 19, Interrupt occurrence in BANK2
' Define Motion IP(2V03)Int MASK1
Public Const IPINTBANK1_DONTUSE = &H0                       ' INTERRUT DISABLED.
Public Const IPINTBANK1_DRIVE_END = &H1                     ' Bit 0, Drive end(default value : 1).
Public Const IPINTBANK1_ICG = &H2                           ' Bit 1, INCNT is greater than INCNTCMP.
Public Const IPINTBANK1_ICE = &H4                           ' Bit 2, INCNT is equal with INCNTCMP.
Public Const IPINTBANK1_ICL = &H8                           ' Bit 3, INCNT is less than INCNTCMP.
Public Const IPINTBANK1_ECG = &H10                          ' Bit 4, EXCNT is greater than EXCNTCMP.
Public Const IPINTBANK1_ECE = &H20                          ' Bit 5, EXCNT is equal with EXCNTCMP.
Public Const IPINTBANK1_ECL = &H40                          ' Bit 6, EXCNT is less than EXCNTCMP.
Public Const IPINTBANK1_SCRQEMPTY = &H80                    ' Bit 7, Script control queue is empty.
Public Const IPINTBANK1_CAPRQEMPTY = &H100                  ' Bit 8, Caption result data queue is empty.
Public Const IPINTBANK1_SCRREG1EXE = &H200                  ' Bit 9, Script control register-1 command is executed.
Public Const IPINTBANK1_SCRREG2EXE = &H400                  ' Bit 10, Script control register-2 command is executed.
Public Const IPINTBANK1_SCRREG3EXE = &H800                  ' Bit 11, Script control register-3 command is executed.
Public Const IPINTBANK1_CAPREG1EXE = &H1000                 ' Bit 12, Caption control register-1 command is executed.
Public Const IPINTBANK1_CAPREG2EXE = &H2000                 ' Bit 13, Caption control register-2 command is executed.
Public Const IPINTBANK1_CAPREG3EXE = &H4000                 ' Bit 14, Caption control register-3 command is executed.
Public Const IPINTBANK1_INTGGENCMD = &H8000                 ' Bit 15, Interrupt generation command is executed(0xFF)
Public Const IPINTBANK1_DOWN = &H10000                      ' Bit 16, At starting point for deceleration drive.
Public Const IPINTBANK1_CONT = &H20000                      ' Bit 17, At starting point for constant speed drive.
Public Const IPINTBANK1_UP = &H40000                        ' Bit 18, At starting point for acceleration drive.
Public Const IPINTBANK1_SIGNALDETECTED = &H80000            ' Bit 19, Signal assigned in MODE1 is detected.
Public Const IPINTBANK1_SP23E = &H100000                    ' Bit 20, Current speed is equal with rate change point RCP23.
Public Const IPINTBANK1_SP12E = &H200000                    ' Bit 21, Current speed is equal with rate change point RCP12.
Public Const IPINTBANK1_SPE = &H400000                      ' Bit 22, Current speed is equal with speed comparison data(SPDCMP).
Public Const IPINTBANK1_INCEICM = &H800000                  ' Bit 23, INTCNT(1'st counter) is equal with ICM(1'st count minus limit data)
Public Const IPINTBANK1_SCRQEXE = &H1000000                 ' Bit 24, Script queue command is executed When SCRCONQ's 30 bit is '1'.
Public Const IPINTBANK1_CAPQEXE = &H2000000                 ' Bit 25, Caption queue command is executed When CAPCONQ's 30 bit is '1'.
Public Const IPINTBANK1_SLM = &H4000000                     ' Bit 26, NSLM/PSLM input signal is activated.
Public Const IPINTBANK1_ELM = &H8000000                     ' Bit 27, NELM/PELM input signal is activated.
Public Const IPINTBANK1_USERDEFINE1 = &H10000000            ' Bit 28, Selectable interrupt source 0(refer "0xFE" command).
Public Const IPINTBANK1_USERDEFINE2 = &H20000000            ' Bit 29, Selectable interrupt source 1(refer "0xFE" command).
Public Const IPINTBANK1_USERDEFINE3 = &H40000000            ' Bit 30, Selectable interrupt source 2(refer "0xFE" command).
Public Const IPINTBANK1_USERDEFINE4 = &H80000000            ' Bit 31, Selectable interrupt source 3(refer "0xFE" command).
' Define Motion IP(2V03)Int MASK2
Public Const IPINTBANK2_DONTUSE = &H0                       ' INTERRUT DISABLED.
Public Const IPINTBANK2_L_C_INP_Q_EMPTY = &H1               ' Bit 0, Linear/Circular interpolation parameter queue is empty.
Public Const IPINTBANK2_P_INP_Q_EMPTY = &H2                 ' Bit 1, Bit pattern interpolation queue is empty.
Public Const IPINTBANK2_ALARM_ERROR = &H4                   ' Bit 2, Alarm input signal is activated.
Public Const IPINTBANK2_INPOSITION = &H8                    ' Bit 3, Inposition input signal is activated.
Public Const IPINTBANK2_MARK_SIGNAL_HIGH = &H10             ' Bit 4, Mark input signal is activated.
Public Const IPINTBANK2_SSTOP_SIGNAL = &H20                 ' Bit 5, SSTOP input signal is activated.
Public Const IPINTBANK2_ESTOP_SIGNAL = &H40                 ' Bit 6, ESTOP input signal is activated.
Public Const IPINTBANK2_SYNC_ACTIVATED = &H80               ' Bit 7, SYNC input signal is activated.
Public Const IPINTBANK2_TRIGGER_ENABLE = &H100              ' Bit 8, Trigger output is activated.
Public Const IPINTBANK2_EXCNTCLR = &H200                    ' Bit 9, External(2'nd) counter is cleard by EXCNTCLR setting.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT0 = &H400      ' Bit 10, ALU1's compare result bit 0 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT1 = &H800      ' Bit 11, ALU1's compare result bit 1 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT2 = &H1000     ' Bit 12, ALU1's compare result bit 2 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT3 = &H2000     ' Bit 13, ALU1's compare result bit 3 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT4 = &H4000     ' Bit 14, ALU1's compare result bit 4 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT0 = &H8000     ' Bit 15, ALU2's compare result bit 0 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT1 = &H10000    ' Bit 16, ALU2's compare result bit 1 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT2 = &H20000    ' Bit 17, ALU2's compare result bit 2 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT3 = &H40000    ' Bit 18, ALU2's compare result bit 3 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT4 = &H80000    ' Bit 19, ALU2's compare result bit 4 is activated.
Public Const IPINTBANK2_L_C_INP_Q_LESS_4 = &H100000         ' Bit 20, Linear/Circular interpolation parameter queue is less than 4.
Public Const IPINTBANK2_P_INP_Q_LESS_4 = &H200000           ' Bit 21, Pattern interpolation parameter queue is less than 4.
Public Const IPINTBANK2_XSYNC_ACTIVATED = &H400000          ' Bit 22, X axis sync input signal is activated.
Public Const IPINTBANK2_YSYNC_ACTIVATED = &H800000          ' Bit 23, Y axis sync input siangl is activated.
Public Const IPINTBANK2_P_INP_END_BY_END_PATTERN = &H1000000 ' Bit 24, Bit pattern interpolation is terminated by end pattern.
'IPINTBANK2_ = 0x02000000,                                  ' Bit 25, Don't care.
'IPINTBANK2_ = 0x04000000,                                  ' Bit 26, Don't care.
'IPINTBANK2_ = 0x08000000,                                  ' Bit 27, Don't care.
'IPINTBANK2_ = 0x10000000,                                  ' Bit 28, Don't care.
'IPINTBANK2_ = 0x20000000,                                  ' Bit 29, Don't care.
'IPINTBANK2_ = 0x40000000,                                  ' Bit 30, Don't care.
'IPINTBANK2_ = 0x80000000                                   ' Bit 31, Don't care.
' Define Motion IP(2V03)Drive Status
Public Const IPMECHANICAL_PELM_LEVEL = &H1                  ' Bit 0, +Limit emergency stop signal input Level
Public Const IPMECHANICAL_NELM_LEVEL = &H2                  ' Bit 1, -Limit emergency stop signal input Level
Public Const IPMECHANICAL_PSLM_LEVEL = &H4                  ' Bit 2, +limit decelerate stop signal input Level
Public Const IPMECHANICAL_NSLM_LEVEL = &H8                  ' Bit 3, -limit decelerate stop signal input Level
Public Const IPMECHANICAL_ALARM_LEVEL = &H10                ' Bit 4, Alarm signal input Level
Public Const IPMECHANICAL_INP_LEVEL = &H20                  ' Bit 5, InPos signal input Level
Public Const IPMECHANICAL_ENC_DOWN_LEVEL = &H40             ' Bit 6, encoder DOWN(B phase) signal input Level
Public Const IPMECHANICAL_ENC_UP_LEVEL = &H80               ' Bit 7, encoder UP(A phase) signal input Level
Public Const IPMECHANICAL_EXMP_LEVEL = &H100                ' Bit 8, EXMP signal input Level
Public Const IPMECHANICAL_EXPP_LEVEL = &H200                ' Bit 9, EXPP signal input Level
Public Const IPMECHANICAL_MARK_LEVEL = &H400                ' Bit 10, MARK# signal input Level
Public Const IPMECHANICAL_SSTOP_LEVEL = &H800               ' Bit 11, SSTOP signal input Level
Public Const IPMECHANICAL_ESTOP_LEVEL = &H1000              ' Bit 12, ESTOP signal input Level
Public Const IPMECHANICAL_SYNC_LEVEL = &H2000               ' Bit 13, SYNC signal input Level
Public Const IPMECHANICAL_MODE8_16_LEVEL = &H4000           ' Bit 14, MODE8_16 signal input Level
' Define Motion QI Detect Signal
Public Const Signal_PosEndLimit = &H0                       ' +Elm(End limit) + direction limit sensor signal
Public Const Signal_NegEndLimit = &H1                       ' -Elm(End limit) - direction limit sensor signal
Public Const Signal_PosSloLimit = &H2                       ' +Slm(Slow Down limit) signal - Not-used
Public Const Signal_NegSloLimit = &H3                       ' -Slm(Slow Down limit) signal - Not-used
Public Const Signal_HomeSensor = &H4                        ' IN0(ORG)  home sensor signal
Public Const Signal_EncodZPhase = &H5                       ' IN1(Z phase)  Encoder Z phase signal
Public Const Signal_UniInput02 = &H6                        ' IN2(universal) universal input number 2 signal
Public Const Signal_UniInput03 = &H7                        ' IN3(universal) universal input number 3 signal
' Define Motion QI Drive status
Public Const QIMECHANICAL_PELM_LEVEL = &H1                  ' Bit 0, +Limit emergency stop signal current state
Public Const QIMECHANICAL_NELM_LEVEL = &H2                  ' Bit 1, -Limit emergency stop signal current state
Public Const QIMECHANICAL_PSLM_LEVEL = &H4                  ' Bit 2, +limit decelerate stop signal current state
Public Const QIMECHANICAL_NSLM_LEVEL = &H8                  ' Bit 3, -limit decelerate stop signal current state
Public Const QIMECHANICAL_ALARM_LEVEL = &H10                ' Bit 4, Alarm signal current state
Public Const QIMECHANICAL_INP_LEVEL = &H20                  ' Bit 5, InPos signal current state
Public Const QIMECHANICAL_ESTOP_LEVEL = &H40                ' Bit 6, emergency stop signal(ESTOP) current state
Public Const QIMECHANICAL_ORG_LEVEL = &H80                  ' Bit 7, home signal current state
Public Const QIMECHANICAL_ZPHASE_LEVEL = &H100              ' Bit 8, Z phase input signal current state
Public Const QIMECHANICAL_ECUP_LEVEL = &H200                ' Bit 9, ECUP terminal signal state
Public Const QIMECHANICAL_ECDN_LEVEL = &H400                ' Bit 10, ECDN terminal signal state
Public Const QIMECHANICAL_EXPP_LEVEL = &H800                ' Bit 11, EXPP terminal signal state
Public Const QIMECHANICAL_EXMP_LEVEL = &H1000               ' Bit 12, EXMP terminal signal state
Public Const QIMECHANICAL_SQSTR1_LEVEL = &H2000             ' Bit 13, SQSTR1 terminal signal state
Public Const QIMECHANICAL_SQSTR2_LEVEL = &H4000             ' Bit 14, SQSTR2 terminal signal state
Public Const QIMECHANICAL_SQSTP1_LEVEL = &H8000             ' Bit 15, SQSTP1 terminal signal state
Public Const QIMECHANICAL_SQSTP2_LEVEL = &H10000            ' Bit 16, SQSTP2 terminal signal state
Public Const QIMECHANICAL_MODE_LEVEL = &H20000              ' Bit 17, MODE terminal signal state
' Define Motion QI End Status
Public Const QIEND_STATUS_0 = &H1                           ' Bit 0, exit by forward direction limit signal (PELM)
Public Const QIEND_STATUS_1 = &H2                           ' Bit 1, exit by reverse direction limit signal (NELM)
Public Const QIEND_STATUS_2 = &H4                           ' Bit 2, exit by forward direction additional limit signal (PSLM)
Public Const QIEND_STATUS_3 = &H8                           ' Bit 3, exit by reverse direction additional limit signal (NSLM)
Public Const QIEND_STATUS_4 = &H10                          ' Bit 4, exit by forward direction soft limit emergency stop function
Public Const QIEND_STATUS_5 = &H20                          ' Bit 5, exit by reverse direction soft limit emergency stop function
Public Const QIEND_STATUS_6 = &H40                          ' Bit 6, exit by forward direction soft limit decelerate stop function
Public Const QIEND_STATUS_7 = &H80                          ' Bit 7, exit by reverse direction soft limit decelerate stop function
Public Const QIEND_STATUS_8 = &H100                         ' Bit 8, drive exit by servo alarm function
Public Const QIEND_STATUS_9 = &H200                         ' Bit 9, drive exit by emergency stop signal input
Public Const QIEND_STATUS_10 = &H400                        ' Bit 10, drive exit by emergency stop command
Public Const QIEND_STATUS_11 = &H800                        ' Bit 11, drive exit by decelerate stop command
Public Const QIEND_STATUS_12 = &H1000                       ' Bit 12, drive exit by entire axes emergency stop command
Public Const QIEND_STATUS_13 = &H2000                       ' Bit 13, drive exit by sync stop function #1(SQSTP1)
Public Const QIEND_STATUS_14 = &H4000                       ' Bit 14, drive exit by sync stop function #2(SQSTP2)
Public Const QIEND_STATUS_15 = &H8000                       ' Bit 15, encoder input (ECUP,ECDN) error occurrence
Public Const QIEND_STATUS_16 = &H10000                      ' Bit 16, MPG input (EXPP,EXMP) error occurrence
Public Const QIEND_STATUS_17 = &H20000                      ' Bit 17, exit with successful home search
Public Const QIEND_STATUS_18 = &H40000                      ' Bit 18, exit with successful signal search
Public Const QIEND_STATUS_19 = &H80000                      ' Bit 19, drive exit by interpolation data abnormality
Public Const QIEND_STATUS_20 = &H100000                     ' Bit 20, abnormal drive stop occurrence
Public Const QIEND_STATUS_21 = &H200000                     ' Bit 21, MPG function block pulse buffer overflow occurrence
Public Const QIEND_STATUS_22 = &H400000                     ' Bit 22, DON'CARE
Public Const QIEND_STATUS_23 = &H800000                     ' Bit 23, DON'CARE
Public Const QIEND_STATUS_24 = &H1000000                    ' Bit 24, DON'CARE
Public Const QIEND_STATUS_25 = &H2000000                    ' Bit 25, DON'CARE
Public Const QIEND_STATUS_26 = &H4000000                    ' Bit 26, DON'CARE
Public Const QIEND_STATUS_27 = &H8000000                    ' Bit 27, DON'CARE
Public Const QIEND_STATUS_28 = &H10000000                   ' Bit 28, current/last move drive direction
Public Const QIEND_STATUS_29 = &H20000000                   ' Bit 29, in output of remaining pulse clear
Public Const QIEND_STATUS_30 = &H40000000                   ' Bit 30, abnormal drive stop cause state
Public Const QIEND_STATUS_31 = &H80000000                   ' Bit 31, interpolation drive data error state
' Define Motion QI Drive Status
Public Const QIDRIVE_STATUS_0 = &H1                         ' Bit 0, BUSY(in drive move)
Public Const QIDRIVE_STATUS_1 = &H2                         ' Bit 1, DOWN(in deceleration)
Public Const QIDRIVE_STATUS_2 = &H4                         ' Bit 2, CONST(in constant speed)
Public Const QIDRIVE_STATUS_3 = &H8                         ' Bit 3, UP(in acceleration)
Public Const QIDRIVE_STATUS_4 = &H10                        ' Bit 4, in move of continuous drive
Public Const QIDRIVE_STATUS_5 = &H20                        ' Bit 5, in move of assigned distance drive
Public Const QIDRIVE_STATUS_6 = &H40                        ' Bit 6, in move of MPG drive
Public Const QIDRIVE_STATUS_7 = &H80                        ' Bit 7, in move of home search drive
Public Const QIDRIVE_STATUS_8 = &H100                       ' Bit 8, in move of signal search drive
Public Const QIDRIVE_STATUS_9 = &H200                       ' Bit 9, in move of interpolation drive
Public Const QIDRIVE_STATUS_10 = &H400                      ' Bit 10, in move of Slave drive
Public Const QIDRIVE_STATUS_11 = &H800                      ' Bit 11, current move drive direction (different indication information in interpolation drive)
Public Const QIDRIVE_STATUS_12 = &H1000                     ' Bit 12, in waiting for servo position completion after pulse output
Public Const QIDRIVE_STATUS_13 = &H2000                     ' Bit 13, in move of straight line interpolation drive
Public Const QIDRIVE_STATUS_14 = &H4000                     ' Bit 14, in move of circular interpolation drive
Public Const QIDRIVE_STATUS_15 = &H8000                     ' Bit 15, in pulse output
Public Const QIDRIVE_STATUS_16 = &H10000                    ' Bit 16, drive reserved data number(start)(0-7)
Public Const QIDRIVE_STATUS_17 = &H20000                    ' Bit 17, drive reserved data number (middle)(0-7)
Public Const QIDRIVE_STATUS_18 = &H40000                    ' Bit 18, drive reserved data number (end)(0-7)
Public Const QIDRIVE_STATUS_19 = &H80000                    ' Bit 19, drive reversed Queue is cleared
Public Const QIDRIVE_STATUS_20 = &H100000                   ' Bit 20, drive reversed Queue is full
Public Const QIDRIVE_STATUS_21 = &H200000                   ' Bit 21, velocity mode of current move drive (start)
Public Const QIDRIVE_STATUS_22 = &H400000                   ' Bit 22, velocity mode of current move drive (end)
Public Const QIDRIVE_STATUS_23 = &H800000                   ' Bit 23, MPG buffer #1 Full
Public Const QIDRIVE_STATUS_24 = &H1000000                  ' Bit 24, MPG buffer #2 Full
Public Const QIDRIVE_STATUS_25 = &H2000000                  ' Bit 25, MPG buffer #3 Full
Public Const QIDRIVE_STATUS_26 = &H4000000                  ' Bit 26, MPG buffer data OverFlow
' Define Motion QI Interrupt MASK1
Public Const QIINTBANK1_DISABLE = &H0                       ' INTERRUT DISABLED.
Public Const QIINTBANK1_0 = &H1                             ' Bit 0,  when drive set interrupt occurrence use is exit
Public Const QIINTBANK1_1 = &H2                             ' Bit 1,  when drive is exited
Public Const QIINTBANK1_2 = &H4                             ' Bit 2,  when drive is started
Public Const QIINTBANK1_3 = &H8                             ' Bit 3,  counter #1 < comparator #1 event occurrence
Public Const QIINTBANK1_4 = &H10                            ' Bit 4,  counter #1 = comparator #1 event occurrence
Public Const QIINTBANK1_5 = &H20                            ' Bit 5,  counter #1 > comparator #1 event occurrence
Public Const QIINTBANK1_6 = &H40                            ' Bit 6,  counter #2 < comparator #2 event occurrence
Public Const QIINTBANK1_7 = &H80                            ' Bit 7,  counter #2 = comparator #2 event occurrence
Public Const QIINTBANK1_8 = &H100                           ' Bit 8,  counter #2 > comparator #2 event occurrence
Public Const QIINTBANK1_9 = &H200                           ' Bit 9,  counter #3 < comparator #3 event occurrence
Public Const QIINTBANK1_10 = &H400                          ' Bit 10, counter #3 = comparator #3 event occurrence
Public Const QIINTBANK1_11 = &H800                          ' Bit 11, counter #3 > comparator #3 event occurrence
Public Const QIINTBANK1_12 = &H1000                         ' Bit 12, counter #4 < comparator #4 event occurrence
Public Const QIINTBANK1_13 = &H2000                         ' Bit 13, counter #4 = comparator #4 event occurrence
Public Const QIINTBANK1_14 = &H4000                         ' Bit 14, counter #4 < comparator #4 event occurrence
Public Const QIINTBANK1_15 = &H8000                         ' Bit 15, counter #5 < comparator #5 event occurrence
Public Const QIINTBANK1_16 = &H10000                        ' Bit 16, counter #5 = comparator #5 event occurrence
Public Const QIINTBANK1_17 = &H20000                        ' Bit 17, counter #5 > comparator #5 event occurrence
Public Const QIINTBANK1_18 = &H40000                        ' Bit 18, timer #1 event occurrence
Public Const QIINTBANK1_19 = &H80000                        ' Bit 19, timer #2 event occurrence
Public Const QIINTBANK1_20 = &H100000                       ' Bit 20, drive reservation setting Queue is cleared
Public Const QIINTBANK1_21 = &H200000                       ' Bit 21, drive reservation setting Queue is full
Public Const QIINTBANK1_22 = &H400000                       ' Bit 22, trigger occurring distance period/absolute position Queue is cleared
Public Const QIINTBANK1_23 = &H800000                       ' Bit 23, trigger occurring distance period/absolute position Queue is full
Public Const QIINTBANK1_24 = &H1000000                      ' Bit 24, trigger signal occurrence event
Public Const QIINTBANK1_25 = &H2000000                      ' Bit 25, script #1 command reservation setting Queue is cleared
Public Const QIINTBANK1_26 = &H4000000                      ' Bit 26, script #2 command reservation setting Queue is cleared
Public Const QIINTBANK1_27 = &H8000000                      ' Bit 27, script #3 initialized with execution of command reservation setting register
Public Const QIINTBANK1_28 = &H10000000                     ' Bit 28, script #4 initialized with execution of command reservation setting register
Public Const QIINTBANK1_29 = &H20000000                     ' Bit 29, servo alarm signal is permitted
Public Const QIINTBANK1_30 = &H40000000                     ' Bit 30, |CNT1| - |CNT2| >= |CNT4| event occurrence
Public Const QIINTBANK1_31 = &H80000000                     ' Bit 31, interrupt occurrence command |INTGEN| execution
' Define Motion QI Interrupt MASK2
Public Const QIINTBANK2_DISABLE = &H0                       ' INTERRUT DISABLED.
Public Const QIINTBANK2_0 = &H1                             ' Bit 0,  script #1 reading command result Queue is full
Public Const QIINTBANK2_1 = &H2                             ' Bit 1,  script #2 reading command result Queue is full
Public Const QIINTBANK2_2 = &H4                             ' Bit 2,  script #3 reading command result register is renewed with new data
Public Const QIINTBANK2_3 = &H8                             ' Bit 3,  script #4 reading command result register is renewed with new data
Public Const QIINTBANK2_4 = &H10                            ' Bit 4,  when reservation command of script #1 is executed, command set by interrupt occurrence is executed
Public Const QIINTBANK2_5 = &H20                            ' Bit 5,  when reservation command of script #2 is executed, command set by interrupt occurrence is executed
Public Const QIINTBANK2_6 = &H40                            ' Bit 6,  when reservation command of script #3 is executed, command set by interrupt occurrence is executed
Public Const QIINTBANK2_7 = &H80                            ' Bit 7,  when reservation command of script #4 is executed, command set by interrupt occurrence is executed
Public Const QIINTBANK2_8 = &H100                           ' Bit 8,  start drive
Public Const QIINTBANK2_9 = &H200                           ' Bit 9,  drive using servo position determination completion(InPos) function, exit condition occurrence
Public Const QIINTBANK2_10 = &H400                          ' Bit 10, event selection #1 condition occurrence to use during event counter operation
Public Const QIINTBANK2_11 = &H800                          ' Bit 11, event selection #2 condition occurrence to use during event counter operation
Public Const QIINTBANK2_12 = &H1000                         ' Bit 12, SQSTR1 signal is permitted
Public Const QIINTBANK2_13 = &H2000                         ' Bit 13, SQSTR2 signal is permitted
Public Const QIINTBANK2_14 = &H4000                         ' Bit 14, UIO0 terminal signal is changed to '1'
Public Const QIINTBANK2_15 = &H8000                         ' Bit 15, UIO1 terminal signal is changed to '1'
Public Const QIINTBANK2_16 = &H10000                        ' Bit 16, UIO2 terminal signal is changed to '1'
Public Const QIINTBANK2_17 = &H20000                        ' Bit 17, UIO3 terminal signal is changed to '1'
Public Const QIINTBANK2_18 = &H40000                        ' Bit 18, UIO4 terminal signal is changed to '1'
Public Const QIINTBANK2_19 = &H80000                        ' Bit 19, UIO5 terminal signal is changed to '1'
Public Const QIINTBANK2_20 = &H100000                       ' Bit 20, UIO6 terminal signal is changed to '1'
Public Const QIINTBANK2_21 = &H200000                       ' Bit 21, UIO7 terminal signal is changed to '1'
Public Const QIINTBANK2_22 = &H400000                       ' Bit 22, UIO8 terminal signal is changed to '1'
Public Const QIINTBANK2_23 = &H800000                       ' Bit 23, UIO9 terminal signal is changed to '1'
Public Const QIINTBANK2_24 = &H1000000                      ' Bit 24, UIO10 terminal signal is changed to '1'
Public Const QIINTBANK2_25 = &H2000000                      ' Bit 25, UIO11 terminal signal is changed to '1'
Public Const QIINTBANK2_26 = &H4000000                      ' Bit 26, error stop condition (LMT, ESTOP, STOP, ESTOP, CMD, ALARM) occurrence
Public Const QIINTBANK2_27 = &H8000000                      ' Bit 27, ata setting error is occurred during interpolation
Public Const QIINTBANK2_28 = &H10000000                     ' Bit 28, Don't Care
Public Const QIINTBANK2_29 = &H20000000                     ' Bit 29, limit signal (PELM, NELM) is inputted
Public Const QIINTBANK2_30 = &H40000000                     ' Bit 30, additional limit signal (PSLM, NSLM) is inputted
Public Const QIINTBANK2_31 = &H80000000                     ' Bit 31, emergency stop signal (ESTOP) is input

' Network Status
Public Const NET_STATUS_DISCONNECTED = 1
Public Const NET_STATUS_LOCK_MISMATCH = 5
Public Const NET_STATUS_CONNECTED = 6
' Motion(QI) Override Condition
Public Const OVERRIDE_POS_START = 0
Public Const OVERRIDE_POS_END = 1
' Motion(QI) Profile Priority
Public Const PRIORITY_VELOCITY = 0
Public Const PRIORITY_ACCELTIME = 1
' Function Return Type Define
Public Const FUNC_RETURN_IMMEDIATE = 0
Public Const FUNC_RETURN_BLOCKING = 1
Public Const FUNC_RETURN_NON_BLOCKING = 2
' Max alarm history count
Public Const MAX_SERVO_ALARM_HISTORY = 15

' Counter Module Define
Public Const F_50M_CLK = 50000000

Public Const CnCommand = &H10
Public Const CnData1 = &H12
Public Const CnData2 = &H14
Public Const CnData3 = &H16
Public Const CnData4 = &H18
Public Const CnData12 = &H44
Public Const CnData34 = &H46

Public Const CnRamAddr1 = &H28
Public Const CnRamAddr2 = &H2A
Public Const CnRamAddr3 = &H2C
Public Const CnRamAddrx1 = &H48
Public Const CnRamAddr23 = &H4A

Public Const CnAbPhase = 0
Public Const CnZPhase = 1

Public Const CnUpDownMode = 0
Public Const CnSqr1Mode = 1
Public Const CnSqr2Mode = 2
Public Const CnSqr4Mode = 3

' CH-1 Group Register
Public Const CnCh1CounterRead = &H10                        ' CH1 COUNTER READ, 24BIT
Public Const CnCh1CounterWrite = &H90                       ' CH1 COUNTER WRITE
Public Const CnCh1CounterModeRead = &H11                    ' CH1 COUNTER MODE READ, 8BIT
Public Const CnCh1CounterModeWrite = &H91                   ' CH1 COUNTER MODE WRITE
Public Const CnCh1TriggerRegionLowerDataRead = &H12         ' CH1 TRIGGER REGION LOWER DATA READ, 24BIT
Public Const CnCh1TriggerRegionLowerDataWrite = &H92        ' CH1 TRIGGER REGION LOWER DATA WRITE
Public Const CnCh1TriggerRegionUpperDataRead = &H13         ' CH1 TRIGGER REGION UPPER DATA READ, 24BIT
Public Const CnCh1TriggerRegionUpperDataWrite = &H93        ' CH1 TRIGGER REGION UPPER DATA WRITE
Public Const CnCh1TriggerPeriodRead = &H14                  ' CH1 TRIGGER PERIOD READ, 24BIT, RESERVED
Public Const CnCh1TriggerPeriodWrite = &H94                 ' CH1 TRIGGER PERIOD WRITE
Public Const CnCh1TriggerPulseWidthRead = &H15              ' CH1 TRIGGER PULSE WIDTH READ
Public Const CnCh1TriggerPulseWidthWrite = &H95             ' CH1 RIGGER PULSE WIDTH WRITE
Public Const CnCh1TriggerModeRead = &H16                    ' CH1 TRIGGER MODE READ
Public Const CnCh1TriggerModeWrite = &H96                   ' CH1 RIGGER MODE WRITE
Public Const CnCh1TriggerStatusRead = &H17                  ' CH1 TRIGGER STATUS READ
Public Const CnCh1NoOperation_97 = &H97
Public Const CnCh1TriggerEnable = &H98
Public Const CnCh1TriggerDisable = &H99
Public Const CnCh1TimeTriggerFrequencyRead = &H1A
Public Const CnCh1TimeTriggerFrequencyWrite = &H9A
Public Const CnCh1ComparatorValueRead = &H1B
Public Const CnCh1ComparatorValueWrite = &H9B
Public Const CnCh1CompareatorConditionRead = &H1D
Public Const CnCh1CompareatorConditionWrite = &H9D

' CH-2 Group Register
Public Const CnCh2CounterRead = &H20                        ' CH2 COUNTER READ, 24BIT
Public Const CnCh2CounterWrite = &HA1                       ' CH2 COUNTER WRITE
Public Const CnCh2CounterModeRead = &H21                    ' CH2 COUNTER MODE READ, 8BIT
Public Const CnCh2CounterModeWrite = &HA1                   ' CH2 COUNTER MODE WRITE
Public Const CnCh2TriggerRegionLowerDataRead = &H22         ' CH2 TRIGGER REGION LOWER DATA READ, 24BIT
Public Const CnCh2TriggerRegionLowerDataWrite = &HA2        ' CH2 TRIGGER REGION LOWER DATA WRITE
Public Const CnCh2TriggerRegionUpperDataRead = &H23         ' CH2 TRIGGER REGION UPPER DATA READ, 24BIT
Public Const CnCh2TriggerRegionUpperDataWrite = &HA3        ' CH2 TRIGGER REGION UPPER DATA WRITE
Public Const CnCh2TriggerPeriodRead = &H24                  ' CH2 TRIGGER PERIOD READ, 24BIT, RESERVED
Public Const CnCh2TriggerPeriodWrite = &HA4                 ' CH2 TRIGGER PERIOD WRITE
Public Const CnCh2TriggerPulseWidthRead = &H25              ' CH2 TRIGGER PULSE WIDTH READ, 24BIT
Public Const CnCh2TriggerPulseWidthWrite = &HA5             ' CH2 RIGGER PULSE WIDTH WRITE
Public Const CnCh2TriggerModeRead = &H26                    ' CH2 TRIGGER MODE READ
Public Const CnCh2TriggerModeWrite = &HA6                   ' CH2 RIGGER MODE WRITE
Public Const CnCh2TriggerStatusRead = &H27                  ' CH2 TRIGGER STATUS READ
Public Const CnCh2NoOperation_A7 = &HA7
Public Const CnCh2TriggerEnable = &HA8
Public Const CnCh2TriggerDisable = &HA9
Public Const CnCh2TimeTriggerFrequencyRead = &H2A
Public Const CnCh2TimeTriggerFrequencyWrite = &HAA
Public Const CnCh2ComparatorValueRead = &H2B
Public Const CnCh2ComparatorValueWrite = &HAB
Public Const CnCh2CompareatorConditionRead = &H2D
Public Const CnCh2CompareatorConditionWrite = &HAD

' Ram Access Group Register
Public Const CnRamDataWithRamAddress = &H30                 ' READ RAM DATA WITH RAM ADDR PORT ADDRESS
Public Const CnRamDataWrite = &HB0                          ' RAM DATA WRITE
Public Const CnRamDataRead = &H31                           ' RAM DATA READ, 32BIT' HPCPort Data WRITE
Public Const HpcReset = &H6                     ' Software reset.
Public Const HpcCommand = &H10
Public Const HpcData12 = &H12                    ' MSB of data port(31 ~ 16 bit)
Public Const HpcData34 = &H14                    ' LSB of data port(15 ~ 0 bit)
Public Const HpcCmStatus = &H1C

' HPCPort Channel STATUS
Public Const HpcCh1Mech = &H20
Public Const HpcCh1Status = &H22
Public Const HpcCh2Mech = &H30
Public Const HpcCh2Status = &H32
Public Const HpcCh3Mech = &H40
Public Const HpcCh3Status = &H42
Public Const HpcCh4Mech = &H50
Public Const HpcCh4Status = &H52

' HPCPort ETC
Public Const HpcDiIntFlag = &H60
Public Const HpcDiIntRiseMask = &H62
Public Const HpcDiIntFallMask = &H64
Public Const HpcCompIntFlag = &H66
Public Const HpcCompIntMask = &H68
Public Const HpcDinData = &H6A
Public Const HpcDoutData = &H6C

' HPCRAM data
Public Const HpcRamAddr1 = &H70                   ' MSB of Ram address(31  ~ 16 bit)
Public Const HpcRamAddr2 = &H72                   ' LSB of Ram address(15  ~ 0 bit)

' CNT COMMAND LIST
Public Const HpcCh1CounterRead = &H10                                  ' CH1 COUNTER READ, 32BIT
Public Const HpcCh1CounterWrite = &H90                                 ' CH1 COUNTER WRITE, 32BIT
Public Const HpcCh1CounterModeRead = &H11                              ' CH1 COUNTER MODE READ, 4BIT
Public Const HpcCh1CounterModeWrite = &H91                             ' CH1 COUNTER MODE WRITE, 4BIT
Public Const HpcCh1TriggerRegionLowerDataRead = &H12                   ' CH1 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh1TriggerRegionLowerDataWrite = &H92                  ' CH1 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh1TriggerRegionUpperDataRead = &H13                   ' CH1 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh1TriggerRegionUpperDataWrite = &H93                  ' CH1 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh1TriggerPeriodRead = &H14                            ' CH1 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh1TriggerPeriodWrite = &H94                           ' CH1 TRIGGER PERIOD WRITE
Public Const HpcCh1TriggerPulseWidthRead = &H15                        ' CH1 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh1TriggerPulseWidthWrite = &H95                       ' CH1 RIGGER PULSE WIDTH WRITE
Public Const HpcCh1TriggerModeRead = &H16                              ' CH1 TRIGGER MODE READ, 8BIT
Public Const HpcCh1TriggerModeWrite = &H96                             ' CH1 RIGGER MODE WRITE                 <<<<<<<<<<<<<<<<<<<<<<<<<  20160527 ������� �۾�
Public Const HpcCh1TriggerStatusRead = &H17                            ' CH1 TRIGGER STATUS READ, 8BIT
Public Const HpcCh1NoOperation_97 = &H97                               ' Reserved.
Public Const HpcCh1NoOperation_18 = &H17                               ' Reserved.
Public Const HpcCh1TriggerEnable = &H98                                ' CH1 TRIGGER ENABLE.
Public Const HpcCh1NoOperation_19 = &H19                               ' Reserved.
Public Const HpcCh1TriggerDisable = &H99                               ' CH1 TRIGGER DISABLE.
Public Const HpcCh1TimeTriggerFrequencyRead = &H1A                     ' CH1 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh1TimeTriggerFrequencyWrite = &H9A                    ' CH1 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh1Comparator1ValueRead = &H1B                         ' CH1 COMPAREATOR1 READ, 31BIT
Public Const HpcCh1Comparator1ValueWrite = &H9B                        ' CH1 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh1Comparator2ValueRead = &H1C                         ' CH1 COMPAREATOR2 READ, 31BIT
Public Const HpcCh1Comparator2ValueWrite = &H9C                        ' CH1 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh1CompareatorConditionRead = &H1D                     ' CH1 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh1CompareatorConditionWrite = &H9D                    ' CH1 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh1AbsTriggerTopPositionRead = &H1E                    ' CH1 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh1AbsTriggerPositionWrite = &H9E                      ' CH1 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh1AbsTriggerFifoStatusRead = &H1F                     ' CH1 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh1AbsTriggerPositionClear = &H9F                      ' CH1 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-2 Group Register
Public Const HpcCh2CounterRead = &H20                                  ' CH2 COUNTER READ, 32BIT
Public Const HpcCh2CounterWrite = &HA0                                 ' CH2 COUNTER WRITE, 32BIT
Public Const HpcCh2CounterModeRead = &H21                              ' CH2 COUNTER MODE READ, 4BIT
Public Const HpcCh2CounterModeWrite = &HA1                             ' CH2 COUNTER MODE WRITE, 4BIT
Public Const HpcCh2TriggerRegionLowerDataRead = &H22                   ' CH2 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh2TriggerRegionLowerDataWrite = &HA2                  ' CH2 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh2TriggerRegionUpperDataRead = &H23                   ' CH2 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh2TriggerRegionUpperDataWrite = &HA3                  ' CH2 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh2TriggerPeriodRead = &H24                            ' CH2 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh2TriggerPeriodWrite = &HA4                           ' CH2 TRIGGER PERIOD WRITE
Public Const HpcCh2TriggerPulseWidthRead = &H25                        ' CH2 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh2TriggerPulseWidthWrite = &HA5                       ' CH2 RIGGER PULSE WIDTH WRITE
Public Const HpcCh2TriggerModeRead = &H26                              ' CH2 TRIGGER MODE READ, 8BIT
Public Const HpcCh2TriggerModeWrite = &HA6                             ' CH2 RIGGER MODE WRITE
Public Const HpcCh2TriggerStatusRead = &H27                            ' CH2 TRIGGER STATUS READ, 8BIT
Public Const HpcCh2NoOperation_97 = &HA7                               ' Reserved.
Public Const HpcCh2NoOperation_18 = &H27                               ' Reserved.
Public Const HpcCh2TriggerEnable = &HA8                                ' CH2 TRIGGER ENABLE.
Public Const HpcCh2NoOperation_19 = &H29                               ' Reserved.
Public Const HpcCh2TriggerDisable = &HA9                               ' CH2 TRIGGER DISABLE.
Public Const HpcCh2TimeTriggerFrequencyRead = &H2A                     ' CH2 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh2TimeTriggerFrequencyWrite = &HAA                    ' CH2 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh2Comparator1ValueRead = &H2B                         ' CH2 COMPAREATOR1 READ, 31BIT
Public Const HpcCh2Comparator1ValueWrite = &HAB                        ' CH2 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh2Comparator2ValueRead = &H2C                         ' CH2 COMPAREATOR2 READ, 31BIT
Public Const HpcCh2Comparator2ValueWrite = &HAC                        ' CH2 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh2CompareatorConditionRead = &H2D                     ' CH2 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh2CompareatorConditionWrite = &HAD                    ' CH2 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh2AbsTriggerTopPositionRead = &H2E                    ' CH2 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh2AbsTriggerPositionWrite = &HAE                      ' CH2 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh2AbsTriggerFifoStatusRead = &H2F                     ' CH2 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh2AbsTriggerPositionClear = &HAF                      ' CH2 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-3 Group Register
Public Const HpcCh3CounterRead = &H30                                  ' CH3 COUNTER READ, 32BIT
Public Const HpcCh3CounterWrite = &HB0                                 ' CH3 COUNTER WRITE, 32BIT
Public Const HpcCh3CounterModeRead = &H31                              ' CH3 COUNTER MODE READ, 4BIT
Public Const HpcCh3CounterModeWrite = &HB1                             ' CH3 COUNTER MODE WRITE, 4BIT
Public Const HpcCh3TriggerRegionLowerDataRead = &H32                   ' CH3 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh3TriggerRegionLowerDataWrite = &HB2                  ' CH3 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh3TriggerRegionUpperDataRead = &H33                   ' CH3 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh3TriggerRegionUpperDataWrite = &HB3                  ' CH3 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh3TriggerPeriodRead = &H34                            ' CH3 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh3TriggerPeriodWrite = &HB4                           ' CH3 TRIGGER PERIOD WRITE
Public Const HpcCh3TriggerPulseWidthRead = &H35                        ' CH3 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh3TriggerPulseWidthWrite = &HB5                       ' CH3 RIGGER PULSE WIDTH WRITE
Public Const HpcCh3TriggerModeRead = &H36                              ' CH3 TRIGGER MODE READ, 8BIT
Public Const HpcCh3TriggerModeWrite = &HB6                             ' CH3 RIGGER MODE WRITE
Public Const HpcCh3TriggerStatusRead = &H37                            ' CH3 TRIGGER STATUS READ, 8BIT
Public Const HpcCh3NoOperation_97 = &HB7                               ' Reserved.
Public Const HpcCh3NoOperation_18 = &H37                               ' Reserved.
Public Const HpcCh3TriggerEnable = &HB8                                ' CH3 TRIGGER ENABLE.
Public Const HpcCh3NoOperation_19 = &H39                               ' Reserved.
Public Const HpcCh3TriggerDisable = &HB9                               ' CH3 TRIGGER DISABLE.
Public Const HpcCh3TimeTriggerFrequencyRead = &H3A                     ' CH3 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh3TimeTriggerFrequencyWrite = &HBA                    ' CH3 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh3Comparator1ValueRead = &H3B                         ' CH3 COMPAREATOR1 READ, 31BIT
Public Const HpcCh3Comparator1ValueWrite = &HBB                        ' CH3 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh3Comparator2ValueRead = &H3C                         ' CH3 COMPAREATOR2 READ, 31BIT
Public Const HpcCh3Comparator2ValueWrite = &HBC                        ' CH3 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh3CompareatorConditionRead = &H3D                     ' CH3 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh3CompareatorConditionWrite = &HBD                    ' CH3 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh3AbsTriggerTopPositionRead = &H3E                    ' CH3 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh3AbsTriggerPositionWrite = &HBE                      ' CH3 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh3AbsTriggerFifoStatusRead = &H3F                     ' CH3 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh3AbsTriggerPositionClear = &HBF                      ' CH3 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-4 Group Register
Public Const HpcCh4CounterRead = &H40                                  ' CH4 COUNTER READ, 32BIT
Public Const HpcCh4CounterWrite = &HC0                                 ' CH4 COUNTER WRITE, 32BIT
Public Const HpcCh4CounterModeRead = &H41                              ' CH4 COUNTER MODE READ, 4BIT
Public Const HpcCh4CounterModeWrite = &HC1                             ' CH4 COUNTER MODE WRITE, 4BIT
Public Const HpcCh4TriggerRegionLowerDataRead = &H42                   ' CH4 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh4TriggerRegionLowerDataWrite = &HC2                  ' CH4 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh4TriggerRegionUpperDataRead = &H43                   ' CH4 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh4TriggerRegionUpperDataWrite = &HC3                  ' CH4 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh4TriggerPeriodRead = &H44                            ' CH4 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh4TriggerPeriodWrite = &HC4                           ' CH4 TRIGGER PERIOD WRITE
Public Const HpcCh4TriggerPulseWidthRead = &H45                        ' CH4 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh4TriggerPulseWidthWrite = &HC5                       ' CH4 RIGGER PULSE WIDTH WRITE
Public Const HpcCh4TriggerModeRead = &H46                              ' CH4 TRIGGER MODE READ, 8BIT
Public Const HpcCh4TriggerModeWrite = &HC6                             ' CH4 RIGGER MODE WRITE
Public Const HpcCh4TriggerStatusRead = &H47                            ' CH4 TRIGGER STATUS READ, 8BIT
Public Const HpcCh4NoOperation_97 = &HC7                               ' Reserved.
Public Const HpcCh4NoOperation_18 = &H47                               ' Reserved.
Public Const HpcCh4TriggerEnable = &HC8                                ' CH4 TRIGGER ENABLE.
Public Const HpcCh4NoOperation_19 = &H49                               ' Reserved.
Public Const HpcCh4TriggerDisable = &HC9                               ' CH4 TRIGGER DISABLE.
Public Const HpcCh4TimeTriggerFrequencyRead = &H4A                     ' CH4 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh4TimeTriggerFrequencyWrite = &HCA                    ' CH4 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh4Comparator1ValueRead = &H4B                         ' CH4 COMPAREATOR1 READ, 31BIT
Public Const HpcCh4Comparator1ValueWrite = &HCB                        ' CH4 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh4Comparator2ValueRead = &H4C                         ' CH4 COMPAREATOR2 READ, 31BIT
Public Const HpcCh4Comparator2ValueWrite = &HCC                        ' CH4 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh4CompareatorConditionRead = &H4D                     ' CH4 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh4CompareatorConditionWrite = &HCD                    ' CH4 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh4AbsTriggerTopPositionRead = &H4E                    ' CH4 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh4AbsTriggerPositionWrite = &HCE                      ' CH4 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh4AbsTriggerFifoStatusRead = &H4F                     ' CH4 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh4AbsTriggerPositionClear = &HCF                      ' CH4 ABS TRIGGER POSITION FIFO CLEAR

    ' Ram Access Group Register
Public Const HpcRamDataWithRamAddress = &H51                           ' READ RAM DATA WITH RAM ADDR PORT ADDRESS
Public Const HpcRamDataWrite = &HD0                                    ' RAM DATA WRITE
Public Const HpcRamDataRead = &H50                                     ' RAM DATA READ, 32BIT

    ' Debugging Registers
Public Const HpcCh1TrigPosIndexRead = &H60                             ' CH1 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh1TrigBackwardDataRead = &H61                         ' CH1 Current RAM trigger backward position data, 32BIT
Public Const HpcCh1TrigCurrentDataRead = &H62                          ' CH1 Current RAM trigger current position data, 32BIT
Public Const HpcCh1TrigForwardDataRead = &H63                          ' CH1 Current RAM trigger next position data, 32BIT
Public Const HpcCh1TrigRamAddressRead = &H64                           ' CH1 Current RAM trigger address, 20BIT

Public Const HpcCh2TrigPosIndexRead = &H65                             ' CH2 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh2TrigBackwardDataRead = &H66                         ' CH2 Current RAM trigger backward position data, 32BIT
Public Const HpcCh2TrigCurrentDataRead = &H67                          ' CH2 Current RAM trigger current position data, 32BIT
Public Const HpcCh2TrigForwardDataRead = &H68                          ' CH2 Current RAM trigger next position data, 32BIT
Public Const HpcCh2TrigRamAddressRead = &H69                           ' CH2 Current RAM trigger address, 20BIT

Public Const HpcCh3TrigPosIndexRead = &H70                             ' CH3 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh3TrigBackwardDataRead = &H71                         ' CH3 Current RAM trigger backward position data, 32BIT
Public Const HpcCh3TrigCurrentDataRead = &H72                          ' CH3 Current RAM trigger current position data, 32BIT
Public Const HpcCh3TrigForwardDataRead = &H73                          ' CH3 Current RAM trigger next position data, 32BIT
Public Const HpcCh3TrigRamAddressRead = &H74                           ' CH3 Current RAM trigger address, 20BIT

Public Const HpcCh4TrigPosIndexRead = &H75                             ' CH4 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh4TrigBackwardDataRead = &H76                         ' CH4 Current RAM trigger backward position data, 32BIT
Public Const HpcCh4TrigCurrentDataRead = &H77                          ' CH4 Current RAM trigger current position data, 32BIT
Public Const HpcCh4TrigForwardDataRead = &H78                          ' CH4 Current RAM trigger next position data, 32BIT
Public Const HpcCh4TrigRamAddressRead = &H79                           ' CH4 Current RAM trigger address, 20BIT

Public Const HpcCh1TestEnable = &H81                                   ' CH1 test enable(Manufacturer only)
Public Const HpcCh2TestEnable = &H82                                   ' CH2 test enable(Manufacturer only)
Public Const HpcCh3TestEnable = &H83                                   ' CH3 test enable(Manufacturer only)
Public Const HpcCh4TestEnable = &H84                                   ' CH4 test enable(Manufacturer only)

Public Const HpcTestFrequency = &H8C                                   ' Test counter output frequency(32bit)
Public Const HpcTestCountStart = &H8D                                  ' Start test counter output with position(32bit signed).
Public Const HpcTestCountEnd = &H8E                                    ' End counter output.

Public Const HpcCh1TrigVectorTopDataOfFifo = &H54                      ' CH1 UnitVector X positin of FIFO top.
Public Const HpcCh1TrigVectorFifoStatus = &H55                         ' CH1 UnitVector X FIFO Status.
Public Const HpcCh2TrigVectorTopDataOfFifo = &H56                      ' CH2 UnitVector Y positin of FIFO top.
Public Const HpcCh2TrigVectorFifoStatus = &H57                         ' CH2 UnitVector Y FIFO Status.
Public Const HpcCh1TrigVectorFifoPush = &HD2                           ' CH1 UnitVector X position, fifo data push.
Public Const HpcCh2TrigVectorFifoPush = &HD3                           ' CH2 UnitVector Y position, fifo data push.