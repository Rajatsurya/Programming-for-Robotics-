#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// holds entries with int key and string values
class Table
{
    // you'll probably want use to use std::pair
    // you will need to make some methods const since they'll be used in processSentence which requires a const Table
    // --- Your code here

    // constructor
public:
    Table() {};
    Table(const std::vector<std::pair<int, std::string>> &entries);
    Table(const std::initializer_list<std::pair<int, std::string>> &entries);

    std::string get(int key) const;

    void add(int key, std::string value);

    std::vector<std::pair<int, std::string>> getEntries() const
    {
        return _entries;
    }

private:
    std::vector<std::pair<int, std::string>> _entries;
};

std::string processSentence(const Table &t, const std::vector<int> &keySequence)
{
    std::string ret = "";
    for (int key : keySequence)
    {
        // should return " " if it's not in the table, otherwise it should return the value
        ret += t.get(key);
    }
    return ret;
}

Table::Table(const std::initializer_list<std::pair<int, std::string>> &entries)
{

    for (const std::pair<int, std::string> &entry : entries)
    {
        _entries.push_back(entry);
    }
}

Table::Table(const std::vector<std::pair<int, std::string>> &entries)
{
    for (const std::pair<int, std::string> &entry : entries)
    {
        _entries.push_back(entry);
    }
}

Table updateTable(const Table &t1, const Table &t2)
{

    std::vector<std::pair<int, std::string>> updatedEntriesVector;

    // fill out the vector with t2 values
    for (const std::pair<int, std::string> &entry : t2.getEntries())
    {
        updatedEntriesVector.push_back(entry);
    }

    // fill out the vector with t1 values that are not in t2
    for (const std::pair<int, std::string> &entry : t1.getEntries())
    {
        bool entryExists = false;

        for (std::pair<int, std::string> &entry2 : updatedEntriesVector)
        {
            if (entry.first == entry2.first)
            {
                entryExists = true;
                break;
            }
        }

        if (!entryExists)
        {
            updatedEntriesVector.push_back(entry);
        }
    }

    return Table(updatedEntriesVector);
}

std::string Table::get(int key) const
{
    for (const std::pair<int, std::string> &entry : _entries)
    {
        if (entry.first == key)
        {
            return entry.second;
        }
    }

    return " ";
}

Table filterOutOddKeys(const Table &t)
{
    Table filtered;

    for (const std::pair<int, std::string> &entry : t.getEntries())
    {
        if (entry.first % 2 == 0)
        {
            filtered.add(entry.first, entry.second);
        }
    }

    return filtered;
}

void Table::add(int key, std ::string value)
{

    std::pair<int, std::string> new_entry = {key, value};

    // checking for duplicate keys
    for (std::pair<int, std::string> &entry : _entries)
    {
        if (entry.first == key)
        {
            if (entry.second != value)
            {
                throw std::runtime_error("Duplicate keys. The key is already taken!");
            }

            return;
        }
    }

    _entries.push_back({key, value});
}

int main(int argc, char *argv[])
{
    // figure out what constructor allows for this initialization
    // since this table is const, the functions you implement that use it must also take in a const table
    const Table t1{{
        {1, "alpha"},
        {2, "beta"},
        {3, "gamma"},
        {4, "delta"},
    }};
    Table t2;

    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    // should output "alphagamma delta" (without parenthesis)
    output << processSentence(t1, {1, 3, 5, 4}) << std::endl;

    while (input.peek() != std::ifstream::traits_type::eof())
    {
        int key;
        std::string value;
        input >> key >> value;

        t2.add(key, value);
    }
    output << processSentence(t2, {2, 1, 5, 6}) << std::endl;

    // create a constant table that is t1 updated with t2
    // you should use the updateTable function here
    // note that for it to be constant, its value has to be finalized at definition time
    // --- Your code here

    const Table t3 = updateTable(t1, t2);

    output << std::is_const<decltype(t3)>::value << std::endl;

    // should not change the original tables
    output << processSentence(t1, {1, 3, 5, 4}) << std::endl;
    output << processSentence(t2, {2, 1, 5, 6}) << std::endl;

    // should have entries of t1 with overriding values from t2
    output << processSentence(t3, {1, 3, 5, 4}) << std::endl;
    // you need to implement this function to create a copy of the Table with only even keys
    output << processSentence(filterOutOddKeys(t3), {2, 1, 3, 5, 4}) << std::endl;
}