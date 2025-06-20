#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem> // C++17 for directory operations
#include <chrono>     // For timestamp (optional, but good for real Git)
#include <iomanip>    // For string formatting (optional)
#include <sstream>    // For string streams

namespace fs = std::filesystem;

// A simple placeholder for a hashing function.
// In a real Git system, you would use a robust cryptographic hash like SHA-1.
// For this simplified version, we'll create a "hash" based on content and timestamp.
std::string generate_simple_hash(const std::string& content) {
    // Generate a timestamp string
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    // Combine content length and timestamp for a simple, pseudo-unique identifier
    std::hash<std::string> hasher;
    std::string data_to_hash = content + std::to_string(timestamp) + std::to_string(hasher(content));
    size_t content_hash = hasher(data_to_hash);

    std::stringstream ss;
    ss << std::hex << std::setw(32) << std::setfill('0') << content_hash; // Use 32 hex chars for a hash-like appearance
    return ss.str();
}

class MiniGit {
public:
    // Constructor initializes the base directory name
    MiniGit() : minigit_dir_name_(".minigit") {}

    // Implements the 'minigit init' command
    void init() {
        std::cout << "Initializing MiniGit repository..." << std::endl;

        // Check if .minigit directory already exists
        if (fs::exists(minigit_dir_name_) && fs::is_directory(minigit_dir_name_)) {
            std::cout << "Reinitializing existing MiniGit repository in " << fs::current_path() << std::endl;
            // In a real Git, re-init might reset HEAD or just confirm.
            // For simplicity, we'll just confirm existence here.
        } else {
            // Create the .minigit directory
            if (!fs::create_directory(minigit_dir_name_)) {
                std::cerr << "Error: Could not create directory " << minigit_dir_name_ << std::endl;
                return;
            }
            std::cout << "Created directory: " << minigit_dir_name_ << std::endl;
        }

        // Create .minigit/objects directory for storing blob contents
        std::string objects_path = minigit_dir_name_ + "/objects";
        if (!fs::exists(objects_path)) {
            if (!fs::create_directory(objects_path)) {
                std::cerr << "Error: Could not create directory " << objects_path << std::endl;
                return;
            }
            std::cout << "Created directory: " << objects_path << std::endl;
        }

        // Create .minigit/refs directory for storing references (branches, tags)
        std::string refs_path = minigit_dir_name_ + "/refs";
        if (!fs::exists(refs_path)) {
            if (!fs::create_directory(refs_path)) {
                std::cerr << "Error: Could not create directory " << refs_path << std::endl;
                return;
            }
            std::cout << "Created directory: " << refs_path << std::endl;
        }

        // Create .minigit/refs/heads directory for storing branch pointers
        std::string heads_path = refs_path + "/heads";
        if (!fs::exists(heads_path)) {
            if (!fs::create_directory(heads_path)) {
                std::cerr << "Error: Could not create directory " << heads_path << std::endl;
                return;
            }
            std::cout << "Created directory: " << heads_path << std::endl;
        }

        // Initialize HEAD file to point to the 'main' branch
        // In real Git, HEAD initially points to 'ref: refs/heads/master' or 'ref: refs/heads/main'
        std::string head_path = minigit_dir_name_ + "/HEAD";
        std::ofstream head_file(head_path);
        if (head_file.is_open()) {
            head_file << "ref: refs/heads/main" << std::endl;
            head_file.close();
            std::cout << "Initialized HEAD to point to refs/heads/main" << std::endl;
        } else {
            std::cerr << "Error: Could not create HEAD file." << std::endl;
        }

        // Create the initial 'main' branch file (it will be empty until the first commit)
        std::string main_branch_path = heads_path + "/main";
        std::ofstream main_branch_file(main_branch_path);
        if (main_branch_file.is_open()) {
            main_branch_file.close(); // File is created but empty, will hold commit hash later
            std::cout << "Created initial 'main' branch reference file." << std::endl;
        } else {
            std::cerr << "Error: Could not create main branch file." << std::endl;
        }


        std::cout << "MiniGit repository initialized successfully!" << std::endl;
    }

    // Stores file content as a 'blob' in the .minigit/objects directory.
    // Returns the hash of the blob.
    std::string save_blob(const std::string& file_content) {
        std::string hash = generate_simple_hash(file_content);
        std::string blob_path = minigit_dir_name_ + "/objects/" + hash;

        std::ofstream outfile(blob_path);
        if (outfile.is_open()) {
            outfile << file_content;
            outfile.close();
            // std::cout << "Saved blob with hash: " << hash << std::endl; // For debugging
            return hash;
        } else {
            std::cerr << "Error: Could not save blob to " << blob_path << std::endl;
            return ""; // Return empty string on error
        }
    }

    // Reads the content of a blob given its hash.
    // Returns the content as a string.
    std::string read_blob(const std::string& hash) {
        std::string blob_path = minigit_dir_name_ + "/objects/" + hash;
        std::ifstream infile(blob_path);
        std::string content;

        if (infile.is_open()) {
            std::string line;
            while (std::getline(infile, line)) {
                content += line + "\n";
            }
            infile.close();
            if (!content.empty()) {
                content.pop_back(); // Remove the last newline character if present
            }
            // std::cout << "Read blob with hash: " << hash << std::endl; // For debugging
            return content;
        } else {
            std::cerr << "Error: Could not read blob from " << blob_path << std::endl;
            return ""; // Return empty string on error
        }
    }

private:
    std::string minigit_dir_name_;
};

// Main function to simulate command line interaction
int main(int argc, char* argv[]) {
    MiniGit minigit;

    if (argc < 2) {
        std::cout << "Usage: minigit <command> [arguments]" << std::endl;
        std::cout << "Available commands: init, test_blob" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        minigit.init();
    } else if (command == "test_blob") {
        // This is a test command to demonstrate blob saving/reading
        std::cout << "--- Testing Blob Storage ---" << std::endl;
        std::string test_content1 = "Hello, MiniGit!";
        std::string hash1 = minigit.save_blob(test_content1);
        std::cout << "Content: \"" << test_content1 << "\", Saved as hash: " << hash1 << std::endl;
        std::string read_content1 = minigit.read_blob(hash1);
        std::cout << "Read content for hash " << hash1 << ": \"" << read_content1 << "\"" << std::endl;
        std::cout << "Content matches: " << (test_content1 == read_content1 ? "true" : "false") << std::endl;

        std::cout << "\n";

        std::string test_content2 = "This is some different content for a second blob.";
        std::string hash2 = minigit.save_blob(test_content2);
        std::cout << "Content: \"" << test_content2 << "\", Saved as hash: " << hash2 << std::endl;
        std::string read_content2 = minigit.read_blob(hash2);
        std::cout << "Read content for hash " << hash2 << ": \"" << read_content2 << "\"" << std::endl;
        std::cout << "Content matches: " << (test_content2 == read_content2 ? "true" : "false") << std::endl;

        std::cout << "\n";

        std::string test_content3 = "Hello, MiniGit!"; // Same content as test_content1
        std::string hash3 = minigit.save_blob(test_content3);
        std::cout << "Content: \"" << test_content3 << "\", Saved as hash: " << hash3 << std::endl;
        std::string read_content3 = minigit.read_blob(hash3);
        std::cout << "Read content for hash " << hash3 << ": \"" << read_content3 << "\"" << std::endl;
        std::cout << "Content matches: " << (test_content3 == read_content3 ? "true" : "false") << std::endl;
        std::cout << "Hash of identical content (with timestamp influence): " << hash1 << " vs " << hash3 << std::endl;


    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }

    return 0;
}
