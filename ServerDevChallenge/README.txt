ServerDev Challenge Project

The object of this exercise is to develop a playable Bingo Game that consist in two applications that communicate with each other: a Client and a Server.
The Bingo Game rules are:
- A 10 number card (numbers should randomized between 1 and 50 without duplicates) to be "filled" with the draw ball numbers
- A ball numbers draw until a card is filled: BINGO!

The Server rules are:
- Listen to connections on startup
- Once a client connects send back a "Connected" event
- Generate and send a 10 number card on every "Game" request from the client
- Start the ball numbers draw only after acknowledging the client received the card numbers
- The ball numbers draw must individually send each number with a 1 second interval between each one and only after each connected client acknowledges that the number was received, until the "Won" event is received

The Client rules are:
- Send a "Game" request after receiving a "Connected" event from the Server.
- Send an acknowledge message when the card is received.
- Warn if each number drawn is in the card and how many numbers are still missing.
- Send a "Won" message to the Server once the card is completed.

Extra points:
- Code with comments to understand the implementation
- It should be possible to disconnect a Client. In this case the server should wait for the client to reconnect send the same card to the game and any already drawn numbers so that the game can resume from the same place.
- The server should allow multiple clients to connect, however there should only be one winner

---------------------------------------------------------------------------------------------------------------------------------------------------

This code should serve as a base for you to do the exercise and to test your knowledge.
The code given is correct and compiles. Also the required code for creating sockets and connecting the server and client is already done.
However, there is still something missing in order to run the server, that part is up to you. ;)
After that your job will be to implement the functionality of the Client and Server as described in the exercise given to you.

Deliverables:
- Source Code
- Binary and dependencies such as assets or libs (if any) and it's mandatory that the project executes in Linux with just the provided binary

Initial considerations:

    -> Base project was developed and tested using Ubuntu.
    -> Project folder contains two subfolders, corresponding to both Server's and Client's application.
    -> Each application folder contains respective header and source files. The rest of the project structure is up to you.

Execution instructions:
	Compile the server with g++ -o main.out main.cpp SourceFiles/ServerInterface.cpp
	Compile the client with g++ -o main.out main.cpp SourceFiles/Client.cpp
	Run using ./main.out