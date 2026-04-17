#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game_shared.h"
#include "player.h" // 假设里面有 updateAttributes 或类似修改属性的函数
using namespace std;

void setDifficulty(Player& p, int diffLevel) {
    switch(diffLevel) {
        case 1: // 简单
            p.strength = 80;
            p.intelligence = 80;
            p.health = 10;
            cout << "[系统] 难度：简单。祝你在这个岛上玩得愉快！" << endl;
            break;
        case 2: // 普通
            p.strength = 50;
            p.intelligence = 50;
            p.health = 8;
            cout << "[系统] 难度：普通。活下去，然后还债。" << endl;
            break;
        case 3: // 困难
            p.strength = 30;
            p.intelligence = 30;
            p.health = 5;
            cout << "[系统] 难度：困难。这几乎是不可能的任务。" << endl;
            break;
        default:
            // 防止输入错误，默认给普通
            p.strength = 50;
            p.intelligence = 50;
            p.health = 8;
    }
}

void updateAttributes(Player& p, int type, int amount) {
    // type: 1-血量, 2-武力, 3-智力, 4-金钱
    if (type == 1) { // 修改血量
        p.health += amount;
        if (p.health > 10) p.health = 10; // 封顶
        if (p.health < 0) p.health = 0;   // 保底
    } 
    else if (type == 2) { // 修改武力
        p.strength += amount;
        if (p.strength > 100) p.strength = 100;
        if (p.strength < 0) p.strength = 0;
    }
    else if (type == 3) { // 修改智力
        p.intelligence += amount;
        if (p.intelligence > 100) p.intelligence = 100;
        if (p.intelligence < 0) p.intelligence = 0;
    }
    else if (type == 4) { // 修改金钱
        p.money += amount;
        if (p.money < 0) p.money = 0; // 钱不能是负数（虽然欠债，但现款不能负）
    }
}


