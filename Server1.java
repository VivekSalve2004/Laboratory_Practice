import java.io.*;
import java.util.*;
import java.net.*;

class Server1
{
    public static void main(String arg[])
    {
        Scanner sobj = new Scanner(System.in);
        System.out.println("Enter port number : ");
        int port = sobj.nextInt();
        try(ServerSocket s = new ServerSocket(port))
        {
            while(true)
            {
                Socket connectionSocket = s.accept();
                System.out.println("Server : Request received from : " + connectionSocket.getInetAddress().toString());
                Thread newthread = new RequestHandler(connectionSocket);
                newthread.start();
            }
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        sobj.close();
    }
}