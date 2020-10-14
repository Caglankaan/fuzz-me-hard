#include "fuzzer.h"

Fuzzer::Fuzzer(const std::filesystem::path& work_dir, const std::filesystem::path& temp_dir_, const std::filesystem::path& binary_dir_)
{
    std::filesystem::path log("log.txt");
    log_dir = work_dir / log;
    binary_dir = binary_dir_;
    temp_dir = temp_dir_;
}

void exec(const char* cmd, std::string &filename) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        FileIO::writeToFile(buffer.data(), filename);
    }
}

void threadForFuzzing(std::string name, std::string command)
{
    exec(command.c_str(), name);
}

bool Fuzzer::fuzz(const std::filesystem::path &filename, Timer &timer)
{
    pid_t pid = fork();
    if(pid < 0)
    {
        std::cout << "Fork Error!\n";
        exit(1);
    }
    else if(pid == 0) // child process so we can run our binary
    {
        //This is to close stdout (redirect it to /dev/null)
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd,1);
        dup2(fd,2);
        close(fd);
        

        execl(binary_dir.c_str(),binary_dir.c_str(),  filename.c_str(), NULL);
        std::cout << "Error occured when running execl()\n";
        exit(1);
    }
    else
    {
        int stat;
        //The waitpid() system call suspends execution of the current process until a child specified by pid argument has changed state.
        if(waitpid(pid, &stat, 0) < 0)
        {
            std::cout << "Waitpid error\n";
            exit(254);
        }
        if(WIFEXITED(stat)) //Successfuly executed
        {
            return false;
            //std::cout << "Process " << pid << " returned " << WEXITSTATUS(stat) << "\n";
        }
        if(WIFSIGNALED(stat)) //Crash occured
        {
            printf("Process %d killed: signal %d%s  (filename: %s)\n",
               pid, WTERMSIG(stat),
               WCOREDUMP(stat) ? " - core dumped" : "", filename.c_str());
            crash_count+=1;
            timer.restart();
            return true;
        }
    }
    return false;
}
