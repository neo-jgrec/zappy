/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Switch
*/

#ifndef SWITCH_HPP_
#define SWITCH_HPP_

template <typename T>
class Switch {
    public:
        Switch(T value) : _value(value) {}
        ~Switch() {}

        Switch &operator=(const T &newValue) {
            _newValue = newValue;
            return *this;
        }

        bool hasChanged(void) {
            if (_value != _newValue) {
                _value = _newValue;
                return true;
            }
            return false;
        }

        T _value;
    protected:
    private:
        T _newValue;

};

#endif /* !SWITCH_HPP_ */
