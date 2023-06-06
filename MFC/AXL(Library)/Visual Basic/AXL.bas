'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXM.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Ajinextek Motion Library Header File
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

Attribute VB_Name = "AXL"

'========== Library initialization =================================================================================

' Library initialization
Public Declare Function AxlOpen Lib "AXL.dll" (ByVal lIrqNo As Long) As Long
' Do not do the lises at a library initialization hardware chip.
Public Declare Function AxlOpenNoReset Lib "AXL.dll" (ByVal lIrqNo As Long) As Long
' Exit from library use
Public Declare Function AxlClose Lib "AXL.dll" () As Byte
' Verify if the library is initialized
Public Declare Function AxlIsOpened Lib "AXL.dll" () As Byte

' Use Interrupt
Public Declare Function AxlInterruptEnable Lib "AXL.dll" () As Long
' Not use Interrupt
Public Declare Function AxlInterruptDisable Lib "AXL.dll" () As Long

'========== library and base board information =================================================================================

' Verify the number of registered base board
Public Declare Function AxlGetBoardCount Lib "AXL.dll" (ByRef lpBoardCount As Long) As Long
' Verify the library version
Public Declare Function AxlGetLibVersion Lib "AXL.dll" (ByRef szVersion As Byte) As Long
' Verify Network models Module Status
Public Declare Function AxlGetModuleNodeStatus Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long) As Long
' Verify Board Status
Public Declare Function AxlGetBoardStatus Lib "AXL.dll" (ByVal lBoardNo As Long) As Long
' return Configuration Lock status of Network product.
' *wpLockMode  : DISABLE(0), ENABLE(1)
Public Declare Function AxlGetLockMode Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wpLockMode As Long) As Long

'========== Log level =================================================================================

' Set message level to be output to EzSpy
' uLevel : 0 - 3 Set
' LEVEL_NONE(0)    : ALL Message don't Output
' LEVEL_ERROR(1)   : Error Message Output
' LEVEL_RUNSTOP(2) : Run/Stop relative Message Output during Motion.
' LEVEL_FUNCTION(3): ALL Message don't Output
Public Declare Function AxlSetLogLevel Lib "AXL.dll" (ByVal uLevel As Long) As Long
' Verify message level to be output to EzSpy
Public Declare Function AxlGetLogLevel Lib "AXL.dll" (ByRef upLevel As Long) As Long

'========== MLIII =================================================================================
Public Declare Function AxlScanStart Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lNet As Long) As Long
Public Declare Function AxlBoardConnect Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lNet As Long) As Long
Public Declare Function AxlBoardDisconnect Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lNet As Long) As Long