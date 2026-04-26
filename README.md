# SFML Game Engine - Comprehensive Technical Manual

A high-performance, scene-based C++ game engine built on top of SFML 2.6.x. This engine is designed for complex 2D games requiring a robust hierarchical object system, stable state transitions through deferred processing, and an intuitive developer workflow.

---

## 1. Engine Philosophy & Overview

The SFML Game Engine is built on the principle of **stability through separation**. In many game engines, modifying the object hierarchy (deleting or reparenting) during a frame update can lead to iterator invalidation or "use-after-free" crashes. This engine solves that by using a **Deferred State Management** system: structural changes are requested during the frame but only executed at safe transition points.

### Core Pillars:

- **True Hierarchy:** Parent-child relationships propagate transforms, visibility, and active states mathematically.
- **Layer-Based Spatiality:** A simple integer-based layering system handles draw order automatically.
- **Opt-in Events:** Objects only pay for the events they choose to listen to.
- **Scene-Driven Architecture:** Entire game states (Main Menu, Level 1, etc.) are encapsulated into self-contained scenes.

---

## 2. Architecture Deep-Dive

### 2.1 The Core Components

The engine follows a strict delegatory chain:

1.  **`Game` (Orchestrator)**: Owns the `sf::RenderWindow` and the global `TimeManager`. It initiates every frame and tells the `SceneManager` what to do.
2.  **`SceneManager` (The Interface)**: This is your primary point of contact. It acts as a gateway to the currently active `Scene`. It provides methods to change scenes and manipulate objects safely.
3.  **`Scene` (The Container)**: The "Source of Truth." It maintains the internal maps of layers, the event subscriber lists, and the queues for deferred operations.
4.  **`Object` (The Entity)**: The base class for all game elements. It handles the recursive logic for updates and drawing.

### 2.2 The Frame Lifecycle

Every frame in `Game::Run()` executes in a precise order to guarantee that no object is modified while it is being iterated over:

1.  **Scene Initialization (`SetActiveScene`)**: If a scene change was requested, the engine wipes the old scene and instantiates the new one.
2.  **Deferred Structural Changes**:
    - **`MoveObjects`**: Objects are moved between rendering layers.
    - **`ChangeParents`**: Relationships are updated. Circular checks are performed here.
    - **`DeleteObjects`**: Memory is safely freed for objects marked for removal.
3.  **Event Dispatching (`OnEvent`)**: SFML events are polled and sent directly to objects that have subscribed to them.
4.  **Logic Update (`Update`)**: The update pass runs recursively through the hierarchy. Global transforms are recalculated here.
5.  **Rendering (`Draw`)**: Objects are drawn layer-by-layer, from bottom to top.

---

## 3. Core Systems & Mathematics

### 3.1 Transform Mathematics (Basis Vectors)

The engine doesn't just "add" offsets; it uses basis-vector math to ensure that child objects "orbit" parents correctly.

- **The Right/Up Vectors**: Based on a parent's rotation, the engine calculates its local coordinate axes.
- **Global Calculation**: `GlobalPos = ParentPos + (LocalX * ParentRight * ParentScaleX) + (LocalY * ParentUp * ParentScaleY)`.
- **Result**: If you rotate a car, the steering wheel child-object stays inside the car and rotates with it perfectly.

### 3.2 The Event System

Objects override `GetEventsToSubscribe()` to return a list of `sf::Event::EventType`.

- **Efficiency**: The `Scene` only iterates over objects that care about a specific event.
- **Hierarchical Respect**: If a parent is `inactive`, its children will **not** receive events, even if the children themselves are marked as active.

---

## 4. Class Reference

### 4.1 `Object` Class (Base)

The root of all entities.

- **`position`, `rotation`, `scale`**: These are **Local** values relative to the parent.
- **`globalPosition`, `globalRotation`, `globalScale`**: These are recalculated every frame. Use these for distance checks or collision logic.
- **`active`**: Toggles whether `Update()` and `OnEvent()` run.
- **`visible`**: Toggles whether `Draw()` runs.
- **`Move(direction, speed, dt)`**: Moves the object. Now requires `dt` (Delta Time) to ensure framerate independence.
- **`Rotate(angle, speed, dt)`**: Rotates the object. Now requires `dt`.
- **`GetChildrenToAdd()`**: Override this to return a list of children that should be automatically registered when the parent is added to a scene.
- **`Update()`**: **CRITICAL**: Always call `BaseClass::Update()` (e.g., `RectangleObject::Update()`) at the end of your override to ensure children update.

### 4.2 `SceneManager` Class

