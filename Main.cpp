/*
 * ============================================================
 *  Project  : Graphical Representation of Linked List
 *  Library  : SFML (Simple and Fast Multimedia Library)
 * ============================================================
 *  Author   : [Your Name]
 *  Roll No  : [Your Roll Number]
 *  Subject  : Data Structures
 * ============================================================
 *
 *  This program visually shows how Singly, Doubly, and
 *  Circular Linked Lists work. Each node is drawn as a
 *  rectangle, arrows show the pointers, and operations
 *  like insert, delete, traverse, and search are animated.
 *
 *  Modules:
 *    1. Splash Screen
 *    2. Main Menu
 *    3. Node Creation (graphical boxes)
 *    4. Insertion (beginning, end, position)
 *    5. Deletion (beginning, end, position)
 *    6. Traversal with highlight animation
 *    7. Search with colour feedback
 *    8. Exit
 *
 * ============================================================
 */

 // --- Include necessary SFML and C++ headers ---
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// ============================================================
//  GLOBAL CONSTANTS
// ============================================================

// Window size
const int Width = 1280;
const int Height = 720;

// Node drawing sizes (in pixels)
const float NODE_W = 90.0f;   // total width of one node box
const float NODE_H = 44.0f;   // height of one node box
const float PTR_W = 28.0f;   // width of the pointer section
const float NODE_GAP = 55.0f;   // gap between two nodes

// Colours used throughout the program
const sf::Color BG_COLOR(30, 30, 46);    // dark background
const sf::Color NODE_COLOR(69, 71, 90);    // node fill
const sf::Color OUTLINE_COLOR(137, 180, 250);   // node border (blue)
const sf::Color ARROW_COLOR(166, 227, 161);   // green arrows (next)
const sf::Color PREV_COLOR(245, 194, 231);   // pink arrows (prev, doubly)
const sf::Color TEXT_COLOR(205, 214, 244);   // white-ish text
const sf::Color HIGHLIGHT_COL(249, 226, 175);   // yellow highlight
const sf::Color FOUND_COLOR(166, 227, 161);   // green = found
const sf::Color NOTFOUND_COL(243, 139, 168);   // red = not found
const sf::Color BTN_COLOR(49, 50, 68);    // button normal
const sf::Color BTN_HOVER(69, 71, 90);    // button hover
const sf::Color TITLE_COLOR(180, 190, 254);   // headings
const sf::Color ACCENT_COLOR(137, 180, 250);   // accent blue
const sf::Color PTR_BG(35, 35, 45);    // darker pointer section

// ============================================================
//  SCREEN STATES  (which screen are we on?)
// ============================================================
enum Screen {
    SPLASH,         // 0 - splash screen
    MAIN_MENU,      // 1 - main menu
    SINGLY_SCREEN,  // 2 - singly linked list operations
    DOUBLY_SCREEN,  // 3 - doubly linked list operations
    CIRCULAR_SCREEN // 4 - circular linked list operations
};


// ============================================================
//  SINGLY LINKED LIST
// ============================================================

// A single node in a singly linked list
struct SNode {
    int   data;     // the value stored
    SNode* next;    // pointer to the next node

    // Constructor: set data and next to NULL
    SNode(int d) {
        data = d;
        next = NULL;
    }
};

// The Singly Linked List class
class SinglyLinkedList {
public:
    SNode* head;    // pointer to the first node
    int    count;   // how many nodes we have

    // Constructor: start with an empty list
    SinglyLinkedList() {
        head = NULL;
        count = 0;
    }

    // Destructor: free all memory when done
    ~SinglyLinkedList() {
        while (head != NULL) {
            deleteBeginning();
        }
    }

    // Insert a new node at the beginning of the list
    void insertBeginning(int value) {
        SNode* newNode = new SNode(value);  // create new node
        newNode->next = head;               // point it to current head
        head = newNode;                     // update head to new node
        count++;
    }

    // Insert a new node at the end of the list
    void insertEnd(int value) {
        SNode* newNode = new SNode(value);

        // If list is empty, new node becomes the head
        if (head == NULL) {
            head = newNode;
            count++;
            return;
        }

        // Otherwise, walk to the last node
        SNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;  // attach at end
        count++;
    }

    // Insert at a specific position (1-based)
    bool insertAtPosition(int value, int pos) {
        // Check if position is valid
        if (pos < 1 || pos > count + 1) {
            return false;
        }

        // If position is 1, just insert at beginning
        if (pos == 1) {
            insertBeginning(value);
            return true;
        }

        // Walk to the node just before the position
        SNode* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        // Create new node and insert it
        SNode* newNode = new SNode(value);
        newNode->next = temp->next;
        temp->next = newNode;
        count++;
        return true;
    }

    // Delete the first node
    bool deleteBeginning() {
        if (head == NULL) return false;  // list is empty

        SNode* temp = head;     // save current head
        head = head->next;      // move head to next node
        delete temp;            // free the old head
        count--;
        return true;
    }

    // Delete the last node
    bool deleteEnd() {
        if (head == NULL) return false;

        // If only one node, delete it
        if (head->next == NULL) {
            delete head;
            head = NULL;
            count--;
            return true;
        }

        // Walk to the second-last node
        SNode* temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        delete temp->next;      // delete last node
        temp->next = NULL;      // second-last becomes last
        count--;
        return true;
    }

