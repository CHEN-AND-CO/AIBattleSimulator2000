If InitNetwork()  And CreateNetworkServer(1,53000)
  
  *in = AllocateMemory(4096)
  OpenConsole()
  PrintN("Server is running")
  
  Repeat
    sEvent = NetworkServerEvent()
    socket = EventClient()
    Select sEvent
      Case #PB_NetworkEvent_Connect
        PrintN(Str(socket)+" connected on "+IPString(GetClientIP(socket)))
        
      Case #PB_NetworkEvent_Disconnect
        PrintN(Str(socket)+" disconnected from "+IPString(GetClientIP(socket)))
        
      Case #PB_NetworkEvent_Data
        recSize = ReceiveNetworkData(socket,*in,4096)
        PrintN(Str(socket)+" send "+Str(recSize)+" bytes of data:"+PeekS(*in,recSize,#PB_Ascii))
        
      Case #PB_NetworkEvent_None
        Delay(10)
        
    EndSelect
  ForEver
  
Else
  Debug "erreur"
EndIf

; IDE Options = PureBasic 5.50 (Linux - x64)
; ExecutableFormat = Console
; CursorPosition = 26
; EnableXP