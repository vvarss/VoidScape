# 🛰️ VoidScape
A Real-Time Space Animation in OpenGL
Language: C with OpenGL

## 📌Project Overview
VoidScape is a real-time space animation created using OpenGL.
It visualizes a dynamic cosmic environment that includes animated planets, stars, asteroids, and camera motion through space.

## 🌕Project Objective
 To visualize a 3D solar system with animated planetary orbits and rotation using OpenGL transformations such as translation, rotation, and scaling and implement dynamic lighting, glowing effects, and object materials.

## 🌕Key Concepts 
| Concept | Code Implementation |
|---------|----------------------|
| 3D Transformations | Translation,Rotation,Scaling |
| Lighting & Material Properties |	Set in initLighting() using glLightfv() for ambient, diffuse, and specular components.|
| Procedural Generation	| Stars are randomly positioned using rand() in generateStars().|
| Animation & Timing | Controlled using glutTimerFunc() and updated in update() function every 33 ms.|
| Camera Movement	| Implemented with gluLookAt() and a rotating top-down view via camAngle.|
| Object Hierarchies	| Planets and rings are drawn relative to the Sun using transformation stacks (glPushMatrix() / glPopMatrix()).|
| Material Emission & Glow	| Sun uses glMaterialfv() with emission to simulate a glowing effect.|
| Nebula Effect | drawNebula() creates a semi-random particle effect for deep-space ambience.|

## 🌕Scene Description

* Sun: Glowing central sphere with a pulsating emission color.

* Planets: Eight rotating planets of different sizes, colors, and speeds.

* Saturn’s Ring: Created using GL_QUAD_STRIP and layered color shading.

* Stars: 200 randomly generated points that twinkle based on time-dependent sine functions.

* Nebula: A soft background made of randomly placed glowing particles.

* Camera: Slowly rotates around the solar system to provide a cinematic overview.


## 🌕Technical Description

* Language: C

* Library: OpenGL (GLUT)

* Window Size: 900×700

* Frame Rate: ~30 FPS (updated every 33 ms)

* Lighting Model: Single light source at the Sun’s position

* Projection Type: Perspective (gluPerspective())

* Camera Control: Top-down circular motion via trigonometric rotation

## 🌕Learning Outcomes

* Real-time rendering and animation synchronization

* Dynamic lighting and material control

* Hierarchical modeling and scene composition

* Use of procedural randomness for realism

* Camera-based scene interaction and smooth motion
## Animation
