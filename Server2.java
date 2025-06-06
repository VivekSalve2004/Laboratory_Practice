import java.io.*;
import java.net.*;
import java.util.*;

class Server2
{
    public static void main(String[] args) {
        Scanner sobj = new Scanner(System.in);
        System.out.println("Enter port no");
        int port = sobj.nextInt();
        sobj.close();
        try(ServerSocket socket = new ServerSocket(port))
        {
            while(true)
            {
                Socket connectionSocket = socket.accept();
                System.out.println("Server : request received from : "+connectionSocket.getInetAddress().toString());
                Thread newThread = new RequestHandler1(connectionSocket);
                newThread.start();
            }
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }
}