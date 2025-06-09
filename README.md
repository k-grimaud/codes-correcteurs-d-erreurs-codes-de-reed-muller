Correction d'erreurs en communication, Codes de Reed Muller.
  
  Lors de la transmission de données, les canaux de communication peuvent être sujets à des bruits. Ce phénomène introduit des erreurs à la réception du message. Pour palier cette problématique, des méthodes ont été développées pour permettre la détection et la correction des erreurs. Elles consistent en général à séparer le message en plusieurs blocs et d'appliquer la méthode blocs par blocs. [1/2/5]
  
  Une première approche simple est d'envoyer le message plusieurs fois. On effectue ensuite unvote de majorité pour déterminer le message originel. Cependant, pour un nombre pair d'envois,il n'est, dans certains cas, pas possible de corriger le message. Cette méthode est fiable pour un nombre limité d'erreurs : s'il y a plus d'une erreur sur deux, le code corrigera en un message différent du message originel. Par exemple : le message 1 sera codé en 111 et après l'introduction d'erreurs il peut être reçu comme étant 100 ce qui sera interprété comme un 0, ou encore le message 1 une fois codé en 111 peut se transformer après des erreurs en 000. Dans ce cas les erreurs ne sont pas détectées. De plus il faut utiliser plusieurs fois la taille du message pour espérer détecter une erreur et peut-être la corriger. [1/2] 
  
  Pour réduire la place utilisée on peut choisir un bit de contrôle. On l'ajoute au message de façon à obtenir un nombre pair de 1 : 110 -> 1100 et 001 -> 1001 par exemple. Il est alors possible de détecter les erreurs grâce à la parité du message tout en gardant un minimum de redondance. Il ne sera néanmoins pas possible de détecter un nombre pair d'erreurs. [1/2/5] 
  
  On pourra alors utiliser les codes de Hamming pour détecter et corriger les erreurs : On organise le message en un carré de 4x4 bits par exemple. On place 11 bits de message auxquels seront ajoutés 5 bits de contrôle de façon à les retrouver sur les emplacements 1-1, 1-2, 1-3, 2-1, 3-1. Il ne restera plus qu'à faire des tests de parité sur des lignes et des colonnes bien choisies ce qui permettra, en croisant les résultats, de détecter jusqu'à deux erreurs et d'en corriger une. [1/2]
  
  Des codes correcteurs avec une meilleure résilience (leur capacité à détecter et corriger des erreurs) plus efficaces et complexes ont été trouvés au fur et a mesure du temps, comme les codes de Reed Solomon qui utilisent des propriétés d'algèbre linéaire pour reconstituer les messages. Nous nous concentrerons sur le cas particulier des codes de Reed Muller plus simples et plus facile à implémenter. Ces codes ont été utilisés par la NASA lors de l'utilisation de la sonde Mariner 9, dans les années 70, permettant de recevoir des photographies en 64 niveaux de gris de la surface de mars. En effet, il était difficile de recevoir des images nettes car jusqu'à 25 pourcent du message (envoyé par ondes radio) pouvait être corrompu par les différents rayons cosmiques et le trajet long de 78 millions de kilomètres. [3/4]



SOURCES 

[1] TOOD K.MOON : Error correction coding - mathematical methods and alrorithms, partie I.1 Introduction and fondations - A context for Error correction coding : ISBN : 978-0-471-648000 - éditeur : Hoboken, NJ : Wiley-Interscience, cop. 2005 - Utah State University

[2] 3BLUE1BROWN : Mais que sont les codes de Hamming ? L'origine de la correction d'erreur : https://youtu.be/X8jsijhllIA - 4 sept. 2020

[3] DAVID F. BRAILSFORD : Building the H5 Reed-Muller Code used by Mariner 9 : http://www.eprg.org/computerphile/h5code.pdf#:~:text=The%20multi-error-correcting%20code%20used%20on%20the%20Mariner%209,early%201950s%20by%20Irving%20Reed%20and%20David%20Muller. - School of Computer Science, University of Nottingham, UK - 2017

[4] TOOD K.MOON : Error correction coding - mathematical methods and alrorithms, partie II.8.3 Block Codes - Other Important Block Codes - Reed-Muller Codes : ISBN : 978-0-47164800-0 - éditeur : Hoboken, NJ : Wiley-Interscience, cop. 2005 - Utah State University

[5] PIERRE ABBRUGIATI : Introduction aux codes correcteurs d’erreurs : https://www.lirmm.fr/~chaumont/download/cours/codescorrecteur/Cours_Pierre_Abbrugiati.pdf - 23 janvier 2006

[6] DAVID F. BRAILSFORD : 64 Shades of Martian Grey - Computerphile : https://www.youtube.com/watch?v=NRv3HMEyuDE&ab_channel=Computerphile - 5 avr. 2017
