# Protocole #

toute commande peut-être refusée par le serveur ou l'interlocuteur du client

## Syntaxe ##
    id@command:argLen arg1 ... argN
    
    id : identifiant de celui qui a envoyé la commande
    command : nom de la commande à effectuer
    argLen : nombre d'arguments
    arg1-N : arguments / données
    
   
Les commandes qui sont envoyés au serveur qui n'ont pas l'id du serveur sont envoyés à l'id cible par le serveur, 
 
## Commandes reçues du serveur ##
    
        id@reply:2 command (ok / fail)
            command contient la commande envoyé précédemment à id
            ( ok / fail ) est la réponse qui permet de vérifier si la commande est réussie
         
        id@map:3 realMapX realMapY data
            realMapX est la position x du morceau de la map sur la map entière
            realMapY est la position y du morceau de la map sur la map entière
            data content le morceau de la map accessible
        
        id@update:3 x y vie
            x contient la position en x du client vu/connue par id
            y contient la position en y du client vu/connue par id
            vie contient la vie du client vu/connue par id
     
## Commandes envoyés par le client ##

 
         id@getMap:0
             permet d'obtenir la map connue/vue par id à la position du client
         id@message:1 message
             permet d'envoyer un message à id
         id@move:3 entity x y
            Réalise une demande de déplacement à la position x,y de l'entité entity
         id@auth:1 clientName
            Authentifie le client sur le serveur (ie. qu'il peut se connecter). Valeur de retour du serveur : id@reply: 2 auth ok
