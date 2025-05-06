# logistics

This C++ project provides a command-line interface (CLI) for managing a logistics warehouse. It's structured into several modules: Inventory, Maintenance, Reports, Shipments, and Space Management.

Key Features:

Modular Design: The project is organized into classes representing different entities (Inventory, Maintenance, Report, Shipment, Space) and their corresponding managers or repositories. This promotes code organization and separation of concerns.
Inventory Management: Allows users to add new inventory items (name, category, quantity, location), view all inventory, search for items by ID, edit existing item details, and delete items.
Maintenance Management: Enables scheduling maintenance tasks for equipment (description, scheduled date, completion status), viewing all schedules, viewing details of a specific schedule, updating schedule information, and removing maintenance schedules.
Report Management: Provides functionality to generate basic reports (type, details, generation date), view all generated reports, and "download" (display) a specific report by ID.
Shipment Management: Supports receiving new shipments (item ID, origin, destination, status, expected delivery), viewing all shipments, tracking a shipment by ID, dispatching shipments (updating details), and removing shipment records.
Space Management: Allows allocation of warehouse space (total capacity, used capacity, zone), viewing current space usage, searching for space by ID, updating space details, and freeing up allocated space.
CLI Interface: Users interact with the application through a text-based menu system. They can navigate between the main modules and perform actions within each module by entering numerical choices.
In-Memory Data Storage: All data (inventory items, maintenance schedules, reports, shipments, and space information) is currently stored in std::vectors within the respective manager/repository classes. This means that when the application is closed, all the data is lost.
Basic Input Validation: The application includes basic checks for invalid numerical input to prevent crashes.
Date and Time Handling: Uses std::time_t and related functions to record timestamps for inventory updates, maintenance schedules, and reports, with basic formatting for display.
In essence, this project is a functional simulation of a logistics warehouse management system accessible through the command line. It allows users to perform core operations on different aspects of the warehouse. However, its primary limitation is the lack of persistent data storage. To retain data between application sessions, it would need to be integrated with a backend database or file storage mechanism.

