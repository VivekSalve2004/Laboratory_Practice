import java.io.*;
import java.util.*;
import java.net.*;

class Client2
{
    public static void main(String[] args) {
        try(Scanner sobj = new Scanner(System.in))
        {
            System.out.println("Enter port number ");
            int port = sobj.nextInt();
            sobj.nextLine();
            while(true)
            {
                System.out.println("Enter message");
                String msg = sobj.nextLine();
                Socket connectionSocket = new Socket("localhost",port);
                PrintWriter out = new PrintWriter(connectionSocket.getOutputStream(),true);
                BufferedReader in = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                out.println(msg);
                String response = in.readLine();
                System.out.println("Client : received response is : => "+response);
                in.close();
                out.close();
                connectionSocket.close();
            }
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }
}
