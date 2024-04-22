# Projet Gestion d'Aiguillage pour Modélisme Ferroviaire

## Description
Ce projet utilise un microcontrôleur ATmega328 pour la gestion des aiguillages d'un réseau de modélisme ferroviaire. Il intègre des servomoteurs pour les aiguillages, le protocole Loconet pour la communication, et fournit des retours visuels via des LEDs.

## Brochage des Pins
![Brochage des pins ATmega328](/images/pin%20atmega328p.jpg)

## Configuration des Broches
- GPIO 9 (PIN 13) : Servo
- GPIO 7 (PIN 11) : LocoNet TX
- GPIO 8 (PIN 12) : LocoNet RX
- GPIO 5 (PIN 9) : Relais

- GPIO 2 (PIN 01) : Pull-UP 1
- GPIO 3 (PIN 32) : Pull-UP 2

- GPIO 16 (PIN 25) : LED position aiguillage
- GPIO 17 (PIN 26) : LED DATA
- GPIO 18 (PIN 27) : LED ERREUR

## Matériel
- Microcontrôleur ATmega328 (ou une carte Arduino compatible)
- Servomoteurs pour aiguillages
- Système Loconet pour la communication
- LEDs pour l'indication de position, de données et d'erreur
- Boutons avec résistances de pull-up pour les entrées de détection

## Machine à État du Menu
Le menu est contrôlé par une série de commandes qui permettent à l'utilisateur de naviguer à travers les options de configuration et de voir les réglages actuels. Voici les commandes disponibles et leur effet :

- **R** : Voir les réglages actuels de la carte.
- **M** : Régler le point milieu du servo-moteur.
- **P** : Régler la fin de course gauche et droite du servo.
- **A** : Régler l'adresse de commande de l'aiguillage.
- **D** : Régler l'adresse de détection.
- **N** : Régler le nombre de moteurs d'aiguillage.
- **S** : Régler le sens logique du moteur d'aiguillage.
- **I** : Isoler la carte.
- **E** : Quitter le mode de configuration.
- **?** : Afficher le menu d'aide.

Pour utiliser ces commandes, entrez la lettre correspondante et appuyez sur 'Entrée'. Le système répondra en fonction de la commande entrée et vous dirigera vers le menu ou l'action appropriée.

### Diagramme d'État du Menu

![Diagramme d'état de la machine](/images//diagramme%20machine%20a%20etat.png)

## Installation
Assemblez le matériel selon le schéma de câblage.
Téléchargez le code source dans le microcontrôleur.
Configurez les paramètres initiaux via les menus série.

## Utilisation
Après le démarrage, le système exécute une routine de configuration et entre dans une boucle principale où il écoute les événements Loconet et les entrées de détection. Utilisez le menu série pour faire des ajustements.

## Contribution
Les contributions à ce projet sont les bienvenues. Veuillez soumettre vos pull requests pour examen.

## Licence
Ce projet est sous licence MIT.

## Auteurs
MARTIN Mathis