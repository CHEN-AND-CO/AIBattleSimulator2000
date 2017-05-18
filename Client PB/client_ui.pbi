#Main = 1

Procedure OpenUI()
  If InitSprite()
    If InitKeyboard()
      If InitMouse()
        If  OpenWindow(#Main, 0, 0, 800, 600, "AIBattleSimulateur3000", #PB_Window_ScreenCentered)
          OpenWindowedScreen(WindowID(#Main),0,0,800,600)
        Else
          MessageRequester("Erreur","Impossible d'ouvrir la fenêtre. Cassez un carreau.",#PB_MessageRequester_Error)
        EndIf
      Else
        MessageRequester("Erreur","Probléme de souris. Chassez votre chat svp.",#PB_MessageRequester_Error)
      EndIf
    Else
      MessageRequester("Erreur","Probléme de clavier. Pressez F2 pour continuer",#PB_MessageRequester_Error)
    EndIf
  Else
    MessageRequester("Erreur","Impossible d'initialiser le systéme graphique",#PB_MessageRequester_Error)
  EndIf
EndProcedure
      

; IDE Options = PureBasic 5.50 (Linux - x64)
; CursorPosition = 22
; Folding = -
; EnableXP