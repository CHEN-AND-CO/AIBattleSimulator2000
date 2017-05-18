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

		id@move:1 [0-3](left/right/up/down)

		id@update:3 x y hp

		id@auth:2 name color

		### Reception ###

		id@reply:2 command (ok/fail)

		id@terrain:1 data

		id@entitys:1 data

		id@buildings:1 data

		id@update:3 x y hp
		