﻿
IncludeFile "definitions.pbi"
IncludeFile "protocol.pbi"
IncludeFile "client_ui.pbi"

#Port = 53000

If InitNetwork()
  ;do domething
  
  socket = OpenNetworkConnection(ServerURI$,#Port)
  If socket
    
    ;Authentification client
    If Not AuthClient(socket) : End : EndIf
    
    ;Here starts the game :)
    ;TODO : un client.
    ;TODO : une IA
    ;TODO: des trucs
  Else
    MessageRequester("Error","Unable to open a connection to the game server",#PB_MessageRequester_Error) : End
Else
    MessageRequester("Error","Unable to initialize the network component. Check your network.",#PB_MessageRequester_Error) : End
EndIf
; IDE Options = PureBasic 5.60 (Windows - x64)
; CursorPosition = 15
; EnableXP