'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXA.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Analog Library Header File
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

Attribute VB_Name = "AXA"
'========== Board and verification API group of module information =================================================================================
'Verify if AIO module exists
Public Declare Function AxaInfoIsAIOModule Lib "AXL.dll" (ByRef upStatus As Long) As Long

'Verify AIO module number
Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

'Verify the number of AIO module
Public Declare Function AxaInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Long) As Long

'Verify the number of input channels of specified module
Public Declare Function AxaInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

'Verify the number of output channels of specified module
Public Declare Function AxaInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

'Verify the first channel number of specified module
Public Declare Function AxaInfoGetChannelNoOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

'Verify the first Input channel number of specified module (Inputmodule, Integration for input/output Module)
Public Declare Function AxaInfoGetChannelNoAdcOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

'Verify the first output channel number of specified module (Inputmodule, Integration for input/output Module)
Public Declare Function AxaInfoGetChannelNoDacOfModuleNo Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpChannelNo As Long) As Long

'Verify base board number, module position and module ID with specified module number
Public Declare Function AxaInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long

'Verify Module status of specified module board
Public Declare Function AxaInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

'========== API group of input module information search ====================================================================================
'Verify module number with specified input channel number
Public Declare Function AxaiInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpModuleNo As Long) As Long

'Verify the number of entire channels of analog input module
Public Declare Function AxaiInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Long) As Long

'========== API group for setting and verifying of input module interrupt ============================================================
'Use window message, callback API or event method in order to get event message into specified channel. Use for the time of collection action( refer AxaStartMultiChannelAdc ) of continuous data by H/W timer
'(Timer Trigger Mode, External Trigger Mode)
Public Declare Function AxaiEventSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal hWnd As Long, ByVal uMesssage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long

'Set whether to use event in specified input channel
'======================================================'
' uUse       : DISABLE(0)   ' Event Disable
'            : ENABLE(1)    ' Event Enable
'======================================================'
Public Declare Function AxaiEventSetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long

'Verify whether to use event in specified input channel
'======================================================'
' *upUse     : DISABLE(0)   ' Event Disable
'            : ENABLE(1)    ' Event Enable
'======================================================'
Public Declare Function AxaiEventGetChannelEnable Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long

'Set whether to use event in specified multiple input channels
'======================================================'
' uUse       : DISABLE(0)' Event Disable
'            : ENABLE(1)    ' Event Enable
'======================================================'
Public Declare Function AxaiEventSetMultiChannelEnable Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal uUse As Long) As Long

'Set kind of event in specified input channel
'======================================================'
' uMask      : DATA_EMPTY(1)
'            : DATA_MANY(2)
'            : DATA_SMALL(3)
'            : DATA_FULL(4)
'======================================================'
Public Declare Function AxaiEventSetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uMask As Long) As Long

'Verify kind of event in specified input channel
'======================================================'
' *upMask    : DATA_EMPTY(1)
'            : DATA_MANY(2)
'            : DATA_SMALL(3)
'            : DATA_FULL(4)
'======================================================'
Public Declare Function AxaiEventGetChannelMask Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upMask As Long) As Long

'Set kind of event in specified multiple input channels
'=============================================================================='
' uMask      : DATA_EMPTY(1)
'            : DATA_MANY(2)
'            : DATA_SMALL(3)
'            : DATA_FULL(4)
'=============================================================================='
Public Declare Function AxaiEventSetMultiChannelMask Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal uMask As Long) As Long

'Verify event occurrence position
'=============================================================================='
' *upMode    : AIO_EVENT_DATA_UPPER(1)
'            : AIO_EVENT_DATA_LOWER(2)
'            : AIO_EVENT_DATA_FULL(3)
'            : AIO_EVENT_DATA_EMPTY(4)
'=============================================================================='
Public Declare Function AxaiEventRead Lib "AXL.dll" (ByRef lpChannelNo As Long, ByRef upMode As Long) As Long

