import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;


public class UDPconn {
    static DatagramSocket serverSocket;

    static DatagramPacket sendPacket;
    static DatagramPacket initPacket1;
    static DatagramPacket initPacket2;
    static DatagramPacket recvPacket;
    static Thread thread;
    public static class recvThread extends Thread {

        @Override
        public void run() {
            while (true) {
                try {
                    serverSocket.receive(recvPacket);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                byte[] data = recvPacket.getData();

                System.out.println(recvPacket.getAddress().getHostAddress() + " " + recvPacket.getPort() + " : " + data.toString());
            }

        }

    }

    public static void init() throws Exception{
        initializeConnection();
        thread = new recvThread();
        thread.start();


    }


    public static void sendTo(int playerNumber, byte[] data) {
        if (playerNumber == 1) {
            sendPacket = new DatagramPacket(data, data.length, initPacket1.getAddress(), initPacket1.getPort());
        }
        if (playerNumber == 2)
        {
            sendPacket = new DatagramPacket(data, data.length, initPacket2.getAddress(), initPacket2.getPort());
        }
        try {
            serverSocket.send(sendPacket);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void initializeConnection() throws Exception {

        byte[] recieveData1 = new byte[1024];
        byte[] recieveData2 = new byte[1024];
        initPacket1 = new DatagramPacket(recieveData1,recieveData1.length);
        initPacket2 = new DatagramPacket(recieveData2, recieveData2.length);
        serverSocket = new DatagramSocket(55555);
        boolean b  = true;
        System.out.println("Waiting for connections...");
        serverSocket.receive(initPacket1);

        System.out.println(initPacket1.getAddress().getHostAddress() + " " + initPacket1.getPort());

        serverSocket.receive(initPacket2);
        while (initPacket2.getAddress().getHostAddress().equals(initPacket1.getAddress().getHostAddress()) && (initPacket2.getPort() == initPacket2.getPort())) {
            serverSocket.receive(initPacket2);
        }

        System.out.println(initPacket2.getAddress().getHostAddress() + " "  + initPacket2.getPort());
    }
}
