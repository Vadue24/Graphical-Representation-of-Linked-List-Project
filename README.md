1)APPROACH AND IMPLEMENTATION

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

2) Overview (main components)
The program's entry point creates three list objects and runs a single SFML render loop. The
animation and UI state are stored in a few global/local variables (e.g. currentScreen,
isAnimating, currentOpAnim, pendingValue, pendingPos, animData, highlightIndex) that
coordinate logic and rendering.
Key initial setup (window, font, lists) -- from main():
//Creating the three linked lists
SinglyLinkedList singlyList;
DoublyLinkedList doublyList;
CircularLinkedList circularList;
// --- Set starting screen ---
Screen currentScreen = SPLASH;
// --- Status bar for messages ---
StatusBar status;
// --- Animation variables ---
int highlightIndex = -1; // which node is highlighted
sf::Color highlightColor = HIGHLIGHT_COL;
sf::Clock animClock; // timer for animation steps
bool isAnimating = false;

Splash Screen Module
Purpose: show project title, authors and course details before navigating to main menu.
The splash screen is shown for a short period of time before the program transitions to the main
menu. This transition helps create a more professional appearance for the application and clearly
identifies the project to the user. In addition, the splash screen ensures that users understand the
purpose of the program before interacting with the system.
Where implemented: inside the main draw loop -- the splash screen is drawn when currentScreen
== SPLASH. The code sets the title and centered info text:
if (currentScreen == SPLASH)
{
 sf::Text title;
5
 title.setFont(font);
 title.setCharacterSize(32);
 title.setFillColor(TITLE_COLOR);
 title.setStyle(sf::Text::Bold);
 title.setString("Graphical Representation of Linked List");
 centerText(title, 200);
 window.draw(title);
 sf::Text info;
 info.setFont(font);
 info.setCharacterSize(20);
 info.setFillColor(TEXT_COLOR);
 info.setString("Author: Aziz Daurov and Abdullo\n"
 "Roll No: [Your Roll Number]\n"
 "Subject: Data Structures");
 centerText(info, 320);
 window.draw(info);
 sf::Text hint;
 hint.setFont(font);
 hint.setCharacterSize(16);
 hint.setFillColor(ACCENT_COLOR);
 hint.setString("Click anywhere to continue...");
 centerText(hint, 450);
 window.draw(hint);
}
This code both draws and centers the splash-screen text and uses centerText() helper for
alignment.
int searchTarget = -1;
This snippet shows where the lists and animation/UI state are instantiated and used in the main
loop.

Main Menu Module
Purpose: provide navigation between the three list visualizers (Singly, Doubly, Circular) and
Exit. The menu is built with clickable buttons; clicking a button sets currentScreen and calls
setupOpButtons() to prepare the operations UI.
Event handling & transitions: in the same main event loop, clicks on main-menu buttons
change the screen:
// ---- MAIN MENU ----
if (currentScreen == MAIN_MENU) {
 if (btnSingly.isClicked(clickX, clickY)) {
 currentScreen = SINGLY_SCREEN;
 setupOpButtons();
 }
 else if (btnDoubly.isClicked(clickX, clickY)) {
 currentScreen = DOUBLY_SCREEN;
 setupOpButtons();
 }
 else if (btnCircular.isClicked(clickX, clickY)) {
 currentScreen = CIRCULAR_SCREEN;
 setupOpButtons();
 }
 else if (btnExit.isClicked(clickX, clickY)) {
 window.close();
 }
 continue;
}
setupOpButtons() defines the operation buttons shown for the selected list (Insert, Delete,
Traverse, Search, etc.). The code that creates these operation buttons is in the button setup
section.

Node Creation Module (data-layer)
Purpose: create nodes dynamically (new) and provide node structures for each list type used by
both logic and drawing layers.
Singly node / class (SNode & SinglyLinkedList) — constructor and basic insert at beginning:
struct SNode {
 int data;
 SNode* next;
 SNode(int d) { data = d; next = NULL; }
};
class SinglyLinkedList {
public:
 SNode* head;
 int count;
 SinglyLinkedList() { head = NULL; count = 0; }
 ~SinglyLinkedList() { while (head != NULL) deleteBeginning(); }
 void insertBeginning(int value) {
 SNode* newNode = new SNode(value);
 newNode->next = head;
 head = newNode;
 count++;
 }
 ...
};
The new operator is used in all insert functions (begin, end, at position). The class also provides
toVector() to export the list contents for animation/drawing.
Doubly node / class (DNode & DoublyLinkedList) — same pattern with prev:
struct DNode {
 int data;
 DNode* next;
 DNode* prev;
 DNode(int d) { data = d; next = NULL; prev = NULL; }
};
class DoublyLinkedList {
public:
 DNode* head;
 int count;
 void insertBeginning(int value) {
 DNode* newNode = new DNode(value);
 newNode->next = head;
 if (head != NULL) head->prev = newNode;
 head = newNode;
 count++;
 }
 ...
};
Doubly nodes allocate via new DNode(...) and maintain both prev and next.
Circular list reuses SNode, but maintains a circular invariant tail->next == head. Example
insertion beginning:
void insertBeginning(int value) {
 SNode* newNode = new SNode(value);
 if (head == NULL) {
 head = newNode;
 newNode->next = newNode;
 count++;
 return;
 }
 SNode* tail = head;
 while (tail->next != head) tail = tail->next;
 newNode->next = head;
 tail->next = newNode;
 head = newNode;
 count++;
}
Circular operations ensure the loop connects back to head.

