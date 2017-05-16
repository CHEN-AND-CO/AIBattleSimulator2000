;################################################
;#          Protocole de communication          #
;################################################

Procedure AuthClient(socket)
  Protected *out = MakeServerCommand(socket,"auth:0")
  Protected *inputBuffer = AllocateMemory(#InputBufferSize)
  
  SendNetworkData(socket,*out,MemorySize(*out))
  
  Repeat
    netEvent = NetworkClientEvent(socket)
    
    Select netEvent
      Case #PB_NetworkEvent_Data
        receivedBytes = ReceiveNetworkData(socket, *inputBuffer,#InputBufferSize)
        serverResponse$ = PeekS(*inputBuffer,receivedBytes,#PB_UTF8)
        Debug "Server said : "+serverResponse$
        
        If FindString(serverResponse$,"auth ok")
          ProcedureReturn 1
        EndIf
        
      Case #PB_NetworkEvent_Disconnect
        ProcedureReturn 0
        
      Default
        Delay(10)
        cpt +1
    EndSelect
    
  Until (cpt/10) > #MaxAuthTimeout
EndProcedure

Procedure MakeServerCommand(socket,Command$)
  Protected *out, str$, param$, paramNumber
  
  param$ = StringField(Command$,2,":")
  paramNumber = CountString(param$," ")
  
  str$ = Str(socket)+"@" + StringField(Command$,1,":") + Str(paramNumber)+" "+param$
  Debug "Command : "+str$

  *out = AllocateMemory(StringByteLength(str$,#PB_UTF8)+1)
  PokeS(*out,str$,-1,#PB_UTF8)
  
  ProcedureReturn *out
EndProcedure

; IDE Options = PureBasic 5.60 (Windows - x64)
; CursorPosition = 31
; Folding = -
; EnableXP