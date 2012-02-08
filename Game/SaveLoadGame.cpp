#include "game.h"

void Game::CopyWorld(const boost::filesystem::path& source, const boost::filesystem::path& dest) 
{
    namespace fs = boost::filesystem;
    try 
    {
        // Check whether the function call is valid
        if(!fs::exists(source) || !fs::is_directory(source)) 
        {
            std::cerr << "Source directory " << source.string().c_str() << " does not exist or is not a directory." << std::endl;
            return;
        }
        if(fs::exists(dest)) 
        {
            std::cerr << "Destination directory " << dest.string().c_str() << " already exists." << std::endl;
            return;
        }
        // Create the destination directory
        if(!fs::create_directory(dest)) 
        {
            std::cerr << "Unable to create destination directory " << dest.string().c_str() << std::endl;
            return;
        }
    }
    catch(fs::filesystem_error& e) 
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    // Iterate through the source directory
    for(fs::directory_iterator it(source); it != fs::directory_iterator(); it++) 
    {
        try 
        {
            fs::path current(it->path());
            if(fs::is_directory(current)) 
            {
                // Found directory: Recursion
                CopyWorld(current, dest.string() + "/" + current.filename().string());
            }
            else 
            {
                // Found file: Copy
                fs::copy_file(current, fs::path(dest.string() + "/" + current.filename().string()));
            }
        }
        catch(fs::filesystem_error& e) 
        {
            std::cerr << e.what() << std::endl;
        }
    }
}