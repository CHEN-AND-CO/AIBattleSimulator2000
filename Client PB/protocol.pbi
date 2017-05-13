;################################################
;#          Protocole de communication          #
;################################################

Procedure AuthClient(socket)
  Protected *out = AllocateMemory(#OutBufferSize);Inutile
  
  SendNetworkString(socket,"QUOI?",#PB_UTF8);Cf protocole, comment authentifier?
EndProcedure
; IDE Options = PureBasic 5.60 (Windows - x64)
; CursorPosition = 7
; Folding = -
; EnableXP