Attribute VB_Name = "AXDev"

' Use Board Number and find Board Address
Public Declare Function AxlGetBoardAddreas Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardAddress As Long) As Long
' Use Board Number and find Board ID
Public Declare Function AxlGetBoardID Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardID As Long) As Long
' Use Board Number and find Board Version
Public Declare Function AxlGetBoardVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef upBoardVersion As Long) As Long
' Use Board Number/Module Position and find Module ID
Public Declare Function AxlGetModuleID Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleID As Long) As Long
' Use Board Number/Module Position and find Module Version
Public Declare Function AxlGetModuleVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upModuleVersion As Long) As Long

Public Declare Function AxlGetModuleNodeInfo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef upNetNo As Long, ByRef upNodeAddr As Long) As Long

' Only for PCI-R1604[RTEX]
' Writing user data to embedded flash memory
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
' Note) Delay time is required for completing writing operation to Flash(Max. 17mSec)
Public Declare Function AxlSetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpSetData As Byte) As Long
' Reading datas from embedded flash memory
' lPageAddr(0 ~ 199)
' lByteNum(1 ~ 120)
Public Declare Function AxlGetDataFlash Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lPageAddr As Long, ByVal lBytesNum As Long, ByRef bpGetData As Byte) As Long

' Use Board Number/Module Position and find AIO Module Number
Public Declare Function AxaGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long
' Use Board Number/Module Position and find DIO Module Number
Public Declare Function AxdGetModuleNo Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByRef lpModuleNo As Long) As Long

' IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' 8bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 8bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData08 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 16bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 16bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData16 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 24bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 24bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData24 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 32bit IPCOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 32bit IPCOMMAND at an appoint axis
Public Declare Function AxmGetCommandData32 Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long

' QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte) As Long
' 8bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 8bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData08Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 16bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 16bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData16Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 24bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 24bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData24Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long
' 32bit QICOMMAND Setting at an appoint axis
Public Declare Function AxmSetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByVal uData As Long) As Long
' Get 32bit QICOMMAND at an appoint axis
Public Declare Function AxmGetCommandData32Qi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sCommand As Byte, ByRef upData As Long) As Long

' Get Port Data at an appoint axis - IP
Public Declare Function AxmGetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef upData As Long) As Long
' Port Data Setting at an appoint axis - IP
Public Declare Function AxmSetPortData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long
' Get Port Data at an appoint axis - QI
Public Declare Function AxmGetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef upData As Long) As Long
' Port Data Setting at an appoint axis - QI
Public Declare Function AxmSetPortDataQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

Public Declare Function AxmSetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal data As Long) As Long
Public Declare Function AxmGetScriptCaptionIp Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef data As Long) As Long
Public Declare Function AxmSetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByVal event1 As Long, ByVal cmd As Long, ByVal data As Long) As Long
Public Declare Function AxmGetScriptCaptionQi Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal sc As Long, ByRef event1 As Long, ByRef cmd As Long, ByRef data As Long) As Long
Public Declare Function AxmSetScriptCaptionQueueClear Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uSelect As Long) As Long
Public Declare Function AxmGetScriptCaptionQueueCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long
Public Declare Function AxmGetScriptCaptionQueueDataCount Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef updata As Long, ByVal uSelect As Long) As Long
Public Declare Function AxmGetOptimizeDriveData Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dMinVel As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByRef wRangeData As Long, ByRef wStartStopSpeedData As Long, ByRef wObjectSpeedData As Long, ByRef wAccelRate As Long, ByRef wDecelRate As Long) As Long

Public Declare Function AxmBoardWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmBoardReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long
Public Declare Function AxmBoardWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmBoardReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef wData As Long) As Long
Public Declare Function AxmBoardWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmBoardReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

Public Declare Function AxmModuleWriteByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal byData As Byte) As Long
Public Declare Function AxmModuleReadByte Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef byData As Byte) As Long
Public Declare Function AxmModuleWriteWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal wData As Long) As Long
Public Declare Function AxmModuleReadWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef wData As Long) As Long
Public Declare Function AxmModuleWriteDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByVal dwData As Long) As Long
Public Declare Function AxmModuleReadDWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal lModulePos As Long, ByVal wOffset As Long, ByRef dwData As Long) As Long

Public Declare Function AxmStatusSetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
Public Declare Function AxmStatusGetActComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long
Public Declare Function AxmStatusSetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double) As Long
Public Declare Function AxmStatusGetCmdComparatorPos Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dpPos As Double) As Long

Public Declare Function AxmLineMoveVel Lib "AXL.dll" (ByVal lCoord As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

Public Declare Function AxmSensorSetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uLevel As Long) As Long
Public Declare Function AxmSensorGetSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upLevel As Long) As Long
Public Declare Function AxmSensorReadSignal Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upStatus As Long) As Long
Public Declare Function AxmSensorMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long
Public Declare Function AxmSensorStartMovePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dPos As Double, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal lMethod As Long) As Long

