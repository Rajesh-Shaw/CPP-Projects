#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_MESSAGES = 1000;

struct Message
{
    string sender;
    string text;
};

Message chatMessages[MAX_MESSAGES];
int messageCount = 0;

void showMenu();
void sendMessage();
void viewChat();
void saveChat();
void loadChat();

int main()
{
    loadChat();
    
    int choice;
    while(true)
    {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch(choice)
        {
            case 1: sendMessage(); break;
            case 2: viewChat(); break;
            case 3: saveChat(); break;
            case 4: saveChat();
                    cout << "Exiting... GoodBye!\n";
                    return 0;
            default: 
                    cout << "Invalid choice! Try again.\n";
        }
        cout << "\n";
    }
    return 0;
}


void showMenu()
{
    cout << "====================================\n";
    cout << "          CHAT APPLICATION          \n";
    cout << "====================================\n";
    cout << "1. Send Message\n";
    cout << "2. View Chat History\n";
    cout << "3. Save Chat\n";
    cout << "4. Exit\n";
}


void sendMessage()
{
    if(messageCount >= MAX_MESSAGES)
    {
        cout << "Chat memory full! Save and restart.\n";
        return;
    }

    cin.ignore();
    string sender, text;
    cout << "Enter Sender Name: ";
    getline(cin, sender);
    cout << "Enter Message: ";
    getline(cin, text);

    chatMessages[messageCount].sender = sender;
    chatMessages[messageCount].text = text;
    messageCount++;
    cout << "Message Sent!\n";
}

void viewChat()
{
    if(messageCount == 0)
    {
        cout << "No messages yet!\n";
        return ;
    }

    cout << "\n--------------- Chat History --------------\n";
    for(int i=0; i<messageCount; i++)
    {
        cout << chatMessages[i].sender << ": " <<chatMessages[i].text << "\n";
    }
    cout << "---------------------------------------------\n";
}

void saveChat()
{
    ofstream out("chat.txt");
    for(int i=0; i<messageCount; i++)
    {
        out << chatMessages[i].sender << endl;
        out << chatMessages[i].text << endl;
    }
    out.close();
    cout << "Chat Saved Successfully.\n";
}

void loadChat()
{
    ifstream in("chat.txt");
    if(!in)
    {
        cout << "No previous chat found!\n";
        return;
    }

    messageCount = 0;
    while(getline(in, chatMessages[messageCount].sender))
    {
        getline(in, chatMessages[messageCount].text);
        messageCount++;
        if(messageCount >= MAX_MESSAGES)
            break;
    }

    in.close();
    cout << "Loaded " << messageCount << " messages(s) from file.\n";
}