Insertion Module (logic + animation trigger)
Logic: each list class implements insertBeginning, insertEnd, and insertAtPosition — these are
standard pointer updates with new. Example (singly insert at end):
void insertEnd(int value) {
 SNode* newNode = new SNode(value);
 if (head == NULL) { head = newNode; count++; return; }
 SNode* temp = head;
 while (temp->next != NULL) temp = temp->next;
 temp->next = newNode;
 count++;
}
All insertion variants follow straightforward pointer updates and increment count. The code for
singly/doubly/circular insertions is in their respective class definitions.
Animation trigger: UI buttons do not directly call list insertion — instead they set animation
state variables so the insertion is animated first and then applied. This is visible in the click
handler:
if (currentScreen == SINGLY_SCREEN) {
 if (i == 0) { // Insert Beginning
 pendingValue = val;
 currentOpAnim = OP_INSERT_BEGIN;
 isAnimating = true;
 highlightIndex = 0;
 animClock.restart();
 status.set("Inserting: " + to_string(val) + " at the beginning");
 inputValue.clear();
 }
 ...
}
When the animation phase completes the program calls the actual insert function (e.g.,
singlyList.insertBeginning(pendingValue)), so the animation and logic are synchronized.

Deletion Module (logic + animation trigger)
Logic: each class implements deletion functions: deleteBeginning, deleteEnd, deleteAtPosition.
Example (singly delete at position):
bool deleteAtPosition(int pos) {
 if (pos < 1 || pos > count) return false;
 if (pos == 1) return deleteBeginning();
 SNode* temp = head;
 for (int i = 1; i < pos - 1; i++) temp = temp->next;
 SNode* toDelete = temp->next;
 temp->next = toDelete->next;
 delete toDelete;
 count--;
 return true;
}
Doubly deletion updates both prev and next. Circular deletion handles tail's next linking back to
new head. These implementations are in the class definitions.
Animation trigger & flow: deletion buttons set currentOpAnim = OP_DELETE_* and
isAnimating = true. After the animation completes (animated nodes highlight and arrows
break/reconnect visually), the code executes the real deletion method and updates status and
liveInfo to reflect success. Example of finalizing operation:
if (currentScreen == SINGLY_SCREEN) {
 if (currentOpAnim == OP_DELETE_BEGIN) {
 singlyList.deleteBeginning();
 status.set("Deleted from beginning");
 liveInfo = "First node deleted";
 highlightIndex = -1;
 }
 ...
}
currentOpAnim = OP_NONE;
pendingValue = 0;
pendingPos = 0;
This decouples animation from structural mutation to keep visuals smooth.
2.7 Traversal / Display Module (drawing + animation)
toVector(): each list has a toVector() method used to snapshot node values for the animation and
drawing pipeline:
vector<int> toVector() {
 vector<int> result;
 SNode* temp = head;
 while (temp != NULL) {
 result.push_back(temp->data);
 temp = temp->next;
 }
 return result;
}
(For circular lists toVector() uses do { ... } while (temp != head);)
Animation engine: the main loop uses animData, highlightIndex, animClock and isAnimating to
step through nodes with a small delay and update liveInfo/status. The engine handles both
traversal and search (search is traversal with isSearchMode = true and searchTarget set):
if (!isAnimating && flashCount > 0 && animClock.getElapsedTime().asSeconds() > 0.2f) {
 animClock.restart();
 flashOn = !flashOn;
 flashCount--;
 if (flashCount == 0) flashOn = true; // leave found node green
}
// During animation:
if (highlightIndex >= 0 && highlightIndex < totalNodes) {
 if (isSearchMode) liveInfo = "Checking node " + to_string(highlightIndex+1) + " Value: " +
to_string(animData[highlightIndex]);
 else liveInfo = "Visiting node " + to_string(highlightIndex+1) + " Value: " +
to_string(animData[highlightIndex]);
}
...
if (isSearchMode && searchTarget >= 0 && highlightIndex == searchTarget) { ... }
else if (highlightIndex >= totalNodes) { isAnimating = false; ... }
The code sets status messages with estimated durations so the user sees progress. This animation
logic is what makes traversal/search visible as sequential node highlights.

