#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    int client;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if(client>0)
        cout<<"Sucessfully established socket connection."<<endl;
     else
       {
           cout<<"Failed to establish sockey connection"<<endl;
           return 0;
       }

    struct sockaddr_in server={0};
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);

    //connect to the server that is in the listenning state
   if( connect(client,(struct sockaddr *)&server, sizeof(server))==-1)
        cout<<"No server is found, programing terminated."<<endl;  

    else
    {
        cout << "Connection with the server established."<<endl;
        cout<<"you can send '0' to the server to end the connection."<<endl;
       
        bool end = false;
        int msize = 100;
        char message[msize];
        do 
        {
            cout << "\nClient: ";
            while (true)
            {
                cin >> message;
                write(client, message, msize);
                if(*message=='.') break;
                if(*message=='0')
                {
                    end=true;
                    break;
                }
            } 

            cout << "Server: ";
            while (true)
            {
                read(client, message, msize);
                if(*message!='0')
                cout << message << " ";
                if(*message=='.') break;
                if(*message=='0') 
                {
                    end =true;
                    break;
                }
            }
        } while (!end);
    }
   cout<<endl;
    close(client);
    return 0;
}

