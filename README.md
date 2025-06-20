# MiniGit Project

## Overview

**MiniGit** is a simplified, command-line version control system inspired by Git, developed in C++. It is designed for educational purposes to help students understand the core concepts behind version control systems, including data structures like Directed Acyclic Graphs (DAGs), trees, hashing, and file differencing. MiniGit operates through a command-line interface (CLI) and simulates essential Git functionalities such as tracking file changes, making commits, creating branches, merging, and viewing commit history.

## ✨ Features

- 🗂️ **Initialization**: Set up a new MiniGit repository with `.minigit/` directory and object storage.
- 📂 **File Tracking & Staging**: Stage files and prepare them for commits using hashing for content identification.
- 📝 **Committing Changes**: Save snapshots of the project, storing metadata and file versions.
- 🌿 **Branching & Log History**: Create and manage branches, view commit logs, and traverse project history.
- 🔄 **Checkout**: Switch between commits or branches, restoring the working directory to previous states.
- 🔀 **Merge**: Merge branches using a three-way merge strategy, including conflict detection.
- 📑 **Documentation & Demo**: Includes a detailed report and video demonstration of system functionalities.

## 🛠️ Core Commands

- `minigit init`  
  Initialize a new MiniGit repository in the current directory.

- `minigit add <filename>`  
  Stage files for the next commit.

- `minigit commit -m "<message>"`  
  Commit staged changes with a descriptive message.

- `minigit log`  
  View commit history.

- `minigit branch <branch-name>`  
  Create a new branch at the current commit.

- `minigit checkout <branch-name|commit-hash>`  
  Switch to a different branch or specific commit.

- `minigit merge <branch-name>`  
  Merge the specified branch into the current one, with conflict handling.

## 📚 Data Structures & Concepts

- 🔑 **Hashing**: Used for uniquely identifying file contents (blobs) and commits.
- 🌳 **Linked Lists & DAGs**: To model commit history and support branching/merging.
- 🗃️ **Hash Tables/Sets**: For managing the staging area and branch references.
- 💾 **File I/O**: For reading/writing file snapshots and repository metadata.

## 🗃️ Project Structure

- **.minigit/**: Hidden directory for all repository data.
  - `objects/`: Stores hashed file contents (blobs).
  - `commits/`: Stores commit objects and metadata.
  - `refs/`: Stores pointers for branches and HEAD.
- **src/**: Source code for MiniGit CLI and core modules.
- **docs/**: Project documentation and report.
- **demo/**: Video demonstration of MiniGit in action.

## 👥 Team Task Distribution

| 👤 Member | 🏷️ Responsibilities |
|--------|------------------|
| 1 | Repository initialization, blob storage, file I/O setup |
| 2 | File staging, committing, staging area management |
| 3 | Log history traversal, branching, branch reference data structures |
| 4 | Checkout functionality, state restoration, HEAD management |
| 5 | Merge functionality, three-way merge, conflict detection |
| 6 | Documentation, video demo, repository management, code editing |

## 🚀 Getting Started

1. **Clone the repository**  
   ```bash
   git clone https://github.com/Krutias/minigit_Project.git
   cd minigit_Project
   ```

2. **Build the project**  
   ```bash
   make
   ```

3. **Run MiniGit**  
   ```bash
   ./minigit <command> [options]
   ```

## ⚠️ Limitations

- Not a full replacement for Git; only supports a subset of features.
- File differencing and merging may be basic compared to Git.
- No remote repositories or network operations.



**Developed by Team MiniGit**  
For educational purposes. See the commit history for individual contributions.
