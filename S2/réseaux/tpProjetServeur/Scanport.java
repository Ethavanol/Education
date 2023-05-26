import java.net.*;


public class Scanport {

    public static void scanPorts(int startPort, int endPort) {
        for (int port = startPort; port <= endPort; port++) {
            try {
                DatagramSocket socket = new DatagramSocket(port);
                socket.close();
                System.out.println("Port " + port + " est ouvert");
            } catch (SocketException e) {
                System.out.println("Port " + port + " est fermé");
            }
        }
    }

    public static void main(String[] args) {
        try {
            DatagramSocket socket = new DatagramSocket(51);
            DatagramSocket d2 = new DatagramSocket(63);

            scanPorts(1, 100);
        } catch (SocketException e) {
            System.out.println("Port 51 est fermé");


        }


    }
}