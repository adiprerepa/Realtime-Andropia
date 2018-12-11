# RealTimeNetworkingGame


Overview : 
  This project's purpose is to make a real time game where two players (beta) can play a game together 
  on a 2 dimensional map. The connections are established through UDP connections. We discovered UDP was faster than TCP, and
  will add more safety to the protocol later. The map is stored as a set of objects with rectangles postitions on the c++ server 
  file, and whenever a client presses the W, A, S, or D keys, it modifies the x and y coordinates which modify the positions of 
  the rectangle, in the c++ server program. The updated positions are then sent back to the two  clients, where the rectangles are 
  rendered by the c++ client program. The updates are happening on the server at around 60 FPS, and the clients update their screens 
  at 60 FPS. 
  
  As of now, the clients only work on Windows with Winsock 2, and use a c++ game engine Cross platform clients will come soon after the 
  engine is replace with nice code. Clients use the C version of SDL. Only certain networks can access our server, so a GUI embedded 
  in SDL to choose port/IP of server will also be added. We currently have one AWS server (more to come in the future!)
  
  The game is currently in a very early version in which players control a rectangle with the WSAD keys. 
    
Things to add : 
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
     
Aditya Prerepa (AWS java networking APIs to pair with c++ & server code functionality) 
Akshay Trivedi (c++ game engine and client functionality) 
12-8-18
