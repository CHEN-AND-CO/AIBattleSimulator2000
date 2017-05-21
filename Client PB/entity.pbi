;Définition des parametres de l'entité
Structure Entity
  *DSVT ;Data Section Virtual Table
  
  x.i
  y.i
  Health.i
  canMove.b
EndStructure

Structure Player Extends Entity
  attack.i
  shield.i
  HoldedMaterial.i
  
  thAI.i
EndStructure

Structure Building Extends Entity
  Map Materials.i()
  Name.s
EndStructure


Interface NewEntity ;Entité de jeu
  Move.i(x,y, Mode=#PB_Relative) ;Déplace aux coordonnées (x,y) absolues ou relatives
  GetHealth.i()                  ;Renvoie la santé de l'entité  (max. 100)
  Reheal.i(Health)               ;Ajoute Health à la santé de l'entité
  
  Destroy.i()       ;Destructeur
EndInterface

Interface NewPlayer Extends NewEntity ;Entité de type joueur
  AttachAI.i(*thAIManager)            ;Attache une IA a l'entité et la pilote
  DetachAI.i()                        ;Détache l'IA attachée à cette entité (Retourne 1 si l'IA a été détachée correctement)
  
  Attack.i(*Target.Entity)   ;Attaque l'entité Target
EndInterface

Interface NewBuilding Extends NewEntity ;Entité de type batiment
  Lock.i(x,y)                           ;Verouille la position
  GetStock(Material.s)                  ;Renvoie la quantité de <matériau> contenue dans le batiment
  SetStock(Material.s, Quantity.f)      ;Modifie la <Quantity> de <matériau> dans le batiment
  
  Pick(Material.s, Quantity.f)          ;Prend une <Quantity> de <Material> dans le batiment
  Add(Material.s, Quantity.f)           ;Ajoute <Quantity> de <Material> dans le batiment
EndInterface

;Initialisation d'un joueur
Procedure.i InitPlayer(x, y, attack)
  Protected *Object.Player = AllocateMemory(SizeOf(Player))
  
  ;Renseigner les propriétés objet
  If *Object
    *Object\DSVT = ?Class
    *Object\x = x
    *Object\y = y
    *Object\canMove = 1
    *Object\Health = 100
    *Object\attack = attack
  EndIf
  
  ProcedureReturn *object
EndProcedure


;##############
;#  Méthodes  #
;##############

Procedure Move(*this.Entity,x,y,Mode=#PB_Relative)
  If *this\canMove
    If Mode = #PB_Relative
      *this\x + x
      *this\y + y
    ElseIf Mode = #PB_Absolute
      *this\x = x
      *this\y = y
    EndIf
  EndIf
EndProcedure

Procedure GetHealth(*this.Entity)
  ProcedureReturn *this\Health
EndProcedure

Procedure Reheal(*this.Entity, Health)
  *this\Health + Health
EndProcedure

Procedure Destroy(*this.Entity)
  FreeMemory(*this)
EndProcedure

Procedure AttachAI(*this.Player,*thAIManager)
  If *this\thAI = CreateThread(*thAIManager,*this)
    ProcedureReturn 1
  Else
    ProcedureReturn 0
  EndIf
EndProcedure

Procedure DetachAI(*this.Player)
  Protected thPtr= *this\thAI
  *this\thAI = 0
  If Not WaitThread(thPtr,100)
    *this\thAI = thPtr
    ProcedureReturn 0
  Else
    ProcedureReturn 1
  EndIf
EndProcedure

Procedure Attack(*this.Player,*Target.Entity)
  *Target\Health - *this\attack
EndProcedure

Procedure Lock(*this.Building,x,y)
  *this\x = x
  *this\y = y
  *this\canMove = 0
EndProcedure

Procedure GetStock(*this.Building, Material.s)
  If FindMapElement(*this\Materials(),Material)
    ProcedureReturn *this\Materials(Material)
  Else
    ProcedureReturn -1  ;Pas de ce Material dans ce batiment
  EndIf
EndProcedure

Procedure SetStock(*this.Building, Material.s, Quantity.f)
  *this\Materials(Material) = Quantity
EndProcedure

Procedure Pick(*this.Building, Material.s, Quantity.f)
  If *this\Materials(Material) - Quantity > 0
    *this\Materials(Material) = *this\Materials(Material) - Quantity
    ProcedureReturn 1
  Else
    ProcedureReturn 0
  EndIf
EndProcedure

Procedure Add(*this.Building, Material.s, Quantity.f)
  *this\Materials(Material) = *this\Materials(Material) + Quantity
EndProcedure

;Datasection des méthodes
DataSection
  Class:
  Data.i @Move()
  Data.i @GetHealth()
  Data.i @Reheal()
  Data.i @Destroy()
  Data.i @AttachAI()
  Data.i @DetachAI()
  Data.i @Attack()
  Data.i @Lock()
  Data.i @GetStock()
  Data.i @SetStock()
  Data.i @Pick()
  Data.i @Add()
EndDataSection
; IDE Options = PureBasic 5.51 (Linux - x64)
; CursorPosition = 162
; FirstLine = 128
; Folding = ---
; EnableXP
; CompileSourceDirectory
; EnableCompileCount = 1
; EnableBuildCount = 0
; EnableExeConstant