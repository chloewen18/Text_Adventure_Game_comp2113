#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game_shared.h"
#include "player.h" 
using namespace std;

void setDifficulty(Player& p, int diffLevel) {

    switch(diffLevel) {
        case 1: 
            p.strength = 40;   
            p.intelligence = 40; 
            p.health = 120;     
            cout << "\n[SYSTEM] Difficulty: EASY" << endl;
            cout << ">> 'The lender is distracted, but 3000 gold is still a mountain.'" << endl;
            cout << ">> 'You have 5 DAYS. Make every strike count, traveler!'" << endl;
            break;

        case 2: 
            p.strength = 30;    
            p.intelligence = 30; 
            p.health = 100;      
            cout << "\n[SYSTEM] Difficulty: NORMAL" << endl;
            cout << ">> 'The town lender is watching your every move...'" << endl;
            cout << ">> '3000 gold in 5 DAYS? Repay it, or face ETERNAL EXILE!'" << endl;
            break;

        default:
            // Default to Normal
            p.strength = 30;
            p.intelligence = 30;
            p.health = 100;
    }
}

void hunt(Player& p) {
    int monsterStr = 20 + (p.currentDay * 5); 
    int monsterHP = 60 + (p.currentDay * 15); 
    bool isWeakened = false; 
    
    cout << "\n======== ⚔️ ENTER COMBAT ZONE ========" << endl;
    cout << "Target: Island Predator | Strength: " << monsterStr << " | HP: " << monsterHP << endl;

    while (monsterHP > 0 && p.health > 0) {
        int monsterIntent = rand() % 3; 
        bool isTrap = false;
        
        if (monsterIntent == 2 && (rand() % 100 < 25)) {
            isTrap = true;
        }

        bool isEnraged = (monsterHP < (60 + p.currentDay * 15) * 0.3);

        cout << "\n--------------------------------" << endl;
        cout << "[STATUS] Health: " << p.health << " | Strength: " << p.strength << " | Intel: " << p.intelligence << endl;
        
        cout << "[INTEL] ";
        bool seeTruth = (p.intelligence + rand() % 40) > 55;

        if (isEnraged) {
            cout << "⚠️ WARNING: The predator is ENRAGED! It's giving up defense for pure slaughter!" << endl;
            if (monsterIntent == 2) monsterIntent = 0; 
        } else if (seeTruth) {
            if (isTrap) cout << "👁️ Your keen eyes detect a fake opening! The beast is LURING you to attack while pretending to rest!";
            else if (monsterIntent == 1) cout << "⚠️ High Alert: The beast is tensing its muscles for a CRUSHING strike!";
            else if (monsterIntent == 2) cout << "💤 Opportunity: The beast is truly exhausted and trying to catch its breath.";
            else cout << "💢 Combat: The predator is preparing a standard claw attack.";
        } else {
            if (monsterIntent == 1 || isTrap) cout << "❓ You sense a strange aura... the predator is making a big move, be careful!";
            else cout << "💢 The predator is staring at you with bloodshot eyes.";
        }
        cout << endl;

        cout << "Command: 1.Attack 2.Analyze 3.Defend 4.Flee" << endl;
        cout << "Action >> ";
        int action; cin >> action;

        if (action == 1) { 
            int damage = (p.strength * 0.7) + (rand() % 10); 
            if (isWeakened) {
                damage *= 2; 
                isWeakened = false;
                cout << "✨ EXPLOTING WEAKNESS! You dealt " << damage << " damage!" << endl;
            } else if (isTrap) {
                damage /= 2;
                cout << "💀 IT'S A TRAP! The beast was faking! Your attack was deflected!" << endl;
            } else {
                cout << "You struck the beast for " << damage << " damage!" << endl;
            }
            monsterHP -= damage;
        } 
        else if (action == 2) { 
            if ((p.intelligence + rand() % 30) > (monsterStr / 2)) {
                isWeakened = true;
                cout << "💡 INSIGHT! You found a gap in its scales! Double damage next turn!" << endl;
            } else {
                cout << "❌ Failure. You couldn't find any opening." << endl;
            }
        }
        else if (action == 3) { 
            cout << "🛡️ You raise your arms, bracing for the impact." << endl;
        }
        else if (action == 4) { 
            if (rand() % 100 < (60 + p.intelligence / 4)) {
                cout << "🏃 You narrowly escaped the predator's territory!" << endl;
                return;
            } else {
                cout << "🚫 Escape blocked! The predator cut off your path!" << endl;
            }
        }

        if (monsterHP > 0) {
            int m_damage = (monsterStr * 0.3) + (rand() % 3);
            
            if (isTrap && action == 1) {
                m_damage *= 2.5; 
                cout << "💥 COUNTER-STRIKE! The predator lunges at your throat!" << endl;
            } else if (isEnraged) {
                m_damage *= 1.5; 
            } else if (monsterIntent == 1) {
                m_damage *= 2; 
            } else if (monsterIntent == 2 && !isTrap) {
                m_damage = 0; 
            }

            if (action == 3) { 
                m_damage /= 3;
                cout << "🛡️ BLOCK! You minimized the damage." << endl;
            }

            if (m_damage > 0) {
                p.health -= m_damage;
                cout << "🩸 The predator gashes you, dealing " << m_damage << " damage!" << endl;
            } else if (monsterIntent == 2 && !isTrap) {
                cout << "🍃 The beast is panting, giving you a brief moment of peace." << endl;
            }
        }
    }

    if (p.health <= 0) {
        cout << "\n💀 WASTED... The island has claimed another soul." << endl;
    } else {
        int gain = (monsterStr * 8) + (rand() % 51 + 50); 
        p.money += gain;
        
        int recovery = (p.intelligence / 5); 
        p.health = (p.health + recovery > 120) ? 120 : (p.health + recovery);
        
        cout << "\n✌️ VICTORY!" << endl;
        cout << "Gained Blood(Money): " << gain << endl;
        if (recovery > 0) cout << "You treated your wounds with wisdom, recovering " << recovery << " HP." << endl;
        
        if (rand() % 10 < 3) {
            addItem(p, 0);
            cout << "[DROP] The predator dropped a Bandage!" << endl;
        }
    }
}