    // Delete at a specific position (1-based)
    bool deleteAtPosition(int pos) {
        if (pos < 1 || pos > count) return false;
        if (pos == 1) return deleteBeginning();

        // Walk to node before the one to delete
        SNode* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        SNode* toDelete = temp->next;   // node to remove
        temp->next = toDelete->next;    // bypass it
        delete toDelete;                // free memory
        count--;
        return true;
    }

    // Search for a value, returns position (1-based) or -1
    int search(int value) {
        SNode* temp = head;
        int pos = 1;
        while (temp != NULL) {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        }
        return -1;  // not found
    }

    // Convert list to a vector (for drawing)
    vector<int> toVector() {
        vector<int> result;
        SNode* temp = head;
        while (temp != NULL) {
            result.push_back(temp->data);
            temp = temp->next;
        }
        return result;
    }
};


// ============================================================
//  DOUBLY LINKED LIST
// ============================================================

// A node with both next and prev pointers
struct DNode {
    int    data;
    DNode* next;
    DNode* prev;

    DNode(int d) {
        data = d;
        next = NULL;
        prev = NULL;
    }
};

class DoublyLinkedList {
public:
    DNode* head;
    int    count;

    DoublyLinkedList() {
        head = NULL;
        count = 0;
    }

    ~DoublyLinkedList() {
        while (head != NULL) {
            deleteBeginning();
        }
    }

    void insertBeginning(int value) {
        DNode* newNode = new DNode(value);
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;   // old head points back to new
        }
        head = newNode;
        count++;
    }

    void insertEnd(int value) {
        DNode* newNode = new DNode(value);
        if (head == NULL) {
            head = newNode;
            count++;
            return;
        }
        DNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;   // new node points back
        count++;
    }

    bool insertAtPosition(int value, int pos) {
        if (pos < 1 || pos > count + 1) return false;
        if (pos == 1) { insertBeginning(value); return true; }

        DNode* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        DNode* newNode = new DNode(value);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next != NULL) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
        count++;
        return true;
    }

    bool deleteBeginning() {
        if (head == NULL) return false;
        DNode* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete temp;
        count--;
        return true;
    }

    bool deleteEnd() {
        if (head == NULL) return false;
        if (head->next == NULL) {
            delete head;
            head = NULL;
            count--;
            return true;
        }
        DNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->prev->next = NULL;
        delete temp;
        count--;
        return true;
    }

    bool deleteAtPosition(int pos) {
        if (pos < 1 || pos > count) return false;
        if (pos == 1) return deleteBeginning();

        DNode* temp = head;
        for (int i = 1; i < pos; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        delete temp;
        count--;
        return true;
    }

    int search(int value) {
        DNode* temp = head;
        int pos = 1;
        while (temp != NULL) {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        }
        return -1;
    }

    vector<int> toVector() {
        vector<int> result;
        DNode* temp = head;
        while (temp != NULL) {
            result.push_back(temp->data);
            temp = temp->next;
        }
        return result;
    }
};


// ============================================================
//  CIRCULAR LINKED LIST  (uses SNode, last->next = head)
// ============================================================

class CircularLinkedList {
public:
    SNode* head;
    int    count;

    CircularLinkedList() {
        head = NULL;
        count = 0;
    }

    ~CircularLinkedList() {
        while (head != NULL) {
            deleteBeginning();
        }
    }

    void insertBeginning(int value) {
        SNode* newNode = new SNode(value);

        // If empty, point to itself (circular)
        if (head == NULL) {
            head = newNode;
            newNode->next = newNode;
            count++;
            return;
        }

        // Find the tail (last node that points to head)
        SNode* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }

        newNode->next = head;   // new node points to old head
        tail->next = newNode;   // tail now points to new node
        head = newNode;         // update head
        count++;
    }

    void insertEnd(int value) {
        SNode* newNode = new SNode(value);

        if (head == NULL) {
            head = newNode;
            newNode->next = newNode;
            count++;
            return;
        }

        SNode* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }

        tail->next = newNode;   // old tail points to new
        newNode->next = head;   // new node loops back to head
        count++;
    }

    bool insertAtPosition(int value, int pos) {
        if (pos < 1 || pos > count + 1) return false;
        if (pos == 1) { insertBeginning(value); return true; }
        if (pos == count + 1) { insertEnd(value); return true; }

        SNode* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        SNode* newNode = new SNode(value);
        newNode->next = temp->next;
        temp->next = newNode;
        count++;
        return true;
    }

    bool deleteBeginning() {
        if (head == NULL) return false;

        // Only one node? Just delete it
        if (count == 1) {
            delete head;
            head = NULL;
            count = 0;
            return true;
        }

        // Find tail
        SNode* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }

        SNode* temp = head;
        head = head->next;     // move head forward
        tail->next = head;     // tail now points to new head
        delete temp;
        count--;
        return true;
    }

    bool deleteEnd() {
        if (head == NULL) return false;
        if (count == 1) {
            delete head;
            head = NULL;
            count = 0;
            return true;
        }

        // Walk to second-last node
        SNode* temp = head;
        while (temp->next->next != head) {
            temp = temp->next;
        }

        delete temp->next;     // delete last
        temp->next = head;     // second-last loops back to head
        count--;
        return true;
    }

    bool deleteAtPosition(int pos) {
        if (pos < 1 || pos > count) return false;
        if (pos == 1) return deleteBeginning();
        if (pos == count) return deleteEnd();

        SNode* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        SNode* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        count--;
        return true;
    }

    // Search uses do-while because it is circular
    int search(int value) {
        if (head == NULL) return -1;

        SNode* temp = head;
        int pos = 1;
        do {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        } while (temp != head);

        return -1;
    }

    vector<int> toVector() {
        vector<int> result;
        if (head == NULL) return result;

        SNode* temp = head;
        do {
            result.push_back(temp->data);
            temp = temp->next;
        } while (temp != head);

        return result;
    }
};


