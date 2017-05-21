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
; IDE Options = PureBasic 5.51 (Linux - x64)
; CursorPosition = 7
; EnableXP
; CompileSourceDirectory
; EnableCompileCount = 2
; EnableBuildCount = 0
; EnableExeConstant