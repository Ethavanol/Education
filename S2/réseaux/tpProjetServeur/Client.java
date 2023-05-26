import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try
        {
            InetAddress ip1, ip2;
            boolean connected = false;
            ip1 = InetAddress.getByAddress(new byte[]{(byte) 127, (byte) 0, (byte) 0, (byte) 1});
            ip2 = InetAddress.getByAddress(new byte[]{(byte) 127, (byte) 0, (byte) 0, (byte) 1});
            DatagramSocket dc = new DatagramSocket(1090, ip2);
            Scanner myObj = new Scanner(System.in);

            while (true){

                if(!connected){
                    System.out.println("Connect to server 1 ? (y/n)");
                    String answer = myObj.nextLine();
                    if(answer.equals("y")){
                        byte[] buffer = "O".getBytes();
                        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, ip1, 1050);
                        dc.send(dp);

                        byte[] receiveData = new byte[1024];

                        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

                        dc.receive(receivePacket);

                        String contenu = new String(receivePacket.getData());
                        InetAddress IPAddress = receivePacket.getAddress();
                        int port = receivePacket.getPort();

                        if (contenu.charAt(0) == '1'){
                            System.out.println("Connected to server 1");
                            System.out.println(contenu);
                            connected = true;
                        }
                        else{
                            System.out.println("Server 1 is not available");
                        }
                    }
                }
                else{
                    System.out.println("Wanna receive or send message ? (r/s) (to disconnect enter d)");
                    String answer = myObj.nextLine();
                    if(answer.equals("r")){
                        byte[] buffer = "R".getBytes();
                        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, ip1, 1050);
                        dc.send(dp);

                        byte[] receiveData = new byte[1024];

                        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

                        dc.receive(receivePacket);
                        String contenu = new String(receivePacket.getData());
                        System.out.println("message : " + contenu);

                        byte[] bufferrmv = "E".getBytes();
                        DatagramPacket dp2 = new DatagramPacket(bufferrmv, bufferrmv.length, ip1, 1050);
                        dc.send(dp2);

                    }
                    else if(answer.equals("s")){
                        byte[] buffer = "S".getBytes();
                        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, ip1, 1050);
                        dc.send(dp);
                        byte[] receiveData = new byte[1024];

                        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

                        dc.receive(receivePacket);

                        String contenu = new String(receivePacket.getData());
                        System.out.println(contenu.substring(2));
                        if(contenu.charAt(0) != '9'){
                            System.out.println("Enter message (put user id first) :");
                            String message = myObj.nextLine();

                            byte[] buffermsg = message.getBytes();

                            DatagramPacket dp2 = new DatagramPacket(buffermsg, buffermsg.length, ip2, 1050);
                            dc.send(dp2);
                        }
                        else{
                            System.out.println("Try again later");
                        }

                    }
                    else if (answer.equals("d")){
                        byte[] buffer = "C".getBytes();
                        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, ip1, 1050);
                        dc.send(dp);

                        byte[] receiveData = new byte[1024];

                        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

                        dc.receive(receivePacket);
                        String contenu = new String(receivePacket.getData());

                        if (contenu.charAt(0) == '2'){
                            System.out.println("Disconnected from server 1");
                            connected = false;
                        }
                    }
                    else{
                        System.out.println("Wrong answer");
                    }

                }
            }


        }catch(SocketException e){
            throw new RuntimeException(e);
        }catch(UnknownHostException e){
            throw new RuntimeException(e);
        } catch(IOException e)
        {
            throw new RuntimeException(e);
        }
    }
}

