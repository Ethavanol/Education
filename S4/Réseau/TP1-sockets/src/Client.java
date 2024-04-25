import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

public class Client {

    private DatagramSocket socketClient;
    private DatagramPacket packet;
    private byte[] buffer;
    private String message;
    private InetAddress ipAdressDestination;
    private int portDestination;

    public static void main(String[] args) {
        try {
//            System.out.println("Client, saisissez votre message : ");
//            Scanner sc = new Scanner(System.in);
//            String message = sc.nextLine();
            Date actualDate = new Date();
            String message = actualDate.getHours() + ":" + actualDate.getMinutes() + ":" + actualDate.getSeconds() + " ";
            byte[] buffer = message.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, InetAddress.getByName("127.0.0.1"), 5356);
            DatagramSocket socketServer = new DatagramSocket();

            socketServer.send(packet);
            byte[] bufferToReceive = new byte[1024];
            packet = new DatagramPacket(bufferToReceive, bufferToReceive.length);
            socketServer.receive(packet);
            Date dateReception = new Date();
            System.out.println("All hours : " + new String(packet.getData()) + ", " + dateReception.getHours() + ":" + dateReception.getMinutes() + ":" + dateReception.getSeconds());
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
