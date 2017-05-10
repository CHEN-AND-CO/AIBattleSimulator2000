#Protocole# 

Généralités :
    Le serveur est prioritaire sur le client, lequel doit être authentifié sur le serveur.
    Le serveur peut envoyer des commandes au client.

1 - Authentification d'un client :
    Un client est identifié par son socket et par un nom d'utilisateur (libre)
    Le client envoie au serveur un message composé de : "ACK:[username]".
    Le serveur répond par "ACK:OK"
    Le client est alors connecté

2 - Demande de la map :
    Le client (lorqu'il se connecte ou aprés une éventuelle erreur ou déconnection) demande au
    serveur la map (enfin la zone de départ) : "MAP:PLSGIVEMEAMAP"
    Le serveur répond en envoyant la map comme suit : "MAP:[taille_x]:[taille_y]:[données]"

3 - Actualisation :
<<<<<<< HEAD
    A chaque gametick le client envoie sa (nouvelle) position comme ceci : "ACT:MOV:[positions]"
    Le serveur répond par "MOV:OK:[newmap]" si le déplacement est autorisé , où [newmap] est la nouvelle
=======
    A chaque gametick le client envoie sa (nouvelle) position comme ceci : "POS:<positions>"
    Le serveur répond par "POS:OK:[newmap]" si le déplacement est autorisé , où [newmap] est la nouvelle
>>>>>>> origin/pureshit
    version de la map telle que découverte par le client aprés le déplacement.
    Si le déplacement est interdit, il répondra par "MOV:NOPE"

    /*
    Le gametick (temps entre deux "frames" de jeu coté serveur) est prédéfini à l'avance, et si un client ne s'actualise
    pas durant un certain nombre de gameticks, il est alors déconnecté et devra se réauthentifier.
    */

4 - Actions (on verra dans le turfu) :
<<<<<<< HEAD
    Pour exécuter une action custom sur la map, le client enverra "ACT:[action]:[paramétres]", où [action] est un identifiant
=======
    Pour exécuter une action custom sur la map, le client enverra "ACT:[actioncode]", où [actioncode] est un identifiant
>>>>>>> origin/pureshit
    d'une action (ramasser objet, miner un truc, ouvrir une porte...)

5 - Commades (coté serveur) :
    Le serveur peut envoyer des commandes à un client (ban, avertissement, fin de partie...)
    Cela se fait en utilisant "CMD:[commande] [param1] ... [param_n]"
<<<<<<< HEAD

6 - Ping
    Pour confirmer la connection (vérifier que le client est là ), le serveur procéde réguliérement à l'envoi de "ACK" auquels le
    client répond "ACK".
=======
>>>>>>> origin/pureshit
