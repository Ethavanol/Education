import org.w3c.dom.ls.LSOutput;

import java.io.IOException;
import java.net.*;
import java.util.HashMap;
import java.util.Map;

public class Server {

    static Map<Integer, Integer> clients = new HashMap<>();
    public static void process(DatagramPacket receivePacket) throws IOException {
        byte[] sendData1  = new byte[1024];

        /*
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        */

        DatagramSocket ds = new DatagramSocket();
        String contenu = new String(receivePacket.getData());
        InetAddress IPAddress = receivePacket.getAddress();
        int port = receivePacket.getPort();

        System.out.println ("From: " + IPAddress + ":" + port);
        System.out.println ("Message: " + contenu);

        if(contenu.charAt(0) == 'O') {


            String answer = "1";
            sendData1 = answer.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData1, sendData1.length, IPAddress, port);
            ds.send(sendPacket);
        }
        else if(contenu.charAt(0) == 'C') {
            clients.remove(getKey(clients, port));
            System.out.println(clients);
            String answer = "2";
            sendData1 = answer.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData1, sendData1.length, IPAddress, port);
            ds.send(sendPacket);
        }
        else if(contenu.charAt(0) == 'R'){
            if(!clients.containsValue(port)){
                clients.put(clients.size(), port);
            }

        }
        else if(contenu.charAt(0) == 'S'){
            String clientskeys = "";
            String answer = "";
            for ( Integer keys : clients.keySet() ) {
                clientskeys = clientskeys + keys + " ";
            }
            if (clientskeys.equals("")){
                answer = "9 You can't chat with anyone";
            }
            else{
                answer = "You can chat with : " + clientskeys;
            }

            sendData1 = answer.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData1, sendData1.length, IPAddress, port);
            ds.send(sendPacket);
        }
        else if(contenu.charAt(0) == 'E'){
            clients.remove(getKey(clients, port));
        }
        else {

            Integer k = Integer.parseInt(String.valueOf(contenu.charAt(0)));

            if( clients.containsKey(k) )
            {
                //System.out.println("J'arrive bien ici");
                String msg = contenu.substring(2);
                sendData1 = msg.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(sendData1, sendData1.length, IPAddress, clients.get(k));
                ds.send(sendPacket);
            }
            else
            {
                //System.out.println("J'arrive ici");
                String answer = "Missing or wrong client number";
                sendData1 = answer.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(sendData1, sendData1.length, IPAddress, port);
                ds.send(sendPacket);
            }
        }





    }
    public static <K, V> K getKey(Map<K, V> map, V value) {
        for (Map.Entry<K, V> entry : map.entrySet()) {
            if (entry.getValue().equals(value)) {
                return entry.getKey();
            }
        }
        return null;
    }
    public static void main(String[] args) {
        // Client/Server packet exchange between client 1 @ip1 and server 1 @ ip2

        try {
            InetAddress ip1 = InetAddress.getByAddress(new byte[]{(byte) 127, (byte) 0, (byte) 0, (byte) 1});
            DatagramSocket ds = new DatagramSocket(1050, ip1);

            while(true){
                byte[] receiveData = new byte[1024];


                DatagramPacket receivePacket =
                        new DatagramPacket(receiveData, receiveData.length);

                System.out.println ("Waiting for datagram packet");



                ds.receive(receivePacket);


                if (receivePacket.getLength() > 0) {
                   // System.out.println ("Datagram packet received");
                    Thread t = new Thread() {
                        public void run() {
                            try {
                                process(receivePacket);
                            } catch (IOException e) {
                                throw new RuntimeException(e);
                            }

                        }
                    };
                    t.start();
                }


            }
        }catch (SocketException e){
            throw new RuntimeException(e);
        }catch (UnknownHostException e){
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}