- **`AddObject(Object*)`**: Registers an object to the current scene.
- **`RemoveObject(Object*)`**: Marks for safe deletion. **Do not use `delete`**.
- **`SetObjectParent(parent, child)`**: Handles reparenting. Passing `nullptr` as parent makes the object a root object.
- **`SetObjectLayer(int, Object*)`**: Changes the render depth. Children follow their parent's layer.

### 4.3 `TimeManager` Class

- **`GetDT()`**: Returns Delta Time (seconds since last frame). Use this to ensure movement is consistent across different CPUs (e.g., `pos += velocity * GetDT()`).

### 4.4 `Object` Class (The Foundation)

The base class for all game entities.

- **`position`, `rotation`, `scale`**: Local transform values relative to the parent.
- **`globalPosition`, `globalRotation`, `globalScale`**: Calculated world coordinates.
- **`active` / `visible`**: Toggles whether an object updates or draws.
- **`Update()`**: **CRITICAL**: Always call `BaseClass::Update()` at the end of your override to ensure transform propagation.

---

## 5. Developer Guide: How to Use the Engine

### 5.1 Creating a Custom Object

Inherit from a specialized class like `RectangleObject` or `SpriteObject`.

```cpp
class MyPlayer : public RectangleObject {
public:
    MyPlayer() : RectangleObject("Player", 1) { // Name: "Player", Layer: 1

        // Use this->rectangle to change how the object looks
        this->rectangle.setSize({50, 50});
        this->rectangle.setFillColor(sf::Color::Blue);
    }

    // Subscribe only to the events you want
    const std::vector<sf::Event::EventType> GetEventsToSubscribe() override {
        return { sf::Event::KeyPressed };
    }

    // React to the events that you have subscribed to
    // If you try to react to an event tye that isn't returned by GetEventsToSubscribe() than nothing will happen
    void OnEvent(sf::Event event) override {
        if (event.key.code == sf::Keyboard::Space) Jump();
    }

    // Add the logic for this object (This will be called every frame)
    void Update() override {
        // Move 100 pixels per second to the right
        this->Move({1, 0}, 100, game.time.GetDT());
        this->RectangleObject::Update(); // Crucial!
    }
};
```

### 5.2 Setting Up a Scene

Use `SceneBuilder` to define a scene's properties and initial objects.

```cpp
SceneBuilder mainScene("MainLevel", //Name
    {1920, 1080}, // Camera Size
    {960, 540}, // Camera center
    [](){ // lambda function to return the objects initially added to the scene
    std::vector<Object*> objs;
    objs.push_back(new MyPlayer());
    return objs;
});
```

### 5.3 Running the Engine

Initialize the `Game` object and trigger the first scene.

```cpp
#include "Game/Game.h"

// Global or accessible pointer to game
Game game(sf::VideoMode(1920, 1080), "My SFML Game");

int main() {
    game.sceneManager.ChangeScene(mainScene);
    game.Run();
    return 0;
}
```

### 5.4 Handling Mouse Input with Camera

When the camera moves, use this formula to get world-space mouse coordinates:

```cpp
sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(game.GetWindow()));
mousePos += game.sceneManager.GetCamera().getCenter();
mousePos -= game.sceneManager.GetCamera().getSize() / 2.f;
```

---

## 6. Best Practices: Do's and Don'ts

### ✅ DO:

- **Call Base Updates**: Always call `this->BaseClass::Update()` at the end of your `Update` override.
- **Use `RemoveObject`**: Trust the engine to clean up memory.
- **Use Delta Time**: Always multiply movement and rotation speeds by `game.time.GetDT()`.
- **Leverage Hierarchies**: If an object "belongs" to another (like a sword to a knight), make it a child.

### ❌ DON'T:

- **Don't `delete` Registered Objects**: This will cause the engine to crash when it tries to update the now-deleted memory.
- **Don't Change Hierarchy Directly**: Use `game.sceneManager.SetObjectParent` instead of modifying `children` vectors manually.
- **Avoid Manipulating objects outside of their class**: By calling `game.sceneManager.SetObjectLayer` or `~.SetObjectParent` or `~.RemoveObject` and passing a pointer to another object as an argument to those functions you can get unexpected behavior (if the object was deleted and another one was added at the same address). Define a function inside of the object's class and use that as a trigger
- **Don't Ignore Layers**: Keep your UI on high layers (e.g., Layer 10+) and background on Layer 0.
- **Don't perform heavy logic in `Draw()`**: Keep `Draw` for rendering only; use `Update` for calculations.

---

## 7. Build Instructions

The project uses **CMake**. Ensure you have SFML 2.6 installed.

1.  **Configure:** `cmake -B Build -S .`
2.  **Build:** `cmake --build Build`
3.  **Run:** `./Build/Release/TestGame(.exe)`
