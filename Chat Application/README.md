💬 Chat Application (C++)
📘 Overview
The Chat Application is a simple console-based program built using core C++ (without vectors or advanced libraries).
It allows two or more users to send messages, view chat history, and save conversations in a text file.
This version simulates an offline chat, storing messages locally inside a file named chat.txt.
________________________________________
🧠 Features
✅ Send messages (from any sender name)
✅ View all chat messages like a conversation
✅ Save chat history to a file (chat.txt)
✅ Automatically load saved messages on startup
✅ Simple, beginner-friendly, and uses only core C++ concepts
________________________________________
⚙️ Concepts Used
Concept	Description
Struct	Used to store message details (sender & text)
Array	Holds all chat messages (max 1000)
File Handling (fstream)	Saves and loads messages from a file
Functions	Modular approach — each task in its own function
Loops & Conditional Statements	Used for menu navigation and control
________________________________________
🧾 Menu Options
====================================
          CHAT APPLICATION
====================================
1. Send Message
2. View Chat History
3. Save Chat
4. Exit
________________________________________
🧍 Example Run
Loaded 3 message(s) from file.

====================================
          CHAT APPLICATION
====================================
1. Send Message
2. View Chat History
3. Save Chat
4. Exit
Enter your choice : 1
Enter Sender Name: Rajesh
Enter Message: Hi Bob!

Message Sent!

Enter your choice : 1
Enter Sender Name: Bob
Enter Message: Hello Rajesh, how are you?

Message Sent!

Enter your choice : 2
--------------- Chat History --------------
Rajesh : Hi Bob!
Bob: Hello Rajesh, how are you?
---------------------------------------------
________________________________________
💾 Data File: chat.txt
Example contents after saving:
Rajesh 
Hi Bob!
Bob
Hello Rajesh, how are you?
When the program restarts, it automatically loads this chat history.
________________________________________
🛠️ How to Compile and Run
Open your terminal or PowerShell inside the Chat Application folder and run:
g++ main.cpp -o chat_app
./chat_app
________________________________________
📁 Project Structure
Chat Application/
│
├── main.cpp        # Source code
├── chat.txt        # Stores chat history
└── README.md       # Project documentation
________________________________________
🚀 Future Improvements
•	Add message timestamps 🕒
•	Add a real-time chat system using sockets
•	Add user authentication (login/register)

👨‍💻 Author
    Rajesh Shaw
    📘 GitHub: Rajesh-Shaw