'Set interrupt mask of specified module. (SIO-AI4RB is not supportive.)
'=================================================================================================='
' uMask      : SCAN_END(1)
'            : FIFO_HALF_FULL(2)
'=================================================================================================='
Public Declare Function AxaiInterruptSetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uMask As Long) As Long

'Verify interrupt mask of specified module
'=================================================================================================='
' *upMask    : SCAN_END(1)
'            : FIFO_HALF_FULL(2)
'=================================================================================================='
Public Declare Function AxaiInterruptGetModuleMask Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upMask As Long) As Long

'========== API group for setting and verifying of input module parameter ========================================================================
'Set the input voltage range in specified input channel
'=================================================================================================='
' AI4RB
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AI16Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaiSetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

'Verify the input voltage range in specified input channel
'=================================================================================================='
' AI4RB
' *dpMinVolt  : -10V/-5V/0V
' *dpMaxVolt  : 10V/5V/
'
' AI16Hx
' *dpMaxVolt  : -10V Fix
' *dpMaxVolt  : 10V Fix
'=================================================================================================='
Public Declare Function AxaiGetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Long

'Set the allowed input voltage range in specified multiple input Modules
'==================================================================================================//
' lModuleNo   : Analog Module Number
'
' RTEX AI16F
' Mode -5~+5  : dMinVolt = -5, dMaxVolt = +5
' Mode -10~+10: dMinVolt = -10, dMaxVolt = +10
'==================================================================================================//
Public Declare Function AxaiSetRangeModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

'Verify the input voltage range in specified input Module
'==================================================================================================//
' lModuleNo   : Analog Module Number
'
' RTEX AI16F
' *dMinVolt   : -5V, -10V
' *dMaxVolt   : +5V, +10V
'==================================================================================================//
Public Declare Function AxaiGetRangeModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dMinVolt As Double, ByRef dMaxVolt As Double) As Long

'Set the allowed input voltage range in specified multiple input channels
'=================================================================================================='
' AI4RB
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AI16Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaiSetMultiRange Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

'Set trigger mode in the specified input module
'=================================================================================================='
' uTriggerMode: NORMAL_MODE(1) 
'             : TIMER_MODE(2)
'             : EXTERNAL_MODE(3)
'=================================================================================================='
Public Declare Function AxaiSetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uTriggerMode As Long) As Long

'Verify trigger mode in the specified input module
'=================================================================================================='
' *upTriggerMode : NORMAL_MODE(1)
'                : TIMER_MODE(2)
'                : EXTERNAL_MODE(3)
'=================================================================================================='
Public Declare Function AxaiGetTriggerMode Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upTriggerMode As Long) As Long

'Set offset of specified input module by mVolt (mV) unit. Max -100~100mVolt
'=================================================================================================='
' dMiliVolt      : -100 ~ 100 
'=================================================================================================='
Public Declare Function AxaiSetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dMiliVolt As Double) As Long

'Verify offset value of specified input module. mVolt unit(mV)
'=================================================================================================='
' *dpMiliVolt    : -100 ~ 100 
'=================================================================================================='
Public Declare Function AxaiGetModuleOffsetValue Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dpMiliVolt As Double) As Long 

'========== Software Timer (Normal Trigger Mode) group =======================================================================================
'Software Trigger Mode API, Convert analog input value to A/D in the specified input channel by user , then return it in voltage value
Public Declare Function AxaiSwReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpVolt As Double) As Long

'Software Trigger Mode API, Return analog input value in digit value to specified input channel
Public Declare Function AxaiSwReadDigit Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upDigit As Long) As Long

'Software Trigger Mode API, Return analog input value in voltage value to specified multiple input channels
Public Declare Function AxaiSwReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef dpVolt As Double) As Long

