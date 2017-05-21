;##############################################
;# Game implementation for AIBattle           #
;##############################################
;This is unsed for test purposes

XIncludeFile "entity.pbi"

Soldat.NewPlayer = InitPlayer(10,10,25)
Sorcier.NewPlayer = InitPlayer(10,25,50)

Debug Soldat\GetHealth()
Debug "Le soldat va aller en 10,25 et attaquer le sorcier"
Soldat\Move(0,15)
Soldat\Attack(Sorcier)
Debug "Le sorcier a "+Sorcier\GetHealth()+" points de vie"
Sorcier\Reheal(10)
Debug "Le sorcier a utilisé son mana pour avoir "+Sorcier\GetHealth()+" points de vie"

Enumeration Materials
  #Grass
  #Wood
  #Water
  #Rock
  #Metal
EndEnumeration

#MapWidth = 42
#MapHeight = 42;!FIXME : valeurs?
#NbPlayers = 20

Global Dim GameMap(#MapWidth, #MapHeight)

Global NewList Players.NewPlayer()

For i=0 To #NbPlayers ;Création d'une ligne de 20 joueurs
  AddElement(Players())
  Players() = InitPlayer(i,10,25)
Next

; IDE Options = PureBasic 5.51 (Linux - x64)
; CursorPosition = 34
; FirstLine = 4
; EnableXP
; CompileSourceDirectory
; EnableCompileCount = 3
; EnableBuildCount = 0
; EnableExeConstant