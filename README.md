# Coil Winder

A **low-cost, precision coil winding machine** built from 3D-printed parts and off-the-shelf components, designed for sensing coils, charging coils, solenoids, and similar applications. See detailed system descriptions and methodology in **Design Docs**. 

---

## Highlights
- Winds coils up to **30 mm length × 250 mm diameter**
- Single-piece **3D-printed frame** for tight tolerances and fast assembly
- **Arbor + Eye architecture** for accurate wire placement
- **Stepper-driven arbor** with 3:1 belt reduction for consistent tension
- **Worm-gear driven eye (40:1)** for fine linear positioning
- Custom **4-layer driver PCB** (STM32L432 + DRV8825)
- **FreeRTOS-based firmware** with prioritized motor control and UI tasking

---

## System Overview
- **Arbor Assembly:** Rotates the coil form and maintains wire tension  
- **Eye Assembly:** Precisely guides wire placement across the arbor  
- **Driver Board:** Handles UI, motor drivers, and peripherals  

---

## Tech Stack
STM32L432 · DRV8825 · FreeRTOS · Step/Dir Steppers · 4-layer PCB · 3D Printing

---

## Capabilities
- Tightly packed first-layer winding
- Supports **30 AWG wire**
- Integrated button-based user interface