void helpVillager(Player& p) {
    cout << "\n==========================================" << endl;
    cout << "        LOCATION: SURVIVAL EXPLORATION     " << endl;
    cout << "==========================================" << endl;

    cout << "Choose a location to explore:" << endl;
    cout << "1. [Shallow Beach]   - Always Available (Daily Training)" << endl;
    
    if (p.intelligence >= 40) 
        cout << "2. [Tribal Altar]    - Unlocked (Logic Test)" << endl;
    else 
        cout << "2. [Tribal Altar]    - [LOCKED] (Requires 40 Intelligence)" << endl;

    if (p.intelligence >= 70)
        cout << "3. [Lost Laboratory] - Unlocked (Advanced Modification)" << endl;
    else 
        cout << "3. [Lost Laboratory] - [LOCKED] (Requires 70 Intelligence)" << endl;

    int sceneChoice;
    cout << "\nYour Choice: ";
    cin >> sceneChoice;

    if ((sceneChoice == 2 && p.intelligence < 40) || (sceneChoice == 3 && p.intelligence < 70)) {
        cout << "\n[!] Access Denied: Your Intelligence is too low to understand this place." << endl;
        return;
    }
    if (sceneChoice < 1 || sceneChoice > 3) {
        cout << "[!] Invalid choice." << endl;
        return;
    }

    if (rand() % 100 < 20) {
        int eventType = rand() % 3;
        if (eventType == 0) {
            cout << "\n[LUCKY] You found a lost wallet buried in the sand!" << endl;
            cout << "Result: +150 Money." << endl;
            p.money += 150;
        } else if (eventType == 1) {
            cout << "\n[EVENT] A mysterious scavenger offers you a 'Strange Pill'." << endl;
            cout << "Spend 100 Money for a 50% chance to gain 10 Strength? (1.Yes / 2.No): ";
            int buy; cin >> buy;
            if (buy == 1) {
                if (p.money >= 100) {
                    p.money -= 100;
                    if (rand() % 2 == 0) {
                        p.strength += 10;
                        cout << ">> Success! Your muscles feel like iron." << endl;
                    } else {
                        p.health -= 5; 
                        cout << ">> It was expired! You feel sick. (Health -5)" << endl;
                    }
                } else {
                    cout << ">> Scavenger: 'No money, no deal!' He walks away." << endl;
                }
            }
        } else {
            cout << "\n[EVENT] You found a peaceful spot and took a long nap." << endl;
            cout << "Result: Health restored by 15, and you found an old bandage (Item+)." << endl;
            p.health = (p.health + 15 > 120) ? 120 : p.health + 15;
            addItem(p, 0); 
        }
        return; 
    }

    if (sceneChoice == 1) {
        p.countA++; 
        int n1 = rand() % 10 + 1, n2 = rand() % 10 + 1, n3 = rand() % 5 + 1;
        int userAnswer;
        bool correct = false;

        if (p.countA <= 5) {
            cout << "\n[TRAINING - LV 1] Quick Math: " << n1 << " + " << n2 << " = ?" << endl;
            cin >> userAnswer;
            if (userAnswer == (n1 + n2)) {
                cout << ">> Correct! Intelligence +5, Money +200." << endl;
                p.intelligence += 5; p.money += 200; correct = true;
            } else { cout << ">> Wrong answer! No gains this time." << endl; }
        } 
        else if (p.countA <= 12) {
            cout << "\n[TRAINING - LV 2] Solve: " << n1 << " + " << n2 << " * " << n3 << " = ?" << endl;
            cin >> userAnswer;
            if (userAnswer == (n1 + n2 * n3)) {
                cout << ">> Well done! Intelligence +5, Money +200." << endl;
                p.intelligence += 5; p.money += 200; correct = true;
            } else { cout << ">> Wrong answer! No gains this time." << endl; }
        } 
        else {
            cout << "\n[TRAINING - LV 3] Mastermind: (" << n1 << " + " << n2 << ") * " << n3 << " = ?" << endl;
            cin >> userAnswer;
            if (userAnswer == ((n1 + n2) * n3)) {
                cout << ">> Perfect! Intelligence +5, Money +200." << endl;
                p.intelligence += 5; p.money += 200; correct = true;
            } else { cout << ">> Wrong answer! No gains this time." << endl; }
        }
        if (correct && (rand() % 10 == 0)) {
            cout << "[BONUS] You found a small tool during training!" << endl;
            addItem(p, 0); 
        }
    } 
    else if (sceneChoice == 2) {
        int questID = rand() % 3;
        int userChoice;
        bool correct = false;
        switch(questID) {
            case 0:
                cout << "\n[ALTAR] ... 'What is index of FIRST element?'" << endl;
                cout << "1. [1] \n2. [0] \n3. [-1]" << endl;
                cin >> userChoice; if (userChoice == 2) correct = true;
                break;
            case 1:
                cout << "\n[ALTAR] ... 'Access struct via POINTER?'" << endl;
                cout << "1. . \n2. -> \n3. &" << endl;
                cin >> userChoice; if (userChoice == 2) correct = true;
                break;
            case 2:
                cout << "\n[ALTAR] ... 'Required for rand()?'" << endl;
                cout << "1. <iostream> \n2. <cmath> \n3. <cstdlib>" << endl;
                cin >> userChoice; if (userChoice == 3) correct = true;
                break;
        }

        if (correct) {
            cout << ">> Wise! +50,000 Money and +15 Intelligence." << endl;
            p.money += 50000; p.intelligence += 15;
            if (rand() % 10 < 3) {
                cout << "[BONUS] Tribal Relic added!" << endl;
                addItem(p, rand() % 3); 
            }
        } else cout << ">> The Shaman is disappointed. No reward." << endl;
    } 
    else if (sceneChoice == 3) {
        int questID = rand() % 3;
        bool solved = false;
        int labAns;

        switch(questID) {
            case 0:
                cout << "\n[LAB] ... 'Dynamically allocate array of 10?'" << endl;
                cout << "1. int arr[10]; \n2. int* arr = new int[10]; \n3. malloc(10);" << endl;
                cin >> labAns; if (labAns == 2) solved = true;
                break;
            case 1:
                cout << "\n[LAB] ... 'Release memory of new int[5]?'" << endl;
                cout << "1. delete arr; \n2. delete[] arr; \n3. free(arr);" << endl;
                cin >> labAns; if (labAns == 2) solved = true;
                break;
            case 2:
                int base = (rand() % 100) * 10;
                cout << "\n[LAB] Memory Offset: a starts at " << base << ". What is a[2] (int=4b)?" << endl;
                cin >> labAns; if (labAns == (base + 2 * 4)) solved = true;
                break;
        }

        if (solved) {
            cout << "\n[ACCESS GRANTED] Terminal Unlocked." << endl;
            addItem(p, 4); 

            cout << "\n--- Choose Modification ---" << endl;
            cout << "1. [Body Boost]     Spend 150,000 Money -> +30 Strength" << endl;
            cout << "2. [Mind Overload]  Spend 150,000 Money -> +30 Intelligence" << endl;
            cout << "3. [DNA-Swap]       Sacrifice 20 Intelligence -> Gain 30 Strength" << endl;
            cout << "4. [Exit]" << endl;
            
            int labAction; cin >> labAction;
            switch (labAction) {
                case 1: 
                    if (p.money >= 1500) { p.money -= 1500; p.strength += 30; cout << "Upgrade Complete." << endl; }
                    else cout << "Insufficient funds!" << endl;
                    break;
                case 2: 
                    if (p.money >= 1500) { p.money -= 1500; p.intelligence += 30; cout << "Upgrade Complete." << endl; }
                    else cout << "Insufficient funds!" << endl;
                    break;
                case 3: 
                    if (p.intelligence >= 20) { p.intelligence -= 20; p.strength += 30; cout << "Swap Complete." << endl; }
                    else cout << "Intelligence too low!" << endl;
                    break;
                default: cout << "Exiting..." << endl; break;
            }
        } else {
            cout << "\n[ERROR] Access Denied. Electrical shock!" << endl;
            p.health -= 15;
        }
    }
    cout << "==========================================\n" << endl;
}