'Software Trigger Mode API, Return analog input value in digit value to specified multiple input channels
Public Declare Function AxaiSwReadMultiDigit Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef upDigit As Long) As Long

'========== Hardware Timer (Timer Trigger Mode + External Trigger Mode) group =======================================================================================
'Hardware Trigger Mode API, Set setting value in order to use immediate mode in specified multiple channels
Public Declare Function AxaiHwSetMultiAccess Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef lpWordSize As Long) As Long

'Hardware Trigger Mode API, Convert A/D as much as number of specified, then return the voltage value
Public Declare Function AxaiHwStartMultiAccess Lib "AXL.dll" (ByRef dpBuffer As Double) As Long

'Set sampling interval to specified module by frequency unit(Hz)
'=================================================================================================='
' dSampleFreq    : 10 ~ 100000 
'=================================================================================================='
Public Declare Function AxaiHwSetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dSampleFreq As Double) As Long

'Verify the setting value of sampling interval to specified module by frequency unit(Hz)
'=================================================================================================='
' *dpSampleFreq  : 10 ~ 100000 
'=================================================================================================='
Public Declare Function AxaiHwGetSampleFreq Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dpSampleFreq As Double) As Long

'Set sampling interval to specified module by time unit (uSec)
'=================================================================================================='
' dSamplePeriod  : 100000 ~ 1000000000
'=================================================================================================='
Public Declare Function AxaiHwSetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dSamplePeriod As Double) As Long

'Verify setting value of sampling interval to specified module by time unit(uSec)
'=================================================================================================='
' *dpSamplePeriod : 100000 ~ 1000000000
'=================================================================================================='
Public Declare Function AxaiHwGetSamplePeriod Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dpSamplePeriod As Double) As Long

'Set control method when the buffer is full in specified input channel
'=================================================================================================='
' uFullMode    : NEW_DATA_KEEP(0)
'              : CURR_DATA_KEEP(1)
'=================================================================================================='
Public Declare Function AxaiHwSetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uFullMode As Long) As Long

'Verify control method when the buffer is full in specified input channel
'=================================================================================================='
' *upFullMode  : NEW_DATA_KEEP(0)
'              : CURR_DATA_KEEP(1)
'=================================================================================================='
Public Declare Function AxaiHwGetBufferOverflowMode Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upFullMode As Long) As Long

'control method when the buffer is full in specified multiple input channels
'=================================================================================================='
' uFullMode    : NEW_DATA_KEEP(0)
'              : CURR_DATA_KEEP(1)
'=================================================================================================='
Public Declare Function AxaiHwSetMultiBufferOverflowMode Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal uFullMode As Long) As Long

'Set the upper limit and lower limit of buffer in specified input channel
Public Declare Function AxaiHwSetLimit Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal lLowLimit As Long, ByVal lUpLimit As Long) As Long

'Verify the upper limit and lower limit of buffer in specified input channel
Public Declare Function AxaiHwGetLimit Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpLowLimit As Long, ByRef lpUpLimit As Long) As Long

'Set the upper limit and lower limit of buffer in multiple input channels
Public Declare Function AxaiHwSetMultiLimit Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal lLowLimit As Long, ByVal lUpLimit As Long) As Long

'Start A/D conversion using H/W timer in specified multiple channels
Public Declare Function AxaiHwStartMultiChannel Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal lBuffSize As Long) As Long

'After starting of A/D conversion in specified multiple channels, manage filtering as much as specified and return into voltage
Public Declare Function AxaiHwStartMultiFilter Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal lFilterCount As Long, ByVal lBuffSize As Long) As Long

'Stop continuous signal A/D conversion used H/W timer
Public Declare Function AxaiHwStopMultiChannel Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

'Inspect the numbers of data in memory buffer of specified input channel
Public Declare Function AxaiHwReadDataLength Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpDataLength As Long) As Long

'Read A/D conversion data used H/W timer in specified input channel by voltage value
Public Declare Function AxaiHwReadSampleVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpCount As Long, ByRef dpVolt As Double) As Long

