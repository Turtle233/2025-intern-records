# Internship Project Overview

This repository documents two major projects I contributed to during my internships.  
My work focused on Qt-based UI development, cross-platform interface design, custom window systems, data visualization, coordinate system design, and modular engineering practices.

---

# Internship Record 1

## Cross-Department Digital Collaboration Tool Development

### Team Size & Roles

A 10-member team consisting of:

- Project Manager
- Architect
- 2 QA/Test Engineers
- 3 Software Engineers
- Quality Manager
- Market Manager

**Goal:** Build a unified collaboration platform with centralized server support to reduce communication cost, enhance cross-department workflows, and integrate multi-user editing tools.

---

## My Responsibilities

### UI & Layout Development

- Developed the **“Create New Project”** dialog using Qt QDialog
- Designed dynamic layouts using QGridLayout, QHBoxLayout, and QVBoxLayout
- Implemented interactions between QListWidget and QLineEdit
- Added item creation/removal and context menu features
- Applied custom interface styling through `.qss` themes

### Interaction & Event Processing

- Implemented communication via Qt’s signal–slot mechanism
- Applied lambda expressions to simplify callback logic
- Designed a custom frameless window supporting drag, resize, maximize/restore
- Implemented custom mouse event handling for interactive features
- Used vector operations to compute coordinate offsets between window states

### Memory & Undo Mechanism

- Managed memory using Qt smart pointers
- Implemented a global undo feature using a stack-based operation log

---

## Tech Stack

- **Language:** C++
- **Framework:** Qt (QDialog, QWidget, QLayout, QSS, QLinguist)
- **Components:** QLabel, QPushButton, QListWidget, QMenu, QAction, QFile, QString

---

## Skills Gained

- Advanced Qt UI design and event handling
- Cross-platform interface design and implementation
- C++ memory management (heap and stack)
- Collaboration within multi-department teams
- Understanding of software engineering workflow and configuration management

---

## Key Technical Highlights

- Resolved Chinese character encoding issues by integrating the Qt Linguist translation workflow (`.ts` → `.qm`).
- Implemented stable drag/resize behavior for a cross-platform custom frameless window.

---
## Limitations & Future Improvements

The UI construction in this dialog is currently implemented as inline, hand-written layouts, resulting in repeated setup logic across the three user-role sections. A future improvement would be to refactor these blocks into a reusable component or a small custom widget to reduce duplication and improve maintainability.


---

## Achievements

- Delivered multiple UI modules integrated successfully into the production environment
- Built a fully functional custom window framework
- Improved multi-user editing experience with consistent UI and smooth interactions


