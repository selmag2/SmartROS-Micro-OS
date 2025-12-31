# SmartROS Micro-OS

## Description
SmartROS Micro-OS est un micro-système intelligent basé sur ROS 2 pour systèmes embarqués.
Il fournit des mécanismes de supervision, de détection de pannes et d’auto-réparation (auto-healing)
pour améliorer la fiabilité des nœuds ROS dans des environnements embarqués.

## Objectifs du projet
- Superviser l’état des nœuds ROS 2
- Détecter les défaillances (nœud bloqué ou arrêté)
- Relancer automatiquement les nœuds défaillants (auto-healing)
- Fournir une architecture modulaire et extensible

1️⃣ Contexte microcontrôleur / embarqué:

Sur un PC ou serveur, le système d’exploitation et le hardware ont déjà des outils intégrés pour monitoring et auto-réparation.

Sur microcontrôleur / ESP32 / Raspberry Pi, ce n’est pas le cas :

Pas de supervision automatique des tâches spécifiques à ton application.

Pas de self-healing pour des capteurs ou modules logiciels spécifiques.

Les OS embarqués classiques (FreeRTOS, Arduino) ne fournissent pas de couche intelligente.

💡 Donc la valeur ajoutée ici est : le micro-OS agit comme un “cerveau local” spécialisé pour ton système embarqué, pas pour l’ordinateur.

2️⃣ Multi-tâches intelligentes:
SmartROS Micro-OS priorise les tâches critiques :

Lecture de capteurs

Communication ROS / MQTT

Diagnostic

Il peut adapter dynamiquement la fréquence ou arrêter une tâche non critique si le système est chargé.

3️⃣ Self-healing spécifique:

Si un capteur ou un nœud ROS tombe, ton micro-OS peut :

Redémarrer uniquement la tâche défaillante

Basculer en mode dégradé

Isoler un module en erreur

Le PC classique ne fait pas ça pour ton application spécifique automatiquement.

4️⃣ Visualisation et supervision intégrée:

on peut montrer  un dashboard ROS où chaque nœud est visible, avec les réactions automatiques du micro-OS.

5️⃣ Extensible et portable:

Le micro-OS peut être porté vers micro-ROS sur ESP32/STM32, où les PC ne peuvent pas gérer ce hardware directement.

L’idée clé : intelligence embarquée à proximité du hardware.

## Plateformes ciblées
- Raspberry Pi
- ESP32 (via micro-ROS, étape ultérieure)

## Technologies
- ROS 2 Humble
- Python (première phase)
- C++ (phase avancée)
- Ubuntu 22.04

## Architecture générale
SmartROS Micro-OS fonctionne comme une couche de supervision au-dessus de ROS 2
et ne remplace pas ROS, mais l’enrichit avec des mécanismes de contrôle système.

## État du projet
🟡 Phase 1 : Mise en place de l’environnement ROS 2  
⬜ Phase 2 : Heartbeat node  
⬜ Phase 3 : System monitor  
⬜ Phase 4 : Auto-healing  
⬜ Phase 5 : Intégration ESP32
# SmartROS-Micro-OS