'Read A/D conversion data used H/W timer in specified input channel by digit value
Public Declare Function AxaiHwReadSampleDigit Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpCount As Long, ByRef upDigit As Long) As Long

'========== API group of input module state check ===================================================================================
'Inspect if there is no data in memory buffer of specified input channel
'=================================================================================================='
' *upEmpty     : FALSE(0)
'              : TRUE(1)
'=================================================================================================='
Public Declare Function AxaiHwIsBufferEmpty Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upEmpty As Long) As Long

'Inspect if the data is more than the upper limit specified in memory buffer of specified input channel
'=================================================================================================='
' *upUpper     : FALSE(0)
'              : TRUE(1)
'=================================================================================================='
Public Declare Function AxaiHwIsBufferUpper Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUpper As Long) As Long

'Inspect if the data is less than the upper limit specified in memory buffer of specified input channel
'=================================================================================================='
' *upLower     : FALSE(0)
'              : TRUE(1)
'=================================================================================================='
Public Declare Function AxaiHwIsBufferLower Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upLower As Long) As Long

'==External Trigger Mode Function
Public Declare Function AxaiExternalStartADC Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lSize As Long, ByRef lpChannelPos As Long) As Long
Public Declare Function AxaiExternalStopADC Lib "AXL.dll" (ByVal lModuleNo As Long) As Long
    '=================================================================================================='
    ' upStatus         : FIFO_DATA_EXIST(0)
    '                  : FIFO_DATA_EMPTY(1)
    '                  : FIFO_DATA_HALF(2)
    '                  : FIFO_DATA_FULL(6)
    '=================================================================================================='
Public Declare Function AxaiExternalReadFifoStatus Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upStatus As Long) As Long
Public Declare Function AxaiExternalReadVoltage Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lSize As Long, ByRef lpChannelPos As Long, ByVal lDataSize As Long, ByVal lBuffSize As Long, ByVal lStartDataPos As Long, ByRef dpVolt As Double, ByRef lpRetDataSize As Long, ByRef upStatus As Long) As Long

'========== API group of output module information search ========================================================================================
'Verify module number with specified output channel number
Public Declare Function AxaoInfoGetModuleNoOfChannelNo Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef lpModuleNo As Long) As Long

'Verify entire number of channel of analog output module
Public Declare Function AxaoInfoGetChannelCount Lib "AXL.dll" (ByRef lpChannelCount As Long) As Long

'========== API group for output module setting and verification ========================================================================================
'Set output voltage range in specified output channel
'=================================================================================================='
' AO4R
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AO2Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaoSetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

'Verify output voltage range in specified output channel
'=================================================================================================='
' AO4R
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AO2Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaoGetRange Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpMinVolt As Double, ByRef dpMaxVolt As Double) As Long

'Set output voltage range in specified multiple output channels
'=================================================================================================='
' AO4R
' dMinVolt    : -10V/-5V/0V
' dMaxVolt    : 10V/5V/
'
' AO2Hx
' dMinVolt    : -10V Fix
' dMaxVolt    : 10V Fix
'=================================================================================================='
Public Declare Function AxaoSetMultiRange Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByVal dMinVolt As Double, ByVal dMaxVolt As Double) As Long

'The Input voltage is output in specified output channel
Public Declare Function AxaoWriteVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dVolt As Double) As Long

'The Input voltage is output in specified multiple output channel
Public Declare Function AxaoWriteMultiVoltage Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef dpVolt As Double) As Long

'Verify voltage which is output in specified output channel
Public Declare Function AxaoReadVoltage Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dpVolt As Double) As Long

'Verify voltage which is output in specified multiple output channels
Public Declare Function AxaoReadMultiVoltage Lib "AXL.dll" (ByVal lSize As Long, ByRef lpChannelNo As Long, ByRef dpVolt As Double) As Long
