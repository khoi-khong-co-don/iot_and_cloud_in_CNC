Option Strict Off
Option Explicit On
Module AXDev
    
    ' Use Board Number and find Board Address
    Public Declare Function AxlGetBoardAddreas Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardAddress As Integer) As Integer
    ' Use Board Number and find Board ID
    Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardID As Integer) As Integer
    ' Use Board Number and find Board Version
    Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef upBoardVersion As Integer) As Integer
    ' Use Board Number/Module Position and find Module ID
    Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upModuleID As Integer) As Integer
    ' Use Board Number/Module Position and find Module Version
    Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upModuleVersion As Integer) As Integer
    
    Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef upNetNo As Integer, ByRef upNodeAddr As Integer) As Integer

    ' Only for PCI-R1604[RTEX]
    ' Writing user data to embedded flash memory
    ' lPageAddr(0 ~ 199)
    ' lByteNum(1 ~ 120)
    ' Note) Delay time is required for completing writing operation to Flash(Max. 17mSec)
    Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lPageAddr As Integer, ByVal lBytesNum As Integer, ByRef bpSetData As Byte) As Integer
    ' Reading datas from embedded flash memory
    ' lPageAddr(0 ~ 199)
    ' lByteNum(1 ~ 120)
    Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lPageAddr As Integer, ByVal lBytesNum As Integer, ByRef bpGetData As Byte) As Integer

    ' Use Board Number/Module Position and find AIO Module Number
    Public Declare Function AxaInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer
    ' Use Board Number/Module Position and find DIO Module Number
    Public Declare Function AxdInfoGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByRef lpModuleNo As Integer) As Integer
    
    ' IPCOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte) As Integer
    ' 8bit IPCOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 8bit IPCOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' 16bit IPCOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 16bit IPCOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' 24bit IPCOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 24bit IPCOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' 32bit IPCOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 32bit IPCOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    
    ' QICOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte) As Integer
    ' 8bit QICOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 8bit QICOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' 16bit QICOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 16bit QICOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' 24bit QICOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 24bit QICOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    ' 32bit QICOMMAND Setting at an appoint axis
    Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByVal uData As Integer) As Integer
    ' Get 32bit QICOMMAND at an appoint axis
    Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sCommand As Byte, ByRef upData As Integer) As Integer
    
    ' Get Port Data at an appoint axis - IP
    Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef upData As Integer) As Integer
    ' Port Data Setting at an appoint axis - IP
    Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer
    ' Get Port Data at an appoint axis - QI
    Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef upData As Integer) As Integer
    ' Port Data Setting at an appoint axis - QI
    Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer
    
    ' Set the script at an appoint axis.  - IP
    ' sc    : Script number (1 - 4)
    ' event : Define an event SCRCON to happen.
    '         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
    ' cmd   : Define a selection SCRCMD however we change any content
    ' data  : Selection to change any Data.
    Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByVal event1 As Integer, ByVal data As Integer) As Integer
    ' Return the script at an appoint axis.  - IP
    Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByRef event1 As Integer, ByRef data As Integer) As Integer

    ' Set the script at an appoint axis.  - QI
    ' sc    : Script number (1 - 4)
    ' event : Define an event SCRCON to happen.
    '         Set event, a number of axis, axis which the event happens, event content 1, 2 attribute
    ' cmd   : Define a selection SCRCMD however we change any content
    ' data  : Selection to change any Data.
    Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByVal event1 As Integer, ByVal cmd As Integer, ByVal data As Integer) As Integer
    ' Return the script at an appoint axis. - QI
    Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal sc As Integer, ByRef event1 As Integer, ByRef cmd As Integer, ByRef data As Integer) As Integer

    ' Clear orders a script inside Queue Index at an appoint axis
    ' uSelect IP. 
    ' uSelect(0): Script Queue Index Clear.
    '        (1): Caption Queue Index Clear.
    ' uSelect QI. 
    ' uSelect(0): Script Queue 1 Index Clear.
    '        (1): Script Queue 2 Index Clear.
    Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uSelect As Integer) As Integer

    ' Return Index of a script inside Queue at an appoint axis.
    ' uSelect IP
    ' uSelect(0): Read Script Queue Index
    '        (1): Read Caption Queue Index
    ' uSelect QI. 
    ' uSelect(0): Read Script Queue 1 Index
    '        (1): Read Script Queue 2 Index
    Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef updata As Integer, ByVal uSelect As Integer) As Integer

    ' Return Data number of a script inside Queue at an appoint axis.
    ' uSelect IP
    ' uSelect(0): Read Script Queue Data
    '        (1): Read Caption Queue Data
    ' uSelect QI.
    ' uSelect(0): Read Script Queue 1 Data
    '        (1): Read Script Queue 2 Data
    Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef updata As Integer, ByVal uSelect As Integer) As Integer

    ' Read an inside data.
    Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dMinVel As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByRef wRangeData As Integer, ByRef wStartStopSpeedData As Integer, ByRef wObjectSpeedData As Integer, ByRef wAccelRate As Integer, ByRef wDecelRate As Integer) As Integer

    ' Setting up confirmes the register besides within the board by Byte.
    Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal byData As Byte) As Integer
    Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef byData As Byte) As Integer

    ' Setting up confirmes the register besides within the board by Word.
    Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal wData As Integer) As Integer
    Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer

    ' Setting up confirmes the register besides within the board by DWord.
    Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer

    ' Setting up confirmes the register besides within the Module by Byte.
    Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal byData As Byte) As Integer
    Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef byData As Byte) As Integer

    ' Setting up confirmes the register besides within the Module by Word.
    Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal wData As Integer) As Integer
    Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer

    ' Setting up confirmes the register besides within the Module by DWord.
    Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal lModulePos As Integer, ByVal wOffset As Integer, ByRef dwData As Integer) As Integer

    ' Set EXCNT (Pos = Unit)
    Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer
    ' Return EXCNT (Positon = Unit)
    Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dpPos As Double) As Integer

    ' Set INCNT (Pos = Unit)
    Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double) As Integer
    ' Return INCNT (Pos = Unit)
    Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dpPos As Double) As Integer

