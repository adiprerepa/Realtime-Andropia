/*
 * (C) Aditya Prerepa 12-2-2018
 * Recieve and send info through UDP sockets
 */

import java.net.*;
public class Main {
    //All variables for the crapFrameRate() function//
    public static long prev;
    public static long now;
    public static long elapsed;
    //Test variables :
    public static InetAddress IPAddr;
    public static Integer portNumber;
    public static String sendDataNotBytes;
    public static DatagramPacket sendPacket;

    public static void main(String[] args) throws Exception {

        UDPconn.initializeConnection();

        // Numbers for coordinate postion of player //

        int x = 100;
        int y = 400;
        DatagramPacket recievePacket;
        byte[] sendData = new byte[256];
        byte[] recieveData = new byte[1024];
        prev = System.currentTimeMillis();

        System.out.println("Waiting for Keypresses...");
        DatagramSocket serverSocket = new DatagramSocket(55555);
        Thread myThread = new CreateThread(serverSocket);

        recievePacket = new DatagramPacket(recieveData, recieveData.length);
        serverSocket.receive(recievePacket);
        IPAddr = recievePacket.getAddress();

        portNumber = recievePacket.getPort();

        sendPacket = new DatagramPacket(sendData, sendData.length, IPAddr, portNumber);
        System.out.println("sending " + sendDataNotBytes);
        myThread.start();
        //heart of code, this is what runs.
        while(true) {

            //check status on if key a was pressed.
            //decrement the x coordinate
            if (((CreateThread) myThread).aStatus) {
                x--;
            }
            //check status on if key w was pressed,
            //decrement the y coordinate
            if (((CreateThread) myThread).wStatus) {
                y--;
            }
            //check status on if key s was pressed,
            //increment y coordinate
            if (((CreateThread) myThread).sStatus) {
                y++;
            }
            //check status on if key d was pressed,
            //increment x coordinate.
            if (((CreateThread) myThread).dStatus) {
                x++;
            }

            String sendDataNotBytes = "0 0 " +  x + " " + y + " 128 128 2";
            sendData = sendDataNotBytes.getBytes();
            sendPacket = new DatagramPacket(sendData, sendData.length, IPAddr, portNumber);
            System.out.println("sending " + sendDataNotBytes);


            try {
                serverSocket.send(sendPacket);

            } catch (Exception e) {

                e.printStackTrace();
            }


            //get info of data being sent. Recent fix, posssible bug here. If
            //bug, comment the next 3 lines and uncomment the same three lines
            //at the bottom.

            //Cap the framerate of the stuff being printed and processed on the screen.
            //The parameter is the fps.
            crapFrameRate(16);
        }
    }

    /*
     * Method in order to cap the framerate of the integers
     * being processed. Takes the time from above
     * and subtracts it from the time now in order
     * to get the elapsed time. Then sleeps the main thread
     * for the elapsed time. Essential to control screen updating.
     */

    private static void crapFrameRate(int millisPerFrame) throws Exception {
        now = System.currentTimeMillis();
        elapsed = millisPerFrame - (now - prev);
        if (elapsed > 0) {
            Thread.sleep(elapsed);
        }
        prev = now;
    }
    /*
     * Static class to create a clientThread object. The
     * Thread runs to update the booleans of W,A,S,D pressed.
     * Sends and recieves data from and the the client, through
     * a UDP connection. Also has an int x and y for testing. The
     * default all the booleans for the keys pressed are false.
     * Also has 2 byte arrays for sending and recieving data for
     * the index of 255 bytes.
     * VARIABLES____________________________
     * - byte array for sending and recieving data-indexes both 255.
     * - String for recieving the keys pressed.
     * - 4 booleans for the statuses of the keys pressed - recived from client.
     * - 2 integers for testing of coordinates.
     * - Class DataGramSocket that is passed through the constructor from the Main
     *   class with port 55555. Gets all data on that port through that socket.
     * - 2 Class Datagram objects for sending and reciveing packets. Recieve the
     *   recievePacket through the serverSocket. The packet has the message in the packet, the
     *   IP it was sent from, and the port it was RECIEVED on. SendPacket will send the
     *   packet to the IP and port that was provided on the recievedPacket.
     * - Global InetAddress and port variables to store the info that is recived on the recieved
     *   packet.
     */
    public static class CreateThread extends Thread {
        byte[] recieveData = new byte[1024];
        byte[] sendData = new byte[256];

        String keyPress;
        public boolean wStatus = false;
        public boolean aStatus = false;
        public boolean sStatus = false;
        public boolean dStatus = false;
        //x and y were scope changes. Change back if error.
        int x;
        int y;
        DatagramSocket serverSocket;
        DatagramPacket recievePacket;
        DatagramPacket sendPacket;


        /*
         * Constructor of the socket passed here and was made in the begininning,
         * had the issue of creating the serverSocket infinite times
         */

        public CreateThread(DatagramSocket serverSocket) {
            this.serverSocket = serverSocket;
        }

        /* Overrides the default run function in the Thread class itself. All the logic
         * of boolean changing happens here.
         */

        @Override
        public void run() {
            System.out.println("Thread running...");

            try {

                /*
                 * Heart of this class. In this while true loop, the socket recieves
                 * all the keypresses and updates the booleans, while incrementing/decrementing
                 * the coordinates and/or positions of the player. Once the connection is
                 * established, immediately grab the IP and the port it was recieved on. Also
                 * get make a recieved packet with the params as the byte array allocated
                 * for the data above.
                 */

                while (true) {
                    recievePacket = new DatagramPacket(recieveData, recieveData.length);
                    serverSocket.receive(recievePacket);
                    // Gets data from the keypress from the recivepacket.

                    keyPress = new String(recievePacket.getData(), 0, recievePacket.getLength());
                    System.out.println("Recieved : " + keyPress);
                    //All conditional statements.
                    if ((keyPress.equals("wp") || (keyPress.equals("wr")))) {
                        if (keyPress.equals("wp")) {
                            wStatus = true;
                            y--;
                        }
                        else {
                            wStatus = false;
                        }
                    }

                    if ((keyPress.equals("ap") || (keyPress.equals("ar")))) {
                        if (keyPress.equals("ap")) {
                            aStatus = true;
                            x--;
                        }
                        else {
                            aStatus = false;
                        }
                    }

                    if ((keyPress.equals("sp") || (keyPress.equals("sr")))) {
                        if (keyPress.equals("sp")) {
                            sStatus= true;
                            y++;
                        }
                        else {
                            sStatus = false;
                        }
                    }

                    if ((keyPress.equals("dp") || (keyPress.equals("dr")))) {
                        if (keyPress.equals("dp")) {
                            dStatus = true;
                            x++;
                        }
                        else {
                            dStatus = false;
                        }
                    }
                }
            }


            catch (Exception e) {
                e.printStackTrace();
            }


            /*
             * Data is sent back here using another DatagramPacket class, and is sent
             * back to the given IP and port. The data sent is the values of x and y, which
             * are incremented/decremented based on keypresses. The string is converted to bytes,
             * which is then sent using the send api.
             */

            //This was a scope test : change back if not working.

            String sendDataNotBytes = x + " " + y;
            sendData = sendDataNotBytes.getBytes();
            sendPacket = new DatagramPacket(sendData, sendData.length, IPAddr, portNumber);
            System.out.println("sending " + sendDataNotBytes);


            try {
                serverSocket.send(sendPacket);

            } catch (Exception e) {

                e.printStackTrace();
            }



        }

    }
}
