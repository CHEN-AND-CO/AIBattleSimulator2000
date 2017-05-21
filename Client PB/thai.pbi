;############################################
;#        Threaded AI for the game          #
;############################################
;/!\ : DISCLAIMER : Si t'as pensé à du riz thai en ouvrant ce fichier, sérieux, pends-toi.
;
;IMPORTANT : L'IA est implémentée sous forme d'un thread. Ce thread reçoit UN argument de type Player (cf classe Player dans 
;entity.pbi. La gestion est faite en interne sur les membres de Player. La map est accessible en Global GameMap()
;
;TODO : des trucs

; IDE Options = PureBasic 5.51 (Linux - x64)
; CursorPosition = 9
; EnableXP
; CompileSourceDirectory
; EnableCompileCount = 0
; EnableBuildCount = 0
; EnableExeConstant