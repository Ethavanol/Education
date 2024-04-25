import java.io.BufferedInputStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ServerTCP {

    public static void main(String[] args) {
        try{
            InetAddress ipServerAdress = InetAddress.getByName("127.0.0.1");
            int portServer = 5356;

            ServerSocket serverSocket = new ServerSocket(portServer, 50, ipServerAdress);

            System.out.println("Nombre de clients maximum accepté ? ");
            Scanner sc = new Scanner(System.in);
            int numberOfThreads = sc.nextInt();

            System.out.println("Server available on port 5635");
            System.out.println("");

            ExecutorService threadPool = Executors.newFixedThreadPool(numberOfThreads);

            while(true){
                Socket socketClient = serverSocket.accept();

                threadPool.execute(new TraitementTCP(socketClient));
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
