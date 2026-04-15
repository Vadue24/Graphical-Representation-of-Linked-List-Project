Here is the Graphical Implementation of Linked List. This project was developed as a mid-term project by me and my groupmate last semester. 
To create this project, we used backend Language C++ in combination with Graphics Library SFML(Simple and Fast Multimedia Library) — specifically SFML/Graphics.hpp for rendering the window, shapes, text, and handling mouse/keyboard events. 
Also we used standard Libraries: <vector>, <string>, <cmath>, <algorithm> and <iostream>.

The explanation of building Process:
1)Data structures — each list type has its own struct/class (SNode/SinglyLinkedList, DNode/DoublyLinkedList, CNode/CircularLinkedList) implementing insert at beginning/end/position, delete, and search from scratch.
2)UI & rendering — SFML draws nodes as rectangles with pointer boxes, arrows between them (including a curved back-arrow for the circular list), and color-coded highlights. The color palette follows the Catppuccin Mocha theme (dark background with soft purples, greens, and pinks).
3)Animation system — the app uses sf::Clock timers to animate operations step by step: traversal highlights each node sequentially, insert/delete show an overlay animation, and a found element flashes green.
4)Screen flow — an enum Screen manages navigation between a splash screen → main menu → one of three list screens, with a sidebar of operation buttons and text input fields for value and position.
