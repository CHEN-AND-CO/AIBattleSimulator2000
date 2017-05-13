
IncludeFile "definitions.pbi"
IncludeFile "protocol.pbi"
IncludeFile "client_ui.pbi"

#Port = 53000

If InitNetwork()
    ;do domething
Else
    MessageRequester("Error","Unable to initialize the network component. Check your network.")
    End
EndIf
; IDE Options = PureBasic 5.60 (Windows - x64)
; CursorPosition = 7
; EnableXP
