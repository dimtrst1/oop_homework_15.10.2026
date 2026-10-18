#include <iostream>
using namespace std;

class Base
{
    static int people_on_base;
    static int vehicles_on_base;
    static double petrol_on_base;
    static double goods_on_base;
public:
    static int GetPeople() { return people_on_base; }
    static int GetVehicles() { return vehicles_on_base; }
    static double GetPetrol() { return petrol_on_base; }
    static double GetGoods() { return goods_on_base; }

    static void SetPeople(int amount)
    {
        if (amount >= 0)
        {
            people_on_base = amount;
        }
    }
    static void SetVehicles(int amount)
    {
        if (amount >= 0)
        {
            vehicles_on_base = amount;
        }
    }
    static void SetPetrol(double amount)
    {
        if (amount >= 0)
        {
            petrol_on_base = amount;
        }
    }
    static void SetGoods(double amount)
    {
        if (amount >= 0)
        {
            goods_on_base = amount;
        }
    }
    static void ShowBase()
    {
        cout << "People: " << people_on_base << endl;
        cout << "Vehicles: " << vehicles_on_base << endl;
        cout << "Petrol: " << petrol_on_base << " L" << endl;
        cout << "Goods: " << goods_on_base << " T" << endl;
        cout << endl;
    }
};

int Base::people_on_base = 200;
int Base::vehicles_on_base = 20;
double Base::petrol_on_base = 3000;
double Base::goods_on_base = 50;

class Vehicle
{
protected:
    double petrol;
    double maxPetrol;
public:
    Vehicle(double fuel, double capacity)
    {
        petrol = 0;
        maxPetrol = 50;
        if (fuel >= 0 && capacity >= 50 && fuel <= capacity)
        {
            petrol = fuel;
            maxPetrol = capacity;
        }
    }
    virtual bool Leave() = 0;
    virtual void Arrive() = 0;
    double GetPetrolAmount()
    {
        return petrol;
    }
    double GetTankVolume()
    {
        return maxPetrol;
    }
    virtual ~Vehicle()
    {
    }
};

class Bus : public Vehicle
{
    int people;
    int maxPeople;
public:
    Bus(int passengers, int seats, double fuel, double tank) : Vehicle(fuel, tank)
    {
        people = 0;
        maxPeople = 0;
        if (passengers >= 0 && seats >= passengers)
        {
            people = passengers;
            maxPeople = seats;
        }
    }
    int GetMaxPeople()
    {
        return maxPeople;
    }
    int GetPeopleCount()
    {
        return people;
    }
    void Arrive() override
    {
        Base::SetPeople(Base::GetPeople() + people + 1);
        Base::SetVehicles(Base::GetVehicles() + 1);
        cout << "Bus arrived. Passengers: " << people << endl;
        people = 0;
    }
    bool Leave() override
    {
        if (Base::GetPeople() < 1)
        {
            return false;
        }
        if (Base::GetVehicles() < 1)
        {
            return false;
        }
        double neededFuel = maxPetrol - petrol;
        if (Base::GetPetrol() < neededFuel)
        {
            return false;
        }
        int passengers = Base::GetPeople() - 1;
        if (passengers > maxPeople)
        {
            passengers = maxPeople;
        }
        Base::SetPeople(Base::GetPeople() - passengers - 1);
        Base::SetVehicles(Base::GetVehicles() - 1);
        Base::SetPetrol(Base::GetPetrol() - neededFuel);
        petrol = maxPetrol;
        people = passengers;
        cout << "Bus left. Passengers: " << people << endl;
        return true;
    }
};

class Truck : public Vehicle
{
    double load;
    double maxLoad;
public:
    Truck(double cargo, double capacity, double fuel, double tank) : Vehicle(fuel, tank)
    {
        load = 0;
        maxLoad = 1;
        if (cargo >= 0 && capacity >= 1 && cargo <= capacity)
        {
            load = cargo;
            maxLoad = capacity;
        }
    }
    double GetMaxLoad()
    {
        return maxLoad;
    }
    double GetCurrentLoad()
    {
        return load;
    }
    void Arrive() override
    {
        Base::SetGoods(Base::GetGoods() + load);
        Base::SetPeople(Base::GetPeople() + 1);
        Base::SetVehicles(Base::GetVehicles() + 1);
        cout << "Truck arrived. Goods: " << load << " T" << endl;
        load = 0;
    }
    bool Leave() override
    {
        if (Base::GetPeople() < 1)
        {
            return false;
        }
        if (Base::GetVehicles() < 1)
        {
            return false;
        }
        double neededFuel = maxPetrol - petrol;
        if (Base::GetPetrol() < neededFuel)
        {
            return false;
        }
        double cargo = Base::GetGoods();
        if (cargo > maxLoad)
        {
            cargo = maxLoad;
        }
        Base::SetGoods(Base::GetGoods() - cargo);
        Base::SetPeople(Base::GetPeople() - 1);
        Base::SetVehicles(Base::GetVehicles() - 1);
        Base::SetPetrol(Base::GetPetrol() - neededFuel);
        petrol = maxPetrol;
        load = cargo;
        cout << "Truck left. Goods: " << load << " T" << endl;
        return true;
    }
};

int main()
{
    Bus bus(1, 30, 50, 100);
    Truck truck(5, 10, 80, 200);
    Base::ShowBase();

    bus.Arrive();
    Base::ShowBase();

    truck.Arrive();
    Base::ShowBase();

    if (bus.Leave() == false)
    {
        cout << "Bus cannot leave" << endl;
    }
    Base::ShowBase();

    if (truck.Leave() == false)
    {
        cout << "Truck cannot leave" << endl;
    }
    Base::ShowBase();
}
