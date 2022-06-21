#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
protected:
    string name;

public:
    Player(string name) {
        setName(name);
    }
    string getName() {
        return this->name;
    }
    void setName(string name) {
        this->name = name;
    }

    void virtual showInfo() {
        cout << "名前: " << getName() << endl;
    }
};

class Solver : public Player {
private:
    int eat = 0;
    int bite = 0;

public:
    Solver(string name, int eat, int bite) : Player(name) {
        setEat(eat);
        setBite(bite);
    }
    int getEat() {
        return this->eat;
    }
    int getBite() {
        return this->bite;
    }
    void setEat(int eat) {
        if(eat < 0) {
            return;
        } else {
            this->eat = eat;
        }
    }
    void setBite(int bite) {
        if(bite < 0) {
            return;
        } else {
            this->bite = bite;
        }
    }
    int guess(int q_first, int q_second, int q_third) {
        int s_first, s_second, s_third;
        int turn = 0;

        while(this->getEat() != 3) {
            setEat(0);
            setBite(0);

            cout << "推測した数字を入力(1つ目): ";
            cin >> s_first;
            cout << "推測した数字を入力(2つ目): ";
            cin >> s_second;
            cout << "推測した数字を入力(3つ目): ";
            cin >> s_third;

            if(s_first == q_first) {
                this->eat++;
            } else if(s_first == q_second) {
                this->bite++;
            } else if(s_first == q_third) {
                this->bite++;
            }
            
            if(s_second == q_first) {
                this->bite++;
            } else if(s_second == q_second) {
                this->eat++;
            } else if(s_second == q_third) {
                this->bite++;
            }

            if(s_third == q_first) {
                this->bite++;
            } else if(s_third == q_second) {
                this->bite++;
            } else if(s_third == q_third) {
                this->eat++;
            }
            
            this->showInfo();

            turn++;
        }

        return turn;
    }
    void showInfo() override {
        string name = Player::getName();

        cout << "=========" << endl;
        cout << "Eat: " << getEat() << endl;
        cout << "Bite: " << getBite() << endl;
        cout << "=========" << endl;
    }
};

class Questioner : public Player {
private:
    int first;
    int second;
    int third;

public:
    Questioner(string name, int first, int second, int third) : Player(name) {
        setFirst(first);
        setSecond(second);
        setThird(third);
    }

    int getFirst() {
        return this->first;
    }
    int getSecond() {
        return this->second;
    }
    int getThird() {
        return this->third;
    }
    void setFirst(int first) {
        if(first < 0 || 10 < first) {
            return;
        } else {
            this->first = first;
        }
    }
    void setSecond(int second) {
        if(second < 0 || 10 < second) {
            return;
        } else {
            this->second = second;
        }
    }
    void setThird(int third) {
        if(third < 0 || 10 < third) {
            return;
        } else {
            this->third = third;
        }
    }

    void showInfo() override {
        string name = Player::getName();

        cout << "名前: " << name << endl;
        cout << "First: " << getFirst() << endl;
        cout << "Second: " << getSecond() << endl;
        cout << "Third: " << getThird() << endl;
    }
};

class CPU : public Questioner {
private:
    int first;
    int second;
    int third;

public:
    CPU() : Questioner(name, first, second, third) {
        setFirst();
        setSecond();
        setThird();
    }

    int getFirst() {
        return this->first;
    }
    int getSecond() {
        return this->second;
    }
    int getThird() {
        return this->third;
    }

    void setFirst() {
        this->first = (rand() % 9) + 1;
        // cout << "first" << this->first << endl;
    }
    void setSecond() {
        do {
            this->second = (rand() % 9) + 1;
        } while(second == first);
        // cout << "second" << this->second << endl;
    }
    void setThird() {
        do {
            this->third = (rand() % 9) + 1;
        } while(third == first);
        // cout << "third" << this->third << endl;
    }
};

void Game() {
    string s_name, q_name;
    int first, second, third;
    srand(time(NULL));

    cout << "解答者の名前を入力してください: ";
    cin >> s_name;
    Solver s = Solver(s_name, 0, 0);

    cout << "出題者の名前を入力してください: ";
    cin >> q_name;

    if(q_name == "cpu") {
        CPU c = CPU();
        cout << s.guess(c.getFirst(), c.getSecond(), c.getThird()) << "回かかりました！" << endl;
        cout << s.getName() <<  "さん正解です!" << endl;
    } else {
        cout << "1つ目の数字を入力(1〜9): ";
        cin >> first;
        cout << "2つ目の数字を入力(1〜9): ";
        cin >> second;
        cout << "3つ目の数字を入力(1〜9): ";
        cin >> third;

        system("clear");    //mac
        // system("cls");   //windows
        
        Questioner q = Questioner(q_name, first, second, third);

        cout << s.guess(first, second, third) << "回かかりました！" << endl;
        cout << s.getName() <<  "さん正解です!" << endl;
    }

};

int main() {
    Game();

    system("pause");        //windows

    return 0;
}
