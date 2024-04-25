import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class Client {

    public String myOwnMail = "test@ethan.fr";

    public static void main(String[] args) {
        try {
            InetAddress ipServerAdress = InetAddress.getByName("127.0.0.1");
            int portServer = 25;

            String myOwnMail = "test@ethan.fr";
            String[] nameList = {"Ethan", "Matt"};
            String[] mailList = {"ethan@ethan.fr", "matt@ethan.fr"};

            int envoiRealise = 0;

            Socket socket = new Socket(ipServerAdress, portServer);

            BufferedInputStream in = new BufferedInputStream(socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            //Connexion au serveur
            System.out.println("Ouverture de la connexion en cours");

            byte[] buffer = new byte[1024];

            int len = in.read(buffer);
            String answer = new String(buffer, 0, len);

            System.out.println(answer);

            String message = "HELO 127.0.0.1 \r\n";

            System.out.println(message);

            out.write(message);
            out.flush();

            len = in.read(buffer);
            answer = new String(buffer, 0, len);

            System.out.println(answer);

            while(!socket.isClosed()){

                System.out.println("Voulez-vous envoyer un mail à chacun des destinataires suivants ? (y/n)");
                Arrays.stream(mailList).map(mail-> mail + " ").forEach(System.out::print);

                Scanner sc = new Scanner(System.in);
                String saisie = sc.nextLine();

                if (saisie.equals("y")) {

                    for(int i = 0; i< nameList.length; i++){

                        message = "MAIL FROM:" + myOwnMail + "\r\n";
                        System.out.println(message);
                        out.write(message);
                        out.flush();

                        len = in.read(buffer);
                        answer = new String(buffer, 0, len);

                        System.out.println(answer);

                        message = "RCPT TO:" + mailList[i] + "\r\n";
                        out.write(message);
                        out.flush();

                        System.out.println(message);

                        len = in.read(buffer);
                        answer = new String(buffer, 0, len);

                        System.out.println(answer);

                        message = "DATA \r\n";
                        out.write(message);
                        out.flush();

                        System.out.println(message);

                        len = in.read(buffer);
                        answer = new String(buffer, 0, len);

                        System.out.println(answer);

                        message = "Subject: SALUT \r\n \r\n";
                        out.write(message);
                        out.flush();

                        System.out.println(message);

                        message = "Bonjour " + nameList[i] + "\r\n.\r\n";
                        out.write(message);
                        out.flush();

                        System.out.println(message);

                        len = in.read(buffer);
                        answer = new String(buffer, 0, len);

                        System.out.println(answer);
                    }

                } else {
                    System.out.println("Fermeture de la connexion");
                    socket.close();
                }

            }

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public void sendToAll(Socket socket, HashMap<String, String> mailList) throws IOException {

        System.out.println("la");

        BufferedInputStream in = new BufferedInputStream(socket.getInputStream());
        PrintWriter out = new PrintWriter(socket.getOutputStream());

        byte[] buffer = new byte[1024];

        AtomicInteger len = new AtomicInteger(in.read(buffer));

        AtomicReference<String> answer = new AtomicReference<>("");
        AtomicReference<String> message = new AtomicReference<>("");

        mailList.forEach((key, value) -> {

            try {
                len.set(in.read(buffer));

                answer.set(new String(buffer, 0, len.get()));

                System.out.println(answer.get());

                message.set("MAIL FROM:" + myOwnMail);
                out.write(message.get());
                out.flush();

                System.out.println(message.get());

                len.set(in.read(buffer));
                answer.set(new String(buffer, 0, len.get()));

                System.out.println(answer.get());

                message.set("RCPT TO:" + myOwnMail);
                out.write(message.get());
                out.flush();

                System.out.println(message.get());

                len.set(in.read(buffer));
                answer.set(new String(buffer, 0, len.get()));

                System.out.println(answer.get());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
    }
}
