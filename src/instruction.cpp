#include <cstring>
#include "errors.h"
#include "instruction.h"
using namespace std;

bool overlap(const vector<byte> &a, const vector<byte> &b) {
    vector<byte>::size_type a_len = a.size();
    vector<byte>::size_type b_len = b.size();
    vector<byte>::size_type min_len = min(a_len, b_len);
    int cmp = memcmp(a.data(), b.data(), min_len);
    return cmp == 0;
}

Instruction::Instruction(std::vector<byte> opcode, SizeType instructionLength, Callback callback) \
    : length(instructionLength), opcode(opcode), callback(callback) {
}

void Instruction::execute(CPU &cpu, const std::vector<byte> &params) const {
    return callback(cpu, *this, params);
}

int InstructionSet::add(const Instruction &instruction) {
    Insertion insert = set.insert(instruction);
    Iterator pos = insert.first;
    bool success = insert.second;
    int ret = ERR_SUCCESS;
    if(success) {
        if(pos != set.begin())
        {
            Iterator prev = pos;
            prev--;
            if(overlap(pos->opcode, prev->opcode)) {
                ret = ERR_CONFLICT;
            }
        }
        if(ret == ERR_SUCCESS) {
            Iterator next = pos;
            next++;
            if(next != set.end())
            {
                if(overlap(pos->opcode, next->opcode)) {
                    ret = ERR_CONFLICT;
                }
            }
        }
    } else {
        ret = ERR_CONFLICT;
    }

    return ret;
}

SizeType InstructionSet::count() const {
    return set.size();
}