Public Declare Function AxmHomeGetStepTrace Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef lpStepCount As Long, ByRef upMainStepNumber As Long, ByRef upStepNumber As Long, ByRef upStepBranch As Long) As Long
Public Declare Function AxmHomeSetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uZphasCount As Long, ByVal lHomeMode As Long, ByVal lClearSet As Long, ByVal dOrgVel As Double, ByVal dLastVel As Double, ByVal dLeavePos As Double) As Long
Public Declare Function AxmHomeGetConfig Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upZphasCount As Long, ByRef lpHomeMode As Long, ByRef lpClearSet As Long, ByRef dpOrgVel As Double, ByRef dpLastVel As Double, ByRef dpLeavePos As Double) As Long
Public Declare Function AxmHomeSetMoveSearch Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long
Public Declare Function AxmHomeSetMoveReturn Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long
Public Declare Function AxmHomeSetMoveLeave Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVel As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long
Public Declare Function AxmHomeSetMultiMoveSearch Lib "AXL.dll" (ByVal lArraySize As Long, ByRef lpAxesNo As Long, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long

Public Declare Function AxmContiSetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByVal uProfileMode As Long) As Long
Public Declare Function AxmContiGetProfileMode Lib "AXL.dll" (ByVal lCoord As Long, ByRef upProfileMode As Long) As Long
Public Declare Function AxmMoveProfilePos Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal lProfileSize As Long, ByRef dpPos As Double, ByRef dpMinVel As Double, ByRef dpVel As Double, ByRef dpAccel As Double, ByRef dpDecel As Double) As Long
Public Declare Function AxdiInterruptFlagReadBit Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
Public Declare Function AxdiInterruptFlagReadByte Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
Public Declare Function AxdiInterruptFlagReadWord Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
Public Declare Function AxdiInterruptFlagReadDword Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal lOffset As Long, ByRef upValue As Long) As Long
Public Declare Function AxdiInterruptFlagRead Lib "AXL.dll" (ByVal lOffset As Long, ByRef upValue As Long) As Long
Public Declare Function AxmLogSetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal uUse As Long) As Long
Public Declare Function AxmLogGetAxis Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef upUse As Long) As Long
Public Declare Function AxaiLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
Public Declare Function AxaiLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long
Public Declare Function AxaoLogSetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal uUse As Long) As Long
Public Declare Function AxaoLogGetChannel Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef upUse As Long) As Long
Public Declare Function AxdLogSetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal uUse As Long) As Long
Public Declare Function AxdLogGetModule Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef upUse As Long) As Long
Public Declare Function AxlGetFirmwareVersion Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal szVersion As String) As Long
Public Declare Function AxlSetFirmwareCopy Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef wData As Long, ByRef wCmdData As Long) As Long
Public Declare Function AxlSetFirmwareUpdate Lib "AXL.dll" (ByVal lBoardNo As Long) As Long
Public Declare Function AxlCheckStatus Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwStatus As Long) As Long
Public Declare Function AxlInitRtex Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwOption As Long) As Long
Public Declare Function AxlRtexUniversalCmd Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wCmd As Long, ByVal wOffset As Long, ByRef wData As Long) As Long
Public Declare Function AxmRtexSlaveCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwCmdCode As Long, ByVal dwTypeCode As Long, ByVal dwIndexCode As Long, ByVal dwCmdConfigure As Long, ByVal dwValue As Long) As Long
Public Declare Function AxmRtexGetSlaveCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwIndex As Long, ByRef dwValue As Long) As Long
Public Declare Function AxmRtexGetAxisStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long
Public Declare Function AxmRtexGetAxisReturnData Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwReturn1 As Long, ByRef dwReturn2 As Long, ByRef dwReturn3 As Long) As Long
Public Declare Function AxmRtexGetAxisSlaveStatus Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwStatus As Long) As Long

Public Declare Function AxmSetAxisCmd Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long
Public Declare Function AxmGetAxisCmdResult Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef tagCommand As Long) As Long
Public Declare Function AxlGetDpRamData Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wAddress As Long, ByRef dwpRdData As Long) As Long
Public Declare Function AxlBoardReadDpramWord Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal wOffset As Long, ByRef dwpRdData As Long) As Long
Public Declare Function AxlSetSendBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByVal dwCommand As Long, ByRef dwpSendData As Long, ByVal dwLength As Long) As Long
Public Declare Function AxlGetResponseBoardCommand Lib "AXL.dll" (ByVal lBoardNo As Long, ByRef dwpReadData As Long) As Long
Public Declare Function AxmInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxaInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function AxdInfoGetFirmwareVersion Lib "AXL.dll" (ByVal lModuleNo As Long, ByRef ucaFirmwareVersion As Long) As Long
Public Declare Function  AxmSetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwTorqFeedForward As Long) As Long

Public Declare Function  AxmGetTorqFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpTorqFeedForward As Long) As Long
Public Declare Function  AxmSetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwVelocityFeedForward As Long) As Long
Public Declare Function AxmGetVelocityFeedForward Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpVelocityFeedForward As Long) As Long

