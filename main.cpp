#include "windows.h"
#include "time.h"
#include <array>
#include <conio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

void cave();
void wait_enter();
void sout(string message, int delay, bool endline); //Declares the sout method.
int waitForKey();
void swapColor();
int DEF_FAST_DELAY = 0;
void statCheck();
void held();

struct Flags {
    bool caveFirst = true;
    bool scavFirst = true;
    bool scavIn = true;
    bool caveIn = true;
    int dayA = 1; //this is the one that is kept eternally, doesnt restart when it hits 7
    int dayB = 1; // this is the temp day, specified with the week
    int week = 1; // the week.
    int hud;
    bool scavDay = true;

} Flg;

enum {
	COLOR_LIGHTBLUE = 9,
	COLOR_LIGHTGREEN,
	COLOR_LIGHTCYAN,
	COLOR_LIGHTRED,
	COLOR_LIGHTMAGENTA,
	COLOR_YELLOW,
	COLOR_WHITE,
};

struct Gob {
    string name = "Drozzle Dim";
    int gold = 2;
    int lvl = 1;
    int maxHP;
    int maxDP;
    int hp;
    int dp;
    int girth = 3;
    int height = 3;
    int weight = 30;
    int age = 25;
    int def;
    int spd;
    int str;
    int crt;
    double pot;
    int cool;
    int bro;
    int ca = 10;
    int co = 15;
    int energy = 3;
} Gob;

/*
        swapColor();
        cout << "";
        swapColor();
        cout << "" << endl;
*/

void statCheck()
{
    if(Gob.spd < 1) {
        Gob.spd = 1;
    }
    if(Gob.def < 1) {
        Gob.def = 1;
    }
    if(Gob.str < 1) {
        Gob.str = 1;
    }
    if(Gob.crt < 0) {
        Gob.crt = 0;
    }
    if(Gob.maxDP < 1) {
        Gob.maxDP = 1;
    }
    if(Gob.maxHP < 5) {
        Gob.maxHP = 5;
    }
}

/*
hud is chosen by the number i gave it because i dont udnerstand classes
1 = goblin hp
2 = goblin dp
3 = enemy hp
4 = enemy dp
*/

void set_console_color(int fg)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, fg);
}

void hud()
{
    float heep;
    float hoop;
    float held;
    float help;
    if(Flg.hud == 1) {
        heep = Gob.hp;
        hoop = Gob.maxHP;
        held = (heep / hoop) * 35;
        cout << " HP: |";
        help = (35 - held) - 1;
        if(held <= 17.5 && held >= 8.76) {
        set_console_color(COLOR_YELLOW);
        } else if(held < 8.75) {
        set_console_color(COLOR_LIGHTRED);
        } else {
        set_console_color(COLOR_LIGHTGREEN);
        }

        for(held; held > 0; --held) {
            cout << (char) 0xDB;
        }

        for(help; help > 0; --help) {
            cout << (char) 0;
        }
        set_console_color(COLOR_WHITE);
        cout << "| (" << Gob.hp << "/" << Gob.maxHP << ")" << endl;
    } else if(Flg.hud == 2) {
        heep = Gob.dp;
        hoop = Gob.maxDP;
        held = (heep / hoop) * 35;
        help = (35 - held) - 1;
        cout << " DP: |";
        set_console_color(COLOR_LIGHTBLUE);
        for(held; held > 0; --held) {
            cout << (char) 0xDB;
        }
        for(help; help > 0; --help) {
            cout << (char) 0;
        }
        set_console_color(COLOR_WHITE);
        cout << "| (" << Gob.dp << "/" << Gob.maxDP << ")" << endl;


    }
}

void eHud() {
    int tem; //this is gob.energy - 1 to print |
    int tom; // diff between tem to get invisible spaces
    tem = Gob.energy;
    tom = 3 - tem;
    cout << "Energy: {";
        if(tem == 3) {
            set_console_color(COLOR_LIGHTGREEN);
        } else if(tem == 2) {
            set_console_color(COLOR_YELLOW);
        } else {
            set_console_color(COLOR_LIGHTRED);
        }
        for(tem; tem >= 1; --tem) {
            cout << "|";
        }
        for(tom; tom >= 1; --tom) {
            cout << " ";
        }
        set_console_color(COLOR_WHITE);
        cout << "}\n" << endl;


}

