(english below)


_______ français _______

Correction d'erreurs en communication, Codes de Reed Muller.

  Lors de la transmission de données, les canaux de communication peuvent être sujets à des bruits. Ce phénomène introduit des erreurs à la réception du message. Pour palier cette problématique, des méthodes ont été développées pour permettre la détection et la correction des erreurs. Elles consistent en général à séparer le message en plusieurs blocs et d'appliquer la méthode blocs par blocs. [1/2/5]
  
  Une première approche simple est d'envoyer le message plusieurs fois. On effectue ensuite unvote de majorité pour déterminer le message originel. Cependant, pour un nombre pair d'envois,il n'est, dans certains cas, pas possible de corriger le message. Cette méthode est fiable pour un nombre limité d'erreurs : s'il y a plus d'une erreur sur deux, le code corrigera en un message différent du message originel. Par exemple : le message 1 sera codé en 111 et après l'introduction d'erreurs il peut être reçu comme étant 100 ce qui sera interprété comme un 0, ou encore le message 1 une fois codé en 111 peut se transformer après des erreurs en 000. Dans ce cas les erreurs ne sont pas détectées. De plus il faut utiliser plusieurs fois la taille du message pour espérer détecter une erreur et peut-être la corriger. [1/2] 
  
  Pour réduire la place utilisée on peut choisir un bit de contrôle. On l'ajoute au message de façon à obtenir un nombre pair de 1 : 110 -> 1100 et 001 -> 1001 par exemple. Il est alors possible de détecter les erreurs grâce à la parité du message tout en gardant un minimum de redondance. Il ne sera néanmoins pas possible de détecter un nombre pair d'erreurs. [1/2/5] 
  
  On pourra alors utiliser les codes de Hamming pour détecter et corriger les erreurs : On organise le message en un carré de 4x4 bits par exemple. On place 11 bits de message auxquels seront ajoutés 5 bits de contrôle de façon à les retrouver sur les emplacements 1-1, 1-2, 1-3, 2-1, 3-1. Il ne restera plus qu'à faire des tests de parité sur des lignes et des colonnes bien choisies ce qui permettra, en croisant les résultats, de détecter jusqu'à deux erreurs et d'en corriger une. [1/2]
  
  Des codes correcteurs avec une meilleure résilience (leur capacité à détecter et corriger des erreurs) plus efficaces et complexes ont été trouvés au fur et a mesure du temps, comme les codes de Reed Solomon qui utilisent des propriétés d'algèbre linéaire pour reconstituer les messages. Nous nous concentrerons sur le cas particulier des codes de Reed Muller plus simples et plus facile à implémenter. Ces codes ont été utilisés par la NASA lors de l'utilisation de la sonde Mariner 9, dans les années 70, permettant de recevoir des photographies en 64 niveaux de gris de la surface de mars. En effet, il était difficile de recevoir des images nettes car jusqu'à 25 pourcent du message (envoyé par ondes radio) pouvait être corrompu par les différents rayons cosmiques et le trajet long de 78 millions de kilomètres. [3/4]


_______ english _______

Error correcting in communications : Reed Muller codes

  During data transmission, communication channels can be subject to noise. This phenomenon introduces errors upon message reception. To address this issue, methods have been developed to enable error detection and correction. They generally involve dividing the message into several blocks and applying the method block by block. [1/2/5]

  A first simple approach is to send the message multiple times. A majority vote is then carried out to determine the original message. However, for an even number of transmissions, in some cases it is not possible to correct the message. This method is reliable for a limited number of errors: if more than half are erroneous, the code will correct to a message different from the original. For example: the message 1 will be encoded as 111 and, after errors, may be received as 100, which will be interpreted as 0; or the message 1 once encoded as 111 could be transformed after errors into 000. In this case, the errors are not detected. Moreover, it is necessary to use several times the message size in order to hope to detect an error and possibly correct it. [1/2]

  To reduce the space used, one can choose a control bit. It is added to the message so as to obtain an even number of 1s: 110 → 1100 and 001 → 1001, for example. It then becomes possible to detect errors via message parity while keeping minimal redundancy. However, an even number of errors cannot be detected. [1/2/5]

  Hamming codes can then be used to detect and correct errors: the message is arranged in a 4x4 bit square, for example. 11 message bits are placed, to which 5 control bits are added, positioned at locations 1-1, 1-2, 1-3, 2-1, 3-1. Parity tests are then performed on well-chosen rows and columns, which allows, by cross-referencing the results, to detect up to two errors and correct one. [1/2]

  More effective and resilient error-correcting codes (their ability to detect and correct errors) have been developed over time, such as Reed–Solomon codes, which use properties of linear algebra to reconstruct messages. We will focus on the particular case of Reed–Muller codes, which are simpler and easier to implement. These codes were used by NASA with the Mariner 9 probe in the 1970s, allowing the reception of 64-level grayscale photographs of the Martian surface. Indeed, it was difficult to receive clear images, as up to 25 percent of the message (sent by radio waves) could be corrupted by various cosmic rays and the long 78-million-kilometer journey. [3/4]



_______ sources _______

[1] TOOD K.MOON : Error correction coding - mathematical methods and alrorithms, partie I.1 Introduction and fondations - A context for Error correction coding : ISBN : 978-0-471-648000 - éditeur : Hoboken, NJ : Wiley-Interscience, cop. 2005 - Utah State University

[2] 3BLUE1BROWN : Mais que sont les codes de Hamming ? L'origine de la correction d'erreur : https://youtu.be/X8jsijhllIA - 4 sept. 2020

[3] DAVID F. BRAILSFORD : Building the H5 Reed-Muller Code used by Mariner 9 : http://www.eprg.org/computerphile/h5code.pdf#:~:text=The%20multi-error-correcting%20code%20used%20on%20the%20Mariner%209,early%201950s%20by%20Irving%20Reed%20and%20David%20Muller. - School of Computer Science, University of Nottingham, UK - 2017

[4] TOOD K.MOON : Error correction coding - mathematical methods and alrorithms, partie II.8.3 Block Codes - Other Important Block Codes - Reed-Muller Codes : ISBN : 978-0-47164800-0 - éditeur : Hoboken, NJ : Wiley-Interscience, cop. 2005 - Utah State University

[5] PIERRE ABBRUGIATI : Introduction aux codes correcteurs d’erreurs : https://www.lirmm.fr/~chaumont/download/cours/codescorrecteur/Cours_Pierre_Abbrugiati.pdf - 23 janvier 2006

[6] DAVID F. BRAILSFORD : 64 Shades of Martian Grey - Computerphile : https://www.youtube.com/watch?v=NRv3HMEyuDE&ab_channel=Computerphile - 5 avr. 2017
