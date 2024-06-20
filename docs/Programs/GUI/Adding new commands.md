Before anything let's define what a command is :\
A command is composed of a keyword followed by it's argument\
`smg 1 "message from the server"`\
here *smg* is the keyword of the function, *1* is the first argument and *"message from the server"* is the second argument.\

to add a new command to the gui you will need two main things.

## The handler
The handler is the first thing you will need to create in order to implement a new command.\
defined in the Parser.hpp file handlers are functions with a defined set of arguments they are defined as such :\
`void handler_name(const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server);`\
handlers usually have a 3 letter name as an abreaviation of their meaning, for example *pnw* for Player new (connection of a new player).\

after defining the hanlder you will have to add it the map of handlers, this operation is neccessary for the parser to recognize the keyword that will trigger the call of your function it is defined as such :\
`{"keyword", std::bind(&Parser::handler_name, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)}`\
with this the definition of your function is complete and it will be called whenever the Parser recieve the keyword.\

## The function
After defining your handler you will need to implement your actual function into the Parser.cpp file
all handler functions have the same initial structure :

```
void Parser::functionName (const std::vector<TokenType>& tokens, Data& gameData, ServerConnect &server) {
    checkType(tokens, std::vector<Type>(2, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData, server]() {
        // your implementation goes here
    };
    _queue.push(lambda);
};
```

The way this structure works is the following :
- your function is called by the parser.parse() function
- the type of all the arguments are checked by via the checkType function
- your function is added to the _queue to be executed later
- when the parser has finished parsing the current input all function in the queue are executed

so the first thing you want to look at here is the `checkType` function, its first and last argument `tokens` and `__func__` nevers changes. the second argument is what you want to modify it correspond to the number of arguments that your funtion takes along with all their types.\

you have two types at your disposition INT and STRING if you wish to use something else it would require futher modification of the Parser.\

here is two example to see how it works :\

1. function with 3 args of the same type (INT)
`heckType(tokens, std::vector<Type>(3, Parser::Type::INT), __func__);`\

2. function with 2 args of different types
`checkType(tokens, std::vector<Type>({Parser::Type::INT, Parser::Type::STRING}), __func__);`\


next is the lambda part of the function, this is where you will implement your function,
during your implementation you will surely need to get the arguments of your function at some point,
here is the sintax to use :\

1. for an int
`int arg = std::get<int>(tokens.at(n));`

2. for a string
`std::string arg = std::get<std::string>(tokens.at(n));`

with n being the index of the argument begining at 1 because 0 is the keyword to call the function.\

if you want to send a message to the server you can use the sendToServer member function of the server parametter.\

all modification to the gameData parametter must be done through a member function of the Data class.\


Lastly you want to look at the parametters you haven't used to mark them as unused and delete them from the array of parametters of the lambda function.\

for example if you didn't send a message to the server in your function :
```
void Parser::functionName (const std::vector<TokenType>& tokens, Data& gameData, [[maybe_unused]]ServerConnect &server) {
    checkType(tokens, std::vector<Type>(2, Parser::Type::INT), __func__);
    auto lambda = [tokens, &gameData]() {
        // your implementation goes here
    };
    _queue.push(lambda);
};
```

`[[maybe_unused]]` is added before `ServerConnect &server` in the function definition and `server` is removed from the array of params of the *lambda* definition.\

Now you should be all set to test your new function.

:::warning
Don't forget to add unit tests for it.
:::
