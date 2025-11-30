# 2025-intern

# Internship Project Overview

This repository documents two major projects I contributed to during my internships.  
My work focused on Qt-based UI development, cross-platform interface design, custom window systems, data visualization, coordinate system design, and modular engineering practices.

Note: Due to company policy, certain parts of the original project code cannot be made public.  
This repository contains my own implementations and representative components that I am allowed to disclose.

---

# Internship Record 1

## Cross-Department Digital Collaboration Tool Backend Integration

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

---

# Internship Record 2

## Meteorological Data Visualization Software Development

### Note

The system requires an input CSV containing wind profile data. A small example dataset is included in `/data/test_ds.csv` for demonstration purposes.

---

### Team Size & Roles

A 15-member team consisting of:

- Project Manager
- Architect
- Meteorological Data Analyst
- 2 QA/Test Engineers
- 5 Software Engineers
- Quality Manager
- 4 Market Managers

**Goal:** Develop a high-precision visualization system for atmospheric wind data varying over time and altitude, improving interpretability and analytical efficiency.

---

## My Responsibilities

### Wind Indicator Rendering

- Implemented wind-barb rendering based on:
  - Horizontal wind direction
  - Vertical wind direction
  - Horizontal and vertical speeds
- Generated 14 levels of wind-barb icons (PNG/BMP formats)
- Designed directional legends (N/E/S/W)

### Main Visualization View

- Designed a grid-based **time × height** visualization
- Enabled click-to-preview interactions for individual data cells
- Rendered axes, legends, gridlines, and text using QPainter
- Applied color-coded indicators based on wind direction and speed

### Data Handling

- Encapsulated data using QVector and custom struct types
- Loaded and parsed CSV files using QFile and QTextStream
- Ensured accurate alignment between raw data and visualized cells

### Coordinate System & Precision

- Redesigned the coordinate system for high-altitude accuracy
- Fixed precision loss caused by integer division by switching to floating-point operations
- Applied vector-based coordinate computation for improved drawing accuracy

### Interaction & Redraw

- Implemented interactive selection using update()/repaint() workflow
- Modularized graphical logic (e.g., `draw_wind_indicator`) for reusability

---

## Tech Stack

- **Language:** C++
- **Qt Tools:** QWidget, QPainter, QColor, QThread, QPolygon, QMouseEvent
- **Data Tools:** QVector, QFile, QTextStream, QStringList, QDateTime

---

## Skills Gained

- Advanced proficiency in Qt graphics rendering and layout engineering
- Practical understanding of meteorological data visualization
- Strong awareness of modularization and code decoupling
- Precision handling of CSV file I/O and text parsing
- Effective debugging of coordinate geometry and pixel-level rendering issues
- Improved communication skills within a multidisciplinary team

---

## Key Technical Challenges


### Precision Loss in Height Mapping

**Solution:** Replaced integer division with floating-point operations and redesigned the coordinate system.

### Inaccurate Click Detection

**Solution:** Implemented tolerance-based matching using absolute value comparisons.

### Wind-Barb Image Alignment

**Solution:** Avoided forced scaling; centered images within each grid cell to maintain clarity and prevent distortion.

---

## Limitations & Future Improvements
The project works functionally, but the rendering pipeline is lacking modularity, layering, and separation of concerns. For example, the wind-flag drawing module (`wind_graphs`) is functional but not yet fully structured. The current implementation still relies on multiple level-specific functions with duplicated drawing logic, and the overall process has not been refactored into a unified or data-driven workflow. In future updates, the rendering pipeline can be redesigned to improve code reuse, and reduce duplication.

---

## Achievements

- Developed a fully interactive meteorological data visualization module
- Resolved multiple precision, coordinate, and rendering challenges
- Achieved efficient integration of large datasets with dynamic graphics
- Significantly enhanced atmospheric data interpretation through visual analytics
