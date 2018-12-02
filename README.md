# RealTimeNetworkingGame


Overview : 
  This project's purpose is to make a real time game where 2 players (beta) can play at the same time on a 2 dimensional
  map. The connections are established through UDP connections, where the server does not need to send a confirmation
  packet, and thus, the connections are faster. The map is stored as a set of rectangle postitions on the server, and 
  whenever a client presses the W, A, S, or D keys, it modifies the x and y coordinates which modifies the positions
  of the rectangle, as shown in SendAndRecieve.java. The updated positions are then sent back to the 2 clients, where the
  positions are rendered by some c++ code and translated into a map. This is happening at 60 fps. There are resources and 
  weapons as well, which will be determined after the beta release.
  
Things to add : 
      - Fix lag problem? Sending from one place to another takes time.
      - Add shop functionality?
      - Complete rendering of map.
     
Aditya Prerepa 12-2-18