// ============================================================
//  DRAWING HELPER FUNCTIONS
// ============================================================

// Draw an arrow from point A to point B
void drawArrow(sf::RenderWindow& window,
    float x1, float y1, float x2, float y2,
    sf::Color color)
{
    // Calculate direction
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    if (length < 1.0f) return;

    // Unit vector (direction)
    float ux = dx / length;
    float uy = dy / length;

    // Perpendicular vector (for arrowhead width)
    float px = -uy;
    float py = ux;

    // Draw the line (shaft of arrow)
    sf::RectangleShape line(sf::Vector2f(length - 10.0f, 2.0f));
    line.setPosition(x1, y1);
    line.setFillColor(color);
    float angle = atan2(dy, dx) * 180.0f / 3.14159f;
    line.setRotation(angle);
    line.setOrigin(0.0f, 1.0f);
    window.draw(line);

    // Draw the triangle arrowhead
    sf::ConvexShape arrowHead;
    arrowHead.setPointCount(3);
    arrowHead.setPoint(0, sf::Vector2f(x2, y2));
    arrowHead.setPoint(1, sf::Vector2f(x2 - ux * 12 + px * 5,
        y2 - uy * 12 + py * 5));
    arrowHead.setPoint(2, sf::Vector2f(x2 - ux * 12 - px * 5,
        y2 - uy * 12 - py * 5));
    arrowHead.setFillColor(color);
    window.draw(arrowHead);
}

// Draw a curved arrow from last node back to head (for circular list)
void drawCurvedArrow(sf::RenderWindow& window,
    float fromX, float fromY,
    float toX, float toY,
    sf::Color color)
{
    // Go down, across, then up
    float belowY = max(fromY, toY) + 50.0f;

    drawArrow(window, fromX, fromY, fromX, belowY, color);
    drawArrow(window, fromX, belowY, toX, belowY, color);
    drawArrow(window, toX, belowY, toX, toY, color);
}

// Draw one node for a SINGLY linked list
//   [  data  |ptr]  -->
void drawSinglyNode(sf::RenderWindow& window, sf::Font& font,
    float x, float y, int value, sf::Color fillColor)
{
    float dataWidth = NODE_W - PTR_W;

    // --- Data section (left part) ---
    sf::RectangleShape dataBox(sf::Vector2f(dataWidth, NODE_H));
    dataBox.setPosition(x, y);
    dataBox.setFillColor(fillColor);
    dataBox.setOutlineColor(OUTLINE_COLOR);
    dataBox.setOutlineThickness(2.0f);
    window.draw(dataBox);

    // --- Pointer section (right part, darker) ---
    sf::RectangleShape ptrBox(sf::Vector2f(PTR_W, NODE_H));
    ptrBox.setPosition(x + dataWidth, y);
    ptrBox.setFillColor(PTR_BG);
    ptrBox.setOutlineColor(OUTLINE_COLOR);
    ptrBox.setOutlineThickness(2.0f);
    window.draw(ptrBox);

    // --- Value text (centered in data section) ---
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(TEXT_COLOR);
    text.setString(to_string(value));
    // Center the text
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);
    text.setPosition(x + dataWidth / 2.0f, y + NODE_H / 2.0f);
    window.draw(text);

    // --- Small green dot in pointer section ---
    sf::CircleShape dot(3.0f);
    dot.setFillColor(ARROW_COLOR);
    dot.setPosition(x + dataWidth + PTR_W / 2.0f - 3.0f,
        y + NODE_H / 2.0f - 3.0f);
    window.draw(dot);
}

// Draw one node for a DOUBLY linked list
//   [prev|  data  |next]
void drawDoublyNode(sf::RenderWindow& window, sf::Font& font,
    float x, float y, int value, sf::Color fillColor)
{
    float dataWidth = NODE_W - 2 * PTR_W;

    // --- Prev pointer section (left, pink border) ---
    sf::RectangleShape prevBox(sf::Vector2f(PTR_W, NODE_H));
    prevBox.setPosition(x, y);
    prevBox.setFillColor(PTR_BG);
    prevBox.setOutlineColor(PREV_COLOR);
    prevBox.setOutlineThickness(2.0f);
    window.draw(prevBox);

    // --- Data section (middle) ---
    sf::RectangleShape dataBox(sf::Vector2f(dataWidth, NODE_H));
    dataBox.setPosition(x + PTR_W, y);
    dataBox.setFillColor(fillColor);
    dataBox.setOutlineColor(OUTLINE_COLOR);
    dataBox.setOutlineThickness(2.0f);
    window.draw(dataBox);

    // --- Next pointer section (right, green border) ---
    sf::RectangleShape nextBox(sf::Vector2f(PTR_W, NODE_H));
    nextBox.setPosition(x + PTR_W + dataWidth, y);
    nextBox.setFillColor(PTR_BG);
    nextBox.setOutlineColor(ARROW_COLOR);
    nextBox.setOutlineThickness(2.0f);
    window.draw(nextBox);

    // --- Value text ---
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(TEXT_COLOR);
    text.setString(to_string(value));
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);
    text.setPosition(x + PTR_W + dataWidth / 2.0f, y + NODE_H / 2.0f);
    window.draw(text);
}