Search Module (logic + visual)
Logic: each list implements search(value) returning position or -1:
int search(int value) {
 SNode* temp = head;
 int pos = 1;
 while (temp != NULL) {
 if (temp->data == value) return pos;
 temp = temp->next;
 pos++;

 }
 return -1;
}
Circular and double lists have similar implementations (circle utilizes do/while). The UI sets the
searchTarget using search() and animates the traversal to the desired index. If the node is found,
it flashes or changes color. Otherwise, it displays "Element not found".
2.9 Rendering Helpers (SFML Drawing Functions)
Draw nodes, pointer boxes, arrows, and curved arrows to create circular lists. These utilities
separate graphics code from data logic.
Arrow drawing & curved arrow for circular lists:
void drawArrow(sf::RenderWindow& window,
 float x1, float y1, float x2, float y2, sf::Color color) {
 // draws line shaft + triangle head (computes ux,uy and angle)
 ...
}
void drawCurvedArrow(sf::RenderWindow& window,
 float fromX, float fromY, float toX, float toY, sf::Color color) {
 // go down, across, then up to create loop-back arrow
 float belowY = max(fromY, toY) + 50.0f;
 drawArrow(window, fromX, fromY, fromX, belowY, color);
 drawArrow(window, fromX, belowY, toX, belowY, color);
 drawArrow(window, toX, belowY, toX, toY, color);
}
Node drawing: node visualizations are split by list type; eg. singly node:
void drawSinglyNode(sf::RenderWindow& window, sf::Font& font,
 float x, float y, int value, sf::Color fillColor) {
 float dataWidth = NODE_W - PTR_W;
 sf::RectangleShape dataBox(sf::Vector2f(dataWidth, NODE_H));
 dataBox.setPosition(x, y);
 dataBox.setFillColor(fillColor);
 dataBox.setOutlineColor(OUTLINE_COLOR);
 dataBox.setOutlineThickness(2.0f);
 window.draw(dataBox);
 // pointer box, dot, text, etc.
}
Doubly nodes show prev and next pointer boxes and different outline colors for clarity. These
functions are the rendering primitives used in the UI draw loop.

UI Widgets: Buttons, InputBox, StatusBar
InputBox handles numeric typing, cursor and active state:
void handleEvent(sf::Event& event) {
 if (!active) return;
 if (event.type != sf::Event::TextEntered) return;
 char c = (char)event.text.unicode;
 if (c == '\b') { if (!text.empty()) text.pop_back(); }
 else if ((c >= '0' && c <= '9') || c == '-') {
 if (text.size() < 10) text += c;
 }
}
int getValue() { if (text.empty()) return 0; try { return stoi(text); } catch (...) { return 0; } }
StatusBar shows temporary messages at bottom:
struct StatusBar {
 string message; sf::Clock clock; float showTime;
 void set(string msg, float seconds = 3.0f) { message = msg; showTime = seconds;
clock.restart(); }
 void draw(sf::RenderWindow& window, sf::Font& font) {
 if (message.empty()) return;
 if (clock.getElapsedTime().asSeconds() > showTime) return;
 // draw text
 }
};
Input, buttons and status bar are used per-screen to get user values and display messages.
2.11 Animation State Machine & Main Loop
Structure: a single render loop manages:
1. Mouse/keyboard event polling
2. When on the list screen, input is forwarded to InputBox
3. Click handling (clicks on operation buttons, menu navigation)
4. Changing the animation state (flashing states, advancing highlightIndex)
5. sketching the current screen (splash, menu, or list UI + nodes + arrows)
Operation flow: currentOpAnim, pendingValue/pendingPos, and isAnimating = true are set
when an operation button is clicked. The actual list method is called to modify the list when the
animation stage (visual highlights, simulated pointer reconnection) has finished. The UI clears
currentOpAnim and changes status following the mutation:
pendingValue/pendingPos and isAnimating = true. The animation stage runs (visual highlights,
simulated pointer reconnection), then the actual list method is called to mutate the list. After
mutation, the UI updates status and clears currentOpAnim:
// Example: after animation completes the code executes operation
if (currentScreen == SINGLY_SCREEN) {
 if (currentOpAnim == OP_INSERT_BEGIN) {
 singlyList.insertBeginning(pendingValue);
 status.set("Inserted " + to_string(pendingValue) + " at beginning");
 highlightIndex = 0;
 }
 ...
}
currentOpAnim = OP_NONE;
pendingValue = 0;
pendingPos = 0;
This design keeps visual transitions and structural changes synchronized while avoiding midanimation pointer inconsistencies.
2.12 Memory management and cleanup
Each list class implements a destructor which deletes remaining nodes (walking through and
calling the delete helpers). The main() exits after closing the window; destructors free all
allocated nodes:
~SinglyLinkedList() {
 while (head != NULL) {
 deleteBeginning();
 }
}
This ensures no heap memory is leaked when the application closes. Circular list destructor uses
repeated deleteBeginning() which is safe because deleteBeginning() updates head and breaks the
loop.
