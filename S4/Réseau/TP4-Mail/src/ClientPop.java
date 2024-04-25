import java.io.BufferedInputStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

public class ClientPop {

    public static void main(String[] args) {
        try {
            Boolean isLogged = false;
            InetAddress ipServerAdress = InetAddress.getByName("127.0.0.1");
            int portServer = 1110;

            Socket socket = new Socket(ipServerAdress, portServer);

            BufferedInputStream in = new BufferedInputStream(socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            byte[] buffer = new byte[1024];

            int len = in.read(buffer);
            String answer = new String(buffer, 0, len);

            System.out.println(answer);
            System.out.println("Veuillez entrer vos logins");


            while(!socket.isClosed()){

                Scanner sc = new Scanner(System.in);
                String saisie = sc.nextLine();
                out.write(saisie + "\r\n");
                out.flush();

                len = in.read(buffer);
                answer = new String(buffer, 0, len);
                System.out.println(answer);

                if(saisie.startsWith("PASS") && answer.startsWith("+OK")){
                    System.out.println("Vous êtes connecté");
                    isLogged = true;
                    out.write("LIST\r\n");
                    out.flush();
                    len = in.read(buffer);
                    answer = new String(buffer, 0, len);
                    int nbOfMails = Integer.parseInt(answer.split(" ")[1]);

                    for (int i = 1; i <= nbOfMails; i++) {
                        out.write("RETR " + i + "\r\n");
                        out.flush();
                        len = in.read(buffer);
                        answer = new String(buffer, 0, len);
                        System.out.println(answer);
                    }
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }


    }
}