// ============================================================
//  SIMPLE BUTTON  (rectangle + text, highlights on hover)
// ============================================================

struct Button {
    sf::RectangleShape box;
    sf::Text           label;

    // Empty constructor
    Button() {}

    // Create a button at position (x, y) with given size
    void create(sf::Font& font, string text,
        float x, float y, float w, float h)
    {
        box.setSize(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(BTN_COLOR);
        box.setOutlineColor(ACCENT_COLOR);
        box.setOutlineThickness(1.5f);

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(16);
        label.setFillColor(TEXT_COLOR);

        // Center label inside button
        sf::FloatRect b = label.getLocalBounds();
        label.setOrigin(b.left + b.width / 2.0f, b.top + b.height / 2.0f);
        label.setPosition(x + w / 2.0f, y + h / 2.0f);
    }

    // Check if a point is inside the button
    bool isClicked(float mx, float my) {
        return box.getGlobalBounds().contains(mx, my);
    }

    // Update hover effect
    void update(float mx, float my) {
        if (box.getGlobalBounds().contains(mx, my)) {
            box.setFillColor(BTN_HOVER);
        }
        else {
            box.setFillColor(BTN_COLOR);
        }
    }

    // Draw the button
    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(label);
    }
};


// ============================================================
//  TEXT INPUT BOX  (lets user type numbers)
// ============================================================

struct TextInput {
    string              text;       // what the user typed
    sf::RectangleShape  box;
    sf::Text            display;
    bool                active;     // is this input focused?

    TextInput() {
        active = false;
    }

    void create(sf::Font& font, float x, float y, float w, float h) {
        box.setSize(sf::Vector2f(w, h));
        box.setPosition(x, y);
        box.setFillColor(sf::Color(40, 40, 60));
        box.setOutlineColor(ACCENT_COLOR);
        box.setOutlineThickness(1.5f);

        display.setFont(font);
        display.setCharacterSize(18);
        display.setFillColor(TEXT_COLOR);
        display.setPosition(x + 6.0f, y + 6.0f);
    }

    // Handle keyboard typing
    void handleEvent(sf::Event& event) {
        if (!active) return;
        if (event.type != sf::Event::TextEntered) return;

        char c = (char)event.text.unicode;

        // Backspace: remove last character
        if (c == '\b') {
            if (!text.empty()) text.pop_back();
        }
        // Only allow digits and minus sign, max 10 chars
        else if ((c >= '0' && c <= '9') || c == '-') {
            if (text.size() < 10) {
                text += c;
            }
        }
    }

    // Get the typed number (0 if empty)
    int getValue() {
        if (text.empty()) return 0;
        try {
            return stoi(text);
        }
        catch (...) {
            return 0;
        }
    }

    void clear() { text = ""; }

    void draw(sf::RenderWindow& window) {
        // Highlight border when active
        if (active) box.setOutlineColor(HIGHLIGHT_COL);
        else        box.setOutlineColor(ACCENT_COLOR);

        window.draw(box);

        // Show text with cursor if active
        if (active) display.setString(text + "_");
        else        display.setString(text);

        window.draw(display);
    }
};


// ============================================================
//  STATUS MESSAGE  (shows messages at bottom of screen)
// ============================================================

struct StatusBar {
    string   message;
    sf::Clock clock;
    float    showTime;   // how long to show (seconds)

    StatusBar() {
        showTime = 0;
    }

    // Set a new message
    void set(string msg, float seconds = 3.0f) {
        message = msg;
        showTime = seconds;
        clock.restart();
    }

    // Draw the message if it hasn't expired
    void draw(sf::RenderWindow& window, sf::Font& font) {
        if (message.empty()) return;
        if (clock.getElapsedTime().asSeconds() > showTime) return;

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(18);
        text.setFillColor(HIGHLIGHT_COL);
        text.setString(message);
        text.setPosition(20.0f, Height - 40.0f);
        window.draw(text);
    }
};


// ============================================================
//  HELPER: Center text horizontally on screen
// ============================================================

void centerText(sf::Text& text, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);
    text.setPosition(Width / 2.0f, y);
}


// ============================================================
//  MAIN FUNCTION
// ============================================================

