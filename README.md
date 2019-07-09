# DataManager

This library provides a class that enables the storing, updating, and managing of key-value pairs. The DataManager class efficiently stores data using linked lists, has O[N] insertion and retrieval complexity, and a memory footprint of O[N]. Note that this implementation is not equivalent to C++ maps or Python dictionaries. While developed for **Arduino** and **ESP8266** applications, it works with plain C++ as well. However, there are more efficient implementation (e.g. std::map) available.

The DataManager class is a templated class that can store arbitrary data types (such as int, float, or String) or user-defined structures.

Based on Ivan Seidel's LinkedList implementation (see https://github.com/ivanseidel/LinkedList).

## Installation

1. [Download](https://github.com/dpickem/Arduino_DataManager/archive/master.zip) the latest release from GitHub.
2. Unzip and modify the Folder name to "data\_manager".
3. Paste the modified folder on your Library folder (On your `Libraries` folder inside Sketchbooks or Arduino software).
4. Reopen the Arduino software.

Alternatively, just clone the repository from [here](https://github.com/dpickem/Arduino_DataManager.git)

-------------------------

## Getting started

### The `DataManager` class

#### To declare a DataManager object
```c++
// Instantiate a DataManager that will hold 'integer' values.
DataManager<int> myDataManager = DataManager<int>();
DataManager<int> myDataManager;

// Instantiate a pointer to a DataManager.
DataManager<int> *myDataManager = new DataManager<int>();

// If you want a DataManager with any other type such as 'MyClass'.
DataManager<MyClass> *myDataManager = new DataManager<MyClass>();
```

#### High-level API methods
```c++
// To add a new element or update an existing one.
myDataManager.update("variable_name", value);

// To check whether a named variable already exists.
bool exists = myDataManager.exists("variable_name");

// To check whether any new data is available.
bool is_new = myDataManager.has_new_data();
```

#### Getting the size of the data storage container in the DataManager instance
```c++
// To get the size of a linked list, make use of the size() method
int data_size = myDataManager.get_size();
```

#### Adding elements

```c++
// To add an new object named "variable_name".
myDataManager.update("variable_name", myObject);
```

#### Getting elements

```c++
// To get a pointer to the container holding the named variable by name.
DataContainer<T>* myObject = myDataManager.get_entry_by_name("variable_name");

// To get the value of a named variable.
int my_value = myDataManager.get_value("variable_name");
```

#### Changing elements
```c++
// To set the value of a named variable.
bool modified = myDataManager.set_value("variable_name", 10);
```

#### Removing elements
```c++
// To remove a named variable.
bool removed = myDataManager.remove_entry_by_name("variable_name");
```

### Version History

* `1.0 (2019-07-08)`: Original release
