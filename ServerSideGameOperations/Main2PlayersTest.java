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
    public static InetAddress IPAddrPlayer1;
    public static Integer portNumberPlayer1;
    public static String sendDataNotBytes;
    public static DatagramPacket sendPacketPlayer1;
    public static DatagramPacket sendPacketPlayer2;
    public static InetAddress IPAddrPlayer2;
    public static Integer portNumberPlayer2;
    public static DatagramPacket recievePacketPlayer1;
    public static DatagramPacket recievePacketPlayer2;

    public static void main(String[] args) throws Exception {

        //UDPconn.initializeConnection();

        // Numbers for coordinate postion of player //

        int xPlayer1 = 100;
        int yPlayer1 = 400;
        int xPlayer2 = 100; //Ask Akshay and change
        int yPlayer2 = 400;
        DatagramPacket recievePacket;
        byte[] sendData = new byte[256];
        byte[] recieveData = new byte[1024];
        prev = System.currentTimeMillis();

        System.out.println("Waiting for Keypresses...");
        DatagramSocket serverSocket = new DatagramSocket(55555);
        Thread myThread = new CreateThread(serverSocket);

        recievePacket = new DatagramPacket(recieveData, recieveData.length);
        serverSocket.receive(recievePacket);
        IPAddrPlayer1 = recievePacket.getAddress();

        portNumberPlayer1 = recievePacket.getPort();


        sendPacketPlayer1 = new DatagramPacket(sendData, sendData.length, IPAddrPlayer1, portNumberPlayer1);
        System.out.println("Connection 1 from " + IPAddrPlayer1.getHostAddress() + ". Port is " + portNumberPlayer1 + ". ");

        do {
            serverSocket.receive(sendPacketPlayer2);

        } while (sendPacketPlayer2.getAddress().getHostAddress().equals(sendPacketPlayer2.getAddress().getHostAddress()) && (sendPacketPlayer2.getPort() == sendPacketPlayer2.getPort()));

        IPAddrPlayer2 = sendPacketPlayer2.getAddress();
        portNumberPlayer2 = sendPacketPlayer2.getPort();

        System.out.println("sending " + sendDataNotBytes);
        myThread.start();
        //heart of code, this is what runs.
        while(true) {

            //check status on if key a was pressed.
            //decrement the x coordinate
            if (((CreateThread) myThread).aStatusPlayer1) {
                xPlayer1--;
            }
            //check status on if key w was pressed,
            //decrement the y coordinate
            if (((CreateThread) myThread).wStatusPlayer1) {
                yPlayer1--;
            }
            //check status on if key s was pressed,
            //increment y coordinate
            if (((CreateThread) myThread).sStatusPlayer1) {
                yPlayer1++;
            }
            //check status on if key d was pressed,
            //increment x coordinate.
            if (((CreateThread) myThread).dStatusPlayer1) {
                xPlayer1++;
            }
            if (((CreateThread) myThread).aStatusPlayer2) {
                xPlayer2--;
            }
            //check status on if key w was pressed,
            //decrement the y coordinate
            if (((CreateThread) myThread).wStatusPlayer2) {
                yPlayer2--;
            }
            //check status on if key s was pressed,
            //increment y coordinate
            if (((CreateThread) myThread).sStatusPlayer2) {
                yPlayer2++;
            }
            //check status on if key d was pressed,
            //increment x coordinate.
            if (((CreateThread) myThread).dStatusPlayer2) {
                xPlayer2++;
            }

            String sendDataNotBytes = "0 0 " +  xPlayer1 + " " + yPlayer1 + " 128 128 2" + " 0 0 " + xPlayer2 + " " + yPlayer2 + " 128 128 2";
            sendData = sendDataNotBytes.getBytes();
            sendPacketPlayer1 = new DatagramPacket(sendData, sendData.length, IPAddrPlayer1, portNumberPlayer1);
            sendPacketPlayer2 = new DatagramPacket(sendData, sendData.length, IPAddrPlayer2, portNumberPlayer2);
            System.out.println("sending " + sendDataNotBytes);


            try {
                serverSocket.send(sendPacketPlayer1);
                serverSocket.send(sendPacketPlayer2);

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
        byte[] recieveDataPlayer1 = new byte[1024];
        byte[] recieveDataPlayer2 = new byte[1024];

        String keyPressPlayer1;
        String keyPressPlayer2;
        public boolean wStatusPlayer1 = false;
        public boolean aStatusPlayer1 = false;
        public boolean sStatusPlayer1 = false;
        public boolean dStatusPlayer1 = false;
        public boolean wStatusPlayer2 = false;
        public boolean aStatusPlayer2 = false;
        public boolean sStatusPlayer2 = false;
        public boolean dStatusPlayer2 = false;
        //x and y were scope changes. Change back if error.
        int xPlayer1;
        int yPlayer1;
        
        int xPlayer2;
        int yPlayer2;
        DatagramSocket serverSocket;
        
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
                    recievePacketPlayer1 = new DatagramPacket(recieveDataPlayer1, recieveDataPlayer1.length, IPAddrPlayer1, portNumberPlayer1);
                    serverSocket.receive(recievePacketPlayer1);
                    // Gets data from the keypress from the recivepacket.

                    keyPressPlayer1 = new String(recievePacketPlayer1.getData(), 0, recievePacketPlayer1.getLength());
                    System.out.println("Recieved : " + keyPressPlayer1 + " from " + IPAddrPlayer1);
                    
                    recievePacketPlayer2 = new DatagramPacket(recieveDataPlayer2, recieveDataPlayer2.length, IPAddrPlayer2, portNumberPlayer2);
                    
                    serverSocket.receive(recievePacketPlayer2);
                    keyPressPlayer2 = new String(recievePacketPlayer2.getData(), 0, recievePacketPlayer2.getLength());
                    //All conditional statements.
                    if ((keyPressPlayer1.equals("wp") || (keyPressPlayer1.equals("wr")))) {
                        if (keyPressPlayer1.equals("wp")) {
                            wStatusPlayer1 = true;
                            yPlayer1--;
                        }
                        else {
                            wStatusPlayer1 = false;
                        }
                    }

                    if ((keyPressPlayer1.equals("ap") || (keyPressPlayer1.equals("ar")))) {
                        if (keyPressPlayer1.equals("ap")) {
                            aStatusPlayer1 = true;
                            xPlayer1--;
                        }
                        else {
                            aStatusPlayer1 = false;
                        }
                    }

                    if ((keyPressPlayer1.equals("sp") || (keyPressPlayer1.equals("sr")))) {
                        if (keyPressPlayer1.equals("sp")) {
                            sStatusPlayer1 = true;
                            yPlayer1++;
                        }
                        else {
                            sStatusPlayer1 = false;
                        }
                    }

                    if ((keyPressPlayer1.equals("dp") || (keyPressPlayer1.equals("dr")))) {
                        if (keyPressPlayer1.equals("dp")) {
                            dStatusPlayer1 = true;
                            xPlayer1++;
                        }
                        else {
                            dStatusPlayer1 = false;
                        }
                    }

                    if ((keyPressPlayer2.equals("wp") || (keyPressPlayer2.equals("wr")))) {
                        if (keyPressPlayer2.equals("wp")) {
                            wStatusPlayer2 = true;
                            yPlayer2--;
                        }
                        else {
                            wStatusPlayer2 = false;
                        }
                    }

                    if ((keyPressPlayer2.equals("ap") || (keyPressPlayer2.equals("ar")))) {
                        if (keyPressPlayer2.equals("ap")) {
                            aStatusPlayer2 = true;
                            xPlayer2--;
                        }
                        else {
                            aStatusPlayer2 = false;
                        }
                    }

                    if ((keyPressPlayer2.equals("sp") || (keyPressPlayer2.equals("sr")))) {
                        if (keyPressPlayer2.equals("sp")) {
                            sStatusPlayer2= true;
                            yPlayer2++;
                        }
                        else {
                            sStatusPlayer2 = false;
                        }
                    }

                    if ((keyPressPlayer2.equals("dp") || (keyPressPlayer2.equals("dr")))) {
                        if (keyPressPlayer2.equals("dp")) {
                            dStatusPlayer2 = true;
                            xPlayer2++;
                        }
                        else {
                            dStatusPlayer2 = false;
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
        }

    }
}
