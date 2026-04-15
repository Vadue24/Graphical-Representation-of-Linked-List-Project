/*
 * ============================================================
 *  Project  : Graphical Representation of Linked List
 *  Library  : SFML (Simple and Fast Multimedia Library)
 * ============================================================
 *  Author   : Abdullo Kamoliddinov and Aziz Daurov
 *  Roll No  : 4218682
 *  Subject  : Data Structures II
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

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//  Global Consant Variables


const int Width = 1280;
const int Height = 720;

const float NODE_W = 90.0f;
const float NODE_H = 44.0f;
const float PTR_W = 28.0f;
const float NODE_GAP = 55.0f;
const float OP_ANIM_DURATION = 0.85f;
const float STEP_ANIM_DURATION = 0.50f;
const float FLASH_DURATION = 0.20f;
const float STATIC_HIGHLIGHT_DURATION = 0.70f;

const float LIST_START_X = 240.0f;
const float LIST_START_Y = 100.0f;
const float LIST_AREA_X = 230.0f;
const float LIST_AREA_Y = 70.0f;
const float LIST_AREA_W = Width - 250.0f;
const float LIST_AREA_H = Height - 100.0f;

const sf::Color BG_COLOR(30, 30, 46);
const sf::Color NODE_COLOR(69, 71, 90);
const sf::Color OUTLINE_COLOR(137, 180, 250);
const sf::Color ARROW_COLOR(166, 227, 161);
const sf::Color PREV_COLOR(245, 194, 231);
const sf::Color TEXT_COLOR(205, 214, 244);
const sf::Color HIGHLIGHT_COL(249, 226, 175);
const sf::Color FOUND_COLOR(166, 227, 161);
const sf::Color NOTFOUND_COL(243, 139, 168);
const sf::Color BTN_COLOR(49, 50, 68);
const sf::Color BTN_HOVER(69, 71, 90);
const sf::Color TITLE_COLOR(180, 190, 254);
const sf::Color ACCENT_COLOR(137, 180, 250);
const sf::Color PTR_BG(35, 35, 45);


//  SCREENS / OP TYPES

enum Screen {
    SPLASH,
    MAIN_MENU,
    SINGLY_SCREEN,
    DOUBLY_SCREEN,
    CIRCULAR_SCREEN
};

enum OperationAnimType {
    OP_NONE,
    OP_INSERT_BEGIN,
    OP_INSERT_END,
    OP_INSERT_POS,
    OP_DELETE_BEGIN,
    OP_DELETE_END,
    OP_DELETE_POS
};

//  SINGLY LINKED LIST

struct SNode {
    int data;
    SNode* next;

    SNode(int d) {
        data = d;
        next = nullptr;
    }
};

class SinglyLinkedList {
public:
    SNode* head;
    SNode* tail;
    int count;

    SinglyLinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~SinglyLinkedList() {
        while (head != nullptr) {
            deleteBeginning();
        }
    }

    void insertBeginning(int value) {
        SNode* newNode = new SNode(value);
        newNode->next = head;
        head = newNode;

        if (tail == nullptr) {
            tail = newNode;
        }

        count++;
    }

    void insertEnd(int value) {
        SNode* newNode = new SNode(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            count++;
            return;
        }

        tail->next = newNode;
        tail = newNode;
        count++;
    }

    bool insertAtPosition(int value, int pos) {
        if (pos < 1 || pos > count + 1) return false;

        if (pos == 1) {
            insertBeginning(value);
            return true;
        }

        if (pos == count + 1) {
            insertEnd(value);
            return true;
        }

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
        if (head == nullptr) return false;

        SNode* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        count--;
        return true;
    }

    bool deleteEnd() {
        if (head == nullptr) return false;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count--;
            return true;
        }

        SNode* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = nullptr;
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

    int search(int value) {
        SNode* temp = head;
        int pos = 1;

        while (temp != nullptr) {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        }

        return -1;
    }

    vector<int> toVector() const {
        vector<int> result;
        SNode* temp = head;

        while (temp != nullptr) {
            result.push_back(temp->data);
            temp = temp->next;
        }

        return result;
    }
};


//  DOUBLY LINKED LIST


struct DNode {
    int data;
    DNode* next;
    DNode* prev;

    DNode(int d) {
        data = d;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
public:
    DNode* head;
    DNode* tail;
    int count;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~DoublyLinkedList() {
        while (head != nullptr) {
            deleteBeginning();
        }
    }

    void insertBeginning(int value) {
        DNode* newNode = new DNode(value);
        newNode->next = head;

        if (head != nullptr) {
            head->prev = newNode;
        }

        head = newNode;

        if (tail == nullptr) {
            tail = newNode;
        }

        count++;
    }

    void insertEnd(int value) {
        DNode* newNode = new DNode(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            count++;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        count++;
    }

    bool insertAtPosition(int value, int pos) {
        if (pos < 1 || pos > count + 1) return false;

        if (pos == 1) {
            insertBeginning(value);
            return true;
        }

        if (pos == count + 1) {
            insertEnd(value);
            return true;
        }

        DNode* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        DNode* newNode = new DNode(value);
        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next != nullptr) {
            temp->next->prev = newNode;
        }

        temp->next = newNode;
        count++;
        return true;
    }

    bool deleteBeginning() {
        if (head == nullptr) return false;

        DNode* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp;
        count--;
        return true;
    }

    bool deleteEnd() {
        if (head == nullptr) return false;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count--;
            return true;
        }

        DNode* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        count--;
        return true;
    }

    bool deleteAtPosition(int pos) {
        if (pos < 1 || pos > count) return false;
        if (pos == 1) return deleteBeginning();
        if (pos == count) return deleteEnd();

        DNode* temp = head;
        for (int i = 1; i < pos; i++) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }

        delete temp;
        count--;
        return true;
    }

    int search(int value) {
        DNode* temp = head;
        int pos = 1;

        while (temp != nullptr) {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        }

        return -1;
    }

    vector<int> toVector() const {
        vector<int> result;
        DNode* temp = head;

        while (temp != nullptr) {
            result.push_back(temp->data);
            temp = temp->next;
        }

        return result;
    }
};


//  CIRCULAR LINKED LIST


class CircularLinkedList {
public:
    SNode* head;
    SNode* tail;
    int count;

    CircularLinkedList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~CircularLinkedList() {
        while (head != nullptr) {
            deleteBeginning();
        }
    }

    void insertBeginning(int value) {
        SNode* newNode = new SNode(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            count++;
            return;
        }

        newNode->next = head;
        head = newNode;
        tail->next = head;
        count++;
    }

    void insertEnd(int value) {
        SNode* newNode = new SNode(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode;
            count++;
            return;
        }

        tail->next = newNode;
        tail = newNode;
        tail->next = head;
        count++;
    }

    bool insertAtPosition(int value, int pos) {
        if (pos < 1 || pos > count + 1) return false;

        if (pos == 1) {
            insertBeginning(value);
            return true;
        }

        if (pos == count + 1) {
            insertEnd(value);
            return true;
        }

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
        if (head == nullptr) return false;

        if (count == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count = 0;
            return true;
        }

        SNode* temp = head;
        head = head->next;
        tail->next = head;
        delete temp;
        count--;
        return true;
    }

    bool deleteEnd() {
        if (head == nullptr) return false;

        if (count == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            count = 0;
            return true;
        }

        SNode* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = head;
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

    int search(int value) {
        if (head == nullptr) return -1;

        SNode* temp = head;
        int pos = 1;

        do {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        } while (temp != head);

        return -1;
    }

    vector<int> toVector() const {
        vector<int> result;
        if (head == nullptr) return result;

        SNode* temp = head;
        do {
            result.push_back(temp->data);
            temp = temp->next;
        } while (temp != head);

        return result;
    }
};


//  DRAWING HELPERS

float clamp01(float v)
{
    if (v < 0.0f) return 0.0f;
    if (v > 1.0f) return 1.0f;
    return v;
}

float lerpFloat(float a, float b, float t)
{
    return a + (b - a) * t;
}

sf::Vector2f lerpVec(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
    return sf::Vector2f(
        lerpFloat(a.x, b.x, t),
        lerpFloat(a.y, b.y, t)
    );
}

float easeInOutCubic(float t)
{
    t = clamp01(t);

    if (t < 0.5f) {
        return 4.0f * t * t * t;
    }

    float f = -2.0f * t + 2.0f;
    return 1.0f - (f * f * f) / 2.0f;
}

vector<sf::Vector2f> buildNodePositions(int nodeCount)
{
    vector<sf::Vector2f> nodePositions;

    float startX = LIST_START_X;
    float startY = LIST_START_Y;
    float maxRight = Width - 40.0f;
    float curX = startX;
    float curY = startY;

    for (int i = 0; i < nodeCount; i++) {
        if (curX + NODE_W > maxRight && i > 0) {
            curX = startX;
            curY += NODE_H + 75.0f;
        }

        nodePositions.push_back(sf::Vector2f(curX, curY));
        curX += NODE_W + NODE_GAP;
    }

    return nodePositions;
}

void drawLineSegment(sf::RenderWindow& window,
    float x1, float y1, float x2, float y2,
    sf::Color color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);

    if (length < 1.0f) return;

    sf::RectangleShape line(sf::Vector2f(length, 2.0f));
    line.setPosition(x1, y1);
    line.setFillColor(color);
    line.setOrigin(0.0f, 1.0f);

    float angle = atan2(dy, dx) * 180.0f / 3.14159f;
    line.setRotation(angle);

    window.draw(line);
}

void drawArrowHead(sf::RenderWindow& window,
    float x1, float y1, float x2, float y2,
    sf::Color color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);

    if (length < 1.0f) return;

    float ux = dx / length;
    float uy = dy / length;
    float px = -uy;
    float py = ux;

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

void drawArrow(sf::RenderWindow& window,
    float x1, float y1, float x2, float y2,
    sf::Color color)
{
    drawLineSegment(window, x1, y1, x2, y2, color);
    drawArrowHead(window, x1, y1, x2, y2, color);
}

void drawPolylineArrow(sf::RenderWindow& window,
    const vector<sf::Vector2f>& pts,
    sf::Color color)
{
    if (pts.size() < 2) return;

    for (int i = 0; i < (int)pts.size() - 1; i++) {
        drawLineSegment(window,
            pts[i].x, pts[i].y,
            pts[i + 1].x, pts[i + 1].y,
            color);
    }

    drawArrowHead(window,
        pts[(int)pts.size() - 2].x, pts[(int)pts.size() - 2].y,
        pts[(int)pts.size() - 1].x, pts[(int)pts.size() - 1].y,
        color);
}

vector<sf::Vector2f> buildNextArrowPath(const sf::Vector2f& fromPos,
    const sf::Vector2f& toPos,
    bool isDoubly)
{
    float y1 = fromPos.y + (isDoubly ? NODE_H * 0.35f : NODE_H * 0.50f);
    float y2 = toPos.y + (isDoubly ? NODE_H * 0.35f : NODE_H * 0.50f);
    float x1 = fromPos.x + NODE_W;
    float x2 = toPos.x;

    vector<sf::Vector2f> pts;

    // same row -> normal straight arrow
    if (fabs(y1 - y2) < 4.0f) {
        pts.push_back(sf::Vector2f(x1, y1));
        pts.push_back(sf::Vector2f(x2, y2));
        return pts;
    }

    // different row -> bend through the empty gap between rows
    float midY = (y1 + y2) / 2.0f;
    float out = 18.0f;

    pts.push_back(sf::Vector2f(x1, y1));
    pts.push_back(sf::Vector2f(x1 + out, y1));
    pts.push_back(sf::Vector2f(x1 + out, midY));
    pts.push_back(sf::Vector2f(x2 - out, midY));
    pts.push_back(sf::Vector2f(x2 - out, y2));
    pts.push_back(sf::Vector2f(x2, y2));

    return pts;
}

vector<sf::Vector2f> buildPrevArrowPath(const sf::Vector2f& curPos,
    const sf::Vector2f& prevPos)
{
    float y1 = curPos.y + NODE_H * 0.65f;
    float y2 = prevPos.y + NODE_H * 0.65f;
    float x1 = curPos.x;
    float x2 = prevPos.x + NODE_W;

    vector<sf::Vector2f> pts;

    // same row -> normal straight arrow
    if (fabs(y1 - y2) < 4.0f) {
        pts.push_back(sf::Vector2f(x1, y1));
        pts.push_back(sf::Vector2f(x2, y2));
        return pts;
    }

    // different row -> bend through the row gap
    float midY = (y1 + y2) / 2.0f;
    float out = 18.0f;

    pts.push_back(sf::Vector2f(x1, y1));
    pts.push_back(sf::Vector2f(x1 - out, y1));
    pts.push_back(sf::Vector2f(x1 - out, midY));
    pts.push_back(sf::Vector2f(x2 + out, midY));
    pts.push_back(sf::Vector2f(x2 + out, y2));
    pts.push_back(sf::Vector2f(x2, y2));

    return pts;
}

void drawNextLink(sf::RenderWindow& window,
    const sf::Vector2f& fromPos,
    const sf::Vector2f& toPos,
    bool isDoubly,
    sf::Color color)
{
    vector<sf::Vector2f> pts = buildNextArrowPath(fromPos, toPos, isDoubly);
    drawPolylineArrow(window, pts, color);
}

void drawPrevLink(sf::RenderWindow& window,
    const sf::Vector2f& curPos,
    const sf::Vector2f& prevPos,
    sf::Color color)
{
    vector<sf::Vector2f> pts = buildPrevArrowPath(curPos, prevPos);
    drawPolylineArrow(window, pts, color);
}

void drawCurvedArrow(sf::RenderWindow& window,
    float fromX, float fromY,
    float toX, float toY,
    sf::Color color)
{
    float loopY = max(fromY, toY) + 75.0f;

    vector<sf::Vector2f> pts;
    pts.push_back(sf::Vector2f(fromX, fromY));
    pts.push_back(sf::Vector2f(fromX + 22.0f, fromY));
    pts.push_back(sf::Vector2f(fromX + 22.0f, loopY));
    pts.push_back(sf::Vector2f(toX - 22.0f, loopY));
    pts.push_back(sf::Vector2f(toX - 22.0f, toY));
    pts.push_back(sf::Vector2f(toX, toY));

    drawPolylineArrow(window, pts, color);
}

void drawSinglyNode(sf::RenderWindow& window, sf::Font& font,
    float x, float y, int value, sf::Color fillColor)
{
    float dataWidth = NODE_W - PTR_W;

    sf::RectangleShape dataBox(sf::Vector2f(dataWidth, NODE_H));
    dataBox.setPosition(x, y);
    dataBox.setFillColor(fillColor);
    dataBox.setOutlineColor(OUTLINE_COLOR);
    dataBox.setOutlineThickness(2.0f);
    window.draw(dataBox);

    sf::RectangleShape ptrBox(sf::Vector2f(PTR_W, NODE_H));
    ptrBox.setPosition(x + dataWidth, y);
    ptrBox.setFillColor(PTR_BG);
    ptrBox.setOutlineColor(OUTLINE_COLOR);
    ptrBox.setOutlineThickness(2.0f);
    window.draw(ptrBox);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(TEXT_COLOR);
    text.setString(to_string(value));

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);
    text.setPosition(x + dataWidth / 2.0f, y + NODE_H / 2.0f);
    window.draw(text);

    sf::CircleShape dot(3.0f);
    dot.setFillColor(ARROW_COLOR);
    dot.setPosition(x + dataWidth + PTR_W / 2.0f - 3.0f,
        y + NODE_H / 2.0f - 3.0f);
    window.draw(dot);
}

void drawDoublyNode(sf::RenderWindow& window, sf::Font& font,
    float x, float y, int value, sf::Color fillColor)
{
    float dataWidth = NODE_W - 2 * PTR_W;

    sf::RectangleShape prevBox(sf::Vector2f(PTR_W, NODE_H));
    prevBox.setPosition(x, y);
    prevBox.setFillColor(PTR_BG);
    prevBox.setOutlineColor(PREV_COLOR);
    prevBox.setOutlineThickness(2.0f);
    window.draw(prevBox);

    sf::RectangleShape dataBox(sf::Vector2f(dataWidth, NODE_H));
    dataBox.setPosition(x + PTR_W, y);
    dataBox.setFillColor(fillColor);
    dataBox.setOutlineColor(OUTLINE_COLOR);
    dataBox.setOutlineThickness(2.0f);
    window.draw(dataBox);

    sf::RectangleShape nextBox(sf::Vector2f(PTR_W, NODE_H));
    nextBox.setPosition(x + PTR_W + dataWidth, y);
    nextBox.setFillColor(PTR_BG);
    nextBox.setOutlineColor(ARROW_COLOR);
    nextBox.setOutlineThickness(2.0f);
    window.draw(nextBox);

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

void drawEraseWipe(sf::RenderWindow& window, float x, float y, float progress)
{
    progress = clamp01(progress);

    float wipeW = (NODE_W + 8.0f) * progress;

    sf::RectangleShape eraser(sf::Vector2f(wipeW, NODE_H + 8.0f));
    eraser.setPosition(x + NODE_W + 4.0f - wipeW, y - 4.0f);
    eraser.setFillColor(BG_COLOR);
    window.draw(eraser);
}

void drawListAtPositions(sf::RenderWindow& window,
    sf::Font& font,
    const vector<int>& data,
    const vector<sf::Vector2f>& positions,
    bool isDoubly,
    bool isCircular,
    int highlightIndex = -1)
{
    if (data.empty()) return;
    if (data.size() != positions.size()) return;

    sf::Text headLabel;
    headLabel.setFont(font);
    headLabel.setCharacterSize(14);
    headLabel.setFillColor(ARROW_COLOR);
    headLabel.setString("HEAD");
    headLabel.setPosition(positions[0].x, positions[0].y - 30);
    window.draw(headLabel);

    drawArrow(window,
        positions[0].x + 25, positions[0].y - 12,
        positions[0].x + 25, positions[0].y - 2,
        ARROW_COLOR);

    for (int i = 0; i < (int)data.size(); i++) {
        float x = positions[i].x;
        float y = positions[i].y;

        sf::Color fillColor = (i == highlightIndex) ? HIGHLIGHT_COL : NODE_COLOR;

        if (isDoubly) {
            drawDoublyNode(window, font, x, y, data[i], fillColor);

            if (i + 1 < (int)data.size()) {
                drawNextLink(window, positions[i], positions[i + 1], true, ARROW_COLOR);
            }

            if (i > 0) {
                drawPrevLink(window, positions[i], positions[i - 1], PREV_COLOR);
            }
        }
        else {
            drawSinglyNode(window, font, x, y, data[i], fillColor);

            if (i + 1 < (int)data.size()) {
                drawNextLink(window, positions[i], positions[i + 1], false, ARROW_COLOR);
            }
        }

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

    if (isCircular && data.size() > 1) {
        int last = (int)data.size() - 1;
        drawCurvedArrow(window,
            positions[last].x + NODE_W,
            positions[last].y + NODE_H / 2.0f,
            positions[0].x,
            positions[0].y + NODE_H / 2.0f,
            ACCENT_COLOR);
    }
    else if (isCircular && data.size() == 1) {
        float cx = positions[0].x + NODE_W / 2.0f;
        float cy = positions[0].y - 10.0f;

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

void clearListArea(sf::RenderWindow& window)
{
    sf::RectangleShape clearRect(sf::Vector2f(LIST_AREA_W, LIST_AREA_H));
    clearRect.setPosition(LIST_AREA_X, LIST_AREA_Y);
    clearRect.setFillColor(BG_COLOR);
    window.draw(clearRect);
}

void drawOperationOverlay(sf::RenderWindow& window, sf::Font& font,
    Screen currentScreen,
    const vector<int>& beforeData,
    OperationAnimType currentOpAnim,
    int pendingValue, int pendingPos, float t)
{
    t = clamp01(t);
    float smoothT = easeInOutCubic(t);

    bool isDoubly = (currentScreen == DOUBLY_SCREEN);
    bool isCircular = (currentScreen == CIRCULAR_SCREEN);

    int n = (int)beforeData.size();

    if ((currentOpAnim == OP_DELETE_BEGIN ||
        currentOpAnim == OP_DELETE_END ||
        currentOpAnim == OP_DELETE_POS) && n == 0)
    {
        return;
    }

    // --------------------------------------------------------
    // INSERT ANIMATION
    // --------------------------------------------------------
    if (currentOpAnim == OP_INSERT_BEGIN ||
        currentOpAnim == OP_INSERT_END ||
        currentOpAnim == OP_INSERT_POS)
    {
        int insertIndex = 0;

        if (currentOpAnim == OP_INSERT_BEGIN) insertIndex = 0;
        else if (currentOpAnim == OP_INSERT_END) insertIndex = n;
        else insertIndex = pendingPos - 1;

        if (insertIndex < 0) insertIndex = 0;
        if (insertIndex > n) insertIndex = n;

        vector<sf::Vector2f> beforePos = buildNodePositions(n);
        vector<sf::Vector2f> afterPos = buildNodePositions(n + 1);

        vector<int> drawData;
        vector<sf::Vector2f> drawPos;

        drawData.reserve(n + 1);
        drawPos.reserve(n + 1);

        for (int i = 0; i < insertIndex; i++) {
            drawData.push_back(beforeData[i]);
            drawPos.push_back(lerpVec(beforePos[i], afterPos[i], smoothT));
        }

        sf::Vector2f newStart = afterPos[insertIndex];

        if (currentOpAnim == OP_INSERT_END) {
            newStart.x += 130.0f;
            newStart.y -= 8.0f;
        }
        else {
            newStart.y -= 95.0f;
        }

        drawData.push_back(pendingValue);
        drawPos.push_back(lerpVec(newStart, afterPos[insertIndex], smoothT));

        for (int i = insertIndex; i < n; i++) {
            drawData.push_back(beforeData[i]);
            drawPos.push_back(lerpVec(beforePos[i], afterPos[i + 1], smoothT));
        }

        clearListArea(window);
        drawListAtPositions(window, font, drawData, drawPos, isDoubly, isCircular, insertIndex);
        return;
    }

    // --------------------------------------------------------
    // DELETE ANIMATION
    // --------------------------------------------------------
    if (currentOpAnim == OP_DELETE_BEGIN ||
        currentOpAnim == OP_DELETE_END ||
        currentOpAnim == OP_DELETE_POS)
    {
        int deleteIndex = 0;

        if (currentOpAnim == OP_DELETE_BEGIN) deleteIndex = 0;
        else if (currentOpAnim == OP_DELETE_END) deleteIndex = n - 1;
        else deleteIndex = pendingPos - 1;

        if (deleteIndex < 0 || deleteIndex >= n) return;

        vector<sf::Vector2f> beforePos = buildNodePositions(n);
        vector<sf::Vector2f> afterPos = buildNodePositions(max(0, n - 1));

        clearListArea(window);

        // draw remaining nodes moving together
        if (n > 1) {
            vector<int> remainData;
            vector<sf::Vector2f> remainPos;

            remainData.reserve(n - 1);
            remainPos.reserve(n - 1);

            for (int i = 0; i < n; i++) {
                if (i == deleteIndex) continue;

                int newIndex = (i < deleteIndex) ? i : i - 1;
                remainData.push_back(beforeData[i]);
                remainPos.push_back(lerpVec(beforePos[i], afterPos[newIndex], smoothT));
            }

            drawListAtPositions(window, font, remainData, remainPos, isDoubly, isCircular, -1);
        }

        // draw deleted node wiping away
        sf::Vector2f deadStart = beforePos[deleteIndex];
        sf::Vector2f deadEnd(deadStart.x + 30.0f, deadStart.y - 50.0f);
        sf::Vector2f deadNow = lerpVec(deadStart, deadEnd, smoothT);

        if (isDoubly) {
            drawDoublyNode(window, font, deadNow.x, deadNow.y,
                beforeData[deleteIndex], HIGHLIGHT_COL);
        }
        else {
            drawSinglyNode(window, font, deadNow.x, deadNow.y,
                beforeData[deleteIndex], HIGHLIGHT_COL);
        }

        drawEraseWipe(window, deadNow.x, deadNow.y, smoothT);
        return;
    }
}


//  BUTTON


struct Button {
    sf::RectangleShape box;
    sf::Text label;

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

        sf::FloatRect b = label.getLocalBounds();
        label.setOrigin(b.left + b.width / 2.0f,
            b.top + b.height / 2.0f);
        label.setPosition(x + w / 2.0f, y + h / 2.0f);
    }

    bool isClicked(float mx, float my) {
        return box.getGlobalBounds().contains(mx, my);
    }

    void update(float mx, float my) {
        if (box.getGlobalBounds().contains(mx, my)) {
            box.setFillColor(BTN_HOVER);
        }
        else {
            box.setFillColor(BTN_COLOR);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(label);
    }
};

// ============================================================
//  INPUT BOX
// ============================================================

struct TextInput {
    string text;
    sf::RectangleShape box;
    sf::Text display;
    bool active;

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

    void handleEvent(sf::Event& event) {
        if (!active) return;
        if (event.type != sf::Event::TextEntered) return;

        char c = (char)event.text.unicode;

        if (c == '\b') {
            if (!text.empty()) text.pop_back();
        }
        else if ((c >= '0' && c <= '9') || c == '-') {
            if (text.size() < 10) {
                text += c;
            }
        }
    }

    int getValue() {
        if (text.empty()) return 0;

        try {
            return stoi(text);
        }
        catch (...) {
            return 0;
        }
    }

    void clear() {
        text = "";
    }

    void draw(sf::RenderWindow& window) {
        if (active) box.setOutlineColor(HIGHLIGHT_COL);
        else        box.setOutlineColor(ACCENT_COLOR);

        window.draw(box);

        if (active) display.setString(text + "_");
        else        display.setString(text);

        window.draw(display);
    }
};

// ============================================================
//  STATUS BAR
// ============================================================

struct StatusBar {
    string message;
    sf::Clock clock;
    float showTime;

    StatusBar() {
        showTime = 0;
    }

    void set(string msg, float seconds = 3.0f) {
        message = msg;
        showTime = seconds;
        clock.restart();
    }

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
//  SMALL HELPER
// ============================================================

void centerText(sf::Text& text, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);
    text.setPosition(Width / 2.0f, y);
}

// ============================================================
//  MAIN
// ============================================================

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(Width, Height),
        "Graphical Representation of Linked List",
        sf::Style::Close | sf::Style::Titlebar
    );
    window.setFramerateLimit(60);

    sf::Font font;
    bool fontOK = false;

    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    bool logoOK = false;

    string fontPaths[] = {
        "Roboto-Regular.ttf",
        "C:/Windows/Fonts/Roboto-Light.ttf",
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

    if (logoTexture.loadFromFile("Webster.png")) {
        logoOK = true;
        logoSprite.setTexture(logoTexture);

        float targetWidth = 90.0f;
        float scale = targetWidth / (float)logoTexture.getSize().x;
        logoSprite.setScale(scale, scale);
        logoSprite.setPosition(Width - targetWidth - 20.0f, 20.0f);
        logoSprite.setColor(sf::Color(255, 255, 255, 220));
    }

    SinglyLinkedList singlyList;
    DoublyLinkedList doublyList;
    CircularLinkedList circularList;

    Screen currentScreen = SPLASH;
    StatusBar status;

    int highlightIndex = -1;
    sf::Clock animClock;
    bool isAnimating = false;

    int searchTarget = -1;
    int totalNodes = 0;
    bool wasFound = false;

    int flashCount = 0;
    bool flashOn = false;
    bool isSearchMode = false;

    string liveInfo = "";
    vector<int> animData;
    vector<int> opSnapshot;

    OperationAnimType currentOpAnim = OP_NONE;
    int pendingValue = 0;
    int pendingPos = 0;

    bool showStaticHighlight = false;
    sf::Clock staticHighlightClock;

    Button btnSingly, btnDoubly, btnCircular, btnExit;

    float menuX = Width / 2.0f - 110.0f;
    btnSingly.create(font, "Singly Linked List", menuX, 260, 220, 42);
    btnDoubly.create(font, "Doubly Linked List", menuX, 320, 220, 42);
    btnCircular.create(font, "Circular Linked List", menuX, 380, 220, 42);
    btnExit.create(font, "Exit", menuX, 440, 220, 42);

    Button opButtons[8];
    Button btnBack;
    TextInput inputValue;
    TextInput inputPos;

    auto setupOpButtons = [&]() {
        float x = 20, y = 60, w = 200, h = 36, gap = 6;
        opButtons[0].create(font, "Insert Beginning", x, y, w, h); y += h + gap;
        opButtons[1].create(font, "Insert End", x, y, w, h); y += h + gap;
        opButtons[2].create(font, "Insert at Pos", x, y, w, h); y += h + gap;
        opButtons[3].create(font, "Delete Beginning", x, y, w, h); y += h + gap;
        opButtons[4].create(font, "Delete End", x, y, w, h); y += h + gap;
        opButtons[5].create(font, "Delete at Pos", x, y, w, h); y += h + gap;
        opButtons[6].create(font, "Traverse", x, y, w, h); y += h + gap;
        opButtons[7].create(font, "Search", x, y, w, h);

        btnBack.create(font, "Back to Menu", x, y + 46, w, h);

        inputValue.create(font, x, y + 120, 90, 30);
        inputPos.create(font, x + 110, y + 120, 70, 30);
        inputValue.active = true;
        inputPos.active = false;
    };

    auto resetAnimationState = [&]() {
        isAnimating = false;
        highlightIndex = -1;
        searchTarget = -1;
        wasFound = false;
        flashCount = 0;
        flashOn = false;
        isSearchMode = false;
        liveInfo = "";
        animData.clear();
        opSnapshot.clear();
        currentOpAnim = OP_NONE;
        pendingValue = 0;
        pendingPos = 0;
        showStaticHighlight = false;
    };

    auto currentListVector = [&]() -> vector<int> {
        if (currentScreen == SINGLY_SCREEN) return singlyList.toVector();
        if (currentScreen == DOUBLY_SCREEN) return doublyList.toVector();
        return circularList.toVector();
    };

    auto startOperationAnim = [&](OperationAnimType type,
        int value,
        int pos,
        int highlight,
        const string& info,
        const string& msg)
    {
        currentOpAnim = type;
        pendingValue = value;
        pendingPos = pos;
        isAnimating = true;
        isSearchMode = false;
        searchTarget = -1;
        wasFound = false;
        flashCount = 0;
        flashOn = false;
        highlightIndex = highlight;
        liveInfo = info;
        animData.clear();
        totalNodes = 0;
        showStaticHighlight = false;
        opSnapshot = currentListVector();
        animClock.restart();
        status.set(msg);
    };

    auto startTraverseAnim = [&](const vector<int>& v) {
        if (v.empty()) {
            status.set("List is empty!");
            liveInfo = "";
            animData.clear();
            return;
        }

        isAnimating = true;
        isSearchMode = false;
        currentOpAnim = OP_NONE;
        highlightIndex = -1;
        totalNodes = (int)v.size();
        animData = v;
        liveInfo = "Traversal started...";
        searchTarget = -1;
        wasFound = false;
        flashCount = 0;
        flashOn = false;
        showStaticHighlight = false;
        animClock.restart();
        status.set("Traversing...", totalNodes * 0.6f + 1);
    };

    auto startSearchAnim = [&](const vector<int>& v, int value, int foundPos) {
        if (v.empty()) {
            status.set("List is empty!");
            inputValue.clear();
            liveInfo = "";
            animData.clear();
            return;
        }

        isAnimating = true;
        isSearchMode = true;
        currentOpAnim = OP_NONE;
        highlightIndex = -1;
        totalNodes = (int)v.size();
        animData = v;
        liveInfo = "Searching for " + to_string(value) + "...";
        searchTarget = (foundPos > 0) ? foundPos - 1 : -1;
        wasFound = (foundPos > 0);
        flashCount = 0;
        flashOn = false;
        showStaticHighlight = false;
        animClock.restart();
        status.set("Searching for " + to_string(value) + "...", totalNodes * 0.6f + 1);
        inputValue.clear();
    };

    auto keepResultHighlight = [&](int idx) {
        highlightIndex = idx;
        if (idx >= 0) {
            showStaticHighlight = true;
            staticHighlightClock.restart();
        }
        else {
            showStaticHighlight = false;
        }
    };

    while (window.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float mx = (float)mousePos.x;
        float my = (float)mousePos.y;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentScreen == SINGLY_SCREEN ||
                currentScreen == DOUBLY_SCREEN ||
                currentScreen == CIRCULAR_SCREEN)
            {
                inputValue.handleEvent(event);
                inputPos.handleEvent(event);
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                float clickX = (float)event.mouseButton.x;
                float clickY = (float)event.mouseButton.y;

                if (currentScreen == SPLASH) {
                    currentScreen = MAIN_MENU;
                    continue;
                }

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

                if (inputValue.box.getGlobalBounds().contains(clickX, clickY)) {
                    inputValue.active = true;
                    inputPos.active = false;
                }
                else if (inputPos.box.getGlobalBounds().contains(clickX, clickY)) {
                    inputPos.active = true;
                    inputValue.active = false;
                }

                if (btnBack.isClicked(clickX, clickY)) {
                    currentScreen = MAIN_MENU;
                    resetAnimationState();
                    continue;
                }

                int val = inputValue.getValue();
                int pos = inputPos.getValue();

                for (int i = 0; i < 8; i++)
                {
                    if (!opButtons[i].isClicked(clickX, clickY)) continue;

                    resetAnimationState();

                    if (currentScreen == SINGLY_SCREEN) {
                        if (i == 0) {
                            startOperationAnim(
                                OP_INSERT_BEGIN, val, 0, 0,
                                "Preparing to insert at the beginning",
                                "Inserting: " + to_string(val) + " at the beginning"
                            );
                            inputValue.clear();
                        }
                        else if (i == 1) {
                            int h = singlyList.count - 1;
                            if (singlyList.count == 0) h = -1;

                            startOperationAnim(
                                OP_INSERT_END, val, 0, h,
                                "Preparing to insert at end",
                                "Inserting " + to_string(val) + " at end"
                            );
                            inputValue.clear();
                        }
                        else if (i == 2) {
                            if (pos < 1 || pos > singlyList.count + 1) {
                                status.set("Invalid position!");
                            }
                            else {
                                int h = (pos == 1) ? 0 : pos - 2;
                                startOperationAnim(
                                    OP_INSERT_POS, val, pos, h,
                                    "Preparing to insert at position " + to_string(pos),
                                    "Inserting " + to_string(val) + " at position " + to_string(pos)
                                );
                            }
                            inputValue.clear();
                            inputPos.clear();
                        }
                        else if (i == 3) {
                            if (singlyList.count == 0) {
                                status.set("The list cannot be empty!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_BEGIN, 0, 0, 0,
                                    "Preparing to delete first node",
                                    "Deleting from beginning"
                                );
                            }
                        }
                        else if (i == 4) {
                            if (singlyList.count == 0) {
                                status.set("The list cannot be empty!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_END, 0, 0, singlyList.count - 1,
                                    "Preparing to delete last node",
                                    "Deleting from end"
                                );
                            }
                        }
                        else if (i == 5) {
                            if (pos < 1 || pos > singlyList.count) {
                                status.set("Wrong position! try again!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_POS, 0, pos, pos - 1,
                                    "Preparing to delete node at position " + to_string(pos),
                                    "Deleting at position " + to_string(pos)
                                );
                            }
                            inputPos.clear();
                        }
                        else if (i == 6) {
                            vector<int> v = singlyList.toVector();
                            startTraverseAnim(v);

                            for (int k = 0; k < (int)v.size(); k++) {
                                cout << "Node " << k << " value:" << v[k] << endl;
                            }
                        }
                        else if (i == 7) {
                            vector<int> v = singlyList.toVector();
                            int idx = singlyList.search(val);
                            startSearchAnim(v, val, idx);
                        }
                    }

                    else if (currentScreen == DOUBLY_SCREEN) {
                        if (i == 0) {
                            startOperationAnim(
                                OP_INSERT_BEGIN, val, 0, 0,
                                "Preparing to insert at beginning",
                                "Inserting " + to_string(val) + " at beginning"
                            );
                            inputValue.clear();
                        }
                        else if (i == 1) {
                            int h = doublyList.count - 1;
                            if (doublyList.count == 0) h = -1;

                            startOperationAnim(
                                OP_INSERT_END, val, 0, h,
                                "Preparing to insert at end",
                                "Inserting " + to_string(val) + " at end"
                            );
                            inputValue.clear();
                        }
                        else if (i == 2) {
                            if (pos < 1 || pos > doublyList.count + 1) {
                                status.set("The position cannot be invalid!");
                            }
                            else {
                                int h = (pos == 1) ? 0 : pos - 2;
                                startOperationAnim(
                                    OP_INSERT_POS, val, pos, h,
                                    "Preparing to insert at position " + to_string(pos),
                                    "Inserting " + to_string(val) + " at position " + to_string(pos)
                                );
                            }
                            inputValue.clear();
                            inputPos.clear();
                        }
                        else if (i == 3) {
                            if (doublyList.count == 0) {
                                status.set("List cannot be empty!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_BEGIN, 0, 0, 0,
                                    "Preparing to delete first node",
                                    "Deleting from beginning"
                                );
                            }
                        }
                        else if (i == 4) {
                            if (doublyList.count == 0) {
                                status.set("List cannot be empty!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_END, 0, 0, doublyList.count - 1,
                                    "Preparing to delete last node",
                                    "Deleting from end"
                                );
                            }
                        }
                        else if (i == 5) {
                            if (pos < 1 || pos > doublyList.count) {
                                status.set("The position cannot be invalid!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_POS, 0, pos, pos - 1,
                                    "Preparing to delete node at position " + to_string(pos),
                                    "Deleting at position " + to_string(pos)
                                );
                            }
                            inputPos.clear();
                        }
                        else if (i == 6) {
                            vector<int> v = doublyList.toVector();
                            startTraverseAnim(v);
                            for (int k = 0; k < (int)v.size(); k++) {
                                cout << "Node " << k << " value:" << v[k] << endl;
                            }
                        }
                        else if (i == 7) {
                            vector<int> v = doublyList.toVector();
                            int idx = doublyList.search(val);
                            startSearchAnim(v, val, idx);
                        }
                    }

                    else if (currentScreen == CIRCULAR_SCREEN) {
                        if (i == 0) {
                            startOperationAnim(
                                OP_INSERT_BEGIN, val, 0, 0,
                                "Preparing to insert at beginning",
                                "Inserting " + to_string(val) + " at beginning"
                            );
                            inputValue.clear();
                        }
                        else if (i == 1) {
                            int h = circularList.count - 1;
                            if (circularList.count == 0) h = -1;

                            startOperationAnim(
                                OP_INSERT_END, val, 0, h,
                                "Preparing to insert at end",
                                "Inserting " + to_string(val) + " at end"
                            );
                            inputValue.clear();
                        }
                        else if (i == 2) {
                            if (pos < 1 || pos > circularList.count + 1) {
                                status.set("Invalid position!");
                            }
                            else {
                                int h = (pos == 1) ? 0 : pos - 2;
                                startOperationAnim(
                                    OP_INSERT_POS, val, pos, h,
                                    "Preparing to insert at position " + to_string(pos),
                                    "Inserting " + to_string(val) + " at position " + to_string(pos)
                                );
                            }
                            inputValue.clear();
                            inputPos.clear();
                        }
                        else if (i == 3) {
                            if (circularList.count == 0) {
                                status.set("The list cannot be empty!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_BEGIN, 0, 0, 0,
                                    "Preparing to delete first node",
                                    "Deleting from beginning"
                                );
                            }
                        }
                        else if (i == 4) {
                            if (circularList.count == 0) {
                                status.set("The list cannot be empty");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_END, 0, 0, circularList.count - 1,
                                    "Preparing to delete last node",
                                    "Deleting from end"
                                );
                            }
                        }
                        else if (i == 5) {
                            if (pos < 1 || pos > circularList.count) {
                                status.set("Position cannot be!");
                            }
                            else {
                                startOperationAnim(
                                    OP_DELETE_POS, 0, pos, pos - 1,
                                    "Preparing to delete node at position " + to_string(pos),
                                    "Deleting at position " + to_string(pos)
                                );
                            }
                            inputPos.clear();
                        }
                        else if (i == 6) {
                            vector<int> v = circularList.toVector();
                            startTraverseAnim(v);
                            for (int k = 0; k < (int)v.size(); k++) {
                                cout << "Node " << k << " value:" << v[k] << endl;
                            }
                        }
                        else if (i == 7) {
                            vector<int> v = circularList.toVector();
                            int idx = circularList.search(val);
                            startSearchAnim(v, val, idx);
                        }
                    }

                    break;
                }
            }
        }

        if (showStaticHighlight &&
            staticHighlightClock.getElapsedTime().asSeconds() > STATIC_HIGHLIGHT_DURATION)
        {
            showStaticHighlight = false;
            highlightIndex = -1;
        }

        float currentAnimLimit = (currentOpAnim != OP_NONE) ? OP_ANIM_DURATION : STEP_ANIM_DURATION;

        if (isAnimating && animClock.getElapsedTime().asSeconds() > currentAnimLimit)
        {
            animClock.restart();

            if (currentOpAnim != OP_NONE) {
                isAnimating = false;

                if (currentScreen == SINGLY_SCREEN) {
                    if (currentOpAnim == OP_INSERT_BEGIN) {
                        singlyList.insertBeginning(pendingValue);
                        status.set("Inserted: " + to_string(pendingValue) + " at beginning");
                        liveInfo = "The node is inserted at beginning";
                        keepResultHighlight(0);
                    }
                    else if (currentOpAnim == OP_INSERT_END) {
                        singlyList.insertEnd(pendingValue);
                        status.set("Inserted: " + to_string(pendingValue) + " at end");
                        liveInfo = "The node inserted at end";
                        keepResultHighlight(singlyList.count - 1);
                    }
                    else if (currentOpAnim == OP_INSERT_POS) {
                        singlyList.insertAtPosition(pendingValue, pendingPos);
                        status.set("Inserted: " + to_string(pendingValue) + " at position " + to_string(pendingPos));
                        liveInfo = "The node inserted at position " + to_string(pendingPos);
                        keepResultHighlight(pendingPos - 1);
                    }
                    else if (currentOpAnim == OP_DELETE_BEGIN) {
                        singlyList.deleteBeginning();
                        status.set("Deleted from beginning");
                        liveInfo = "The first node deleted";
                        keepResultHighlight(-1);
                    }
                    else if (currentOpAnim == OP_DELETE_END) {
                        singlyList.deleteEnd();
                        status.set("Deleted from end");
                        liveInfo = "The last node deleted";
                        keepResultHighlight(-1);
                    }
                    else if (currentOpAnim == OP_DELETE_POS) {
                        singlyList.deleteAtPosition(pendingPos);
                        status.set("Deleted at position " + to_string(pendingPos));
                        liveInfo = "The node deleted at position: " + to_string(pendingPos);
                        keepResultHighlight(-1);
                    }
                }
                else if (currentScreen == DOUBLY_SCREEN) {
                    if (currentOpAnim == OP_INSERT_BEGIN) {
                        doublyList.insertBeginning(pendingValue);
                        status.set("Inserted " + to_string(pendingValue) + " at beginning");
                        liveInfo = "Node inserted at beginning";
                        keepResultHighlight(0);
                    }
                    else if (currentOpAnim == OP_INSERT_END) {
                        doublyList.insertEnd(pendingValue);
                        status.set("Inserted " + to_string(pendingValue) + " at end");
                        liveInfo = "Node inserted at end";
                        keepResultHighlight(doublyList.count - 1);
                    }
                    else if (currentOpAnim == OP_INSERT_POS) {
                        doublyList.insertAtPosition(pendingValue, pendingPos);
                        status.set("Inserted " + to_string(pendingValue) + " at position " + to_string(pendingPos));
                        liveInfo = "Node inserted at position " + to_string(pendingPos);
                        keepResultHighlight(pendingPos - 1);
                    }
                    else if (currentOpAnim == OP_DELETE_BEGIN) {
                        doublyList.deleteBeginning();
                        status.set("Deleted from beginning");
                        liveInfo = "First node deleted";
                        keepResultHighlight(-1);
                    }
                    else if (currentOpAnim == OP_DELETE_END) {
                        doublyList.deleteEnd();
                        status.set("Deleted from end");
                        liveInfo = "Last node deleted";
                        keepResultHighlight(-1);
                    }
                    else if (currentOpAnim == OP_DELETE_POS) {
                        doublyList.deleteAtPosition(pendingPos);
                        status.set("Deleted at position " + to_string(pendingPos));
                        liveInfo = "Node deleted at position " + to_string(pendingPos);
                        keepResultHighlight(-1);
                    }
                }
                else if (currentScreen == CIRCULAR_SCREEN) {
                    if (currentOpAnim == OP_INSERT_BEGIN) {
                        circularList.insertBeginning(pendingValue);
                        status.set("Inserted " + to_string(pendingValue) + " at beginning");
                        liveInfo = "Node inserted at beginning";
                        keepResultHighlight(0);
                    }
                    else if (currentOpAnim == OP_INSERT_END) {
                        circularList.insertEnd(pendingValue);
                        status.set("Inserted " + to_string(pendingValue) + " at end");
                        liveInfo = "Node inserted at end";
                        keepResultHighlight(circularList.count - 1);
                    }
                    else if (currentOpAnim == OP_INSERT_POS) {
                        circularList.insertAtPosition(pendingValue, pendingPos);
                        status.set("Inserted " + to_string(pendingValue) + " at position " + to_string(pendingPos));
                        liveInfo = "Node inserted at position " + to_string(pendingPos);
                        keepResultHighlight(pendingPos - 1);
                    }
                    else if (currentOpAnim == OP_DELETE_BEGIN) {
                        circularList.deleteBeginning();
                        status.set("Deleted from beginning");
                        liveInfo = "First node deleted";
                        keepResultHighlight(-1);
                    }
                    else if (currentOpAnim == OP_DELETE_END) {
                        circularList.deleteEnd();
                        status.set("Deleted from end");
                        liveInfo = "Last node deleted";
                        keepResultHighlight(-1);
                    }
                    else if (currentOpAnim == OP_DELETE_POS) {
                        circularList.deleteAtPosition(pendingPos);
                        status.set("Deleted at position " + to_string(pendingPos));
                        liveInfo = "Node deleted at position " + to_string(pendingPos);
                        keepResultHighlight(-1);
                    }
                }

                currentOpAnim = OP_NONE;
                pendingValue = 0;
                pendingPos = 0;
                opSnapshot.clear();
                continue;
            }

            highlightIndex++;

            if (highlightIndex >= 0 && highlightIndex < totalNodes) {
                if (isSearchMode) {
                    liveInfo = "Checking node " + to_string(highlightIndex + 1) +
                        " Value: " + to_string(animData[highlightIndex]);
                }
                else {
                    liveInfo = "Visiting node " + to_string(highlightIndex + 1) +
                        " Value: " + to_string(animData[highlightIndex]);
                }
            }

            if (isSearchMode && searchTarget >= 0 && highlightIndex == searchTarget) {
                isAnimating = false;
                flashCount = 6;
                flashOn = true;
                liveInfo = "Found at position " + to_string(searchTarget + 1) +
                    " | Value: " + to_string(animData[searchTarget]);
                status.set("Element found at position " + to_string(searchTarget + 1));
            }
            else if (highlightIndex >= totalNodes) {
                isAnimating = false;

                if (!isSearchMode) {
                    status.set("Traversal complete");
                    liveInfo = "Traversal complete";
                    highlightIndex = -1;
                }
                else if (!wasFound) {
                    highlightIndex = -1;
                    liveInfo = "Element not found";
                    status.set("Element not found!");
                }
            }
        }

        if (!isAnimating && flashCount > 0 &&
            animClock.getElapsedTime().asSeconds() > FLASH_DURATION)
        {
            animClock.restart();
            flashOn = !flashOn;
            flashCount--;

            if (flashCount == 0) {
                flashOn = true;
            }
        }

        // ========================================================
        //  DRAWING
        // ========================================================

        window.clear(BG_COLOR);

        if (currentScreen == SPLASH)
        {
            sf::Text title;
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
            info.setString("Author: Aziz Daurov and Abdullo Kamoliddinov\n"
                "Roll No: 4223575  4218682\n"
                "Subject: COSC 3100 - Data Structures II");
            centerText(info, 320);
            window.draw(info);

            sf::Text hint;
            hint.setFont(font);
            hint.setCharacterSize(16);
            hint.setFillColor(ACCENT_COLOR);
            hint.setString("Click anywhere to continue");
            centerText(hint, 450);
            window.draw(hint);
        }
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

            if (logoOK) {
                window.draw(logoSprite);
            }

            btnSingly.update(mx, my);   btnSingly.draw(window);
            btnDoubly.update(mx, my);   btnDoubly.draw(window);
            btnCircular.update(mx, my); btnCircular.draw(window);
            btnExit.update(mx, my);     btnExit.draw(window);
        }
        else
        {
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

            sf::Text title;
            title.setFont(font);
            title.setCharacterSize(22);
            title.setFillColor(TITLE_COLOR);
            title.setStyle(sf::Text::Bold);
            title.setString(titleText);
            title.setPosition(240, 14);
            window.draw(title);

            sf::Text liveText;
            liveText.setFont(font);
            liveText.setCharacterSize(16);
            liveText.setFillColor(HIGHLIGHT_COL);
            liveText.setString(liveInfo);
            liveText.setPosition(240, 44);
            window.draw(liveText);

            for (int i = 0; i < 8; i++) {
                opButtons[i].update(mx, my);
                opButtons[i].draw(window);
            }

            btnBack.update(mx, my);
            btnBack.draw(window);

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

            sf::Text countText;
            countText.setFont(font);
            countText.setCharacterSize(14);
            countText.setFillColor(TEXT_COLOR);
            countText.setString("Nodes: " + to_string(data.size()));
            countText.setPosition(Width - 120, 16);
            window.draw(countText);

            if (!data.empty())
            {
                vector<sf::Vector2f> nodePositions = buildNodePositions((int)data.size());

                sf::Text headLabel;
                headLabel.setFont(font);
                headLabel.setCharacterSize(14);
                headLabel.setFillColor(ARROW_COLOR);
                headLabel.setString("HEAD");
                headLabel.setPosition(nodePositions[0].x, nodePositions[0].y - 30);
                window.draw(headLabel);

                drawArrow(window,
                    nodePositions[0].x + 25, nodePositions[0].y - 12,
                    nodePositions[0].x + 25, nodePositions[0].y - 2,
                    ARROW_COLOR);

                for (int i = 0; i < (int)data.size(); i++)
                {
                    float x = nodePositions[i].x;
                    float y = nodePositions[i].y;

                    sf::Color fillColor = NODE_COLOR;

                    if (i == highlightIndex && (isAnimating || showStaticHighlight)) {
                        fillColor = HIGHLIGHT_COL;
                    }

                    if (!isAnimating && searchTarget >= 0 && i == searchTarget && wasFound) {
                        fillColor = flashOn ? FOUND_COLOR : NODE_COLOR;
                    }

                    if (isDoubly) {
                        drawDoublyNode(window, font, x, y, data[i], fillColor);

                        if (i + 1 < (int)data.size()) {
                            drawNextLink(window, nodePositions[i], nodePositions[i + 1], true, ARROW_COLOR);
                        }

                        if (i > 0) {
                            drawPrevLink(window, nodePositions[i], nodePositions[i - 1], PREV_COLOR);
                        }
                    }
                    else {
                        drawSinglyNode(window, font, x, y, data[i], fillColor);

                        if (i + 1 < (int)data.size()) {
                            drawNextLink(window, nodePositions[i], nodePositions[i + 1], false, ARROW_COLOR);
                        }
                    }

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

                if (isCircular && data.size() > 1)
                {
                    int last = (int)data.size() - 1;
                    drawCurvedArrow(window,
                        nodePositions[last].x + NODE_W,
                        nodePositions[last].y + NODE_H / 2.0f,
                        nodePositions[0].x,
                        nodePositions[0].y + NODE_H / 2.0f,
                        ACCENT_COLOR);
                }
                else if (isCircular && data.size() == 1)
                {
                    float cx = nodePositions[0].x + NODE_W / 2.0f;
                    float cy = nodePositions[0].y - 10.0f;

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

            if (currentOpAnim != OP_NONE && isAnimating) {
                float opProgress = animClock.getElapsedTime().asSeconds() / OP_ANIM_DURATION;
                drawOperationOverlay(window, font,
                    currentScreen,
                    opSnapshot,
                    currentOpAnim,
                    pendingValue,
                    pendingPos,
                    opProgress);
            }
        }

        status.draw(window, font);
        window.display();
    }

    return 0;
}
