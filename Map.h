#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
#define RESET "\033[0m"
#define BLUE  "\033[34m"
#define RED  "\033[31m"
#define BG_CYAN   "\033[46m"
#define YELLOW  "\033[33m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define ORANGE "\033[38;5;202m"
#define BG_RED   "\033[41m"

void Delay(int milliseconds) {
    Sleep(milliseconds);
}

void MapShow(){
	cout<<"-___-----___--------============================================================================"<<endl;
	cout<<"| Z |   | Y |    | |     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||     ||"<<endl;
	cout<<"| B |   | B |    | | FGU || IGR || JGQ || MGN || NGM || QGJ || RGI || UGF || VGE || YGB || ZGA ||"<<endl;
	cout<<"| A |   | B |    | |-----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----||"<<endl;
	cout<<"|___|   |___|    | |                                 "<<GREEN<<"Gulshan"<<RESET<<"                                   ||"<<endl;
	cout<<" "<<YELLOW<<"Bahadurabad"<<RESET<<"      | |-----  -----  -----  -----  -----        -----  -----  -----  -----  ----- ||"<<endl;
	cout<<" ___     ___     | | GGT || HGS || KGP || LGO || OGL |      | PGK || SGH || TGG || WGD || XGC  ||"<<endl;
	cout<<"| X |   | W |    | |==================================      ===================================||"<<endl;
	cout<<"| B |   | B |    | |                                                                           ||"<<endl;
	cout<<"| C |   | D |    | |                                                                           ||"<<endl;
	cout<<"|___| $ |___|-------                    ------                                                 ||"<<endl;
	cout<<"                                       /      \\                                                ||"<<endl;
	cout<<"---------------                       | "<<BG_CYAN<<"Crosss"<<RESET<<" |                                               ||"<<endl;
	cout<<"               |                      |  "<<BG_CYAN<<"Road"<<RESET<<"  |               ================================||"<<endl;
	cout<<"    "<<BLUE<<"Police"<<RESET<<"     $                       \\      /               |                                ||"<<endl;
	cout<<"    "<<BLUE<<"station"<<RESET<<"    $                         ----                 |                                ||"<<endl;
	cout<<"               |                                              $           "<<RED<<"HOSPITAL"<<RESET<<"             ||"<<endl;
	cout<<"---------------                                               $                                ||"<<endl;
	cout<<"                                                              |                                ||"<<endl;
	cout<<"                                                              |                                ||"<<endl;
	cout<<"                   ~~~~~~$$~~~~~~                     =========================================||"<<endl;
	cout<<"               || |              |                    || ZQA || WQD || VQE || SQH || RQI | OQL ||"<<endl;
	cout<<" =====$$=====  || |              |                    ||-----  -----  -----  -----  ----- -----||"<<endl;
	cout<<"|            | || |    "<<CYAN<<"Garden"<<RESET<<"    |                                     "<<ORANGE<<"Quidabad"<<RESET<<"                ||"<<endl;
	cout<<"|   "<<MAGENTA<<"Market"<<RESET<<"   | || |              |                    ||-----  -----  -----  -----  ----- -----||"<<endl;
	cout<<"|            | || |              |                    || YQB || XQC || UQF || TQG || QQJ | PQK ||"<<endl;
	cout<<" ==============================================================================================||"<<endl;
}

int CalculateIndex() {
    string area;
    Upagain:
    cout << "\nEnter Area: ";
    cin >> area;

    // Convert area to lowercase for case-insensitive comparison
    for (int i=0;i<area.length();i++) {
        area[i] = tolower( area[i] );
    }

    if (area == "police") {
        return 0;
    } else if (area == "market") {
        return 1;
    } else if (area == "garden") {
        return 2;
    } else if (area == "hospital") {
        return 3;
    } else if (area == "bahadurabad") {
		string house;
        cout << "Enter House Number (0 if Not): ";
        cin >> house;
        if(house!="0"){
	        cout << ": " << house[house.length() - 1] << " ";
	        int cal = house[house.length() - 1] - 'A' + 1;
	        cal+=4;
			return cal;
		}
		return 4;
    } else if (area == "quidabad") {
    	string house;
        cout << "Enter House Number (0 if Not): ";
        cin >> house;
        if(house!="0"){
	        cout << ": " << house[house.length() - 1] << " ";
	        int cal = house[house.length() - 1] - 'A' + 1;
	        cal+=9;
			return cal;
		}
        return 9;
    } else if (area == "gulshan") {
        string house;
        cout << "Enter House Number (0 if Not): ";
        cin >> house;
        if(house!="0"){
	        cout << ": " << house[house.length() - 1] << " ";
	        int cal = house[house.length() - 1] - 'A' + 1;
	        cal+=22;
			return cal;
		}
		return 22;
    }

	cout<<"<< Wrong Input >>";
	goto Upagain;
}

string GetLocation(int index){
	int flag=0;
	Again:
	if(flag==1){
		cin>>index;
		flag=0;
	}
	if (index == 0) { //Police
        return "Police";
    } else if (index == 1) { //Market
        return "Market";
    } else if (index == 2) { //Garden
        return "Garden";
    } else if (index == 3) { //Hospital
        return "Hospital";
    } else if (index >= 4 && index < 9) { //Shah Latif
    	if(index==4){ return "Bahadurabad"; }
    	string result;
    	index=index-4;
    	char nextLetter = 'Z' + 1 - index;  
        result += nextLetter;			result+="B";
        nextLetter= 'A' -1 + index;		result+=nextLetter;
        return result;
    	
    } else if (index >= 9 && index <22 ) { //Quidabad
        if(index==9){ return "Quidabad"; }
        string result;
        index=index-9;
    	char nextLetter = 'Z' + 1 - index;  
        result += nextLetter;			result+="Q";
        nextLetter= 'A' -1 + index;		result+=nextLetter;
        return result;
    } else if (index >= 22 && index <44) {  // Gulshan
        if(index==22){ return "Gulshan"; }
        index=index-22;
        string result;
    	char nextLetter = 'Z' + 1 - index;  
        result += nextLetter;			result+="G";
        nextLetter= 'A' -1 + index;		result+=nextLetter;
        return result;
    }
    else{
    	cout<<"\n\n <<    Wrong Input    >>\n\n";
    	flag=1;
    	goto Again;
	}
}

void Intro() {
    string var = "EMERGENCY MANAGEMENT SYSTEM";
    cout<<BG_RED;
    cout << "\n\n\n\n\n\t\t\t\t\t  ";
    for (int i = 0; i < var.length(); i++) {
        cout << var[i];
        Delay(100);
    }
	cout<<RESET;
    var = "By\n";
    cout << "\n\n\n\n\n\t\t\t\t\t            ";
    cout<<RED;
    for (int i = 0; i < var.length(); i++) {
        cout << var[i];
       Delay(100);
    }
	cout<<RESET;
    var = "Muhammad Huzaifa [22k-0502]\n";
    cout << "\t\t\t\t            ";
    cout<<RED;
    for (int i = 0; i < var.length(); i++) {
        cout << var[i];
        Delay(100);
    }
	cout<<RESET;
    var = "Muhammad Haris [22k-0505]\n";
    cout << "\t\t\t\t            ";
    cout<<RED;
    for (int i = 0; i < var.length(); i++) {
        cout << var[i];
        Delay(100);
    }
	cout<<RESET;
    var = "Muhammad Daniyal [22k-4294]\n";
    cout << "\t\t\t\t            ";
    cout<<RED;
    for (int i = 0; i < var.length(); i++) {
        cout << var[i];
        Delay(100);
    }
	cout<<RESET;
    Delay(500);
    system("cls");
}

