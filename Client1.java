import java.io.*;
import java.net.*;
import java.util.*;

class Client1
{
    public static void main(String[] args) {
        try(Scanner sobj = new Scanner(System.in))
        {
            System.out.println("Enter port no : ");
            int port = sobj.nextInt();
            sobj.nextLine();
            while(true)
            {
                System.out.println("Enter message : ");
                String message = sobj.nextLine();
                Socket connectionSocket = new Socket("localhost" , port);

                PrintWriter out = new PrintWriter(connectionSocket.getOutputStream(),true);
                BufferedReader in = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));

                out.println(message);
                String k = in.readLine();
                System.out.println("Message received is : " + k);
                out.close();
                in.close();
                connectionSocket.close();
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

    }
}