' Set Encoder type.
' Default value : 0(TYPE_INCREMENTAL)
' Setting range : 0 ~ 1
' dwEncoderType : 0(TYPE_INCREMENTAL), 1(TYPE_ABSOLUTE).
Public Declare Function AxmSignalSetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwEncoderType As Long) As Long

' Verify Encoder type.
Public Declare Function AxmSignalGetEncoderType Lib "AXL.dll" (ByVal lAxisNo As Long, ByRef dwpEncoderType As Long) As Long

' For updating the slave firmware(only for RTEX-PM).
' Public Declare Function AxmSetSendAxisCommand Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal wCommand As Long, ByRef wpSendData As Long, ByVal wLength As Long) As Long

'======== Only for PCI-R1604-RTEX, RTEX-PM============================================================== 
' When Input Universal Input 2, 3, Set Jog move velocity
' Set only once execute after all drive setting (Ex, PulseOutMethod, MoveUnitPerPulse etc..)
Public Declare Function AxmMotSetUserMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double) As Long

' When Input Universal Input 2, 3, Set Jog move usage
' Setting value :  0(DISABLE), 1(ENABLE)
Public Declare Function AxmMotSetUserMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long

' Set Load/UnLoad Position to Automatically move use MPGP Input.
Public Declare Function AxmMotSetUserPosMotion Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dVelocity As Double, ByVal dAccel As Double, ByVal dDecel As Double, ByVal dLoadPos As Double, ByVal dUnLoadPos As Double, ByVal dwFilter As Long, ByVal dwDelay As Long) As Long

' Set Usage Load/UnLoad Position to Automatically move use MPGP Input 
' Setting value :  0(DISABLE), 1(Position function A), 2(Position function B).
Public Declare Function AxmMotSetUserPosMotionUsage Lib "AXL.dll" (ByVal lAxisNo As Long, ByVal dwUsage As Long) As Long
'======================================================================================================== 

'======== SIO-CN2CH, Only for absolute position trigger module(B0) ================================================
Public Declare Function AxcKeWriteRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByVal dwData As Long) As Long
Public Declare Function AxcKeReadRamDataAddr Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwAddr As Long, ByRef dwpData As Long) As Long
Public Declare Function AxcKeResetRamDataAll Lib "AXL.dll" (ByVal lModuleNo As Long, ByVal dwData As Long) As Long
Public Declare Function AxcTriggerSetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwTimeout As Long) As Long
Public Declare Function AxcTriggerGetTimeout Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpTimeout As Long) As Long
Public Declare Function AxcStatusGetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByRef dwpState As Long) As Long
Public Declare Function AxcStatusSetWaitState Lib "AXL.dll" (ByVal lChannelNo As Long, ByVal dwState As Long) As Long
'========================================================================================================

' ======== Only for PCI-N804/N404, Sequence Motion ===========================================================
' Set Axis Information of sequence Motion (min 1axis)
' lSeqMapNo : Sequence Motion Index Point
' lSeqMapSize : Number of axis
' long* LSeqAxesNo : Number of arrar
Public Declare Function AxmSeqSetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long
Public Declare Function AxmSeqGetAxisMap Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lSeqMapSize As Long, ByRef lSeqAxesNo As Long) As Long

' Set Standard(Master)Axis of Sequence Motion.
' By all means Set in AxmSeqSetAxisMap setting axis.
Public Declare Function AxmSeqSetMasterAxisNo Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal lMasterAxisNo As Long) As Long

' Notifies the library node start loading of Sequence Motion.
Public Declare Function AxmSeqBeginNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Notifies the library node end loading of Sequence Motion.
Public Declare Function AxmSeqEndNode Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Start Sequence Motion Move.
Public Declare Function AxmSeqStart Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStartOption As Long) As Long

' Set each profile node Information of Sequence Motion in Library.
' if used 1axis Sequence Motion, Must be Set *dPosition one Array.
Public Declare Function AxmSeqAddNode Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dPosition As Double, ByVal dVelocity As Double, ByVal dAcceleration As Double, ByVal dDeceleration As Double, ByVal dNextVelocity As Double) As Long

' Return Node Index number of Sequence Motion.
Public Declare Function AxmSeqGetNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lCurNodeNo As Long) As Long

'  Return All node count of Sequence Motion.
Public Declare Function AxmSeqGetTotalNodeNum Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef lTotalNodeCnt As Long) As Long

' Return Sequence Motion drive status  of specific SeqMap.
' dwInMotion : 0(Drive end), 1(In drive).
Public Declare Function AxmSeqIsMotion Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByRef dwInMotion As Long) As Long

' Clear Sequence Motion Memory
Public Declare Function AxmSeqWriteClear Lib "AXL.dll" (ByVal lSeqMapNo) As Long

' Stop sequence motion
' dwStopMode : 0(EMERGENCY_STOP), 1(SLOWDOWN_STOP)
Public Declare Function AxmSeqStop Lib "AXL.dll" (ByVal lSeqMapNo As Long, ByVal dwStopMode As Long) As Long
'========================================================================================================