# RealTimeNetworkingGame


Overview : 
  This project's purpose is to make a real time game where 2 players (beta) can play a game (designed by Akshay) together 
  on a 2 dimensional map. The connections are established through UDP connections, where the server does not need to send a 
  confirmation packet, and thus, the connections are simpler (and maybe faster). The map is stored as a set of rectangle 
  postitions on the server, and whenever a client presses the W, A, S, or D keys, it modifies the x and y coordinates which 
  modifies the positions of the rectangle, as shown in SendAndRecieve.java. The updated positions are then sent back to the 2 
  clients, where the positions are rendered by some c++ code and translated into a map. The updates are happening at around 60 
  fps. We plan to add resources and weapons as well.
  
  As of now, the clients only work on Windows with Winsock 2, and use Akshay's game engine that is used for all of his games, 
  so it is a lot bigger than it should be. Cross platform clients will come after the engine is replace with nice code. Clients 
  use the C version of SDL. Only certain networks can access our server, so a GUI embedded in SDL to choose port/IP of server 
  will also be added.
  
Things to add : 
      - Fix lag problem? Sending from one place to another takes time.
      - Add shop functionality?
      - Complete rendering of map.
      - Cross platform clients
      - Smaller clients
      - Map loading
      - Weapons
      - Damage & player data
      - HUDs
      - Word rendering (red damage thingies at points of impact, green healy things maybe later)
      - The "fun"ctionality of the game (objective points, scoring points)
      - Many other things
      - Verification packets sent every n seconds to determine connection status 
          (when a player disconnects, server does not receive packets)
     
Aditya Prerepa 12-2-18
