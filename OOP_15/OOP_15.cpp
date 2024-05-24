// OOP_14.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

class Animal {};

class Herbivore : public Animal {
protected:
    bool alive = true;
public:
    virtual bool IsAlive() { return alive; }
    virtual void EatGrass() {}
    virtual void Die() { alive = false; }
};

class Carnivore : public Animal {
public:
    virtual void Eat(Herbivore* herbivore) {}
};

class Continent {
public:
    virtual void Populate(vector<Herbivore*>& herbivores, vector<Carnivore*>& carnivores) = 0;
};

class Wildebeest : public Herbivore {
    int weight;
public:
    Wildebeest() : Wildebeest(25) {}

    Wildebeest(int weight) {
        SetWeight(weight);
    }

    void SetWeight(int weight) {
        this->weight = weight;
    }

    void EatGrass() override {
        weight += 10;
        cout << "Гну ест. Его вес: " << weight << "\n";
    }

    bool IsAlive() override {
        return weight > 0;
    }

    int GetWeight() const {
        return weight;
    }

    void Die() override {
        Herbivore::Die();
        weight = 0;
    }
};

class Lion : public Carnivore {
    int power;
public:
    Lion() : Lion(45) {}

    Lion(int power) {
        SetPower(power);
    }

    void SetPower(int power) {
        this->power = power;
    }

    void Eat(Herbivore* herbivore) override {
        Wildebeest* w = dynamic_cast<Wildebeest*>(herbivore);
        if (w && power > w->GetWeight()) {
            power += 10;
            w->Die();
            cout << "Лев ест гну. Его сила: " << power << "\n";
        }
        else {
            power -= 10;
            cout << "Лев не ест гну. Его сила: " << power << "\n";
        }
    }
};

class Bison : public Herbivore {
    int weight;
public:
    Bison() : Bison(40) {}

    Bison(int weight) {
        SetWeight(weight);
    }

    void SetWeight(int weight) {
        this->weight = weight;
    }

    void EatGrass() override {
        weight += 10;
        cout << "Бизон ест. Его вес: " << weight << "\n";
    }

    bool IsAlive() override {
        return weight > 0;
    }

    int GetWeight() const {
        return weight;
    }

    void Die() override {
        Herbivore::Die();
        weight = 0;
    }
};

class Wolf : public Carnivore {
    int power;
public:
    Wolf() : Wolf(50) {}

    Wolf(int power) {
        SetPower(power);
    }

    void SetPower(int power) {
        this->power = power;
    }

    void Eat(Herbivore* herbivore) override {
        Bison* b = dynamic_cast<Bison*>(herbivore);
        if (b && power > b->GetWeight()) {
            power += 10;
            b->Die();
            cout << "Волк ест бизона. Его сила: " << power << "\n";
        }
        else {
            power -= 10;
            cout << "Волк не ест бизона. Его сила: " << power << "\n";
        }
    }
};


class AnimalWorld {
    vector<Continent*> continents;
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
    ~AnimalWorld() {
        cout << "Мир животных разрушен\n";
        for (auto continent : continents) {
            delete continent;
        }
        for (auto herbivore : herbivores) {
            delete herbivore;
        }
        for (auto carnivore : carnivores) {
            delete carnivore;
        }
    }

    void AddContinent(Continent* continent) {
        continents.push_back(continent);
    }

    void PopulateWorld() {
        for (auto continent : continents) {
            continent->Populate(herbivores, carnivores);
        }
    }

    void MealsHerbivores() {
        cout << "Травоядные едят траву...\n";
        for (auto herbivore : herbivores) {
            if (herbivore->IsAlive()) {
                herbivore->EatGrass();
            }
        }
    }

    void NutritionCarnivores() {
        cout << "Хищники охотятся на травоядных...\n";
        for (auto carnivore : carnivores) {
            for (auto herbivore : herbivores) {
                if (herbivore->IsAlive()) {
                    carnivore->Eat(herbivore);
                }
            }
        }
    }
};

class Africa : public Continent {
public:
    void Populate(vector<Herbivore*>& herbivores, vector<Carnivore*>& carnivores) override {
        herbivores.push_back(new Wildebeest());
        carnivores.push_back(new Lion());
    }
};

class NorthAmerica : public Continent {
public:
    void Populate(vector<Herbivore*>& herbivores, vector<Carnivore*>& carnivores) override {
        herbivores.push_back(new Bison());
        carnivores.push_back(new Wolf());
    }
};


int main() {
    setlocale(0, "");
    AnimalWorld a;
    a.AddContinent(new Africa());
    a.AddContinent(new NorthAmerica());

    a.PopulateWorld();
    a.MealsHerbivores();
    a.NutritionCarnivores();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
