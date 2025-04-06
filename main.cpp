#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Colony
{
public:
    int x, y, food, workers, warriors;
    string species;

    Colony(int x, int y, string species) : x(x), y(y), food(0), workers(0), warriors(0), species(species) {}

    void give_resources(const string& resource_type, int amount)
    {
        if (resource_type == "food")
        {
            food += amount;
            cout << "Gave " << amount << " food to colony " << species << endl;
        }
        else if (resource_type == "worker")
        {
            workers += amount;
            cout << "Gave " << amount << " workers to colony " << species << endl;
        }
        else if (resource_type == "warrior")
        {
            warriors += amount;
            cout << "Gave " << amount << " warriors to colony " << species << endl;
        }
        else
        {
            cout << "Unknown resource type!" << endl;
        }
    }

    void print_status() const
    {
        cout << "Colony Species: " << species << ", Position: (" << x << ", " << y << "), Food: "
             << food << ", Workers: " << workers << ", Warriors: " << warriors << endl;
    }

    string fight(const Colony& other)
    {
        stringstream summary;
        summary << "Fight Summary:\n";
        summary << species << " (Warriors: " << warriors << ") vs " << other.species << " (Warriors: " << other.warriors << ")\n";

        if (warriors > other.warriors)
        {
            summary << species << " wins the fight!\n";
        }
        else if (warriors < other.warriors)
        {
            summary << other.species << " wins the fight!\n";
        }
        else
        {
            summary << "It's a draw!\n";
        }
        return summary.str();
    }
};

class ColonyFactory
{
public:
    static unique_ptr<Colony> create_colony(int x, int y, const string& species)
    {
        return make_unique<Colony>(x, y, species);
    }
};

class AntFarm
{
private:
    unordered_map<int, unique_ptr<Colony>> colonies;
    int colony_id = 1;

    unordered_map<int, string> species_map = {
        {1, "Killer"}, {2, "Worker"}, {3, "Hunter"}, {4, "Scout"}, {5, "Defender"},
        {6, "Gatherer"}, {7, "Builder"}, {8, "Shaman"}, {9, "Protector"}, {10, "Warrior"},
        {11, "Explorer"}, {12, "Marauder"}, {13, "Champion"}, {14, "Strategist"}
    };

    AntFarm() {}

public:
    static AntFarm& get_instance()
    {
        static AntFarm instance;
        return instance;
    }

    void spawn_colony(int x, int y, int roll_number)
    {
        int species_number = (roll_number % 6) + 10; // Calculate species number as per requirement
        if (species_map.find(species_number) != species_map.end())
        {
            string species_name = species_map[species_number];
            colonies[colony_id] = ColonyFactory::create_colony(x, y, species_name);
            cout << "New colony spawned with species " << species_name << " at (" << x << ", " << y << ")." << endl;
            colony_id++;
        }
        else
        {
            cout << "Invalid species number!" << endl;
        }
    }

    void list_colonies() const
    {
        if (colonies.empty())
        {
            cout << "No colonies have been spawned yet." << endl;
        }
        else
        {
            cout << "List of Colonies:" << endl;
            for (const auto& colony : colonies)
            {
                colony.second->print_status();
            }
        }
    }

    void give_resources(int colony_id, const string& resource_type, int amount)
    {
        auto colony = colonies.find(colony_id);
        if (colony != colonies.end())
        {
            colony->second->give_resources(resource_type, amount);
        }
        else
        {
            cout << "Colony with ID " << colony_id << " not found!" << endl;
        }
    }

    void fight_colonies(int colony_id_1, int colony_id_2)
    {
        auto colony_1 = colonies.find(colony_id_1);
        auto colony_2 = colonies.find(colony_id_2);

        if (colony_1 != colonies.end() && colony_2 != colonies.end())
        {
            string result = colony_1->second->fight(*colony_2->second);
            cout << result << endl;

            colony_1->second->print_status();
            colony_2->second->print_status();
        }
        else
        {
            cout << "One or both colonies not found!" << endl;
        }
    }
};

class Command
{
public:
    virtual void execute() = 0;
};

class SpawnCommand : public Command
{
    int x, y, roll_number;
public:
    SpawnCommand(int x, int y, int roll_number) : x(x), y(y), roll_number(roll_number) {}

    void execute() override
    {
        AntFarm::get_instance().spawn_colony(x, y, roll_number);
    }
};

class ListCommand : public Command
{
public:
    void execute() override
    {
        AntFarm::get_instance().list_colonies();
    }
};

class GiveCommand : public Command
{
    int colony_id;
    string resource_type;
    int amount;
public:
    GiveCommand(int colony_id, string resource_type, int amount)
        : colony_id(colony_id), resource_type(resource_type), amount(amount) {}

    void execute() override
    {
        AntFarm::get_instance().give_resources(colony_id, resource_type, amount);
    }
};

class FightCommand : public Command
{
    int colony_id_1, colony_id_2;
public:
    FightCommand(int colony_id_1, int colony_id_2)
        : colony_id_1(colony_id_1), colony_id_2(colony_id_2) {}

    void execute() override
    {
        AntFarm::get_instance().fight_colonies(colony_id_1, colony_id_2);
    }
};

class CommandInvoker
{
    vector<shared_ptr<Command>> commands;
public:
    void add_command(shared_ptr<Command> command)
    {
        commands.push_back(command);
    }

    void execute_commands()
    {
        for (auto& command : commands)
        {
            command->execute();
        }
    }
};

int main()
{
    string command;
    CommandInvoker invoker;

    while (true)
    {
        cout << "Enter command: ";
        getline(cin, command);

        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "spawn")
        {
            int x, y, roll_number;
            iss >> x >> y >> roll_number;
            invoker.add_command(make_shared<SpawnCommand>(x, y, roll_number));
        }
        else if (cmd == "list_colonies")
        {
            invoker.add_command(make_shared<ListCommand>());
        }
        else if (cmd == "give")
        {
            int colony_id, amount;
            string resource_type;
            iss >> colony_id >> resource_type >> amount;
            invoker.add_command(make_shared<GiveCommand>(colony_id, resource_type, amount));
        }
        else if (cmd == "fight")
        {
            int colony_id_1, colony_id_2;
            iss >> colony_id_1 >> colony_id_2;
            invoker.add_command(make_shared<FightCommand>(colony_id_1, colony_id_2));
        }
        else if (cmd == "exit")
        {
            cout << "Exiting program..." << endl;
            break;
        }
        else
        {
            cout << "Unknown command!" << endl;
        }

        invoker.execute_commands();
        invoker = CommandInvoker();
    }

    return 0;
}