'========== Append function. =========================================================================================================
    ' Increase a straight line interpolation at speed to the infinity.
    ' Must put the distance speed rate.
    Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

 '========= Sensor drive API( Read carefully: Available only PI , No function in QI)=========================================================================
    ' Set mark signal( used in sensor positioning drive)
    Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uLevel As Integer) As Integer
    ' Verify mark signal( used in sensor positioning drive)
    Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upLevel As Integer) As Integer
    ' Verify mark signal( used in sensor positioning drive)state
    Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upStatus As Integer) As Integer

    ' Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. 
    ' Applied motion is started upon the start of API, and escapes from the API after the motion is completed.
    Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Integer) As Integer

    ' Drive API which moves from edge detection of sensor input pin during velocity mode driving as much as specified position, then stop. 
    ' Applied motion is started upon the start of API, then escapes from the API immediately without waiting until the motion is completed.
    Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Integer) As Integer

Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef lpStepCount As Integer, ByRef upMainStepNumber As Integer, ByRef upStepNumber As Integer, ByRef upStepBranch As Integer) As Integer

'=======Additive home search (Applicable to PI-N804/404  only)=================================================================================

    ' Set home setting parameters of axis specified by user. (Use exclusive-use register for QI chip).
    ' uZphasCount : Z phase count after home completion. (0 - 15)
    ' lHomeMode   : Home setting mode( 0 - 12)
    ' lClearSet   : Select use of position clear and remaining pulse clear (0 - 3)
    '               0: No use of position clear, no use of remaining pulse clear
    '               1: use of position clear, no use of remaining pulse clear
    '               2: No use of position clear, use of remaining pulse clear
    '               3: use of position clear, use of remaining pulse clear
    ' dOrgVel : Set Org  Speed related home
    ' dLastVel: Set Last Speed related home
    Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uZphasCount As Integer, ByVal lHomeMode As Integer, ByVal lClearSet As Integer, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Integer
    ' Return home setting parameters of axis specified by user.
    Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upZphasCount As Integer, ByRef lpHomeMode As Integer, ByRef lpClearSet As Integer, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Integer

   ' Start home search of axis specified by user
    ' Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
    ' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
    ' Move direction      : CW when Vel value is positive, CCW when negative.
    Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' Start home return of axis specified by user.
    ' Set when lHomeMode is used: set 0 - 12  
    ' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
    ' Move direction      : CW when Vel value is positive, CCW when negative.
    Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' Home separation of axis specified by user is started. 
    ' Move direction      : CW when Vel value is positive, CCW when negative.
    Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' User start home search of multi-axis specified by user. 
    ' Set when use lHomeMode : Set 0 - 5 (Start search after Move Return.)
    ' If lHomeMode -1is used as it is, the setting is done as used in HomeConfig.
    ' Move direction      : CW when Vel value is positive, CCW when negative.
    Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Integer, ByRef lpAxesNo As Integer, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Integer

    'Set move velocity profile mode of specific coordinate system. 
    ' (caution : Available to use only after axis mapping)
    'ProfileMode : '0' - symmetry Trapezoid
    '              '1' - asymmetric Trapezoid
    '              '2' - symmetry Quasi-S Curve
    '              '3' - symmetry S Curve
    '              '4' - asymmetric S Curve
    Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Integer, ByVal uProfileMode As Integer) As Integer
    ' Return move velocity profile mode of specific coordinate system.
    Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Integer, ByRef upProfileMode As Integer) As Integer
    Public Declare Function AxmMoveProfilePos Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal lProfileSize As Integer, ByRef dpPos As Double, ByRef dpMinVel As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Integer

    '========== Reading group for input interrupt occurrence flag
    ' Reading the interrupt occurrence state by bit unit in specified input contact module and Offset position of Interrupt Flag Register
    Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' Reading the interrupt occurrence state by byte unit in specified input contact module and Offset position of Interrupt Flag Register
    Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' Reading the interrupt occurrence state by word unit in specified input contact module and Offset position of Interrupt Flag Register
    Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' Reading the interrupt occurrence state by double word unit in specified input contact module and Offset position of Interrupt Flag Register
    Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal lOffset As Integer, ByRef upValue As Integer) As Integer
    ' Reading the interrupt occurrence state by bit unit in entire input contact module and Offset position of Interrupt Flag Register
    Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Integer, ByRef upValue As Integer) As Integer

    '========= API related log ==========================================================================================   
    ' This API sets or resets in order to monitor the API execution result of set axis in EzSpy. 
    ' uUse : use or not use => DISABLE(0), ENABLE(1)
    Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal uUse As Integer) As Integer

    ' This API verifies if the API execution result of set axis is monitored in EzSpy. 
    Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef upUse As Integer) As Integer

    '==Log
    ' Set whether execute log output on EzSpy of specified module
    Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal uUse As Integer) As Integer
    ' Verify whether execute log output on EzSpy of specified module
    Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef upUse As Integer) As Integer

    ' Set whether to log output to EzSpy of specified input channel
    Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer
    ' Verify whether to log output to EzSpy of specified input channel
    Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer

    ' Set whether to log output in EzSpy of specified output channel
    Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal uUse As Integer) As Integer
    ' Verify whether log output is done in EzSpy of specified output channel.
    Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef upUse As Integer) As Integer

    ' Verify whether to firmware version designated RTEX board.
    Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal szVersion As String) As Integer
    ' Sent to firmware designated board.
    Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef wData As Integer, ByRef wCmdData As Integer) As Integer
    ' Execute Firmware update to designated board. 
    Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Integer) As Integer
    ' Verify whether currently RTEX status Initialized.
    Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwStatus As Integer) As Integer
    ' To Initialized currently RTEX on designated board.
    Public Declare Function AxlInitRtex Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwOption As Integer) As Integer
    ' Execute universal command designated axis of board.
    Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wCmd As Integer, ByVal wOffset As Integer, ByRef wData As Integer) As Integer
    ' Execute RTEX communication command designated axis.
    Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwCmdCode As Integer, ByVal dwTypeCode As Integer, ByVal dwIndexCode As Integer, ByVal dwCmdConfigure As Integer, ByVal dwValue As Integer) As Integer
    ' Verify whether Result of RTEX communication command designated axis.
    Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwIndex As Integer, ByRef dwValue As Integer) As Integer
    ' Verify whether RTEX status information designated axis.
    Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwStatus As Integer) As Integer
    ' Verify whether RTEX communication return information designated axis.(Actual position, Velocity, Torque)
    Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwReturn1 As Integer, ByRef dwReturn2 As Integer, ByRef dwReturn3 As Integer) As Integer
    ' Verify whether currently status information of RTEX slave axis.(mechanical, Inposition and etc)
    Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwStatus As Integer) As Integer

    Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef tagCommand As Integer) As Integer
    Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef tagCommand As Integer) As Integer

    Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wAddress As Integer, ByRef dwpRdData As Integer) As Integer
    Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal wOffset As Integer, ByRef dwpRdData As Integer) As Integer

    Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByVal dwCommand As Integer, ByRef dwpSendData As Integer, ByVal dwLength As Integer) As Integer
    Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Integer, ByRef dwpReadData As Integer) As Integer

    Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
    Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
    Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Integer, ByRef ucaFirmwareVersion As Integer) As Integer
   
    Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwTorqFeedForward As Integer) As Integer
    Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpTorqFeedForward As Integer) As Integer
    Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwVelocityFeedForward As Integer) As Integer
    Public Declare Function AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpVelocityFeedForward As Integer) As Integer

    ' Set Encoder type.
    ' Default value : 0(TYPE_INCREMENTAL)
    ' Setting range : 0 ~ 1
    ' dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
    Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwEncoderType As Integer) As Integer

    ' Verify Encoder type.
    Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Integer, ByRef dwpEncoderType As Integer) As Integer

    ' For updating the slave firmware(only for RTEX-PM).
    ' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal wCommand As Integer, ByRef wpSendData As Integer, ByVal wLength As Integer) As Integer

    '======== Only for PCI-R1604-RTEX, RTEX-PM============================================================== 
    ' When Input Universal Input 2, 3, Set Jog move velocity
    ' Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
    Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Integer

    ' When Input Universal Input 2, 3, Set Jog move usage
    ' Setting value :  0(DISABLE), 1(ENABLE)
    Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwUsage As Integer) As Integer

    ' Set Load/UnLoad Position to Automatically move use MPGP Input.
    Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Integer, ByVal dwDelay As Integer) As Integer

    ' Set Usage Load/UnLoad Position to Automatically move use MPGP Input 
    ' Setting value :  0(DISABLE), 1(Position function A), 2(Position function B).
    Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Integer, ByVal dwUsage As Integer) As Integer
    '======================================================================================================== 

    '======== SIO-CN2CH, Only for absolute position trigger module(B0) ================================================
    Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwAddr As Integer, ByRef dwpData As Integer) As Integer
    Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Integer, ByVal dwData As Integer) As Integer
    Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwTimeout As Integer) As Integer
    Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpTimeout As Integer) As Integer
    Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Integer, ByRef dwpState As Integer) As Integer
    Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Integer, ByVal dwState As Integer) As Integer
    '========================================================================================================

    ' ======== Only for PCI-N804/N404, Sequence Motion ===========================================================
    ' Set Axis Information of sequence Motion (min 1axis)
    ' lSeqMapNo : Sequence Motion Index Point
    ' lSeqMapSize : Number of axis
    ' long* LSeqAxesNo : Number of arrar
    Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal lSeqMapSize As Integer, ByRef lSeqAxesNo As Integer) As Integer
    Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lSeqMapSize As Integer, ByRef lSeqAxesNo As Integer) As Integer

    ' Set Standard(Master)Axis of Sequence Motion.
    ' By all means Set in AxmSeqSetAxisMap setting axis.
    Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal lMasterAxisNo As Integer) As Integer

    ' Notifies the library node start loading of Sequence Motion.
    Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer

    ' Notifies the library node end loading of Sequence Motion.
    Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer

    ' Start Sequence Motion Move.
    Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal dwStartOption As Integer) As Integer

    ' Set each profile node Information of Sequence Motion in Library.
    ' if used 1axis Sequence Motion, Must be Set *dPosition one Array.
    Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Integer

    ' Return Node Index number of Sequence Motion.
    Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lCurNodeNo As Integer) As Integer

    '  Return All node count of Sequence Motion.
    Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef lTotalNodeCnt As Integer) As Integer

    ' Return Sequence Motion drive status  of specific SeqMap.
    ' dwInMotion : 0(Drive end), 1(In drive).
    Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByRef dwInMotion As Integer) As Integer

    ' Clear Sequence Motion Memory
    Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo As Integer) As Integer

    ' Stop sequence motion
    ' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
    Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Integer, ByVal dwStopMode As Integer) As Integer
    '========================================================================================================

End Module
