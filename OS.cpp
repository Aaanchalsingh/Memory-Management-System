#include <iostream>
using namespace std;

class MemoryManager
{
private:
    struct MemoryBlock
    {
        bool free;
        size_t size;
        MemoryBlock *next;
    };
    MemoryBlock *head;
    size_t total_size;

public:
    MemoryManager(size_t size)
    {
        head = new MemoryBlock{true, size, nullptr};
        total_size = size;
    }

    void *allocate(size_t size)
    {
        MemoryBlock *current_block = head;
        MemoryBlock *previous_block = nullptr;
        while (current_block != nullptr)
        {
            if (current_block->free && current_block->size >= size)
            {
                current_block->free = false;

                if (current_block->size > size + sizeof(MemoryBlock))
                {
                    MemoryBlock *new_block = (MemoryBlock *)((char *)current_block + sizeof(MemoryBlock) + size);
                    new_block->free = true;
                    new_block->size = current_block->size - size - sizeof(MemoryBlock);
                    new_block->next = current_block->next;
                    current_block->next = new_block;
                    current_block->size = size;
                }

                return (char *)current_block + sizeof(MemoryBlock);
            }

            previous_block = current_block;
            current_block = current_block->next;
        }
        cout << "Not enough free memory available :( ";
        return nullptr;
    }

    void free(void *ptr)
    {
        MemoryBlock *current_block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
        current_block->free = true;

        MemoryBlock *next_block = current_block->next;
        while (next_block != nullptr && next_block->free)
        {
            current_block->size += sizeof(MemoryBlock) + next_block->size;
            current_block->next = next_block->next;
            next_block = current_block->next;
        }
    }

    size_t get_internal_fragmentation() const
    {
        size_t internal_fragmentation = 0;
        MemoryBlock *current_block = head;
        while (current_block != nullptr)
        {
            if (current_block->free)
            {
                internal_fragmentation += current_block->size;
            }
            current_block = current_block->next;
        }
        return internal_fragmentation;
    }

    size_t get_external_fragmentation() const
    {
        size_t external_fragmentation = 0;
        MemoryBlock *current_block = head;
        while (current_block != nullptr)
        {
            if (current_block->free)
            {
                external_fragmentation += current_block->size + sizeof(MemoryBlock);
            }
            current_block = current_block->next;
        }
        return external_fragmentation;
    }

    void print_memory_map() const
    {
        cout << "Memory Map:" << endl;
        MemoryBlock *current_block = head;
        while (current_block != nullptr)
        {
            cout << "  " << current_block << " - " << current_block + current_block->size + sizeof(MemoryBlock) << " [";
            if (current_block->free)
            {
                cout << "free";
            }
            else
            {
                cout << "allocated";
            }
            cout << ", " << current_block->size << "]" << endl;
            current_block = current_block->next;
        }
        cout << endl;
    }
};
int main()
{
    MemoryManager memory(1024); // 1KB total memory
    int time = 1;

    void *ptr1 = memory.allocate(256);
    if (ptr1)
    {

        if (time <= 10)
        {
            cout << endl
                 << "Time : " << time << endl;
            cout << "Allocated 256 bytes at address " << ptr1 << endl;
            time++;
        }
        else
        {
            cout << "Times UP!!";
            return 0;
        }
    }
    else
        return 0;
    memory.print_memory_map();
    cout << "Internal fragmentation: "<< memory.get_internal_fragmentation() 
         << " bytes" << endl;
    cout << "External fragmentation: " << memory.get_external_fragmentation() << " bytes" << endl;
    cout << "Wasted Memory: " << memory.get_internal_fragmentation() << " bytes" << endl;

    void *ptr2 = memory.allocate(512);
    if (ptr2)
    {

        if (time <= 10)
        {
            cout << endl
                 << "Time : " << time << endl;
            cout << "Allocated 512 bytes at address " << ptr2 << endl;
            time++;
        }
        else
        {
            cout << "Times UP!!";
            return 0;
        }
    }
    else
        return 0;
    memory.print_memory_map();
    cout << "Internal fragmentation: " << memory.get_internal_fragmentation() << " bytes" << endl;
    cout << "External fragmentation: " << memory.get_external_fragmentation() << " bytes" << endl;
    cout << "Wasted Memory: " << memory.get_internal_fragmentation() << " bytes" << endl;

    void *ptr3 = memory.allocate(156);
    if (ptr3)
    {

        if (time <= 10)
        {
            cout << endl
                 << "Time : " << time << endl;
            cout << "Allocated 256 bytes at address " << ptr3 << endl;
            time++;
        }
        else
        {
            cout << "Times UP!!";
            return 0;
        }
    }
    else
        return 0;
    memory.print_memory_map();
    cout << "Internal fragmentation: " << memory.get_internal_fragmentation() << " bytes" << endl;
    cout << "External fragmentation: " << memory.get_external_fragmentation() << " bytes" << endl;
    cout << "Wasted Memory: " << memory.get_internal_fragmentation() << " bytes" << endl;

    memory.free(ptr1);
    cout << "Freed 256 bytes at address " << ptr1 << endl;
    memory.print_memory_map();
    cout << "Internal fragmentation: " << memory.get_internal_fragmentation() << " bytes" << endl;
    cout << "External fragmentation: " << memory.get_external_fragmentation() << " bytes" << endl;
    cout << "Wasted Memory: " << memory.get_internal_fragmentation() << " bytes" << endl;

    void *ptr4 = memory.allocate(328);
    if (ptr4)
    {
        if (time <= 10)
        {
            cout << endl
                 << "Time : " << time << endl;
            cout << "Allocated 328 bytes at address " << ptr4 << endl;
            time++;
        }
        else
        {
            cout << "Times UP!!";
            return 0;
        }
    }
    else
        return 0;
    memory.print_memory_map();
    cout << "Internal fragmentation: " << memory.get_internal_fragmentation() << " bytes" << endl;
    cout << "External fragmentation: " << memory.get_external_fragmentation() << " bytes" << endl;
    cout << "Wasted Memory: " << memory.get_internal_fragmentation() << " bytes" << endl;

    return 0;
}
