#include <iostream>
#include <fstream>
#include<cstring>
#include <windows.h>
#include<conio.h>
#include "Map.h"
#include "Dijekstra.h"
using namespace std;
int foruser=1;
int forservice=1;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class node;

class ServiceProvider {
    int Id;
    char Username[50]; 
    char Password[50]; 
    char Full_Name[100]; 
    int Location;
	int TypeService;
public:
    bool available;
    ServiceProvider() : Location(0), available(false) {
		this->Id=forservice++;
	}
    ServiceProvider(const ServiceProvider& other) : Id(other.Id), Location(other.Location), available(other.available) {
        if(Id!=0){
        	Id=forservice++;
		}
		strcpy(Username, other.Username);
        strcpy(Password, other.Password);
        strcpy(Full_Name, other.Full_Name);
    }
    ServiceProvider(const char* username, const char* password, const char* fullName, int Location, bool avail)
        : Location(Location), available(avail) {
        Id=forservice++;
        strncpy(Username, username, sizeof(Username) - 1);
        strncpy(Password, password, sizeof(Password) - 1);
        strncpy(Full_Name, fullName, sizeof(Full_Name) - 1);
        Username[sizeof(Username) - 1] = '\0';
        Password[sizeof(Password) - 1] = '\0';
        Full_Name[sizeof(Full_Name) - 1] = '\0';
    }

    ServiceProvider& operator=(const ServiceProvider& other) {
        if (this != &other) {
            Id = other.Id;
            Location = other.Location;
            available = other.available;
            strcpy(Username, other.Username);
            strcpy(Password, other.Password);
            strcpy(Full_Name, other.Full_Name);
        }
        return *this;
    }
	
	void ServiceInput(int choice) {
		gotoxy(48, 7);
        cout << "\n\n\n\n\n\t\t\t\t\tEnter Username: ";
		cin.ignore();
		cin.getline(Username, sizeof(Username));

        cout << "\n\t\t\t\t\tEnter Password: ";  
		cin.ignore();
		cin.getline(Password, sizeof(Password));

        cout << "\n\t\t\t\t\tEnter Full Name: "; 
		fflush(stdin);
		cin.getline(Full_Name, sizeof(Full_Name));

        cout << "\n\t\t\t\t\tIs the service provider available? (1 for true, 0 for false): "; cin >> available;
        choice=TypeService;
        system("cls");
        MapShow();
        this->Location = CalculateIndex();
    }
	
    int getId() const { return Id; }

    const char* getUsername() const { return Username; }
    void setUsername(const char* username) { strncpy(Username, username, sizeof(Username) - 1); }

    const char* getPassword() const { return Password; }
    void setPassword(const char* password) { strncpy(Password, password, sizeof(Password) - 1); }

    const char* getFullName() const { return Full_Name; }
    void setFullName(const char* fullName) { strncpy(Full_Name, fullName, sizeof(Full_Name) - 1); }

    int getLocation() const { return Location; }
    void setLocation(int Location) { Location = Location; }

    bool isAvailable() const { return available; }
    void setAvailable(bool avail) { available = avail; }
    void InputAvailableStatus(){ cin>>available; }
    void SetTypeService(int TypeService){ this->available=TypeService; }
    
    //////////////////////////////////////////////////
    void display() const {
        cout << "\n\n\n\n\n\t\t\t\t\t\tService Provider ID: " << getId() << "\n";
        cout << "\t\t\t\t\t\tUsername: " << getUsername() << "\n";
        cout << "\t\t\t\t\t\tFull Name: " << getFullName() << "\n";
        cout << "\t\t\t\t\t\tAvailable: " << (isAvailable() ? "Yes" : "No") << "\n";
        cout << "\n";
    }
    int ServiceStoreInFile(int);
    int ServiceGetFromFile(int,const char*,const char*);
};

