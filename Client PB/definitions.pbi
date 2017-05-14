
#InputBufferSize = 2048
#MaxAuthTimeout = 5000

Declare AuthClient(socket)
Declare MakeServerCommand(socket,Command$)

XIncludeFile "protocol.pbi"
XIncludeFile "client_ui.pbi"
; IDE Options = PureBasic 5.60 (Windows - x64)
; CursorPosition = 2
; EnableXP