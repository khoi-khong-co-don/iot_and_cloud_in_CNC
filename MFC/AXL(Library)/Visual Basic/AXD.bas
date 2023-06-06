'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXD.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Digital Library Header File
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

Attribute VB_Name = "AXD"

'========== Board and module information =================================================================================

' Verify if DIO module exists
Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Long) As Long

' Verify DIO in/output module number
Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

' Verify the number of DIO in/output module
Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Long) As Long

' Verify the number of input contacts of specified module
Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

' Verify the number of output contacts of specified module
Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpCount As Long) As Long

' Verify the base board number, module position and module ID with specified module number
Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef lpBoardNo As Long, ByRef lpModulePos As Long, ByRef upModuleID As Long) As Long

Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Long) As Long

'========== Verification group for input interrupt setting =================================================================================
' Use window message, callback API or event method in order to get interrupt message into specified module
Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal hWnd As Long, ByVal uMessage As Long, ByVal pProc As Long, ByRef pEvent As Long) As Long

' Set whether to use interrupt of specified module
'======================================================'
' uUse       : DISABLE(0)   ' Interrupt Disable
'            : ENABLE(1)    ' Interrupt Enable
'======================================================'
Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long

' Verify whether to use interrupt of specified module
'======================================================'
' *upUse     : DISABLE(0)   ' Interrupt Disable
'            : ENABLE(1)    ' Interrupt Enable
'======================================================'
Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long

' Verify the position interrupt occurred
Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Long, ByRef upFlag As Long) As Long

'========== Input interrupt rising / Verification group for setting of interrupt occurrence in falling edge =================================================================================

' Set the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' Set the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FF 
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' Set the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFF 
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' Set the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' Verify the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' Verify the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' Verify the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' Verify the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

' Set the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' uValue     : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Long, ByVal uMode As Long, ByVal uValue As Long) As Long

' Verify the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
'==============================================================================================='
' uMode      : DOWN_EDGE(0)
'            : UP_EDGE(1)
' *upValue   : DISABLE(0)
'            : ENABLE(1)
'==============================================================================================='
Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Long, ByVal uMode As Long, ByRef upValue As Long) As Long

'========== Verification group of input / output signal level setting =================================================================================

' Set data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by word unit in Offset position of specified input contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Verify data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Verify data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' *upLevel   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Verify data level by word unit in Offset position of specified input contact module
'==============================================================================================='
' *upLevel   : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Verify data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' *upLevel   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Set data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Verify data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' *upLevel   : LOW(0)
'            : HIGH(1)
'===============================================================================================' 
Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upLevel As Long) As Long


' Set data level by bit unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by byte unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by word unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by double word unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Verify data level by bit unit in Offset position of specified output contact module
'==============================================================================================='
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Verify data level by byte unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Verify data level by word unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Verify data level by double word unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upLevel As Long) As Long

' Set data level by bit unit in Offset position of entire output contact module
'==============================================================================================='
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Verify data level by bit unit in Offset position of entire output contact module
'==============================================================================================='
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upLevel As Long) As Long


'========== Input / Output signal reading / writing =================================================================================

' Output data by bit unit in Offset position of entire output contact module
'==============================================================================================='
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by bit unit in Offset position of specified output contact module
'==============================================================================================='
' uLevel     : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by byte unit in Offset position of specified output contact module
'==============================================================================================='
' uValue     : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by word unit in Offset position of specified output contact module
'==============================================================================================='
' uValue     : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by double word unit in Offset position of specified output contact module
'==============================================================================================='
' uValue     : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Read data by bit unit in Offset position of entire output contact module
'==============================================================================================='
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data by bit unit in Offset position of specified output contact module
'==============================================================================================='
' *upLevel   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data by byte unit in Offset position of specified output contact module
'==============================================================================================='
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data by word unit in Offset position of specified output contact module
'==============================================================================================='
' *upValue   : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data by double word unit in Offset position of specified output contact module
'==============================================================================================='
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by bit unit in Offset position of entire input contact module
'==============================================================================================='
' *upValue   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by bit unit in Offset position of specified input contact module
'==============================================================================================='
' *upValue   : LOW(0)
'            : HIGH(1)
'==============================================================================================='
Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by byte unit in Offset position of specified input contact module
'==============================================================================================='
' *upValue   : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by wordt unit in Offset position of specified input contact module
'==============================================================================================='
' *upValue   : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by double word unit in Offset position of specified input contact module
'==============================================================================================='
' *upValue   : 0x00 ~ 0x0FFFFFFFF
'==============================================================================================='
Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