/*			To Write Service Provider into Object in File			*/
int ServiceProvider::ServiceStoreInFile(int choice){
    ofstream SaveinFile;
    if (choice == 1) {
        SaveinFile.open("Ambulance.dat", ios::app | ios::binary);
    } else if (choice == 2) {
        SaveinFile.open("FireBrigade.dat", ios::app | ios::binary);
    } else if (choice == 3) {
        SaveinFile.open("Police.dat", ios::app | ios::binary);
    }

    if (!SaveinFile.is_open()) {
        cout << "Error opening file.\n";
        return -1;
    }

    SaveinFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    SaveinFile.close();
    return 0;
}
/*			To GetBack Service Provider From File into Object			*/
int ServiceProvider::ServiceGetFromFile(int choice, const char* email, const char* pass) {
    ifstream Getme;
    if (choice == 1) {
        Getme.open("Ambulance.dat", ios::in | ios::binary);
    } else if (choice == 2) {
        Getme.open("FireBrigade.dat", ios::in | ios::binary);
    } else if (choice == 3) {
        Getme.open("Police.dat", ios::in | ios::binary);
    }

    if (!Getme.is_open()) {
        cout << "Error opening file.\n";
        return -1;
    }

    Getme.read(reinterpret_cast<char*>(this), sizeof(*this));
    while (!Getme.eof()) {
        if (strcmp(this->Username, email) == 0 && strcmp(this->Password, pass) == 0) {
            Getme.close();
            return 1;
        }
        Getme.read(reinterpret_cast<char*>(this), sizeof(*this));
    }

    Getme.close();
    return 0;
}
/*			LinkedList To Store List of Available Service Provider			*/     
class node{
	public:
		ServiceProvider obj;
		int ShortestPath;
		string CompletePath;
		node* next;
		node():ShortestPath(0),CompletePath(""){
			next=NULL;
		}
		node(ServiceProvider naya){
			obj=naya;
			next=NULL;
		}
};
node* head=NULL;
/*        Take Service Providers From File to Provide Service       */
void insertNode(ServiceProvider obj) {
    node* newNode = new node(obj);
    if (head==NULL) {
        head = newNode;
        head->next=NULL;
        return;
    }
	else {
        node* temp = head;
        while (temp->next!=NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        temp->next->next=NULL;
    }
}
//////   ----->
int ServiceProvidersFromFile(int choice){
	ServiceProvider obj;
	ifstream Getme;
	if(choice==1){
		Getme.open("Ambulance.dat",ios::in | ios::binary);
	}
	else if(choice==2){
		Getme.open("FireBrigade.dat",ios::in | ios::binary);
	}
	else if(choice==3){
		Getme.open("Police.dat",ios::in | ios::binary);
	}
	//
	if (!Getme) {
        cout << "<< File Not Found >>" << endl;
        return -1;
    }
	Getme.read(reinterpret_cast<char*>(&obj), sizeof(obj));
    while (!Getme.eof()) {
        if (obj.available == 1) {
            insertNode(obj); // Insert the service provider into the linked list
        }
        Getme.read(reinterpret_cast<char*>(&obj), sizeof(obj));
    }

    Getme.close();
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Find_The_Nearest_One( int Destination ){
	node* temp=head;
	node* Shortestone;
	int ShortDistance=INT_MAX;
	if(temp==NULL){
		system("cls");
		cout<<"\n\n\n\t\t\t\t\t\t<< No Service Provider FOund >>\n";
		exit(0);
	}
	while(temp!=NULL){
		temp->ShortestPath=ApplyDijekstra( temp->obj.getLocation(), Destination, temp->CompletePath );
		if(temp->ShortestPath < ShortDistance){
			ShortDistance = temp->ShortestPath;
			Shortestone = temp;
		}
		temp=temp->next;
	}
	cout<<"\n\n\t\t\t\tPress Any Key to Continue...";
		getch();
	for(int i=0;i<8;i++){
		cout<<"\n\n\n\n\n\t\t\t\t\tCalculating...";
		Delay(50);
		system("cls");
	}
	cout<<endl<<endl<<"\t\t\t\t\t<<  Selected One  >>"<<endl<<endl;
	cout<<"\t\t\t\t\t\tDetail:\n";
	Shortestone->obj.display();
	cout<<"\t\t\t\t\t\tDriver is "<<Shortestone->ShortestPath<<" Miles Away\n";
	if (Shortestone->CompletePath.length() >= 3) {
    	Shortestone->CompletePath = Shortestone->CompletePath.substr(0, Shortestone->CompletePath.length() - 3);
	}
	cout<<endl<<"\t\t\t\t\t\t"<<Shortestone->CompletePath<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class User {
    int Id;
    char Username[50];
    char Password[50];
    char Full_Name[100];

public:
    User(){
		Id=foruser++;
	}
    User(const User& other) : Id(other.Id){
    	if(Id==0){
    		Id=foruser++;
		}
        strcpy(Username, other.Username);
        strcpy(Password, other.Password);
        strcpy(Full_Name, other.Full_Name);
    }
    User(const char* username, const char* password, const char* fullName) {
        strncpy(Username, username, sizeof(Username) - 1);
        strncpy(Password, password, sizeof(Password) - 1);
        strncpy(Full_Name, fullName, sizeof(Full_Name) - 1);
        Username[sizeof(Username) - 1] = '\0';
        Password[sizeof(Password) - 1] = '\0';
        Full_Name[sizeof(Full_Name) - 1] = '\0';
        Id=foruser++;
    }

    User& operator=(const User& other) {
        if (this != &other) {
            Id = other.Id;
            strcpy(Username, other.Username);
            strcpy(Password, other.Password);
            strcpy(Full_Name, other.Full_Name);
        }
        return *this;
    }
    void UserInput();

    int getId() const { return Id; }
    void setId(int id) { Id = id; }

    const char* getUsername() const { return Username; }
    void setUsername(const char* username) { strncpy(Username, username, sizeof(Username) - 1); }

    const char* getPassword() const { return Password; }
    void setPassword(const char* password) { strncpy(Password, password, sizeof(Password) - 1); }

    const char* getFullName() const { return Full_Name; }
    void setFullName(const char* fullName) { strncpy(Full_Name, fullName, sizeof(Full_Name) - 1); }

    void display(){
        cout << "User ID: " << getId() << "\n";
        cout << "Username: " << getUsername() << "\n";
        cout << "Full Name: " << getFullName() << "\n";
        cout << "\n";
    }
    
    int UserStoreInFile();
    int UserGetFromFile(char*,char*);
};
/*						User Input								*/
void User::UserInput() {
        cout << "\n\n\n\n\n\t\t\t\t\tEnter Username: ";
        cin.ignore();
        cin.getline(Username, sizeof(Username));
        cout << "\n\t\t\t\t\tEnter Password: ";
        cin.ignore();
        cin.getline(Password, sizeof(Password));
        cout << "\n\t\t\t\t\tEnter Full Name: ";
        fflush(stdin);
        cin.getline(Full_Name, sizeof(Full_Name));
        system("cls");
    	cout<<"<< You Are Registered >>";
		cout<<"\n\n\t\t\t\tPress Any Key to Continue...";
		getch();
		system("cls");
}
/*			To Write User in File			*/
int User::UserStoreInFile(){
	
	ofstream SaveinFile;
	SaveinFile.open("Users.dat",ios::app | ios::binary);
	SaveinFile.write( (char*)this , sizeof(*this) );
	SaveinFile.close();
}
/*			To GetBack User From File into Object			*/
int User::UserGetFromFile(char* email,char* pass){
	ifstream Getme;
	Getme.open("Users.dat",ios::in | ios::binary);
	if(!Getme){
		cout<<"\n<< File Not Found >>\n";
	}
	else{
		Getme.read( (char*)this , sizeof(*this) );
		while( !Getme.eof() ){
			if( strcmp(this->Username,email)==0 && strcmp(this->Password,pass)==0 ){
				return 1;
			}
			Getme.read( (char*)this , sizeof(*this) );
		}

		return 0;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Who(){
	bool choice;
	cout<<"\n\n\n\n\n\t\t\t\t\tPress-1 User";
	cout<<"\n\t\t\t\t\tPress-0 Service Provider:	";
	cin>>choice;

	return choice;
}


void ServiceLoginSignUp(){
	char Username[50];
	char Password[50];
	int choice;
	system("cls");
	gotoxy(48, 7);
	cout<<"Press-1 Login";
	gotoxy(48, 8);
	cout<<"Press-0 SignUp:	";
	gotoxy(50, 12);
	cin>>choice;
	system("cls");
	ServiceProvider obj;
	if(choice==0){
    	cout<<"Press-1 Ambulence Service\n Press-2 FireBrigade Service\nPress3 For Police Service:	";cin>>choice;
		obj.ServiceInput(choice);
		obj.ServiceStoreInFile(choice);
		return;
	}
	cout << "\n\n\n\n\n\t\t\t\t\tEnter Username: ";
	cin.ignore();
    cin.getline(Username, sizeof(Username));
	cout << "\n\t\t\t\t\tEnter Password: ";
    cin.ignore();
	cin.getline(Password, sizeof(Password));
    cout<<"Press-1 Ambulence Service\n Press-2 FireBrigade Service\nPress-3 For Police Service:	";cin>>choice;
    if(obj.ServiceGetFromFile(choice,Username,Password) ==0){
    	cout<<"\n<< No User Found >>\n";
		ServiceProvider Nul;
		return;
	}
	cout<<endl<<endl;
	system("cls");
	obj.display();
	cout<<"Currently Available? (1-Available, 0-Not Available)	"; obj.InputAvailableStatus();
	cout<<"Change Location: (1-Yes, 0-No)";		bool mychoice;		cin >> mychoice;
	if( mychoice == 1 ){ obj.setLocation( CalculateIndex() ); }
}

void UserLoginSignUp(){
	char Username[50];
	char Password[50];
	bool choice;
	system("cls");
	gotoxy(48, 7);
	cout<<"Press-1 Login";
	gotoxy(48, 8);
	cout<<"Press-0 SignUp:	";
	gotoxy(50, 12);
	cin>>choice;
	User obj;
	system("cls");
	if(choice==0){
		obj.UserInput();
		obj.UserStoreInFile(); // Saved in File
		goto Catch;
	}
	gotoxy(48, 7);
	cout << "Enter Username: ";
	cin.ignore();
    cin.getline(Username, sizeof(Username));
	gotoxy(48, 8);
	cout << "Enter Password: ";
	cin.ignore();
    cin.getline(Password, sizeof(Password));
    if(obj.UserGetFromFile(Username,Password) ==0){
    	cout<<"\n<< No User Found >>\n";
		return ;
	}
	obj.display();	int Location;
	Catch:
	MapShow();
	cout<<endl<<endl<<"Enter Location:	";
	Location = CalculateIndex();
		
	cout<<endl<<endl<<"WANT SERVICE? (1-YES, 0-NO): ";		cin>>choice;
	if(choice==1){
		cout<<endl<<endl<<"Which Type Emergency?\nPress-1 Ambulence\nPress-2 Fire Brigade\nPress-3 Police:	";cin>>choice;
		ServiceProvidersFromFile(choice);			/// Now Work Start to Find The Nearest Person;
		Find_The_Nearest_One( Location );
		head=NULL;
	}
}

int main() {
  //  Intro();
	if( Who()==1 ){
		UserLoginSignUp();
	}
	else{
		ServiceLoginSignUp();
	}
    return 0;
}