int main()
{
    // --- Create the window ---
    sf::RenderWindow window(
        sf::VideoMode(Width, Height),
        "Midterm project. Linked List - Aziz Daurov, Abdullo",
        sf::Style::Close | sf::Style::Titlebar
    );
    window.setFramerateLimit(60);

    // --- Load a font ---
    sf::Font font;
    bool fontOK = false;

    // Picking a font
    string fontPaths[] = {
        "Roboto-Light.ttf",
        "C:/Windows/Fonts/Roboto-Light",
        "C:/Windows/Fonts/segoeui.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/System/Library/Fonts/Helvetica.ttc"
    };

    for (int i = 0; i < 6; i++) {
        if (font.loadFromFile(fontPaths[i])) {
            fontOK = true;
            break;
        }
    }

    if (!fontOK) {
        cout << "ERROR: Cannot find a font file!" << endl;
        cout << "You can put Roboto-Regular.ttf in the project to continue" << endl;
        return 1;
    }

    //Creating the three linked lists
    SinglyLinkedList   singlyList;
    DoublyLinkedList   doublyList;
    CircularLinkedList  circularList;

    // --- Set starting screen ---
    Screen currentScreen = SPLASH;

    // --- Status bar for messages ---
    StatusBar status;

    // --- Animation variables ---
    int       highlightIndex = -1;      // which node is highlighted
    sf::Color highlightColor = HIGHLIGHT_COL;
    sf::Clock animClock;                // timer for animation steps
    bool      isAnimating = false;
    int       searchTarget = -1;      // index of found node (-1 = not found)
    int       totalNodes = 0;
    bool      wasFound = false;

    // --- Main menu buttons ---
    Button btnSingly, btnDoubly, btnCircular, btnExit;

    float menuX = Width / 2.0f - 110.0f;
    btnSingly.create(font, "Singly Linked List", menuX, 260, 220, 42);
    btnDoubly.create(font, "Doubly Linked List", menuX, 320, 220, 42);
    btnCircular.create(font, "Circular Linked List", menuX, 380, 220, 42);
    btnExit.create(font, "Exit", menuX, 440, 220, 42);

    // --- Operation buttons (used in all three list screens) ---
    Button opButtons[8];     // 8 operation buttons
    Button btnBack;          // back to menu button
    TextInput inputValue;    // input for value
    TextInput inputPos;      // input for position

    // This function sets up the operation buttons
    // (we call it when entering a list screen)
    auto setupOpButtons = [&]() {
        float x = 20, y = 60, w = 200, h = 36, gap = 6;
        opButtons[0].create(font, "Insert Beginning", x, y, w, h); y += h + gap;
        opButtons[1].create(font, "Insert End", x, y, w, h); y += h + gap;
        opButtons[2].create(font, "Insert at Pos", x, y, w, h); y += h + gap;
        opButtons[3].create(font, "Delete Beginning", x, y, w, h); y += h + gap;
        opButtons[4].create(font, "Delete End", x, y, w, h); y += h + gap;
        opButtons[5].create(font, "Delete at Pos", x, y, w, h); y += h + gap;
        opButtons[6].create(font, "Traverse", x, y, w, h); y += h + gap;
        opButtons[7].create(font, "Search", x, y, w, h); y += h + gap;

        btnBack.create(font, "Back to Menu", x, y + 10, w, h);

        inputValue.create(font, x, y + 60, 90, 30);
        inputPos.create(font, x + 110, y + 60, 70, 30);
        inputValue.active = true;
    };


    // ========================================================
    //  MAIN GAME LOOP
    // ========================================================

    while (window.isOpen())
    {
        // Get mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float mx = (float)mousePos.x;
        float my = (float)mousePos.y;

        // --- Process events ---
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Forward typing to input boxes (only on list screens)
            if (currentScreen == SINGLY_SCREEN ||
                currentScreen == DOUBLY_SCREEN ||
                currentScreen == CIRCULAR_SCREEN)
            {
                inputValue.handleEvent(event);
                inputPos.handleEvent(event);
            }

            // --- Mouse click ---
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                float clickX = (float)event.mouseButton.x;
                float clickY = (float)event.mouseButton.y;

                // ---- SPLASH SCREEN ----
                if (currentScreen == SPLASH) {
                    currentScreen = MAIN_MENU;
                    continue;
                }

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

                // ---- LIST OPERATION SCREENS ----

                // Click on input boxes to focus them
                if (inputValue.box.getGlobalBounds().contains(clickX, clickY)) {
                    inputValue.active = true;
                    inputPos.active = false;
                }
                else if (inputPos.box.getGlobalBounds().contains(clickX, clickY)) {
                    inputPos.active = true;
                    inputValue.active = false;
                }

                // Back button
                if (btnBack.isClicked(clickX, clickY)) {
                    currentScreen = MAIN_MENU;
                    isAnimating = false;
                    highlightIndex = -1;
                    continue;
                }

                // Get input values
                int val = inputValue.getValue();
                int pos = inputPos.getValue();

                // Check each operation button
                for (int i = 0; i < 8; i++)
                {
                    if (!opButtons[i].isClicked(clickX, clickY)) continue;

                    // Stop any running animation
                    isAnimating = false;
                    highlightIndex = -1;

                    // ---- SINGLY LINKED LIST ----
                    if (currentScreen == SINGLY_SCREEN) {
                        if (i == 0) { // Insert Beginning
                            singlyList.insertBeginning(val);
                            inputValue.clear();
                            status.set("Inserted " + to_string(val) + " at beginning");
                        }
                        else if (i == 1) { // Insert End
                            singlyList.insertEnd(val);
                            inputValue.clear();
                            status.set("Inserted " + to_string(val) + " at end");
                        }
                        else if (i == 2) { // Insert at Position
                            if (singlyList.insertAtPosition(val, pos))
                                status.set("Inserted " + to_string(val) + " at position " + to_string(pos));
                            else
                                status.set("Invalid position!");
                            inputValue.clear(); inputPos.clear();
                        }
                        else if (i == 3) { // Delete Beginning
                            if (singlyList.deleteBeginning()) status.set("Deleted from beginning");
                            else status.set("List is empty!");
                        }
                        else if (i == 4) { // Delete End
                            if (singlyList.deleteEnd()) status.set("Deleted from end");
                            else status.set("List is empty!");
                        }
                        else if (i == 5) { // Delete at Position
                            if (singlyList.deleteAtPosition(pos))
                                status.set("Deleted at position " + to_string(pos));
                            else
                                status.set("Invalid position!");
                            inputPos.clear();
                        }
                        else if (i == 6) { // Traverse
                            vector<int> v = singlyList.toVector();
                            if (v.empty()) { status.set("List is empty!"); }
                            else {
                                isAnimating = true;
                                highlightIndex = 0;
                                totalNodes = v.size();
                                searchTarget = -1;
                                highlightColor = HIGHLIGHT_COL;
                                animClock.restart();
                                status.set("Traversing...", totalNodes * 0.6f + 1);
                                for (int i = 0; i < totalNodes; i++) {
                                    cout << "Node "<< i <<" value:"<<v[i] << endl;
                                }
                            }
                        }
                        else if (i == 7) { // Search
                            vector<int> v = singlyList.toVector();
                            if (v.empty()) { status.set("List is empty!"); inputValue.clear(); }
                            else {
                                int idx = singlyList.search(val);
                                isAnimating = true;
                                highlightIndex = 0;
                                totalNodes = v.size();
                                searchTarget = (idx > 0) ? idx - 1 : -1;
                                wasFound = (idx > 0);
                                highlightColor = HIGHLIGHT_COL;
                                animClock.restart();
                                status.set("Searching for " + to_string(val) + "...",
                                    totalNodes * 0.6f + 1);
                                inputValue.clear();
                            }
                        }
                    }

                    // ---- DOUBLY LINKED LIST ----
                    else if (currentScreen == DOUBLY_SCREEN) {
                        if (i == 0) {
                            doublyList.insertBeginning(val);
                            inputValue.clear();
                            status.set("Inserted " + to_string(val) + " at beginning");
                        }
                        else if (i == 1) {
                            doublyList.insertEnd(val);
                            inputValue.clear();
                            status.set("Inserted " + to_string(val) + " at end");
                        }
                        else if (i == 2) {
                            if (doublyList.insertAtPosition(val, pos))
                                status.set("Inserted " + to_string(val) + " at position " + to_string(pos));
                            else
                                status.set("Invalid position!");
                            inputValue.clear(); inputPos.clear();
                        }
                        else if (i == 3) {
                            if (doublyList.deleteBeginning()) status.set("Deleted from beginning");
                            else status.set("List is empty!");
                        }
                        else if (i == 4) {
                            if (doublyList.deleteEnd()) status.set("Deleted from end");
                            else status.set("List is empty!");
                        }
                        else if (i == 5) {
                            if (doublyList.deleteAtPosition(pos))
                                status.set("Deleted at position " + to_string(pos));
                            else
                                status.set("Invalid position!");
                            inputPos.clear();
                        }
                        else if (i == 6) { // Traverse
                            vector<int> v = doublyList.toVector();
                            if (v.empty()) { status.set("List is empty!"); }
                            else {
                                isAnimating = true;
                                highlightIndex = 0;
                                totalNodes = v.size();
                                searchTarget = -1;
                                highlightColor = HIGHLIGHT_COL;
                                animClock.restart();
                                status.set("Traversing...", totalNodes * 0.6f + 1);
                            }
                        }
                        else if (i == 7) { // Search
                            vector<int> v = doublyList.toVector();
                            if (v.empty()) { status.set("List is empty!"); inputValue.clear(); }
                            else {
                                int idx = doublyList.search(val);
                                isAnimating = true;
                                highlightIndex = 0;
                                totalNodes = v.size();
                                searchTarget = (idx > 0) ? idx - 1 : -1;
                                wasFound = (idx > 0);
                                highlightColor = HIGHLIGHT_COL;
                                animClock.restart();
                                status.set("Searching for " + to_string(val) + "...",
                                    totalNodes * 0.6f + 1);
                                inputValue.clear();
                            }
                        }
                    }

                    // ---- CIRCULAR LINKED LIST ----
                    else if (currentScreen == CIRCULAR_SCREEN) {
                        if (i == 0) {
                            circularList.insertBeginning(val);
                            inputValue.clear();
                            status.set("Inserted " + to_string(val) + " at beginning");
                        }
                        else if (i == 1) {
                            circularList.insertEnd(val);
                            inputValue.clear();
                            status.set("Inserted " + to_string(val) + " at end");
                        }
                        else if (i == 2) {
                            if (circularList.insertAtPosition(val, pos))
                                status.set("Inserted " + to_string(val) + " at position " + to_string(pos));
                            else
                                status.set("Invalid position!");
                            inputValue.clear(); inputPos.clear();
                        }
                        else if (i == 3) {
                            if (circularList.deleteBeginning()) status.set("Deleted from beginning");
                            else status.set("List is empty!");
                        }
                        else if (i == 4) {
                            if (circularList.deleteEnd()) status.set("Deleted from end");
                            else status.set("List is empty!");
                        }
                        else if (i == 5) {
                            if (circularList.deleteAtPosition(pos))
                                status.set("Deleted at position " + to_string(pos));
                            else
                                status.set("Invalid position!");
                            inputPos.clear();
                        }
                        else if (i == 6) { // Traverse
                            vector<int> v = circularList.toVector();
                            if (v.empty()) { status.set("List is empty!"); }
                            else {
                                isAnimating = true;
                                highlightIndex = 0;
                                totalNodes = v.size();
                                searchTarget = -1;
                                highlightColor = HIGHLIGHT_COL;
                                animClock.restart();
                                status.set("Traversing...", totalNodes * 0.6f + 1);
                            }
                        }
                        else if (i == 7) { // Search
                            vector<int> v = circularList.toVector();
                            if (v.empty()) { status.set("List is empty!"); inputValue.clear(); }
                            else {
                                int idx = circularList.search(val);
                                isAnimating = true;
                                highlightIndex = 0;
                                totalNodes = v.size();
                                searchTarget = (idx > 0) ? idx - 1 : -1;
                                wasFound = (idx > 0);
                                highlightColor = HIGHLIGHT_COL;
                                animClock.restart();
                                status.set("Searching for " + to_string(val) + "...",
                                    totalNodes * 0.6f + 1);
                                inputValue.clear();
                            }
                        }
                    }

                    break;  // only handle one button click
                }
            }
        } // end event loop


        // ========================================================
        //  ANIMATION UPDATE  (move highlight every 0.5 seconds)
        // ========================================================

        if (isAnimating && animClock.getElapsedTime().asSeconds() > 0.5f)
        {
            animClock.restart();
            highlightIndex++;

            // If searching and we reached the target
            if (searchTarget >= 0 && highlightIndex == searchTarget) {
                highlightColor = FOUND_COLOR;
                isAnimating = false;
                status.set("Element found at position " + to_string(searchTarget + 1));
            }
            // If we went past all nodes
            else if (highlightIndex >= totalNodes) {
                isAnimating = false;

                if (searchTarget == -1) {
                    // Was traversal
                    status.set("Traversal complete");
                    highlightIndex = -1;
                }
                else if (!wasFound) {
                    // Was search, not found
                    highlightIndex = -1;
                    status.set("Element not found!");
                }
            }
        }


        // ========================================================
        //  DRAWING
        // ========================================================

        window.clear(BG_COLOR);

        // ---- SPLASH SCREEN ----
        if (currentScreen == SPLASH)
        {
            sf::Text title;
            title.setFont(font);
            title.setCharacterSize(32);
            title.setFillColor(TITLE_COLOR);
            title.setStyle(sf::Text::Bold);
            title.setString("Linked Lists. Midterm. Aziz Daurov, Abdullo");
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

        // ---- MAIN MENU ----
        else if (currentScreen == MAIN_MENU)
        {
            sf::Text title;
            title.setFont(font);
            title.setCharacterSize(28);
            title.setFillColor(TITLE_COLOR);
            title.setStyle(sf::Text::Bold);
            title.setString("Main Menu");
            centerText(title, 180);
            window.draw(title);

            // Update hover + draw each button
            btnSingly.update(mx, my);   btnSingly.draw(window);
            btnDoubly.update(mx, my);   btnDoubly.draw(window);
            btnCircular.update(mx, my); btnCircular.draw(window);
            btnExit.update(mx, my);     btnExit.draw(window);
        }

        // ---- LIST OPERATION SCREENS ----
        else
        {
            // Figure out which list type and get its data
            string titleText;
            vector<int> data;
            bool isCircular = false;
            bool isDoubly = false;

            if (currentScreen == SINGLY_SCREEN) {
                titleText = "Singly Linked List";
                data = singlyList.toVector();
            }
            else if (currentScreen == DOUBLY_SCREEN) {
                titleText = "Doubly Linked List";
                data = doublyList.toVector();
                isDoubly = true;
            }
            else {
                titleText = "Circular Linked List";
                data = circularList.toVector();
                isCircular = true;
            }

            // Draw title text
            sf::Text title;
            title.setFont(font);
            title.setCharacterSize(22);
            title.setFillColor(TITLE_COLOR);
            title.setStyle(sf::Text::Bold);
            title.setString(titleText);
            title.setPosition(240, 14);
            window.draw(title);

            // Draw operation buttons
            for (int i = 0; i < 8; i++) {
                opButtons[i].update(mx, my);
                opButtons[i].draw(window);
            }
            btnBack.update(mx, my);
            btnBack.draw(window);

            // Draw input labels and boxes
            sf::Text lbl;
            lbl.setFont(font);
            lbl.setCharacterSize(14);
            lbl.setFillColor(TEXT_COLOR);

            lbl.setString("Value:");
            lbl.setPosition(inputValue.box.getPosition().x,
                inputValue.box.getPosition().y - 18);
            window.draw(lbl);

            lbl.setString("Pos:");
            lbl.setPosition(inputPos.box.getPosition().x,
                inputPos.box.getPosition().y - 18);
            window.draw(lbl);

            inputValue.draw(window);
            inputPos.draw(window);

            // Draw node count
            sf::Text countText;
            countText.setFont(font);
            countText.setCharacterSize(14);
            countText.setFillColor(TEXT_COLOR);
            countText.setString("Nodes: " + to_string(data.size()));
            countText.setPosition(Width - 120, 16);
            window.draw(countText);

            // ==============================================
            //  DRAW THE LINKED LIST NODES
            // ==============================================

            if (!data.empty())
            {
                // Calculate positions for each node
                float startX = 240.0f;
                float startY = 100.0f;
                float maxRight = Width - 40.0f;
                float curX = startX;
                float curY = startY;

                // Store each node's (x, y) position
                vector<sf::Vector2f> nodePositions;

                for (int i = 0; i < (int)data.size(); i++) {
                    // Wrap to next row if we run out of space
                    if (curX + NODE_W > maxRight && i > 0) {
                        curX = startX;
                        curY += NODE_H + 75.0f;
                    }
                    nodePositions.push_back(sf::Vector2f(curX, curY));
                    curX += NODE_W + NODE_GAP;
                }

                // --- Draw "HEAD" label above first node ---
                sf::Text headLabel;
                headLabel.setFont(font);
                headLabel.setCharacterSize(14);
                headLabel.setFillColor(ARROW_COLOR);
                headLabel.setString("HEAD");
                headLabel.setPosition(nodePositions[0].x, nodePositions[0].y - 30);
                window.draw(headLabel);

                // Small arrow pointing down to first node
                drawArrow(window,
                    nodePositions[0].x + 25, nodePositions[0].y - 12,
                    nodePositions[0].x + 25, nodePositions[0].y - 2,
                    ARROW_COLOR);

                // --- Draw each node ---
                for (int i = 0; i < (int)data.size(); i++)
                {
                    float x = nodePositions[i].x;
                    float y = nodePositions[i].y;

                    // Decide node colour
                    sf::Color fillColor = NODE_COLOR;

                    // Highlight during animation
                    if (i == highlightIndex) {
                        fillColor = highlightColor;
                    }
                    // Keep found node highlighted after animation
                    if (!isAnimating && searchTarget >= 0 &&
                        i == searchTarget && wasFound) {
                        fillColor = FOUND_COLOR;
                    }

                    // Draw the node based on list type
                    if (isDoubly) {
                        drawDoublyNode(window, font, x, y, data[i], fillColor);

                        // Draw NEXT arrow (green, upper part)
                        if (i + 1 < (int)data.size()) {
                            float nextX = nodePositions[i + 1].x;
                            float nextY = nodePositions[i + 1].y;
                            drawArrow(window,
                                x + NODE_W, y + NODE_H * 0.35f,
                                nextX, nextY + NODE_H * 0.35f,
                                ARROW_COLOR);
                        }
                        // Draw PREV arrow (pink, lower part)
                        if (i > 0) {
                            float prevX = nodePositions[i - 1].x;
                            float prevY = nodePositions[i - 1].y;
                            drawArrow(window,
                                x, y + NODE_H * 0.65f,
                                prevX + NODE_W, prevY + NODE_H * 0.65f,
                                PREV_COLOR);
                        }
                    }
                    else {
                        // Singly or Circular: same node shape
                        drawSinglyNode(window, font, x, y, data[i], fillColor);

                        // Draw arrow to next node
                        if (i + 1 < (int)data.size()) {
                            float nextX = nodePositions[i + 1].x;
                            float nextY = nodePositions[i + 1].y;
                            drawArrow(window,
                                x + NODE_W, y + NODE_H / 2.0f,
                                nextX, nextY + NODE_H / 2.0f,
                                ARROW_COLOR);
                        }
                    }

                    // Draw "NULL" label after last node (singly and doubly only)
                    if (!isCircular && i == (int)data.size() - 1) {
                        sf::Text nullText;
                        nullText.setFont(font);
                        nullText.setCharacterSize(14);
                        nullText.setFillColor(NOTFOUND_COL);
                        nullText.setString("NULL");
                        nullText.setPosition(x + NODE_W + 8, y + NODE_H / 2.0f - 8);
                        window.draw(nullText);
                    }
                }

                // --- Draw circular arrow: last node → head ---
                if (isCircular && data.size() > 1)
                {
                    int last = data.size() - 1;
                    drawCurvedArrow(window,
                        nodePositions[last].x + NODE_W,
                        nodePositions[last].y + NODE_H / 2.0f,
                        nodePositions[0].x,
                        nodePositions[0].y + NODE_H / 2.0f,
                        ACCENT_COLOR);
                }
                // Single node circular: draw a self-loop arc
                else if (isCircular && data.size() == 1)
                {
                    float cx = nodePositions[0].x + NODE_W / 2.0f;
                    float cy = nodePositions[0].y - 10.0f;

                    // Draw a small loop using line segments
                    for (int a = 0; a < 20; a++) {
                        float angle1 = 3.14159f + (float)a / 20.0f * 2.0f * 3.14159f;
                        float angle2 = 3.14159f + (float)(a + 1) / 20.0f * 2.0f * 3.14159f;

                        sf::Vertex line[] = {
                            sf::Vertex(sf::Vector2f(cx + 25 * cos(angle1),
                                                    cy + 15 * sin(angle1)), ACCENT_COLOR),
                            sf::Vertex(sf::Vector2f(cx + 25 * cos(angle2),
                                                    cy + 15 * sin(angle2)), ACCENT_COLOR)
                        };
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }
        }

        // Draw status message at bottom
        status.draw(window, font);

        // Show everything on screen
        window.display();

    } // end main loop

    return 0;
}
