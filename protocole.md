# Protocole #

	## Syntaxe ##

	id@command:argLen arg1 ... argN

	'id' est l'identifiant du messager
	'command' est l'action à effectuer
	'argLen' est le nombre d'arguments
	'argN' sont les arguments

	## Commandes Client ##

		### Envoi ###

		id@getTerrainMap:0 //Demande la map du terrain

		id@getEntitysMap:0 //Demande la map des entités

		id@getBuildingsMap:0 //Demande la map des batiments

		id@move:5 r g b int direction

		id@update:3 x y hp

		id@auth:2 name r g b

		id@attack:5 r g b int direction

		id@collect:5 r g b int direction

		id@putInTown:5 r g b int direction

		id@addEntity:5 r g b int entType

		id@addBuildind:5 r g b int buildType

		id@getPlayer:3 r g b

		### Reception ###

		id@reply:1 command (ok/fail)

		id@terrain:1 data

		id@entitys:14 x y r g b hp type x y r g b hp type

		id@buildings:14 x y r g b hp type x y r g b hp type

		id@player:4 ressourceType amount ressoureType amount
