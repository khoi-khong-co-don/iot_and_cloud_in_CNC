Option Strict Off
Option Explicit On
Module AXD
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
    
    
    '========== Board and module information =================================================================================
    
    ' Verify if DIO module exists
    Public Declare Function AxdInfoIsDIOModule Lib "AXL.dll" (ByRef upStatus As Integer) As Integer
    
    ' Verify DIO in/output module number
    Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer
    
    ' Verify the number of DIO in/output module
    Public Declare Function AxdInfoGetModuleCount Lib "AXL.dll" (ByRef lpModuleCount As Integer) As Integer
    
    ' Verify the number of input contacts of specified module
    Public Declare Function AxdInfoGetInputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer
    
    ' Verify the number of output contacts of specified module
    Public Declare Function AxdInfoGetOutputCount Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpCount As Integer) As Integer
    
    ' Verify the base board number, module position and module ID with specified module number
    Public Declare Function AxdInfoGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef lpBoardNo As Integer, ByRef lpModulePos As Integer, ByRef upModuleID As Integer) As Integer
    
    '========== Verification group for input interrupt setting =================================================================================
    
    ' Use window message, callback API or event method in order to get interrupt message into specified module
    Public Declare Function AxdiInterruptSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal hWnd As Integer, ByVal uMessage As Integer, ByVal pProc As Integer, ByRef pEvent As Integer) As Integer
    
    Public Declare Function AxdInfoGetModuleStatus Lib "AXL.dll" (ByVal lModuleNo As Integer) As Integer
    
    ' Set whether to use interrupt of specified module
    '======================================================'
    ' uUse       : DISABLE(0)   ' Interrupt Disable
    '            : ENABLE(1)    ' Interrupt Enable
    '======================================================'
    Public Declare Function AxdiInterruptSetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer
    
    ' Verify whether to use interrupt of specified module
    '======================================================'
    ' *upUse     : DISABLE(0)   ' Interrupt Disable
    '            : ENABLE(1)    ' Interrupt Enable
    '======================================================'
    Public Declare Function AxdiInterruptGetModuleEnable Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer
    
    ' Verify the position interrupt occurred
    Public Declare Function AxdiInterruptRead Lib "AXL.dll" (ByRef lpModuleNo As Integer, ByRef upFlag As Integer) As Integer
    
    '========== Input interrupt rising / Verification group for setting of interrupt occurrence in falling edge =================================================================================
    
    ' Set the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer
    
    ' Set the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FF 
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer
    
    ' Set the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FFFF 
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer
    
    ' Set the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer
    
    ' Verify the rising or falling edge value by bit unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer
    
    ' Verify the rising or falling edge value by byte unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer
    
    ' Verify the rising or falling edge value by word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer
    
    ' Verify the rising or falling edge value by double word unit in specified input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGetDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer
    
    ' Set the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' uValue     : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeSet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByVal uValue As Integer) As Integer
    
    ' Verify the rising or falling edge value by bit unit in entire input contact module and Offset position of Interrupt Rising / Falling Edge register
    '==============================================================================================='
    ' uMode      : DOWN_EDGE(0)
    '            : UP_EDGE(1)
    ' *upValue   : DISABLE(0)
    '            : ENABLE(1)
    '==============================================================================================='
    Public Declare Function AxdiInterruptEdgeGet Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uMode As Integer, ByRef upValue As Integer) As Integer
    
    '========== Verification group of input / output signal level setting =================================================================================
    
    ' Set data level by bit unit in Offset position of specified input contact module
    '==============================================================================================='
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Set data level by byte unit in Offset position of specified input contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Set data level by word unit in Offset position of specified input contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Set data level by double word unit in Offset position of specified input contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Verify data level by bit unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Verify data level by byte unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upLevel   : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Verify data level by word unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upLevel   : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Verify data level by double word unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upLevel   : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdiLevelGetInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Set data level by bit unit in Offset position of entire input contact module
    '==============================================================================================='
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiLevelSetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Verify data level by bit unit in Offset position of entire input contact module
    '==============================================================================================='
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '===============================================================================================' 
    Public Declare Function AxdiLevelGetInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    
    ' Set data level by bit unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Set data level by byte unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Set data level by word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Set data level by double word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Verify data level by bit unit in Offset position of specified output contact module
    '==============================================================================================='
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Verify data level by byte unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Verify data level by word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Verify data level by double word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer
    
    ' Set data level by bit unit in Offset position of entire output contact module
    '==============================================================================================='
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelSetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer
    
    ' Verify data level by bit unit in Offset position of entire output contact module
    '==============================================================================================='
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoLevelGetOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upLevel As Integer) As Integer

    '========== Input / Output signal reading / writing =================================================================================
    
    ' Output data by bit unit in Offset position of entire output contact module
    '==============================================================================================='
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByVal uValue As Integer) As Integer
    
    ' Output data by bit unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uLevel     : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer
    
    ' Output data by byte unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uValue     : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer
    
    ' Output data by word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uValue     : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer
    
    ' Output data by double word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' uValue     : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdoWriteOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer
    
    ' Read data by bit unit in Offset position of entire output contact module
    '==============================================================================================='
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoReadOutport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data by bit unit in Offset position of specified output contact module
    '==============================================================================================='
    ' *upLevel   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdoReadOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data by byte unit in Offset position of specified output contact module
    '==============================================================================================='
    ' *upValue   : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdoReadOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data by word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' *upValue   : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdoReadOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data by double word unit in Offset position of specified output contact module
    '==============================================================================================='
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdoReadOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data level by bit unit in Offset position of entire input contact module
    '==============================================================================================='
    ' *upValue   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiReadInport Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data level by bit unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upValue   : LOW(0)
    '            : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdiReadInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data level by byte unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upValue   : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdiReadInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data level by wordt unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upValue   : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdiReadInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Read data level by double word unit in Offset position of specified input contact module
    '==============================================================================================='
    ' *upValue   : 0x00 ~ 0x0FFFFFFFF
    '==============================================================================================='
    Public Declare Function AxdiReadInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    '== Only for MLII, M-Systems DIO(R7 series)
    ' Read data level by bit unit in Offset position of specified extended input contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by bit unit between input index.(0~15)
    ' *upValue    : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdReadExtInportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by byte unit in Offset position of specified extended input contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : offset position by byte unit between input index.(0~1)
    ' *upValue    : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdReadExtInportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by word unit in Offset position of specified extended input contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : offset position by word unit between input index.(0)
    ' *upValue    : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdReadExtInportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by double word unit in Offset position of specified extended input contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : offset position by dword unit between input index.(0)
    ' *upValue    : 0x00 ~ 0x00000FFFF
    '==============================================================================================='
    Public Declare Function AxdReadExtInportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by bit unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by bit unit between output index.(0~15)
    ' *upValue    : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by byte unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by byte unit between output index.(0~1)
    ' *upValue    : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by word unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by word unit between output index.(0)
    ' *upValue    : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Read data level by double word unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by dword unit between output index.(0)
    ' *upValue    : 0x00 ~ 0x0000FFFF
    '==============================================================================================='
    Public Declare Function AxdReadExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    ' Output data by bit unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by bit unit between output index.(0~15)
    ' uValue      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' Output data by byte unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by byte unit between output index.(0~1)
    ' uValue      : 0x00 ~ 0x0FF
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' Output data by word unit in Offset position of specified extended output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by word unit between output index.(0~1)
    ' uValue      : 0x00 ~ 0x0FFFF
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' Output data by dword unit in Offset position of specified extended output contact module
    '==============================================================================================/'
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by dword unit between output index.(0)
    ' uValue    : 0x00 ~ 0x00000FFFF
    '==============================================================================================='
    Public Declare Function AxdWriteExtOutportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uValue As Integer) As Integer

    ' Set data level by bit unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by bit unit between input/output index.(0~15)
    ' uLevel      : LOW(0)
    '             : HIGH(1)
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' Set data level by byte unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by byte unit between input/output index.(0~1)
    ' uLevel      : 0x00 ~ 0xFF
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' Set data level by word unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by word unit between input/output index.(0)
    ' uLevel      : 0x00 ~ 0xFFFF
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' Set data level by dword unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by dword unit between input/output index.(0)
    ' uLevel      : 0x00 ~ 0x0000FFFF
    '==============================================================================================='
    Public Declare Function AxdLevelSetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uLevel As Integer) As Integer

    ' Verify data level by bit unit in Offset position of specified extended input/output contact module
    '===============================================================================================//'
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by bit unit between input/output index.(0~15)
    ' uLevel      : LOW(0)
    '             : HIGH(1)
    '===============================================================================================//'
    Public Declare Function AxdLevelGetExtportBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' Verify data level by byte unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by byte unit between input/output index.(0~1)
    ' uLevel      : 0x00 ~ 0xFF
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' Verify data level by word unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by word unit between input/output index.(0)
    ' uLevel      : 0x00 ~ 0xFFFF
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    ' Verify data level by dword unit in Offset position of specified extended input/output contact module
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' lOffset     : Offset position by dword unit between input/output index.(0)
    ' uLevel      : 0x00 ~ 0x0000FFFF
    '==============================================================================================='
    Public Declare Function AxdLevelGetExtportDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal upLevel As Integer) As Integer

    '========== Advanced API =================================================================================
    
    ' Verify if the signal was switched from Off to On in Offset position of specified input contact module
    '==============================================================================================='
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==============================================================================================='
    Public Declare Function AxdiIsPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Verify if the signal was switched from On to Off in Offset position of specified input contact module
    '==============================================================================================='
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    '==============================================================================================='
    Public Declare Function AxdiIsPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    
    ' Verify if the signal is maintained On state during the calling time as much as count in Offset position of specified input contact module
    '==============================================================================================='
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1
    '            : 0
    '==============================================================================================='
    Public Declare Function AxdiIsOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer
    
    ' Verify if the signal is maintained Off state during the calling time as much as count in Offset position of specified input contact module
    '==============================================================================================='
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' *upValue   : FALSE(0)
    '            : TRUE(1)
    ' lStart     : 1
    '            : 0
    '==============================================================================================='
    Public Declare Function AxdiIsOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lCount As Integer, ByRef upValue As Integer, ByVal lStart As Integer) As Integer
    
    ' Maintain On state during mSec set in Offset position of specified output contact module, then turns Off
    '==============================================================================================='
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==============================================================================================='
    Public Declare Function AxdoOutPulseOn Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer
    
    ' Maintain Off state during mSec set in Offset position of specified output contact module, then turns On
    '==============================================================================================='
    ' lCount     : 0 ~ 0x7FFFFFFF(2147483647)
    ' lmSec      : 1 ~ 30000
    '==============================================================================================='
    Public Declare Function AxdoOutPulseOff Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lmSec As Integer) As Integer
    
    ' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
    '==============================================================================================='
    ' lInitState : Off(0)
    '            : On(1)
    ' lmSecOn    : 1 ~ 30000
    ' lmSecOff   : 1 ~ 30000
    ' lCount     : 1 ~ 0x7FFFFFFF(2147483647)
    '            : -1
    '==============================================================================================='
    Public Declare Function AxdoToggleStart Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal lInitState As Integer, ByVal lmSecOn As Integer, ByVal lmSecOff As Integer, ByVal lCount As Integer) As Integer
    
    ' Toggling by numbers and interval which are set in Offset position of specified output contact module, then afterward maintaining the original output state
    '==============================================================================================='
    ' uOnOff     : Off(0)
    '            : On(1)
    '==============================================================================================='
    Public Declare Function AxdoToggleStop Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByVal uOnOff As Integer) As Integer

    ' In disconnect cases Set output status of specified module by byte.
    '==============================================================================================='
    ' lModuleNo   : Module number
    ' dwSize      : Set Byte Number(ex. RTEX-DB32 : 2, RTEX-DO32 : 4)
    ' dwaSetValue : Set Value(Default는 Network 끊어 지기 전 상태 유지)
    '             : 0 --> Disconnect before Status
    '             : 1 --> On
    '             : 2 --> Off
    '==============================================================================================='
    Public Declare Function AxdoSetNetworkErrorAct Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwSize As Integer, ByRef dwaSetValue As Integer) As Integer

    Public Declare Function AxdSetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwInputNum As Integer, ByVal dwOutputNum As Integer) As Integer

    Public Declare Function AxdGetContactNum Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef dwpInputNum As Integer, ByRef dwpOutputNum As Integer) As Integer
End Module
