# SmartROS Micro-OS

[![license: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![ROS 2](https://img.shields.io/badge/ROS--2-Humble-orange.svg)](https://docs.ros.org/en/humble/)
[![status](https://img.shields.io/badge/status-alpha-yellow.svg)](#etat-du-projet)

Résumé
-------
SmartROS Micro-OS est un micro-système intelligent de supervision et d'auto-réparation conçu pour améliorer la fiabilité des nœuds ROS 2 sur plateformes embarquées (Raspberry Pi, ESP32 via micro-ROS, etc.). Il surveille l'état des nœuds, détecte les défaillances et effectue des actions de récupération ciblées (redémarrage d'une tâche, basculement en mode dégradé, isolation d'un module).

Principales fonctionnalités
---------------------------
- Supervision et heartbeat des nœuds ROS 2
- Détection automatique des défaillances (blocage, crash)
- Auto-healing : redémarrage ciblé et modes dégradés
- Priorisation dynamique des tâches (capteurs, communication, diagnostic)
- Dashboard de supervision (visualisation des nœuds et actions)
- Architecture modulaire et extensible pour microcontrôleurs et single-board computers

Pourquoi utiliser SmartROS Micro-OS ?
------------------------------------
Sur microcontrôleurs et SBCs (ESP32, Raspberry Pi), il manque souvent une couche de supervision applicative dédiée. SmartROS Micro-OS agit comme un "cerveau local" pour:
- Protéger les tâches critiques (lecture capteurs, communication)
- Faire du self-healing au niveau applicatif
- Réduire les interventions manuelles et augmenter la disponibilité

Prérequis
---------
- Ubuntu 22.04 OR compatible (pour la phase PC)
- ROS 2 Humble installé (voir https://docs.ros.org)
- Python 3.10+ (phase d'orchestration initiale)
- Pour la cible ESP32 : micro-ROS agent et toolchain (phase ultérieure)

Installation (exemple rapide)
-----------------------------
1. Cloner le dépôt:
   git clone https://github.com/selmag2/SmartROS-Micro-OS.git
2. Se placer dans l'espace de travail ROS 2:
   cd SmartROS-Micro-OS
3. Installer dépendances (exemple):
   pip install -r requirements.txt
4. Soudre et builder (si packages ROS 2 présents):
   colcon build

Quick start (exécution minimale)
--------------------------------
cd ~/ros2_ws

colcon build --symlink-install

source install/setup.bash

Architecture (aperçu)
---------------------
- HeartbeatNode : émet un signal périodique pour chaque nœud supervisé
- MonitorNode : consomme les heartbeats, détecte anomalies et escalade
- ManagerNode : applique les actions d'auto-healing (restart, isoler, degarde)
- Dashboard/UI : visualisation et historique des actions
(Schéma: ajouter un diagramme dans docs/architecture.png ou README)

Interfaces principales
----------------------
- Topics:
  - /smartros/heartbeat (publication régulière des états)
  - /smartros/events (événements de monitoring et actions)
- Services:
  - /smartros/restart_node (redémarrer un nœud supervisé)
  - /smartros/set_mode (basculer en mode dégradé/normal)
- Paramètres (exemples):
  - heartbeat_interval (s)
  - failure_threshold (nombre de heartbeats manquants avant alerte)

État du projet
--------------
- 🟡 Phase 1 : Mise en place de l’environnement ROS 2 (fait)
- ⬜ Phase 2 : Heartbeat node
- ⬜ Phase 3 : System monitor
- ⬜ Phase 4 : Auto-healing
- ⬜ Phase 5 : Intégration ESP32 / micro-ROS

Roadmap (extraits)
------------------
- Démo fonctionnelle Raspberry Pi (v0.1)
- Intégration micro-ROS pour ESP32
- Dashboard web temps réel + historique
- Tests automatisés et CI

Contribuer
----------
Les contributions sont bienvenues ! Pour contribuer :
1. Ouvrir une issue pour discuter de la fonctionnalité ou du bug.
2. Créer une branche dédiée "feature/..." ou "fix/...".
3. Soumettre une Pull Request bien documentée.

Ajouts recommandés 
- LICENSE 
- CONTRIBUTING.md
- CODE_OF_CONDUCT.md
- docs/architecture.png (diagramme)
- examples/ (démonstrations et scripts)
- requirements.txt et package.xml / setup.py si packages ROS 2

Contact
-------
Auteur: selmag2
Repo: https://github.com/selmag2/SmartROS-Micro-OS

FAQ / Dépannage
---------------
- Le node ne redémarre pas ? Vérifier les permissions et le gestionnaire de processus (systemd / supervisor).
- Heartbeat non reçu ? Vérifier la fréquence et la latence réseau.

Licence
-------
Ce dépôt n'inclut pas encore de fichier LICENSE. Il est recommandé d'ajouter une licence (p.ex. MIT) pour clarifier l'utilisation.

