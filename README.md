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
