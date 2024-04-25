import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Date;

public class Server {

    private DatagramSocket socketServer;
    private DatagramPacket packetToReceive;
    private byte[] buffer;
    private String ipAdress;
    // supérieur à 1024
    private int port;

    public static void main(String[] args) {
        try {
            DatagramSocket socketServer = new DatagramSocket(5356, InetAddress.getByName("127.0.0.1"));

            while(true){
                System.out.println("Server is running on port 5356");
                byte[] buffer = new byte[1024];
                DatagramPacket packetToReceive = new DatagramPacket(buffer, buffer.length);
                socketServer.receive(packetToReceive);
                Date dateReception = new Date();
                String dateEnvoiClient = new String(packetToReceive.getData());

                System.out.println("Message received : " + dateEnvoiClient);

                InetAddress ipAdressToSend = packetToReceive.getAddress();
                int portToSend = packetToReceive.getPort();

                Date dateRenvoi = new Date();

                StringBuilder messageToSend = new StringBuilder()
                        .append(dateEnvoiClient)
                        .append(" | ")
                        .append(dateReception.getHours() + ":" + dateReception.getMinutes() + ":" + dateReception.getSeconds())
                        .append(" | ")
                        .append(dateRenvoi.getHours() + ":" + dateRenvoi.getMinutes() + ":" + dateRenvoi.getSeconds());
                System.out.println("Message sent : " + messageToSend.toString());
                byte[] bufferToSend = messageToSend.toString().getBytes();
                DatagramPacket packetToSend = new DatagramPacket(bufferToSend, bufferToSend.length, ipAdressToSend, portToSend);
                socketServer.send(packetToSend);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
