STRUCTURE PROJET:
-Les exécutables sont dans /BuildC++/buil/Release.
-/RAT contient le code source et des .bat espiègle pouvant être
exécuté MANUELLEMENT ("put", suivi de "start") sur l'ordinateur infecté.
-La racine contient des .bat pouvant lancé les exécutables du 
dossier Release. Par défaut, uilises 127.0.0.1 comme adresse.

RÉSUMÉ DÉROULEMENT:
-Distributor.exe attend une connection de l'injecteur pour lui envoyer RAT.exe.
-Injector.exe se connecte à Distributor.exe, puis demande, reçois et exécute RAT.exe.
***IMPORTANT: L'injecteur redémarre le RAT.exe tout les 5 secondes si
***RAT.exe est terminé d'une façon innatendu, il doit être terminé avec
***la commande "exit" à partir de RATremote.
-Lorsque lancé par l'injecteur, RAT.exe se connecte à RATremote.
-RATremote attand une connection du RAT.exe pour avoir accès au PC zombie.

LANCEMENT:
Les exécutables peuvent être lancés dans n'importe quel ordre, ils 
attendront simplement de recevoir une réponse à leur tantative de
connection/réception.

Les exécutables sont lancés en ligne de commande avec les arguments suivant:
Hote:
    -Distributor.exe <Num_PortA>  
    -RATremote.exe <Num_PortB>
Zombie:
    -Injector.exe <NomPCdistant|Addr_IP> <Num_PortA> <Fichier_a_Envoyer.exe>
    -RAT.exe <NomPCdistant|Addr_IP> <Num_PortA>

Note: Injector à été hard codé avec <127.0.0.1> <2020> <RAT.exe> comme parametres,
      décommenter #define HARD_CODED_ARGS pour utiliser la ligne de commande.
Note: RAT à été hard codé avec <127.0.0.1> <2030> comme parametres,
      décommenter #define HARD_CODED_ARGS pour utiliser la ligne de commande
      (Les parametres seront recu de Injector.exe, 127.0.0.1 2030 par défaut).






