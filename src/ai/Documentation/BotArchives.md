# Archives of bot code

**canLvlUp**
```cpp
bool Bot::canLvlUp(int lvl)
{
    if (lvl < 2 || lvl > 8)
        return false;

    const auto requirements = levelRequirements[lvl];

    bool hasRequiredResources =
        state.ressources.linemate >= requirements[0] &&
        state.ressources.deraumere >= requirements[1] &&
        state.ressources.sibur >= requirements[2] &&
        state.ressources.mendiane >= requirements[3] &&
        state.ressources.phiras >= requirements[4] &&
        state.ressources.thystame >= requirements[5];

    if (hasRequiredResources)
    {
        return true;
    }
    return false;
}
```