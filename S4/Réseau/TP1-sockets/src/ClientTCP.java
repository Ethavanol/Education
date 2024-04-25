import java.io.BufferedInputStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class ClientTCP {

    public static void main(String[] args) {
        try {
            InetAddress ipServerAdress = InetAddress.getByName("127.0.0.1");
            int portServer = 5356;

            Socket socket = new Socket(ipServerAdress, portServer);

            BufferedInputStream in = new BufferedInputStream(socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            String message = "test";

            while(!socket.isClosed()){
                out.write(message);
                out.flush();

                byte[] buffer = new byte[1024];

                int len = in.read(buffer);
                String answer = new String(buffer, 0, len);

                System.out.println("Message reçu : " + answer);

                System.out.println("Souhaitez-vous arrêter la communication ? (y/n)");
                Scanner sc = new Scanner(System.in);
                String wantToClose = sc.nextLine();
                if(wantToClose.equals("y")) {
                    socket.close();
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
