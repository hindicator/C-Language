#include "input.h"
#include "operands.h"

/**
 * This function will add a new memory word with the value of num
 */
void addMemword(mem_wt **head, int num)
{
    mem_wt *current = NULL;
    mem_wt *new_node = (mem_wt *)malloc(sizeof(mem_wt));
    new_node->value = num;
    new_node->ARE1 = IsBitSet(num, 0);
    new_node->ARE2 = IsBitSet(num, 1);
    new_node->op_dest1 = IsBitSet(num, 2);
    new_node->op_dest2 = IsBitSet(num, 3);
    new_node->op_source1 = IsBitSet(num, 4);
    new_node->op_source2 = IsBitSet(num, 5);
    new_node->opcode1 = IsBitSet(num, 6);
    new_node->opcode2 = IsBitSet(num, 7);
    new_node->opcode3 = IsBitSet(num, 8);
    new_node->opcode4 = IsBitSet(num, 9);
    new_node->next = NULL;
    if (*head != NULL)
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        new_node->address = (current->address) + 1;
        current->next = new_node;
    }
    else
    {
        new_node->address = 100;
        *head = new_node;
    }
}

/**
 * This function will generate a memory word value
 * based on opcode, op_source, op_dest and ARE.
 */
int getMemWord(int opcode, int op_source, int op_dest, int ARE)
{
    int result = 0;

    result |= (ARE & 1) << 0;
    result |= ((ARE >> 1) & 1) << 1;
    result |= ((op_dest)&1) << 2;
    result |= ((op_dest >> 1) & 1) << 3;
    result |= ((op_source)&1) << 4;
    result |= ((op_source >> 1) & 1) << 5;
    result |= ((opcode)&1) << 6;
    result |= ((opcode >> 1) & 1) << 7;
    result |= ((opcode >> 2) & 1) << 8;
    result |= ((opcode >> 3) & 1) << 9;

    return result;
}

/**
 * This function will handle a command type sentences
 */
int handleCommand(char *line, int isLabel, symbol_t **label_list, mem_wt **cmd_list, entry_t **entry_list, extern_t **extern_list)
{
    int cmd_type = 0;
    int result1 = -1;
    int result2 = -1;
    char *op_index1, *op_index2;

    cmd_type = get_command_type(line, isLabel);
    op_index1 = getOperand1_Label(line, isLabel);
    op_index2 = getOperand2_Label(line, isLabel);
    /* 2 Operands commands */
    if ((cmd_type >= 0 && cmd_type <= 3) || cmd_type == 6)
    {

        result1 = getOperand_Type(op_index1, *label_list);
        result2 = getOperand_Type(op_index2, *label_list);
        addMemword(cmd_list, getMemWord(cmd_type, result1, result2, 0));
    }
    /* 1 operand commands */
    else if (cmd_type == 4 || cmd_type == 5 || (cmd_type >= 7 && cmd_type <= 13))
    {
        result2 = getOperand_Type(op_index2, *label_list);
        addMemword(cmd_list, getMemWord(cmd_type, 0, result2, 0));
    }
    else
    {
        /* Commands with no operands */
        addMemword(cmd_list, cmd_type << 6);
    }
    /* Handle additional words of operand1 */
    /*=====================================*/
    if (result1 == 0)
    {
        addMemword(cmd_list, getOperand_num(op_index1) << 2);
    }
    else if (result1 == 1)
    {
        /* For some label address in second process */
        addMemword(cmd_list, 0);
    }
    else if (result1 == 2)
    {
        /* For some label address in second process */
        addMemword(cmd_list, 0);
        addMemword(cmd_list, (getStruct_address(op_index1) << 2));
    }
    /* Handle registers as operands */
    if ((result1 == 3) && (result2 == 3))
    {
        addMemword(cmd_list, (getRegister_num(op_index1) << 6) + (getRegister_num(op_index2) << 2));
    }
    else if (result1 == 3)
    {
        addMemword(cmd_list, (getRegister_num(op_index1) << 6));
    }
    else if (result2 == 3)
    {
        addMemword(cmd_list, (getRegister_num(op_index2) << 2));
    }
    /* Handle additional words of operand2 */
    /*=====================================*/
    if (result2 == 0)
    {
        addMemword(cmd_list, (getOperand_num(op_index2) << 2));
    }
    else if (result2 == 1)
    {
        /* For some label address in second process */
        addMemword(cmd_list, 0);
    }
    else if (result2 == 2)
    {
        /* For some label address in second process */
        addMemword(cmd_list, 0);
        addMemword(cmd_list, (getStruct_address(op_index2) << 2));
    }
    if (op_index1)
    {
        free(op_index1);
    }
    if (op_index2)
    {
        free(op_index2);
    }
    return 1;
}

int getCommands_Len(mem_wt *head)
{
    mem_wt *current = head;
    int total = 0;
    if (current)
    {
        while (current)
        {
            total++;
            current = current->next;
        }
    }
    return total;
}

void freeCommand_List(mem_wt **head)
{
    mem_wt *current = *head;
    mem_wt *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            if (prev)
            {
                free(prev);
            }
        }
        if (current)
        {
            free(current);
        }
    }
}