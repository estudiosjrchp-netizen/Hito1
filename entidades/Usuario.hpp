#pragma once
#include <string>

class Usuario {
private:
    std::string username;
    std::string password;
    std::string email;
    int idUsuario; 

public:


    Usuario() {} 
    Usuario(std::string _username, std::string _password, std::string _email, int _id) 
        : username(_username), password(_password), email(_email), idUsuario(_id) {}

    // Getters básicos
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getEmail() const { return email; }
    int getId() const { return idUsuario; }
};