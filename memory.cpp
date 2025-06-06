#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Block
{
    int size;
    bool isFree;
};

class MemoryManager
{
    private:
    vector<Block> blocks;
    public:
    MemoryManager(const vector<int> &sizes)
    {
        for(int size : sizes)
        {
            blocks.push_back({size, true});
        }
    }

    void displayMemory()
    {
        cout << "Memory Blocks:\n";
        for (size_t i = 0; i < blocks.size(); i++)
        {
            cout << "Block " << i << ": Size = " << blocks[i].size << ", "
            << (blocks[i].isFree ? "Free" : "Allocated") << "\n";
        }
    }

    int firstFit(int requestSize)
    {
        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= requestSize)
            {
                blocks[i].isFree = false;
                cout << "Allocated " << requestSize << " to Block " << i << " using First Fit.\n";
                return i;
            }
        }
        cout << "No suitable block found for " << requestSize << " using First Fit.\n";
        return -1;
    }

    int bestFit(int requestSize)
    {
        int bestIndex = -1;
        int minSize = numeric_limits<int>::max();   // INT_MAX
        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= requestSize && blocks[i].size < minSize)
            {
                minSize = blocks[i].size;
                bestIndex = i;
            }
        }
        if (bestIndex != -1)
        {
            blocks[bestIndex].isFree = false;
            cout << "Allocated " << requestSize << " to Block " << bestIndex << " using Best Fit.\n";
        }
        else
        {
            cout << "No suitable block found for " << requestSize << " using Best Fit.\n";
        }
        return bestIndex;
    }

    int worstFit(int requestSize)
    {
        int worstIndex = -1;
        int maxSize = -1;
        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= requestSize && blocks[i].size > maxSize)
            {
                maxSize = blocks[i].size;
                worstIndex = i;
            }
        }

        if (worstIndex != -1)
        {
            blocks[worstIndex].isFree = false;
            cout << "Allocated " << requestSize << " to Block " << worstIndex << " using Worst Fit.\n";
        }
        else
        {
            cout << "No suitable block found for " << requestSize << " using Worst Fit.\n";
        }
        return worstIndex;
    }

    int nextFit(int requestSize, int &lastAllocated)
    {
        for (size_t i = lastAllocated; i < blocks.size(); i++)
        {
            if (blocks[i].isFree && blocks[i].size >= requestSize)
            {
                blocks[i].isFree = false; 
                lastAllocated = i;
                cout << "Allocated " << requestSize << " to Block " << i << " using Next Fit.\n";
                return i;
            }
        }
        for (size_t i = 0; i < lastAllocated; i++)
        {
            if (blocks[i].isFree && blocks[i].size >= requestSize)
            {
                blocks[i].isFree = false;
                lastAllocated = i;
                cout << "Allocated " << requestSize << " to Block " << i << " using Next Fit.\n";
                return i;
            }
        }
        cout << "No suitable block found for " << requestSize << " using Next Fit.\n";
        return -1;
    }
};

int main()
{
    vector<int> blockSizes = {100, 500, 200, 300, 600};
    MemoryManager mm(blockSizes);
    mm.displayMemory();
    int lastAllocated = 0;
    mm.firstFit(212);
    mm.displayMemory();

    mm.bestFit(100);
    mm.displayMemory();
    mm.worstFit(600);
    mm.displayMemory();
    mm.nextFit(400, lastAllocated);
    mm.displayMemory();
    return 0;
}
