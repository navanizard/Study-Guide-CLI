# Study Guide CLI

This is a command-line study guide application written in C++ that dynamically generates and adjusts quizzes based on user performance. It was developed as a semester-long project for CSCI 135: Software Analysis & Design I at Hunter College, where we were encouraged to iteratively build upon our code each week — refining functionality, improving logic, and eventually creating a complete study tool.

What started as a small assignment grew into something genuinely useful. I actually used this project to prepare for my midterm and found it incredibly helpful for reinforcing concepts we’d learned in class.

## 🧠 How It Works

When the program runs, it reads from a file of pre-written question-answer pairs and presents them to you one at a time. It tracks your performance across the quiz and displays your results at the end.

The key features include:

- ❌ **Adaptive Prioritization**: If you answer a question incorrectly **three times**, the program identifies its topic and flags all questions with that same topic as a top priority. Those questions move up in the queue so you can focus on your weaker areas.
- 🔀 **Randomized Practice**: To prevent memorization and encourage real understanding, the program randomly shuffles the order of questions (except for those prioritized by difficulty).
- 📝 **Built-In Grading**: At the end of your session, you’ll get a summary of how you did — including how many questions you got right and your overall accuracy percentage.

This approach mimics spaced repetition and helps improve retention through targeted review.

The code is modular and includes:
- `main.cpp`: The driver file that runs the program loop.  
- `quiz.cpp`: Functions for reading questions, tracking attempts, and ordering the quiz strategically.  

## 🚀 Getting Started

To compile and run the project:

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/Study-Guide-CLI.git
    ```

2. Navigate to the project directory:
   ```bash
   cd Study-Guide-CLI
   ```

3. Compile the code using the `g++` compiler with the C++20:
   ```bash
    g++ -std=c++20 -o study-guide main.cpp quiz.cpp

   ```

4. Run the executable:
   ```bash
   ./study-guide
   ```

You can modify the question file or create your own using a simple text format. Each line represents a single question-answer pair.

## 📚 Educational Purpose

This project reflects my journey learning C++ — from simple I/O and file processing to more advanced concepts like arrays, pointers, classes, and data tracking. Building this project helped me practice debugging, modular design, and real-world application of class materials.

More importantly, it gave me something *practical* that I could use to study smarter, not just harder.

## 🔐 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.


## 🙏 Credits

- Special thanks to the CS teaching staff at Hunter College for their guidance throughout the semester.  
- Huge appreciation to **Professor Tong Yi**, whose question files and feedback laid the groundwork for this tool.
