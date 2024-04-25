import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class TraitementTCP implements Runnable{

    private Socket socket;
    public TraitementTCP(Socket socket){
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            BufferedInputStream in = new BufferedInputStream(this.socket.getInputStream());
            PrintWriter out = new PrintWriter(this.socket.getOutputStream());

            byte[] buffer = new byte[1024];

            while(!this.socket.isClosed()) {
                int len = in.read(buffer);
                if(len > 0 ) {
                    String message = new String(buffer, 0, len);

                    System.out.println("Message reçu de " + this.socket.getPort() + " : " + message);

                    String answer = "réponse";

                    out.write(answer);
                    out.flush();
                } else {
                    this.socket.close();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
