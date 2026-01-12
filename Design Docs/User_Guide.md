# User Guide

This document provides steps and recommendations to get this project up and running

## Overview 

This project intends to provide a simple way of winding wire coils. It's composed of a few main assemblies:

- The *Frame* is a single printed part that contains the  *Arbor* and *Eye* assemblies

    - The *Arbor* is the form on which the coil is wound
    - The *Arbor Motor Assembly* contains the *Arbor* and components used to rotate it
    - The *Eye* sets the position of the wire relative to the arbor
    - The *Eye Motor Assembly* contains the *Eye* and components used to drive it's position


## Assembly Instructions  

### Parts List


| Part                                   | Qty |
|:-------------------------------------- |:---:|
| Ball Bearing (22mm OD, 8mm ID, 7mm Wd) | 2   |
| Ball Bearing (10mm OD, 5mm ID, 4mm Wd) | 3   |
| Shaft Collar (5mm ID)                  | 1   |
| Shaft Collar (8mm ID)                  | 2   |
| Worm Wheel (Module 0.5)                | 1   |
| Worm Gear (Module 0.5)                 | 1   |
| 4 wire NEMA 17 Stepper Motor (48mm Lg) | 2   |
| M2 x 10mm Screw                        | 2   |
| M3 x 10mm Screw                        | 9   |
| M5 x 12mm Screw                        | 2   |
| Shaft (8mm OD, 125mm Lg)               | 1   |
| Shaft (5mm OD, 75mm Lg)                | 1   |
| Timing Pulley (60T GT2 8mm ID)         | 1   |
| Timing Pulley (20T GT2 5mm ID)         | 1   |
| Timing Belt (GT2 200mm Lg)             | 1   |
| M3 x 10mm Set Screw                    | 2   |
| M3 Square Nut                          | 2   |
| M3 Heat Set Insert                     | 2   |


### Pre-Assembly

Choose an Arbor from the pre-generated list, or create your own with the included .f3d file. Print the Arbor, Eye and Frame, then proceed with the steps below.


### Arbor Motor Assembly

- Install a Stepper Motor on the Arbor Motor Assembly side of the frame using the M3 x 10mm Screws
- Press fit the 22mm OD Ball Bearings into the frame's pillow block assembly 
- Insert the 8mm shaft into the pillow block assembly, sliding on the 60T Pulley and Timing Belt. Secure both sides of the assembly with Shaft Collars (8mm ID).
- Wrap the timing belt around the 20T Timing Pulley, and slide it onto the Arbor Stepper motor shaft
- Press the M3 Square nuts into the Arbor, install the M3 x 10mm Set Screws in the square nuts. 
- Install the heat set insert, and screw on an M3 x 10mm screw. This is the *wire retention screw*.

[comment]: <> (Add images)


### Eye Motor Assembly

- Install a Stepper Motor on the Eye Motor Assembly side of the frame using the M3 x 10mm Screws
- Press fit a 10mm OD Ball Bearing into the printed V-Roller
- Use the M5 x 12mm Screw to capture the V-Roller in the Eye
- Install a heat set insert in the Eye, in the hole perpendicular to the 5mm shaft hole
- Grind a ≈1.5mm x ≈10mm Lg flat onto one end of the 5mm shaft
- Press fit 10mm OD Ball Bearings onto the frame's eye assembly 
- Insert the 5mm shaft into the eye assembly, with the ground end facing the arbor assembly. Do so while sliding on the Worm Wheel as shown. Secure the non-ground end of the assembly with Shaft a Collar (5mm ID)
- Insert the eye onto the open end of the 5mm shaft
- Install the worm on the Eye Stepper motor, allowing the worm wheel to rotate as you do so. Ensure that the Worm and Worm Wheel mesh correctly.
- Use the M2 x 10 mm Screws to install the limit switch

[comment]: <> (Add images)


## User Interface

Three buttons are used to navigate the user interface: 

- The (+) and (-) buttons increase or decrease the values of the field currently selected by the cursor. A long press on either button with rapidly increase or decrease the selected field. 
- The (SELECT) button move the cursor to the next field. The first 4 fields provide information about the coil being wound. 
    - Selecting the arrow field starts the coil winding process when either (+/-) button is pressed. 


## Setup and Usage

Setting up the Arbor correctly is crucial to winding a tight coil. 
- First wind a few centimeters of wire around the wire retention screw and tighten it to secure. Feed the wire through the thin slot inline with the the retention screw. 
- Rest the wire on top of the V-Roller, and install the wire spool on the spool holder.
- Install the Arbor along the Arbor Motor Assembly shaft, leaving the Arbor set screws loose.
- Select the values describing your chosen coil using the user interface, then start the coil winding process.
- Once the Eye has found it's home position, position the Arbor so that the wire is flush with the retention screw wall. Tighten the Arbor set screws to secure.
- Press the select button to begin the coil winding process
- Once the coil has finished winding, remove the Arbor and feed lengths of Lacing/Kapton tape through the 4 rectangular cutouts along the edge of the arbor. Secure the tape around the coil (this will maintain the coil's shape when removed from the Arbor.)
- Remove the coil from the Arbor