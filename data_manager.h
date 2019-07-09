/*
 * This is a library to support and facilitate management of numeric data.
 *
 * You may use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software but you must include this copyright notice and
 * this permission in all copies or substantial portions of the Software.
 *
 * Copyright 2019 Daniel Pickem (daniel.pickem@gmail.com)
 * http://www.danielpickem.com
 * 
 * MIT-License
 */

#ifndef _DATA_MANAGER_
#define _DATA_MANAGER_

// Include Arduino libraries.
#include "Arduino.h"

// Include STL containers.
#include "LinkedList.h"


/*! @brief A templated data container class for storing named values.
 */
template <class T> class DataContainer {
 public:
    //-------------------------------------------
    //                 Lifecycle
    //-------------------------------------------
    // Constructor
    DataContainer(const String name, const T value, const bool is_new)
        : name_(name), value_(value), is_new_(is_new) {}

    // Destructor
    ~DataContainer() = default;

    //-------------------------------------------
    //             Getter functions
    //-------------------------------------------
    String get_name() { return name_; }
    T get_value() { return value_; }
    bool get_is_new() { return is_new_; }

    //-------------------------------------------
    //             Setter functions
    //-------------------------------------------
    void set_name(String name) { name_ = name; }
    void set_value(T value) { value_ = value; }
    void set_is_new(bool is_new) { is_new_ = is_new; }

 private:
    String name_;
    T value_;
    bool is_new_;
};


/*! @brief A class enabling the management of named data.
 *
 * Templated function implementations are most conveniently done in the header
 * file that defines them according to the following article:
 *
 *    https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 */
template <class T> class DataManager {
 public:
    //-------------------------------------------
    //                 Lifecycle
    //-------------------------------------------
    // Constructor
    DataManager() : data_() {}

    // Destructor
    ~DataManager() = default;

    //-------------------------------------------
    //             High-level functions
    //-------------------------------------------
    // Update a stored value or add new value if not yet available.
    void update(String name, T value) {
        if (exists(name)) {
            set_value(name, value);
        } else {
            data_.add(new DataContainer<T>(name, value, true));
        }
    }

    //-------------------------------------------
    //             Utility functions
    //-------------------------------------------
    // Check whether a variable with a given name already exists.
    bool exists(String name) {
        return get_entry_by_name(name) != nullptr;
    }

    // Check whether new data is available.
    bool has_new_data() {
        for (int i = 0; i < data_.size(); i++) {
            if (data_.get(i)->get_is_new() == true) {
                return true;
            }
        }

        return false;
    }

    // Get a data entry by name or return nullptr if non-existant.
    DataContainer<T>* get_entry_by_name(String name) {
        for (int i = 0; i < data_.size(); i++) {
            if (data_.get(i)->get_name() == name) {
                return data_.get(i);
            }
        }

        return nullptr;
    }

    // Remove an entry.
    bool remove_entry_by_name(String name) {
        for (int i = 0; i < data_.size(); i++) {
            if (data_.get(i)->get_name() == name) {
                data_.remove(i);
                return true;
            }
        }

        return false;
    }

    //-------------------------------------------
    //             Getter functions
    //-------------------------------------------
    uint8_t get_size() {
        return data_.size();
    }

    String get_name(int index) {
        if (index >= 0 && index < data_.size()) {
            return data_.get(index)->get_name();
        }
    }

    bool get_is_new(int index) {
        if (index >= 0 && index < data_.size()) {
            return data_.get(index)->get_is_new();
        }
    }

    T get_value(int index) {
        if (index >= 0 && index < data_.size()) {
            return data_.get(index)->get_value();
        }
    }

    T get_value(String name) {
        DataContainer<T>* entry = get_entry_by_name(name);

        if (entry != nullptr) {
            return entry->get_value();
        }
    }

    //-------------------------------------------
    //             Setter functions
    //-------------------------------------------
    bool set_value(String name, T value) {
        DataContainer<T>* entry = get_entry_by_name(name);

        if (entry != nullptr) {
            entry->set_value(value);
            entry->set_is_new(true);
            return true;
        }

        return false;
    }

 private:
    bool set_is_new(String name, bool is_new) {
        DataContainer<T>* entry = get_entry_by_name(name);

        if (entry != nullptr) {
            entry->set_is_new(true);
            return true;
        }

        return false;
    }

    bool set_is_new(int index, bool is_new) {
        if (index >= 0 && index < data_.size()) {
            data_.get(index)->set_is_new(is_new);
            return true;
        }

        return false;
    }

 private:
    // List of device modes.
    LinkedList<DataContainer<T>*> data_;
};

#endif  // _DATA_MANAGER_
