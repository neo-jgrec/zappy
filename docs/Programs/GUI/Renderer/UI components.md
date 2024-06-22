---
sidebar_position: 1
---

UI components are things you can put in a scene to make them interactive they come in three types:
- Buttons
- Input Fields
- Chat display

:::warning
If you want to uses theses component make sure to use a shared pointer.
:::

## Buttons

Buttons have a really simple logic, first you build them using their constructor, then you call their update member to know if they are pressed or not.

They have 4 parameters:
1. position
```cpp
sf::Vector2f pos
```
2. Police Size
```cpp
sf::Vector2f size
```
3. Text content
```cpp
std::string text
```
4. Font
```cpp
sf::Font &font
```

The update function of a button return `true` if the button is released and `false` otherwise. It also set the internal state of the button to have an effect on hover.

## Inputs Fields

Inputs Fields have 3 parameters that influence the style:
- Position
- Police Size
- Font

And 2 more parameters for the input in itself

1. placeholder text, displayed when input is empty 
```cpp
std::string _placeHolder
```
2. accepted characters, characters that can be used in the input field (all alphabet letters and digit by default)
```cpp
std::string _accept
```

Input fields also have a gestion of internal state to know when they are hovered or focused on.

The way you get the information differ from the button as the update member only return false.

Instead there is a setter and getter pair for the input:
```cpp
void setInput(std::string input)
std::string getInput()
```

## Chat display

Chat display is not a component a user can interact with, it's used as a text display.

If you know about the *Minecraft* chat, then you know what this one look likes.

The only customisable parameters are the `Font`, the `max` number of message displayed and the `color` of the text.

The text always have a size of `17`.

To add a message to the chat simply use the
add Message funtion:
```cpp
void addMessage(std::string msg, sf::Color color)
``` 
By default the color of the text is white.
