Here is general description of the project design and the approaches towards the
implementation of the graphical representation of the linked list operations will be presented.
The software is programmed in C++ and the graphical representation and interaction with the
user was done in SFML (Simple and Fast Multimedia Library). The SFML offers convenient
functions to draw shapes, create graphic windows, show text and process the events related to the
user input like keyboard keys presses or mouse clicks.
The implementation was aimed at relating the logical data structure operations to a graphical
display, in which a user can view how the linked list evolves in execution. Whenever an
operation like insertion or deletion is done, the internal linked list structure is modified initially
and the graphical items redraw themselves to show the new structure.
The program was subdivided into a few functional modules in order to make the system
structured and easy to manage. The modules carry out a particular operation like main menu,
creating nodes, adding/removing nodes, traversing the list and value search. These modules work
together to give an interactive visualization of the collection of data within the linked listing.
