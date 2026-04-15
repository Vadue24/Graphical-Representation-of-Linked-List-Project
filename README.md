# Data Structures Visualizer: Linked Lists 🚀

A high-performance, interactive educational tool built in **C++** using the **SFML library**. This project provides a step-by-step visual representation of how different types of linked lists function, making it easier for students and developers to understand memory management and pointer logic.

---

### 📝 Overview
Understanding pointers and linked structures can be challenging. This application bridges the gap between abstract code and visual logic. It allows users to manipulate data structures in real-time and observe how nodes are created, how pointers are redirected, and how memory is traversed.

---

### 🛠 Tech Stack
* **Language:** C++11 / C++14
* **Graphics Library:** SFML (Simple and Fast Multimedia Library)
* **Mathematics:** Linear interpolation (Lerp) for smooth node transitions and custom geometry for drawing arrows/pointers.
* **Paradigm:** Object-Oriented Programming (OOP).

---

### 🌟 Key Features

#### 1. Supported Data Structures
* **Singly Linked List:** Classic one-way traversal.
* **Doubly Linked List:** Two-way traversal with next and previous pointers.
* **Circular Linked List:** Demonstrates the loop-back logic from the tail to the head.

#### 2. Interactive Operations
* **Insertion:** Add nodes at the Head, Tail, or any specific Index.
* **Deletion:** Remove nodes from any position.
* **Search:** Real-time visual "traversal" where the program highlights each node as it searches for a specific value.
* **Update:** Modify the data within an existing node.

#### 3. Advanced Visualization
* **Smooth Animations:** Nodes don't just appear; they slide into position, and existing nodes shift to make room.
* **Color Coding:** * 🟢 **Green** for new/active nodes.
  * 🔴 **Red** for nodes being deleted.
  * 🟡 **Yellow** for the current pointer position during traversal.
* **Real-time Logic:** The visual representation is directly tied to the underlying C++ logic classes.

---

### 🏗 Project Architecture
The project is structured to separate data logic from the rendering engine:

1. **Linked List Classes:** Custom implementations of Singly, Doubly, and Circular lists. These classes handle the pointer manipulation (assigning `next` and `prev` addresses).
2. **UI Engine:** A custom-built UI system within SFML including a Button class, TextInput for node values, and a StatusBar for textual feedback.
3. **Renderer:** A specialized module that calculates coordinates for nodes and draws dynamic arrows that adjust their length and angle.

---

### 🎮 How to Use
1. **Select Mode:** Choose the list type from the main menu.
2. **Input Data:** Click on the text field to type a value (0-99).
3. **Choose Operation:** Click "Insert", "Delete", or "Search".
4. **Watch the Logic:** Observe the status bar and the moving nodes.

---

### 👥 Authors
* **Abdullo Kamoliddinov** - Logic & UI Development
* **Aziz Daurov** - Graphics & Animations
