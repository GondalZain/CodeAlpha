#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

// Convert std::string to std::wstring
std::wstring stringToWString(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

// Convert std::wstring to std::string
std::string wstringToString(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

// List the contents of a directory
void listDirectory(const std::string& path) {
    std::wstring searchPath = stringToWString(path + "\\*"); // Create search path with wildcard
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData); // Find the first file in the directory

    if (hFind == INVALID_HANDLE_VALUE) { // Check if the handle is valid
        std::cout << "Failed to open directory." << std::endl;
        return;
    }

    do {
        const bool isDirectory = (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0; // Check if it is a directory
        std::wcout << findFileData.cFileName << (isDirectory ? L"/" : L"") << std::endl; // Print file or directory name
    } while (FindNextFile(hFind, &findFileData) != 0); // Loop through all files

    FindClose(hFind); // Close the handle
}

// Change the current directory
void changeDirectory(std::string& currentPath, const std::string& newPath) {
    std::wstring newDir = stringToWString(currentPath + "\\" + newPath); // Create new path
    if (SetCurrentDirectory(newDir.c_str())) { // Attempt to change the directory
        wchar_t buffer[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, buffer); // Get the current directory
        currentPath = wstringToString(buffer); // Update currentPath
    }
    else {
        std::cout << "Directory does not exist." << std::endl; // Print error if directory does not exist
    }
}

// View the contents of a file
void viewFile(const std::string& filePath) {
    std::ifstream file(filePath); // Open the file
    if (file.is_open()) { // Check if the file is open
        std::string line;
        while (std::getline(file, line)) { // Read the file line by line
            std::cout << line << std::endl; // Print each line
        }
    }
    else {
        std::cout << "File does not exist." << std::endl; // Print error if file does not exist
    }
}

// Create a new directory
void createDirectory(const std::string& dirPath) {
    std::wstring wDirPath = stringToWString(dirPath); // Convert directory path to wstring
    if (CreateDirectory(wDirPath.c_str(), nullptr)) { // Attempt to create the directory
        std::cout << "Directory created successfully." << std::endl; // Print success message
    }
    else {
        std::cout << "Failed to create directory." << std::endl; // Print error message
    }
}

// Copy a file from srcPath to destPath
void copyFile(const std::string& srcPath, const std::string& destPath) {
    std::wstring wSrcPath = stringToWString(srcPath); // Convert source path to wstring
    std::wstring wDestPath = stringToWString(destPath); // Convert destination path to wstring
    if (CopyFile(wSrcPath.c_str(), wDestPath.c_str(), FALSE)) { // Attempt to copy the file
        std::cout << "File copied successfully." << std::endl; // Print success message
    }
    else {
        std::cout << "Error copying file." << std::endl; // Print error message
    }
}

// Move a file from srcPath to destPath
void moveFile(const std::string& srcPath, const std::string& destPath) {
    std::wstring wSrcPath = stringToWString(srcPath); // Convert source path to wstring
    std::wstring wDestPath = stringToWString(destPath); // Convert destination path to wstring
    if (MoveFile(wSrcPath.c_str(), wDestPath.c_str())) { // Attempt to move the file
        std::cout << "File moved successfully." << std::endl; // Print success message
    }
    else {
        std::cout << "Error moving file." << std::endl; // Print error message
    }
}

int main() {
    wchar_t buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer); // Get the current directory
    std::string currentPath = wstringToString(buffer); // Convert the current directory to string
    std::string command;
    std::string argument1, argument2;

    while (true) {
        std::cout << "Current directory: " << currentPath << std::endl; // Print the current directory
        std::cout << "Enter command: ";
        std::cin >> command; // Get the user command

        if (command == "ls") {
            listDirectory(currentPath); // List the directory contents
        }
        else if (command == "cd") {
            std::cin >> argument1; // Get the directory to change to
            changeDirectory(currentPath, argument1); // Change the directory
        }
        else if (command == "view") {
            std::cin >> argument1; // Get the file to view
            viewFile(currentPath + "\\" + argument1); // View the file
        }
        else if (command == "mkdir") {
            std::cin >> argument1; // Get the directory name to create
            createDirectory(currentPath + "\\" + argument1); // Create the directory
        }
        else if (command == "cp") {
            std::cin >> argument1 >> argument2; // Get the source and destination paths for copying
            copyFile(currentPath + "\\" + argument1, currentPath + "\\" + argument2); // Copy the file
        }
        else if (command == "mv") {
            std::cin >> argument1 >> argument2; // Get the source and destination paths for moving
            moveFile(currentPath + "\\" + argument1, currentPath + "\\" + argument2); // Move the file
        }
        else if (command == "exit") {
            break; // Exit the program
        }
        else {
            std::cout << "Unknown command." << std::endl; // Print error for unknown command
        }
    }

    return 0;
}