void scav() {
    Flg.scavIn = true;
    int sc1;
    while(Flg.scavIn == true) {
    if(Flg.scavFirst == true) {
        system("cls");
        cout << "-*- SCAV PIT -*-\n\nA goblin(?) can scavenge at the scavenging pit right outside your beautiful house.\nThe capitalist basttards of Slorptee City dump all their garbage right outside of your cave hole.\nit Costs 1 energy to scavenge and find gold, potions, trash, or armed explosives!\nYou may scavenge at night by waiting (takes all your current energy) and you have the new Robbery option\n\nGood scavenging!" << endl;
        Flg.scavFirst = false;
        wait_enter();
    } else {
        system("cls");
        cout << "-*- SCAV PIT -*-" << endl;
        swapColor();
        cout << "1";
        swapColor();
        cout << ") Start Scavenging!" << endl;
        swapColor();
        cout << "2";
        swapColor();
        if(Flg.scavDay == true) {
        cout << ") Wait til Night.\n" << endl;
        } else if(Flg.scavDay == false) {
        cout << ") Do some Robbery.\n" << endl;
        }
        swapColor();
        cout << "3";
        swapColor();
        cout << ") Exit" << endl;
        eHud();
        sc1 = waitForKey();
        switch(sc1) {
            case 1:

            break;
            case 2:

            break;
            case 3:
                Flg.caveIn = false;
                cave();
            break;
        }
    }


    }
}


void cave()
{
    Flg.caveIn = true;
    int sc1; // input
    while(Flg.caveIn == true) { //this determines the week v day
        if(Flg.dayB >= 8) {
            Flg.dayB = 1;
            Flg.week = Flg.week + 1;
        }
    if(Flg.caveFirst == true) { //this is the first timne you enter the cave
        system("cls");
        cout << "-*- cave scene -*-\n  This is your goblin cave, " << Gob.name << " lives here! There is nothing out of the ordinary, because it's goblin stuff.\nIn your goblin cave, you can pass time, go scavenging, looting, killing, but you do have an energy meter to manage.\nIf your goblin's energy reaches 0/3, then your goblin will fall asleep when they return to the G-Cave\n\n   Goblin knowledge says that a Goblin Warrior named Drizzle Dum defeated the orc god Col, and left the world in ruin.\nThere are few days left in your goblin world, and there is a chance that if your goblin takes too long doing nothing..\n\nThe world may collapse.\n\nGo forth " << Gob.name << ", and prove to the world that you are a real goblin." << endl;
        wait_enter();
        Flg.caveFirst = false;
    } else if(Flg.caveIn = true) {
        system("cls");
        cout << "-*- goblin cave - Week " << Flg.week << ", Day " <<  Flg.dayB << " -*-\n"<< endl;
        swapColor();
        cout << "1";
        swapColor();
        cout << ") Travel\n";
        swapColor();
        cout << "2";
        swapColor();
        cout << ") Scavenge\n";
        swapColor();
        cout << "3";
        swapColor();
        cout << ") Pass Time\n";
        swapColor();
        cout << "4";
        swapColor();
        cout << ") Take Inventory\n\n";
        swapColor();
        cout << "5";
        swapColor();
        cout << ") Sleep\n\n\n\n-*- Stats -*-\n " << endl;
        eHud();
        Flg.hud = 1;
        hud();
        Flg.hud = 2;
        hud();
        cout << "\n " << Gob.name << " / Level: " << Gob.lvl << "\n Gold: " << Gob.gold << endl;
        sc1 = waitForKey();
        switch(sc1) {
            case 1:

            break;
            case 2:
                Flg.caveIn = false;
                scav();
            break;
            case 3:

            break;
            case 4:

            break;
            case 5:

            break;
            }
        }
    }
}

