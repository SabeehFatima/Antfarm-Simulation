# Antfarm Simulation Project

## Description
This project simulates an ant farm, where various species of ants are spawned, interact, and perform tasks like gathering resources and fighting each other. The project uses object-oriented programming principles in C++ to simulate the behavior of different species in the colony.

## How the Code Works
- The program uses classes to represent `Colony`, `ColonyFactory`, and `AntFarm`.
- The `Colony` class defines the properties of a colony (species, resources, warriors, workers, etc.) and includes methods to give resources, fight other colonies, and print the colony's status.
- The `ColonyFactory` class is used to create new colonies.
- The `AntFarm` class acts as a singleton that manages all colonies, spawning new colonies, giving resources, and handling fights between colonies.
- Commands such as spawning colonies, listing colonies, giving resources, and initiating fights are executed using the `Command` design pattern.

## Design Patterns Used

### 1. **Singleton Pattern: `AntFarm`**
   - **Purpose**: The Singleton pattern ensures that only one instance of the `AntFarm` class exists throughout the simulation. This guarantees that all operations are performed within a single context and avoids conflicts between multiple instances of the farm.
   - **How It Was Used**: The `AntFarm` class is designed as a Singleton, providing a single point of control for spawning and managing colonies, as well as handling the state of the simulation.

### 2. **Factory Pattern: `ColonyFactory`**
   - **Purpose**: The Factory pattern allows the dynamic creation of new colonies without modifying existing code. It abstracts the colony creation process, making it easier to introduce new types of colonies in the future.
   - **How It Was Used**: The `ColonyFactory` class is responsible for creating new colonies based on the species and coordinates provided. This pattern helps separate the logic of colony creation from other parts of the program.

### 3. **Command Pattern: `Command`, `SpawnCommand`, `GiveCommand`, `ListCommand`, `FightCommand`**
   - **Purpose**: The Command pattern encapsulates requests as objects. This provides flexibility in handling commands and decouples the request from the actual execution.
   - **How It Was Used**: Different operations in the simulation, such as spawning colonies, giving resources, listing colonies, and initiating fights, are implemented as command objects. Each command class implements the `execute()` method, allowing easy invocation of actions without directly coupling them to user input or the main program flow.

### 4. **Strategy Pattern (Potential Future Implementation)**
   - **Purpose**: The Strategy pattern could be implemented in the future to allow colonies to choose different strategies for resource gathering, fighting, or interacting with other colonies based on environmental conditions.
   - **How It Could Be Used**: A strategy interface could be created with methods like `gatherResources()`, `fight()`, and `defend()`, and each colony could use different strategy classes to determine how to perform these tasks. This would make the code more flexible and allow for easier adjustments in the behavior of colonies.

### 5. **Observer Pattern (Potential Future Implementation)**
   - **Purpose**: The Observer pattern could be used to notify different components of the simulation whenever a colony's state changes (e.g., resources, warriors, or status).
   - **How It Could Be Used**: A colony might act as the "subject" and notify other objects, such as a display system or resource manager, when there is a change in its state. This would allow different parts of the system to respond in real-time to changes, such as when a colony gathers enough resources or wins a fight.

## Outputs
The console output of the simulation has been attached for convenience.

## How to Run
1. Clone the repository: `git clone https://github.com/your-username/ant-simulation.git`
2. Open the project in a C++ IDE or text editor (I have used CodeBlock).
3. Compile and run the `main.cpp` file.
4. Follow the on-screen prompts to interact with the ant colonies.