'== Only for MLII, M-Systems DIO(R7 series)
' Read data level by bit unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input index.(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by byte unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by byte unit between input index.(0~1)
' *upValue    : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by word unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by word unit between input index.(0)
' *upValue    : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by double word unit in Offset position of specified extended input contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : offset position by dword unit between input index.(0)
' *upValue    : 0x00 ~ 0x00000FFFF
'==============================================================================================='
Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by bit unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between output index.(0~15)
' *upValue    : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by byte unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between output index.(0~1)
' *upValue    : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between output index.(0)
' *upValue    : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Read data level by double word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between output index.(0)
' *upValue    : 0x00 ~ 0x0000FFFF
'==============================================================================================='
Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Output data by bit unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between output index.(0~15)
' uValue      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by byte unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between output index.(0~1)
' uValue      : 0x00 ~ 0x0FF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by word unit in Offset position of specified extended output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between output index.(0~1)
' uValue      : 0x00 ~ 0x0FFFF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Output data by dword unit in Offset position of specified extended output contact module
'==============================================================================================/'
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between output index.(0)
' uValue    : 0x00 ~ 0x00000FFFF
'==============================================================================================='
Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uValue As Long) As Long

' Set data level by bit unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input/output index.(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by byte unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between input/output index.(0~1)
' uLevel      : 0x00 ~ 0xFF
'==============================================================================================='
Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by word unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between input/output index.(0)
' uLevel      : 0x00 ~ 0xFFFF
'==============================================================================================='
Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Set data level by dword unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between input/output index.(0)
' uLevel      : 0x00 ~ 0x0000FFFF
'==============================================================================================='
Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uLevel As Long) As Long

' Verify data level by bit unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by bit unit between input/output index.(0~15)
' uLevel      : LOW(0)
'             : HIGH(1)
'==============================================================================================='
Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

' Verify data level by byte unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by byte unit between input/output index.(0~1)
' uLevel      : 0x00 ~ 0xFF
'==============================================================================================='
Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

' Verify data level by word unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by word unit between input/output index.(0)
' uLevel      : 0x00 ~ 0xFFFF
'==============================================================================================='
Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

' Verify data level by dword unit in Offset position of specified extended input/output contact module
'==============================================================================================='
' lModuleNo   : Module number
' lOffset     : Offset position by dword unit between input/output index.(0)
' uLevel      : 0x00 ~ 0x0000FFFF
'==============================================================================================='
Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal upLevel As Long) As Long

'========== Advanced API =================================================================================

' Verify if the signal was switched from Off to On in Offset position of specified input contact module
'==============================================================================================='
' *upValue   : FALSE(0)
'            : TRUE(1)
'==============================================================================================='
Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Verify if the signal was switched from On to Off in Offset position of specified input contact module
'==============================================================================================='
' *upValue   : FALSE(0)
'            : TRUE(1)
'==============================================================================================='
Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long

' Verify if the signal is maintained On state during the calling time as much as count in Offset position of specified input contact module
'==============================================================================================='
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' *upValue   : FALSE(0)
'            : TRUE(1)
' lStart     : 1
'            : 0
'==============================================================================================='
Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lCount As Long, ByRef upValue As Long, ByVal lStart As Long) As Long

' Verify if the signal is maintained Off state during the calling time as much as count in Offset position of specified input contact module
'==============================================================================================='
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' *upValue   : FALSE(0)
'            : TRUE(1)
' lStart     : 1
'            : 0
'==============================================================================================='
Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lCount As Long, ByRef upValue As Long, ByVal lStart As Long) As Long

' Maintain On state during mSec set in Offset position of specified output contact module, then turns Off
'==============================================================================================='
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' lmSec      : 1 ~ 30000
'==============================================================================================='
Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lmSec As Long) As Long

' Maintain Off state during mSec set in Offset position of specified output contact module, then turns On
'==============================================================================================='
' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
' lmSec      : 1 ~ 30000
'==============================================================================================='
Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lmSec As Long) As Long

' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
'==============================================================================================='
' lInitState : Off(0)
'            : On(1)
' lmSecOn    : 1 ~ 30000
' lmSecOff   : 1 ~ 30000
' lCount     : 1 ~ 0x7FFFFFFF(2147483647)
'            : -1
'==============================================================================================='
Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal lInitState As Long, ByVal lmSecOn As Long, ByVal lmSecOff As Long, ByVal lCount As Long) As Long

' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
'==============================================================================================='
' uOnOff     : Off(0)
'            : On(1)
'==============================================================================================='
Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByVal uOnOff As Long) As Long

' In disconnect cases Set output status of specified module by byte.
'==============================================================================================='
' lModuleNo   : Module number
' dwSize      : Set Byte Number(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
' dwaSetValue : Set Value(Default는 Network 끊어 지기 전 상태 유지)
'             : 0 --> Disconnect before Status
'             : 1 --> On
'             : 2 --> Off
'==============================================================================================='
Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwSize As Long, ByRef dwaSetValue As Long) As Long

Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwInputNum As Long, ByVal dwOutputNum As Long) As Long

Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef dwpInputNum As Long, ByRef dwpOutputNum As Long) As Long