void superstart()
{
    int sc;
    int sc2;
    int sc3;
    int ssecret = 0;
    bool startdone = false;
    while(startdone == false) {
        ssecret = ssecret + 1;
        system("CLS");
        cout << "welcome to drozzle dim i will help you goblin THIS IS UPDATE .99 VERSION .99" << endl;
        swapColor();
        cout << "1";
        swapColor();
        cout << ") goblin name" << endl;
        swapColor();
        cout << "2";
        swapColor();
        cout << ") height!!" << endl;
        swapColor();
        cout << "3";
        swapColor();
        cout << ") weight!!" << endl;
        swapColor();
        cout << "4";
        swapColor();
        cout << ") girth." << endl;
        swapColor();
        cout << "5";
        swapColor();
        cout << ") age!!\n\n";
        swapColor();
        cout << "6";
        swapColor();
        cout << ") END IT!\n\n-*- your stupid stats -*-\ngoblin name: ";
        swapColor();
        cout << Gob.name;
        swapColor();
        cout << "\nheight: ";
        swapColor();
        cout << Gob.height;
        swapColor();
        cout << " feet\nweight: ";
        swapColor();
        cout << Gob.weight;
        swapColor();
        cout << " ponds \ngirth size >:) ";
        swapColor();
        cout << Gob.girth;
        swapColor();
        cout << " INCHy BIG\nage: ";
        swapColor();
        cout << Gob.age;
        swapColor();
        cout << " old" << endl;
        if(ssecret >= 10) {
            cout << "\n\n\nyou spend alot of time thinking about goblins..i cant help you though because that would be cheating\n if  you wanna know more how to beat the" << endl;
        }
        if(ssecret >= 50) {
            cout << "\n\nyou freaking suck" << endl;
        }
         if(ssecret >= 250) {
            cout << "\n\nTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN ANGRY GOBLIN ANGEyTGOBLIN " << endl;
        }
        int sc = waitForKey();
        switch(sc) {
            case 1:
            system("cls");
            cout << "whats your name space goblin boy\n (for inspiration use drizle dum.exe to figure out \n a good goblin name >:)-=" << endl;
            getline(cin, Gob.name);
            break;
            case 2:
            system("cls");
            cout << "your stinky goblin height reflects your defense and strength,. sucier with speed tho if big :p\n(enter numeral between 2 (small goblin) and 6 feet ( tall goblin)\n decimals make me mad!!" << endl;
            cin >> sc3;
            if(sc3 > 1 && sc3 < 7) {
                Gob.height = sc3;
            }
            break;
            case 3:
            system("cls");
            cout << "hehe,,, goblin is heavy!! ( defense big, strenght ok, speed and spell bad!! (big goblin bad channel magic)\n[YOU BETTER do 17 pound to 50 pound (HUGE GOBLIN)" << endl;
            cin >> sc3;
            if(sc3 > 16 && sc3 < 51) {
                Gob.weight = sc3;
            }
            break;
            case 4:
            system("cls");
            cout << "0 inches to 10 inches." << endl;
            cin >> sc3;
            if(sc3 > -1 && sc3 < 11) {
                Gob.girth = sc3;
            }
            break;
            case 5:
            system("cls");
            cout << "old goblin beetter with magic.. (age between 15 (teen goblin) 50 (daddy goblin)" << endl;
            cin >> sc3;
            if(sc3 > 14 && sc3 < 51) {
                Gob.age = sc3;
            }
            break;
            case 6:
                if(Gob.height == 0 || Gob.weight == 0 || Gob.age == 0 || Gob.girth < 0 || Gob.girth > 10) {
                system("cls");
                cout << "NO YOULL DIE!!!" << endl;
                wait_enter();
            } else {
                Gob.spd = 50 - (Gob.height * 3 + Gob.weight + Gob.age / 3) - Gob.girth / 5;
                Gob.def = 10 + (Gob.height * 5 + Gob.weight / 2) - Gob.age / 3;
                Gob.str = 5 + (Gob.weight * 2) - (Gob.height + Gob.age / 2);
                Gob.crt = Gob.age;
                if(Gob.age >= 30) {
                    Gob.pot = 1.25;
                } else if (Gob.age >= 40) {
                    Gob.pot = 1.5;
                } else if (Gob.age >= 45) {
                    Gob.pot = 1.75;
                }
                Gob.cool = Gob.spd + Gob.def + Gob.str + Gob.crt + Gob.pot;
                Gob.bro = Gob.girth * 10;
                Gob.maxHP = ((Gob.def + Gob.str + (Gob.spd / 5)) - Gob.age / 2) + Gob.bro;
                Gob.maxDP = Gob.age - (Gob.str / 2 + Gob.def / 3) + (Gob.bro / 2);
                statCheck();
                Gob.hp = Gob.maxHP;
                Gob.dp = Gob.maxDP;
                system("cls");
                cout << "now we learn about your goblin....\n\nSTRENGTH: ";
                swapColor();
                cout << Gob.str;
                swapColor();
                cout << "\nDEFENSE:  ";
                swapColor();
                cout << Gob.def;
                swapColor();
                cout << "\nSPEED:    ";
                swapColor();
                cout << Gob.spd;
                swapColor();
                cout << "\nCRIT %:   ";
                swapColor();
                cout << Gob.crt;
                swapColor();
                cout << "%\n\nMAX HP: ";
                swapColor();
                cout << Gob.maxHP;
                swapColor();
                cout << "\nMAX DP: ";
                swapColor();
                cout << Gob.maxDP;
                cout << "\n\n1";
                swapColor();
                cout << ") Yes, that is the perfect Goblin. Don't recommend me another Goblin ever again.\n";
                swapColor();
                cout << "2";
                swapColor();
                cout << ") Let me be free, go back@!!!!!!" << endl;
                sc3 = waitForKey();
                switch(sc3) {
                    case 1:
                        startdone = true;
                        cave();
                    break;
                }
            break;
        }
        }
    }


}



void swapColor()
{
	static bool accent = true;
	if (accent)
		SetConsoleTextAttribute(hConsole, Gob.ca);
	else
		SetConsoleTextAttribute(hConsole, Gob.co);
	accent = !accent;
}

int waitForKey()
{
	return _getch() - 48;
}

void wait_enter(void) //Method of wait_enter, call it to create a Press Enter to continue screen.
{
    cin.ignore();
    cout << "Press ENTER to continue...";
    cin.ignore();
}


void sout(string message, int delay, bool endline) // The REAL Sout method
{
    int start_delay = delay;
    for (int i = 0; i <= message.size(); ++i)
    {
        if (GetAsyncKeyState(VK_CONTROL) && 0x8000)
            delay = DEF_FAST_DELAY;
        else
            delay = start_delay;
        cout << message[i];
        Sleep(delay);
    }
    if (endline) cout << endl;
    else return;
}

int main()
{
    SetConsoleTitle("DrozzleDim");
    superstart();
    return 0;
}
