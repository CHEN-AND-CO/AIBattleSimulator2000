
IncludeFile "definitions.pbi"

ServerURI$ = "127.0.0.1"
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
  EndIf
  
Else
    MessageRequester("Error","Unable to initialize the network component. Check your network.",#PB_MessageRequester_Error) : End
EndIf
; IDE Options = PureBasic 5.50 (Linux - x64)
; ExecutableFormat = Console
; CursorPosition = 9
; EnableXP