void hunt(Player& p) {
    // --- 1. 初始化怪物数据 (保留原逻辑) ---
    int monsterStr = (rand() % 31 + 20) + (p.currentDay * 3);
    int monsterHP = 50 + (p.currentDay * 5);
    bool isWeakened = false; // 破绽标记
    
    cout << "\n======== ⚔️ ENTER COMBAT ZONE ========" << endl;
    cout << "Target: Island Predator | Strength: " << monsterStr << " | HP: " << monsterHP << endl;

    // --- 2. 战斗主循环 ---
    while (monsterHP > 0 && p.health > 0) {
        // [新增] 动态意图生成
        int monsterIntent = rand() % 3; // 0: Normal, 1: Heavy, 2: Rest
        bool isTrap = false;
        
        // [新增] 假动作逻辑：如果随机到休息，25% 概率是陷阱
        if (monsterIntent == 2 && (rand() % 100 < 25)) {
            isTrap = true;
        }

        // [新增] 狂暴判定：血量低于 30%，怪物变得疯狂
        bool isEnraged = (monsterHP < (50 + p.currentDay * 5) * 0.3);

        cout << "\n--------------------------------" << endl;
        cout << "[STATUS] Health: " << p.health << " | Strength: " << p.strength << " | Intel: " << p.intelligence << endl;
        
        // --- [核心改变] 信息不对称显示系统 ---
        cout << "[INTEL] ";
        // 智力判定：决定信息的透明度
        bool seeTruth = (p.intelligence + rand() % 40) > 55;

        if (isEnraged) {
            cout << "⚠️ WARNING: The predator is ENRAGED! It's giving up defense for pure slaughter!" << endl;
            if (monsterIntent == 2) monsterIntent = 0; // 狂暴后不再真正休息
        } else if (seeTruth) {
            // 高智力/运气好：看穿真相
            if (isTrap) cout << "👁️ Your keen eyes detect a fake opening! The beast is LURING you to attack while pretending to rest!";
            else if (monsterIntent == 1) cout << "⚠️ High Alert: The beast is tensing its muscles for a CRUSHING strike!";
            else if (monsterIntent == 2) cout << "💤 Opportunity: The beast is truly exhausted and trying to catch its breath.";
            else cout << "💢 Combat: The predator is preparing a standard claw attack.";
        } else {
            // 低智力/运气差：模糊叙述
            if (monsterIntent == 1 || isTrap) cout << "❓ You sense a strange aura... the predator is making a big move, be careful!";
            else cout << "💢 The predator is staring at you with bloodshot eyes.";
        }
        cout << endl;

        cout << "Command: 1.Attack 2.Analyze 3.Defend 4.Flee" << endl;
        cout << "Action >> ";
        int action; cin >> action;

        // --- 3. 玩家行动逻辑 (保留核心，加入陷阱反馈) ---
        if (action == 1) { // 普通攻击
            int damage = (p.strength / 5) + (rand() % 5);
            if (isWeakened) {
                damage *= 2; 
                isWeakened = false;
                cout << "✨ EXPLOTING WEAKNESS! You dealt " << damage << " damage!" << endl;
            } else if (isTrap) {
                // [新增] 踩中陷阱：伤害减半，且怪物反击
                damage /= 2;
                cout << "💀 IT'S A TRAP! The beast was faking! Your attack was deflected!" << endl;
            } else {
                cout << "You struck the beast for " << damage << " damage!" << endl;
            }
            monsterHP -= damage;
        } 
        else if (action == 2) { // 寻找破绽 (智力流)
            if ((p.intelligence + rand() % 30) > (monsterStr / 2)) {
                isWeakened = true;
                cout << "💡 INSIGHT! You found a gap in its scales! Double damage next turn!" << endl;
            } else {
                cout << "❌ Failure. You couldn't find any opening." << endl;
            }
        }
        else if (action == 3) { // 格挡
            cout << "🛡️ You raise your arms, bracing for the impact." << endl;
        }
        else if (action == 4) { // 逃跑
            if (rand() % 100 < (60 + p.intelligence / 4)) {
                cout << "🏃 You narrowly escaped the predator's territory!" << endl;
                return;
            } else {
                cout << "🚫 Escape blocked! The predator cut off your path!" << endl;
            }
        }

        // --- 4. 怪物反击逻辑 (包含陷阱惩罚) ---
        if (monsterHP > 0) {
            int m_damage = (monsterStr / 8) + (rand() % 3);
            
            if (isTrap && action == 1) {
                // 陷阱触发：怪物趁你攻击时反击，伤害极高
                m_damage *= 2.5; 
                cout << "💥 COUNTER-STRIKE! The predator lunges at your throat!" << endl;
            } else if (isEnraged) {
                m_damage *= 1.5; // 狂暴加成
            } else if (monsterIntent == 1) {
                m_damage *= 2; // 重击加成
            } else if (monsterIntent == 2 && !isTrap) {
                m_damage = 0; // 真正休息
            }

            if (action == 3) { // 格挡修正
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

    // --- 5. 战斗结果结算 (保留原逻辑) ---
    if (p.health <= 0) {
        cout << "\n💀 WASTED... The island has claimed another soul." << endl;
    } else {
        int gain = monsterStr * 1000 + (rand() % 5000);
        p.money += gain;
        int recovery = (p.intelligence / 40); 
        p.health = (p.health + recovery > 10) ? 10 : (p.health + recovery);
        
        cout << "\n✌️ VICTORY!" << endl;
        cout << "Gained Blood(Money): " << gain << endl;
        if (recovery > 0) cout << "You treated your wounds with wisdom, recovering " << recovery << " HP." << endl;
    }
}

// 提示：itemID 0-2 假设为基础道具，ItemID 3 以上为实验室高级道具
// 如果你的 addItem 函数名不同，请自行替换
void helpVillager(Player& p) {
    cout << "\n==========================================" << endl;
    cout << "        LOCATION: SURVIVAL EXPLORATION     " << endl;
    cout << "==========================================" << endl;

    // --- 1. 场景解锁与自主选择菜单 ---
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

    // --- 2. 权限校验 ---
    if ((sceneChoice == 2 && p.intelligence < 40) || (sceneChoice == 3 && p.intelligence < 70)) {
        cout << "\n[!] Access Denied: Your Intelligence is too low to understand this place." << endl;
        return;
    }
    if (sceneChoice < 1 || sceneChoice > 3) {
        cout << "[!] Invalid choice." << endl;
        return;
    }

    // --- 3. 20% 概率触发“运气事件” (Wildcard Events) ---
    if (rand() % 100 < 20) {
        int eventType = rand() % 3;
        if (eventType == 0) {
            cout << "\n[LUCKY] You found a lost wallet buried in the sand!" << endl;
            cout << "Result: +15,000 Money." << endl;
            p.money += 15000;
        } else if (eventType == 1) {
            cout << "\n[EVENT] A mysterious scavenger offers you a 'Strange Pill'." << endl;
            cout << "Spend 10,000 Money for a 50% chance to gain 10 Strength? (1.Yes / 2.No): ";
            int buy; cin >> buy;
            if (buy == 1 && p.money >= 10000) {
                p.money -= 10000;
                if (rand() % 2 == 0) {
                    p.strength += 10;
                    cout << ">> Success! Your muscles feel like iron." << endl;
                } else {
                    p.health -= 1;
                    cout << ">> It was expired! You feel sick. (Health -1)" << endl;
                }
            }
        } else {
            cout << "\n[EVENT] You found a peaceful spot and took a long nap." << endl;
            cout << "Result: Health restored by 1, and you found an old bandage (Item+)." << endl;
            p.health = (p.health + 1 > 10) ? 10 : p.health + 1;
            // 运气事件白送道具
            addItem(p, rand() % 3); 
        }
        return; 
    }

    // --- 4. 正常任务逻辑：多题库、动态数值、道具掉落 ---
    if (sceneChoice == 1) {
        // --- 场景 A：日常修炼 (难度随次数递增) ---
        p.countA++; 
        int n1 = rand() % 10 + 1, n2 = rand() % 10 + 1, n3 = rand() % 5 + 1;
        int userAnswer;
        bool correct = false;

        if (p.countA <= 5) {
            cout << "\n[TRAINING - LV 1] Quick Math: " << n1 << " + " << n2 << " = ?" << endl;
            cin >> userAnswer;
            if (userAnswer == (n1 + n2)) {
                cout << ">> Correct! Intelligence +1, Money +5,000." << endl;
                p.intelligence += 1; p.money += 5000; correct = true;
            }
        } 
        else if (p.countA <= 12) {
            cout << "\n[TRAINING - LV 2] Solve: " << n1 << " + " << n2 << " * " << n3 << " = ?" << endl;
            cin >> userAnswer;
            if (userAnswer == (n1 + n2 * n3)) {
                cout << ">> Well done! Intelligence +2, Money +8,000." << endl;
                p.intelligence += 2; p.money += 8000; correct = true;
            }
        } 
        else {
            cout << "\n[TRAINING - LV 3] Mastermind: (" << n1 << " + " << n2 << ") * " << n3 << " = ?" << endl;
            cin >> userAnswer;
            if (userAnswer == ((n1 + n2) * n3)) {
                cout << ">> Perfect! Intelligence +3, Money +12,000." << endl;
                p.intelligence += 3; p.money += 12000; correct = true;
            }
        }
        // 场景 A 答对后 10% 概率给基础小道具
        if (correct && (rand() % 10 == 0)) {
            cout << "[BONUS] You found a small tool during training!" << endl;
            addItem(p, 0); 
        }
    } 
    else if (sceneChoice == 2) {
        // --- 场景 B：土著试炼 (随机三题库) ---
        int questID = rand() % 3;
        int userChoice;
        bool correct = false;
        switch(questID) {
            case 0:
                cout << "\n[ALTAR] Shaman asks: 'What is the index of the FIRST element in a C++ array?'" << endl;
                cout << "1. [1] \n2. [0] \n3. [-1]" << endl;
                cin >> userChoice; if (userChoice == 2) correct = true;
                break;
            case 1:
                cout << "\n[ALTAR] Shaman asks: 'Which operator is used to access members of a struct via a POINTER?'" << endl;
                cout << "1. . (Dot) \n2. -> (Arrow) \n3. & (Ampersand)" << endl;
                cin >> userChoice; if (userChoice == 2) correct = true;
                break;
            case 2:
                cout << "\n[ALTAR] Shaman asks: 'Which header is required for using rand() and srand()?'" << endl;
                cout << "1. <iostream> \n2. <cmath> \n3. <cstdlib>" << endl;
                cin >> userChoice; if (userChoice == 3) correct = true;
                break;
        }

        if (correct) {
            cout << ">> Wise! +30,000 Money." << endl;
            p.money += 30000;
            // 场景 B 答对后 30% 概率给道具
            if (rand() % 10 < 3) {
                cout << "[BONUS] The Shaman gives you a Tribal Relic (Item added)!" << endl;
                addItem(p, rand() % 3); 
            }
        } else cout << ">> The Shaman is disappointed. No reward." << endl;
    } 
    else if (sceneChoice == 3) {
        // --- 场景 C：失落实验室 (随机三题库，含动态地址题) ---
        int questID = rand() % 3;
        bool solved = false;
        int labAns;

        switch(questID) {
            case 0:
                cout << "\n[LAB] System Check: 'How do you correctly dynamically allocate an integer array of size 10?'" << endl;
                cout << "1. int arr[10]; \n2. int* arr = new int[10]; \n3. malloc(10);" << endl;
                cin >> labAns; if (labAns == 2) solved = true;
                break;
            case 1:
                cout << "\n[LAB] System Check: 'Which of the following releases memory allocated by new int[5]?'" << endl;
                cout << "1. delete arr; \n2. delete[] arr; \n3. free(arr);" << endl;
                cin >> labAns; if (labAns == 2) solved = true;
                break;
            case 2:
                int base = (rand() % 100) * 10;
                cout << "\n[LAB] Memory Offset Calculation: \nArray 'a' starts at address " << base << ". Each int is 4 bytes. \nWhat is the address of a[2]?" << endl;
                cin >> labAns; if (labAns == (base + 2 * 4)) solved = true;
                break;
        }

        if (solved) {
            cout << "\n[ACCESS GRANTED] Terminal Unlocked." << endl;
            // 场景 C 答对必给一个高级道具，作为通过硬核测试的奖励
            cout << "[BONUS] System ejects an Experimental Supply (Item added)!" << endl;
            addItem(p, 4); 

            cout << "\n--- Choose Modification ---" << endl;
            cout << "1. [Body Boost]     Spend 150,000 Money -> +20 Strength" << endl;
            cout << "2. [Mind Overload]  Spend 150,000 Money -> +20 Intelligence" << endl;
            cout << "3. [DNA-Swap]       Sacrifice 15 Intelligence -> Gain 25 Strength" << endl;
            cout << "4. [Exit]" << endl;
            
            int labAction; cin >> labAction;
            switch (labAction) {
                case 1:
                    if (p.money >= 150000) { p.money -= 150000; p.strength += 20; cout << "Upgrade Complete." << endl; }
                    else cout << "Insufficient funds!" << endl;
                    break;
                case 2:
                    if (p.money >= 150000) { p.money -= 150000; p.intelligence += 20; cout << "Upgrade Complete." << endl; }
                    else cout << "Insufficient funds!" << endl;
                    break;
                case 3:
                    if (p.intelligence >= 15) { p.intelligence -= 15; p.strength += 25; cout << "Swap Complete." << endl; }
                    else cout << "Intelligence too low!" << endl;
                    break;
                default: cout << "Exiting terminal..." << endl; break;
            }
        } else {
            cout << "\n[ERROR] Access Denied. Security system activated! Electrical shock!" << endl;
            p.health -= 2;
        }
    }
    cout << "==========================================\n" << endl;
}